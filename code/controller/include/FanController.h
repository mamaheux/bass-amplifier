#ifndef FAN_CONTROLLER_H
#define FAN_CONTROLLER_H

#include "config.h"
#include "ControlAdc.h"

class FanController
{
    ControlAdc& m_adc;
    
public:
    FanController(ControlAdc& m_adc);
    void begin();

    void update();

private:
    float readTemperature();
};

#endif
