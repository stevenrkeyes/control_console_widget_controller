#include <Arduino.h>
#include <FastLED.h>
#include "LEDGrid.h"
#include "pins.h"
#include "GlobalState.h"
#include "LEDGridPatterns.h"

LEDGrid::LEDGrid(GlobalState& state) : state(state) {}

void LEDGrid::setup() {
  FastLED.addLeds<LED_GRID_CHIPSET, LED_GRID_PIN, LED_GRID_COLOR_ORDER>(leds, LED_GRID_NUM_LEDS).setCorrection(TypicalLEDStrip);
  // Caution: too bright appears to brown out the teensy, so test carefully or change the power source if the brightness is increased
  FastLED.setBrightness(LED_GRID_BRIGHTNESS);
}

void LEDGrid::CheckDataSendHID() {
}

uint8_t remap(uint8_t value, uint8_t min, uint8_t max) {
    return min + (uint8_t) (value * (max - min) / 255.0f);
}

void LEDGrid::UpdateAnimationFrame() {
  uint8_t hue = state.getLEDGridHue();
  uint8_t saturation = state.getLEDGridSaturation();
  uint8_t missile_switch_state = state.getMissileSwitchState();

  // TODO make this switch case.
  if (missile_switch_state == 7) {
    showPulsatingBars(hue, leds);
  } else if (missile_switch_state == 6) {
    // uint8_t wavelength = 5;
    // uint8_t amplitude = 3;

    uint8_t wavelength = remap(saturation, 3, 10);
    uint8_t amplitude = remap(hue, 1, 5);

    animateWave(amplitude, wavelength, leds);
  } else {
    // Fill the LEDs with a solid color based on state values set by last 2 faders.
    fill_solid(leds, LED_GRID_NUM_LEDS, CHSV(hue, saturation, 255));
  }

  FastLED.show();
}
