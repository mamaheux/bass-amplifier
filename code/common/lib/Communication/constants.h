#ifndef COMMUNICATION_CONSTANTS_H
#define COMMUNICATION_CONSTANTS_H

#include <stdint.h>

constexpr uint8_t DSP_PREAMBLE = 170;

constexpr uint8_t CONTOUR_CODE = 0;
constexpr uint8_t PRESENCE_CODE = 1;
constexpr uint8_t EQ_CODE = 2;
constexpr uint8_t COMPRESSOR_CODE = 3;
constexpr uint8_t OCTAVER_CODE = 4;
constexpr uint8_t DELAY_CODE = 5;
constexpr uint8_t REVERB_CODE = 6;
constexpr uint8_t OVERDRIVE_CODE = 7;
constexpr uint8_t MUTE_CODE = 8;

constexpr uint8_t EFFECT_CODE_COUNT = 9;

#endif
