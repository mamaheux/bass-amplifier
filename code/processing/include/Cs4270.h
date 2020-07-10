#ifndef CS4270_H
#define CS4270_H

#include "config.h"
#include "Cs4270Buffer.h"

#include <stdint.h>

class Cs4270
{
    static constexpr uint8_t CS4270_ADDRESS = 0b1001100;

    static constexpr uint32_t I2S_TCSR_FRIE = 0x00000100;
    static constexpr uint32_t I2S_RCSR_FRIE = 0x00000100;

    Cs4270Buffer<BLOCK_SIZE> m_leftInputBuffer;
    Cs4270Buffer<BLOCK_SIZE> m_rightInputBuffer;
    Cs4270Buffer<BLOCK_SIZE> m_leftOutputBuffer;
    Cs4270Buffer<BLOCK_SIZE> m_rightOutputBuffer;

public:
    Cs4270();
    void begin();

    bool read(float* leftBlock, float* rightBlock);
    bool write(float* leftBlock, float* rightBlock);

private:
    void setupCs4270();
    void setupCs4270Pins();
    void setupCs4270Parameters();

    void setupI2s();

    void setupI2sClocks();
    void setupPLL4(int& n1, int& n2);

    void setupI2sTx();
    void setupI2sRx();
    void setupInterrupt();
    void enableI2s();

    float int32ToFloat(int32_t v);
    int32_t floatToInt32(float v);
};

#endif
