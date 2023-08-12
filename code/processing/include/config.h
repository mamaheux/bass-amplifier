#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>
#include <Wire.h>

//#define TEST

// Effects
constexpr float SAMPLING_FREQUENCY = 48000;
constexpr uint32_t BLOCK_SIZE = 32;
constexpr uint32_t MAX_DELAY = 96256;
constexpr float CLIPPING_VALUE = 0.99;

// IO
#define DEBUG_SERIAL Serial
constexpr uint32_t DEBUG_SERIAL_BAUD_RATE = 9600;

#define CONTROLLER_SERIAL Serial4
constexpr uint32_t CONTROLLER_SERIAL_BAUD_RATE = 38400;

#define CS4270_I2C Wire

constexpr uint8_t CS4270_AD0_PIN = 2;
constexpr uint8_t CS4270_AD1_PIN = 3;
constexpr uint8_t CS4270_AD2_PIN = 4;
constexpr uint8_t CS4270_RESET_PIN = 5;

constexpr uint8_t CS4270_SDIN_PIN = 7;
constexpr uint8_t CS4270_SDOUT_PIN = 8;
constexpr uint8_t CS4270_LRCLK_PIN = 20;
constexpr uint8_t CS4270_SCLK_PIN = 21;
constexpr uint8_t CS4270_MCLK_PIN = 23;


#endif
