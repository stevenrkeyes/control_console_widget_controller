#ifndef LEDGridPatterns_H
#define LEDGridPatterns_H
#include <cstdint>
#include <FastLED.h>

void showPulsatingBars(uint8_t hue, CRGB* leds);

void animateWave(uint8_t amplitude, uint8_t wavelength, CRGB* leds);

#endif