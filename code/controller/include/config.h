#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>
#include <SPI.h>

constexpr uint32_t STARTUP_DELAY_MS = 500;

// Update interval
constexpr uint32_t EFFECT_DESIGNER_UPDATE_INTERVAL_US = 2500;
constexpr uint32_t STATUS_LED_UPDATE_INTERVAL_US = 20000;
constexpr uint32_t FAN_UPDATE_INTERVAL_US = 1000000;
constexpr uint32_t FOOTSWITCH_COMMUNICATION_FAST_UPDATE_INTERVAL_US = 2500;
constexpr uint32_t FOOTSWITCH_COMMUNICATION_SLOW_UPDATE_INTERVAL_US = 50000;

// Effects
constexpr float SAMPLING_FREQUENCY = 48000;
constexpr uint32_t MAX_DELAY = 96000;

// IO
#define DEBUG_SERIAL Serial
constexpr uint32_t DEBUG_SERIAL_BAUD_RATE = 9600;

#define FOOTSWITCH_SERIAL Serial2
constexpr uint32_t FOOTSWITCH_SERIAL_BAUD_RATE = 115200;

#define DSP_SERIAL Serial1
constexpr uint32_t DSP_SERIAL_BAUD_RATE = 38400;

constexpr uint8_t ADC_RESOLUTION = 12;
constexpr uint16_t ADC_MAX_VALUE = 4095;

#define EXTERNAL_ADC_SPI SPI
constexpr uint32_t EXTERNAL_ADC_SPI_CLK = 1600000;
constexpr uint8_t EXTERNAL_ADC_CS_PIN = 14;

enum class AdcSource
{
    INTERNAL_ADC,
    EXTERNAL_ADC
};

struct AdcChannel
{
    AdcSource source;
    uint8_t channel;
};

constexpr uint16_t POT_DEAD_ZONE = 64;

constexpr AdcChannel CONTOUR_GAIN_POT = {AdcSource::INTERNAL_ADC, 20};
constexpr AdcChannel PRESENCE_GAIN_POT = {AdcSource::INTERNAL_ADC, 21};
constexpr AdcChannel EQ_LOW_GAIN_POT = {AdcSource::INTERNAL_ADC, 18};
constexpr AdcChannel EQ_LOW_MID_GAIN_POT = {AdcSource::INTERNAL_ADC, 19};
constexpr AdcChannel EQ_HIGH_MID_GAIN_POT = {AdcSource::INTERNAL_ADC, 16};
constexpr AdcChannel EQ_HIGH_GAIN_POT = {AdcSource::INTERNAL_ADC, 17};
constexpr AdcChannel COMPRESSOR_THRESHOLD_POT = {AdcSource::INTERNAL_ADC, 15};
constexpr AdcChannel COMPRESSOR_RATIO_POT = {AdcSource::EXTERNAL_ADC, 7};
constexpr AdcChannel OCTAVER_DOWM_VOLUME_POT = {AdcSource::EXTERNAL_ADC, 2};
constexpr AdcChannel OCTAVER_UP_VOLUME_POT = {AdcSource::EXTERNAL_ADC, 3};
constexpr AdcChannel DELAY_VOLUME_POT = {AdcSource::EXTERNAL_ADC, 0};
constexpr AdcChannel REVERB_VOLUME_POT = {AdcSource::EXTERNAL_ADC, 1};
constexpr AdcChannel OVERDRIVE_GAIN_POT = {AdcSource::EXTERNAL_ADC, 4};
constexpr AdcChannel OVERDRIVE_TONE_POT = {AdcSource::EXTERNAL_ADC, 5};

constexpr uint8_t DELAY_TAP_PIN = 23;
constexpr uint8_t MUTE_PIN = 22;


constexpr uint8_t COMPRESSOR_LED_PIN = 24;
constexpr uint8_t OCTAVER_LED_PIN = 4;
constexpr uint8_t DELAY_LED_PIN = 5;
constexpr uint8_t REVERB_LED_PIN = 7;
constexpr uint8_t OVERDRIVE_LED_PIN = 6;
constexpr uint8_t MUTE_LED_PIN = 25;
constexpr uint8_t CLIPPING_LED_PIN = 8;


constexpr AdcChannel THERMISTOR = {AdcSource::EXTERNAL_ADC, 6};
constexpr uint8_t FAN_PIN = 3;

// Other
constexpr uint32_t CLIPPING_LED_ON_DURATION_MS = 500;

constexpr float FAN_THERMISTOR_BETA = 3900;
constexpr float FAN_THERMISTOR_RTH1 = 10000;
constexpr float FAN_THERMISTOR_RB = 10000;
constexpr float FAN_THERMISTOR_T_KELVIN = 298.15; //25 °C
constexpr float FAN_THRESHOLD_T_KELVIN = 323.15; // 50 °C

#endif
