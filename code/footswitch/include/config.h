#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>
#include <SPI.h>

// Update interval
constexpr uint32_t CONTROLLER_COMMUNICATION_UPDATE_INTERVAL_US = 2500;
constexpr uint32_t STATUS_LED_UPDATE_INTERVAL_US = 20000;
constexpr uint32_t EFFECT_CONTROLS_UPDATE_INTERVAL_US = 2500;
constexpr uint32_t HEARTBEAT_INTERVAL_US = 100000;

// Effects
constexpr float SAMPLING_FREQUENCY = 48000;
constexpr uint32_t MAX_DELAY = 96000;

// IO
#define DEBUG_SERIAL Serial
constexpr uint32_t DEBUG_SERIAL_BAUD_RATE = 9600;

#define CONTROLLER_SERIAL Serial1
constexpr uint32_t CONTROLLER_SERIAL_BAUD_RATE = 115200;


constexpr uint8_t COMPRESSOR_PIN = 3;
constexpr uint8_t OCTAVER_PIN = 5;
constexpr uint8_t DELAY_PIN = 7;
constexpr uint8_t DELAY_TAP_PIN = 6;
constexpr uint8_t REVERB_PIN = 10;
constexpr uint8_t OVERDRIVE_PIN = 2;
constexpr uint8_t MUTE_PIN = 4;
constexpr uint8_t OPT_1_PIN = 9;
constexpr uint8_t OPT_2_PIN = 8;
constexpr uint8_t OPT_3_PIN = 13;
constexpr uint8_t OPT_4_PIN = 12;
constexpr uint8_t OPT_5_PIN = 11;


constexpr uint8_t COMPRESSOR_LED_PIN = 18;
constexpr uint8_t OCTAVER_LED_PIN = 16;
constexpr uint8_t DELAY_LED_PIN = 14;
constexpr uint8_t REVERB_LED_PIN = 15;
constexpr uint8_t OVERDRIVE_LED_PIN = 17;
constexpr uint8_t MUTE_LED_PIN = 20;
constexpr uint8_t CLIPPING_LED_PIN = 19;


// Other
constexpr uint32_t CLIPPING_LED_ON_DURATION_MS = 500;
constexpr uint32_t ACK_TIMEOUT_MS = 20;

#endif
