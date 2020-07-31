#include "Cs4270.h"

#include "InterruptLock.h"

static constexpr uint32_t I2S_TCSR_FRF = 0x00010000;
static constexpr uint32_t I2S_RCSR_FRF = 0x00010000;


static Cs4270Buffer<BLOCK_SIZE>* leftInputBuffer;
static Cs4270Buffer<BLOCK_SIZE>* rightInputBuffer;
static Cs4270Buffer<BLOCK_SIZE>* leftOutputBuffer;
static Cs4270Buffer<BLOCK_SIZE>* rightOutputBuffer;

static void cs4270Interrupt()
{
    constexpr int32_t SAMPLE_MASK = 0xFFFFFF00;

    if (I2S1_TCSR & I2S_TCSR_FRF)
    {
        // Write samples
        int32_t leftSample = 0;
        int32_t rightSample = 0;

        leftOutputBuffer->read(leftSample);
        rightOutputBuffer->read(rightSample);

        I2S1_TDR0 = leftSample & SAMPLE_MASK;
        I2S1_TDR0 = rightSample & SAMPLE_MASK;
    }
    
    if (I2S1_RCSR & I2S_RCSR_FRF)
    {
        // Read samples
        int32_t leftSample = I2S1_RDR0;
        int32_t rightSample = I2S1_RDR0;

        leftInputBuffer->write(leftSample & SAMPLE_MASK);
        rightInputBuffer->write(rightSample & SAMPLE_MASK);
    }
}


Cs4270::Cs4270()
{
    static_assert(CS4270_SDIN_PIN == 7, "Invalid SDIN pin");
    static_assert(CS4270_SDOUT_PIN == 8, "Invalid SDOUT pin");
    static_assert(CS4270_LRCLK_PIN == 20, "Invalid LRCLK pin");
    static_assert(CS4270_SCLK_PIN == 21, "Invalid SCLK pin");
    static_assert(CS4270_MCLK_PIN == 23, "Invalid MCLK pin");
}

void Cs4270::begin()
{
    CCM_CCGR5 |= CCM_CCGR5_SAI1(CCM_CCGR_ON);

    setupCs4270();
    setupI2s();
}

bool Cs4270::read(float* leftBlock, float* rightBlock)
{
    InterruptLock lock(IRQ_SAI1);
    if (m_leftInputBuffer.readAvailable() < BLOCK_SIZE || m_rightInputBuffer.readAvailable() < BLOCK_SIZE)
    {
        return false;
    }

    for (uint32_t i = 0; i < BLOCK_SIZE; i++)
    {
        int32_t leftSample;
        int32_t rightSample;

        m_leftInputBuffer.read(leftSample);
        m_rightInputBuffer.read(rightSample);

        leftBlock[i] = int32ToFloat(leftSample);
        rightBlock[i] = int32ToFloat(rightSample);
    }

    return true;
}

bool Cs4270::write(float* leftBlock, float* rightBlock)
{
    InterruptLock lock(IRQ_SAI1);
    if (m_leftOutputBuffer.writeAvailable() < BLOCK_SIZE || m_rightOutputBuffer.writeAvailable() < BLOCK_SIZE)
    {
        return false;
    }

    for (uint32_t i = 0; i < BLOCK_SIZE; i++)
    {
        m_leftOutputBuffer.write(floatToInt32(leftBlock[i]));
        m_rightOutputBuffer.write(floatToInt32(rightBlock[i]));
    }

    return true;
}

void Cs4270::setupCs4270()
{
    setupCs4270Pins();

    CS4270_I2C.begin();
    setupCs4270Parameters();
}

void Cs4270::setupCs4270Pins()
{
    pinMode(CS4270_AD0_PIN, OUTPUT);
    digitalWrite(CS4270_AD0_PIN, LOW);

    pinMode(CS4270_AD1_PIN, OUTPUT);
    digitalWrite(CS4270_AD1_PIN, LOW);

    pinMode(CS4270_AD2_PIN, OUTPUT);
    digitalWrite(CS4270_AD2_PIN, HIGH);

    pinMode(CS4270_RESET_PIN, OUTPUT);
    digitalWrite(CS4270_RESET_PIN, HIGH);
}

void Cs4270::setupCs4270Parameters()
{
    // Default values are good.
}

void Cs4270::setupI2s()
{
    // if TX or RX are enabled
    if ((I2S1_TCSR & I2S_TCSR_TE) || (I2S1_RCSR & I2S_RCSR_RE)) return;

    setupI2sClocks();

    //Setup I2S (TX is sync and RX is async because TX and RX must use RX_BCLK and RX_SYNC)
    setupI2sTx();
    setupI2sRx();

    setupInterrupt();

    enableI2s(); 
}

void Cs4270::setupI2sClocks()
{
    int n1;
    int n2;
    setupPLL4(n1, n2);
    // Setup SAI1_CLK 
    CCM_CSCMR1 = (CCM_CSCMR1 & ~(CCM_CSCMR1_SAI1_CLK_SEL_MASK)) | CCM_CSCMR1_SAI1_CLK_SEL(2); // Set PLL4 clock source
    CCM_CS1CDR = (CCM_CS1CDR & ~(CCM_CS1CDR_SAI1_CLK_PRED_MASK | CCM_CS1CDR_SAI1_CLK_PODF_MASK))
           | CCM_CS1CDR_SAI1_CLK_PRED(n1 - 1) // Set clock pred to n1 (1 <= n1 <= 8)
           | CCM_CS1CDR_SAI1_CLK_PODF(n2 - 1); // Set clock prodf to n1 (1 <= n1 <= 2^6)
           
    // Setup MCLK1
    IOMUXC_GPR_GPR1 = (IOMUXC_GPR_GPR1 & ~(IOMUXC_GPR_GPR1_SAI1_MCLK1_SEL_MASK))
        | IOMUXC_GPR_GPR1_SAI1_MCLK_DIR // Set MCLK as an output
        | IOMUXC_GPR_GPR1_SAI1_MCLK1_SEL(0); // Set MCLK source to ccm.ssi1_clk_root
        
    // Setup clock pins
    CORE_PIN23_CONFIG = 3;  // Set pin23 as MCLK
    CORE_PIN21_CONFIG = 3;  // Set pin21 as RX_BCLK
    CORE_PIN20_CONFIG = 3;  // Set pin20 as RX_SYNC
}
    
void Cs4270::setupPLL4(int& n1, int& n2)
{
    int fs = SAMPLING_FREQUENCY;
    n1 = 4; 
	n2 = 1 + (24000000 * 27) / (fs * 256 * n1);

	double C = ((double)fs * 256 * n1 * n2) / 24000000;
	int c0 = C;
	uint32_t c2 = 10000;
	int32_t c1 = C * c2 - (c0 * c2);

    // From :https://github.com/PaulStoffregen/Audio/blob/master/utility/imxrt_hw.cpp
    if (CCM_ANALOG_PLL_AUDIO & CCM_ANALOG_PLL_AUDIO_ENABLE) return;

	CCM_ANALOG_PLL_AUDIO = CCM_ANALOG_PLL_AUDIO_BYPASS | CCM_ANALOG_PLL_AUDIO_ENABLE
			     | CCM_ANALOG_PLL_AUDIO_POST_DIV_SELECT(2) // 2: 1/4; 1: 1/2; 0: 1/1
			     | CCM_ANALOG_PLL_AUDIO_DIV_SELECT(c0);

	CCM_ANALOG_PLL_AUDIO_NUM   = c1 & CCM_ANALOG_PLL_AUDIO_NUM_MASK;
	CCM_ANALOG_PLL_AUDIO_DENOM = c2 & CCM_ANALOG_PLL_AUDIO_DENOM_MASK;

	CCM_ANALOG_PLL_AUDIO &= ~CCM_ANALOG_PLL_AUDIO_POWERDOWN;//Switch on PLL
	while (!(CCM_ANALOG_PLL_AUDIO & CCM_ANALOG_PLL_AUDIO_LOCK)) {}; //Wait for pll-lock

	const int div_post_pll = 1; // other values: 2,4
	CCM_ANALOG_MISC2 &= ~(CCM_ANALOG_MISC2_DIV_MSB | CCM_ANALOG_MISC2_DIV_LSB);
	if(div_post_pll>1) CCM_ANALOG_MISC2 |= CCM_ANALOG_MISC2_DIV_LSB;
	if(div_post_pll>3) CCM_ANALOG_MISC2 |= CCM_ANALOG_MISC2_DIV_MSB;

	CCM_ANALOG_PLL_AUDIO &= ~CCM_ANALOG_PLL_AUDIO_BYPASS;//Disable Bypass
}

void Cs4270::setupI2sTx()
{
    I2S1_TMR = 0; // Set the transmit mask to 0
    I2S1_TCR1 = I2S_TCR1_RFW(1); // Set the FIFO watermark to 1
    I2S1_TCR2 = I2S_TCR2_SYNC(1) // Set TX mode to sync
        | I2S_TCR2_BCP // Set BCLK active low
        | I2S_TCR2_BCD // Set BCLK as an output
        | I2S_TCR2_DIV(1) // Set bit clock divide to 4
        | I2S_TCR2_MSEL(1); // Set MCLK to MCLK1
    I2S1_TCR3 = I2S_TCR3_TCE; // Enable the first transmit data channel
    I2S1_TCR4 = I2S_TCR4_FRSZ((2 - 1)) // Set 2 words per frame
        | I2S_TCR4_SYWD((32 - 1)) // Set SYNC width to 32;
        | I2S_TCR4_MF // Set MSB first
        | I2S_TCR4_FSD // Set SYNC as an output 
        | I2S_TCR4_FSE // Set SYNC to assert one bit before the first bit of the frame
        | I2S_TCR4_FSP; // Set SYNC active low
    I2S1_TCR5 = I2S_TCR5_WNW((32 - 1)) // Set the word width to 32
        | I2S_RCR5_W0W((32 - 1)) // Set the word 0 width to 32
        | I2S_RCR5_FBT((32 - 1)); // Set the first bit shifted to 32
}

void Cs4270::setupI2sRx()
{
    I2S1_RMR = 0; // Set the receive mask to 0
    I2S1_RCR1 = I2S_RCR1_RFW(1); // Set the FIFO watermark to 1
    I2S1_RCR2 = I2S_RCR2_SYNC(0) // Set RX mode to async
        | I2S_RCR2_BCP // Set BCLK active low
        | I2S_RCR2_BCD // Set BCLK as an output
        | I2S_RCR2_DIV(1) // Set bit clock divide to 4
        | I2S_RCR2_MSEL(1); // Set MCLK to MCLK1
    I2S1_RCR3 = I2S_RCR3_RCE; // Enable the first transmit data channel
    I2S1_RCR4 = I2S_RCR4_FRSZ((2 - 1)) // Set 2 words per frame
        | I2S_RCR4_SYWD((32 - 1)) // Set SYNC width to 32;
        | I2S_RCR4_MF // Set MSB first
        | I2S_RCR4_FSD // Set SYNC as an output 
        | I2S_RCR4_FSE // Set SYNC to assert one bit before the first bit of the frame
        | I2S_RCR4_FSP; // Set SYNC active low
    I2S1_RCR5 = I2S_RCR5_WNW((32-1)) // Set the word width to 32
        | I2S_RCR5_W0W((32-1)) // Set the word 0 width to 32
        | I2S_RCR5_FBT((32-1)); // Set the first bit shifted to 32
}

void Cs4270::setupInterrupt()
{
    leftInputBuffer = &m_leftInputBuffer;
    rightInputBuffer = &m_rightInputBuffer;
    leftOutputBuffer = &m_leftOutputBuffer;
    rightOutputBuffer = &m_rightOutputBuffer;
    attachInterruptVector(IRQ_SAI1, cs4270Interrupt);
}

void Cs4270::enableI2s()
{
    // Offset the output by 1 sample to prevent transmit FIFO errors
    I2S1_TDR0 = 0;
    I2S1_TDR0 = 0;

    // Setup TX/RX pins
    CORE_PIN7_CONFIG  = 3;  // Set pin7 as TX
    CORE_PIN8_CONFIG  = 3;  // Set pin8 as RX
    IOMUXC_SAI1_RX_DATA0_SELECT_INPUT = 2;

    I2S1_TCSR = I2S_TCSR_TE // Enable the transmitter
        | I2S_TCSR_BCE // Enable BCLK
        | I2S_TCSR_FRIE; // Enable transmitter FIFO interrupt

    I2S1_RCSR = I2S_RCSR_RE // Enable the receiver
        | I2S_RCSR_BCE // Enable BCLK
        | I2S_RCSR_FRIE // Enable receiver FIFO interrupt
        | I2S_RCSR_FR; // Reset FIFO
}

float Cs4270::int32ToFloat(int32_t v)
{
    return -static_cast<float>(v) / static_cast<float>(INT32_MIN);
}

int32_t Cs4270::floatToInt32(float v)
{    
    if (v < INT32_MIN)
    {
        v = INT32_MIN;
    }
    if (v > INT32_MAX)
    {
        v = INT32_MAX;
    }

    return static_cast<int32_t>(v);
}
