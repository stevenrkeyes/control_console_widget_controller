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

void LEDGrid::UpdateAnimationFrame() {
  uint8_t hue = state.getLEDGridHue();
  uint8_t saturation = state.getLEDGridSaturation();
  uint8_t missile_switch_state = state.getMissileSwitchState();

  // TODO make this switch case.
  if (missile_switch_state == 7) {
    showPulsatingBars(hue, leds);
  } else {
    // Fill the LEDs with a solid color based on state values set by last 2 faders.
    fill_solid(leds, LED_GRID_NUM_LEDS, CHSV(hue, saturation, 255));
  }

  FastLED.show();
}
