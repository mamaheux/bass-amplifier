#ifndef CONTROL_ADC_H
#define CONTROL_ADC_H

#include "config.h"

class ControlAdc
{
    SPISettings m_externalAdcSettings;

public:
    ControlAdc();
    void begin();

    uint16_t read(AdcChannel channel);

private:
    uint16_t readInternalAdc(uint8_t channel);
    uint16_t readExternalAdc(uint8_t channel);
};

#endif
