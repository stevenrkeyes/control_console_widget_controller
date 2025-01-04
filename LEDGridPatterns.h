#ifndef LEDGridPatterns_H
#define LEDGridPatterns_H
#include <cstdint>
#include <FastLED.h>

void showPulsatingBars(uint8_t hue, uint8_t width_param, CRGB* leds);

void animateWave(uint8_t amplitude_unmapped, uint8_t wavelength_unmapped, CRGB* leds);

void animatePacman(uint8_t hue, uint8_t mouth_angle, CRGB* leds);

void animateTriangle(uint8_t frequency, CRGB* leds);

void animateInvader(uint8_t colorHue, uint8_t brightness, CRGB* leds);

void animateRain(uint8_t density, u_int8_t speed, CRGB* leds);
#endif