#include "ControlAdc.h"

ControlAdc::ControlAdc() : m_externalAdcSettings(EXTERNAL_ADC_SPI_CLK, MSBFIRST, SPI_MODE0)
{    
}

void ControlAdc::begin()
{
    pinMode(EXTERNAL_ADC_CS_PIN, OUTPUT);
    digitalWrite(EXTERNAL_ADC_CS_PIN, HIGH);
    EXTERNAL_ADC_SPI.begin();

    analogReadResolution(ADC_RESOLUTION);
}

uint16_t ControlAdc::read(AdcChannel channel)
{
    if (channel.source == AdcSource::INTERNAL_ADC)
    {
        return readInternalAdc(channel.channel);
    }
    else if (channel.source == AdcSource::EXTERNAL_ADC)
    {
        return readExternalAdc(channel.channel);
    }
    return 0; 
}

uint16_t ControlAdc::readInternalAdc(uint8_t channel)
{
    return analogRead(channel);
}

uint16_t ControlAdc::readExternalAdc(uint8_t channel)
{
    EXTERNAL_ADC_SPI.beginTransaction(m_externalAdcSettings);
    digitalWrite(EXTERNAL_ADC_CS_PIN, LOW);
    delayMicroseconds(1);

    uint8_t commandMsb = 0b110 | ((channel & 0b0100) >> 2);
    uint8_t commandLsb = (channel & 0b0011) << 6;

    EXTERNAL_ADC_SPI.transfer(commandMsb);
    uint16_t dataMsb = EXTERNAL_ADC_SPI.transfer(commandLsb) & 0b1111;
    uint16_t dataLsb = EXTERNAL_ADC_SPI.transfer(0);

    digitalWrite(EXTERNAL_ADC_CS_PIN, HIGH);
    EXTERNAL_ADC_SPI.endTransaction();

    return (dataMsb << 8) | dataLsb;
}
