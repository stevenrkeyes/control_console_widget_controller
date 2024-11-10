#include <Arduino.h>
#include <FastLED.h>
#include "LEDGrid.h"
#include "pins.h"


LEDGrid::LEDGrid() {}

void LEDGrid::setup() {
  FastLED.addLeds<LED_GRID_CHIPSET, LED_GRID_PIN, LED_GRID_COLOR_ORDER>(leds, LED_GRID_NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(LED_GRID_BRIGHTNESS);
}

void LEDGrid::CheckDataSendHID() {
}

void LEDGrid::UpdateAnimationFrame() {
  uint8_t hue = (millis() / RAINBOW_CYCLE_SPEED) % 255;

  // Fill the LEDs with a rainbow starting at the calculated hue
  fill_rainbow(leds, LED_GRID_NUM_LEDS, hue, 7);

  FastLED.show();
}
