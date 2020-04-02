#include "FanController.h"

#include <math.h>

FanController::FanController(ControlAdc adc) : m_adc(adc)
{
}

void FanController::begin()
{
    pinMode(FAN_PIN, OUTPUT);
    digitalWrite(FAN_PIN, LOW);
}

void FanController::update()
{
    digitalWrite(FAN_PIN, readTemperature() > FAN_THRESHOLD_T_KELVIN);
}

float FanController::readTemperature()
{
    float v = m_adc.read(THERMISTOR);
    float rth2 = FAN_THERMISTOR_RB * (ADC_MAX_VALUE / v - 1);

    return 1 / (1 / FAN_THERMISTOR_T_KELVIN + log(rth2 / FAN_THERMISTOR_RTH1) / FAN_THERMISTOR_BETA);
}