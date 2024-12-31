#ifndef LEDGRID_H
#define LEDGRID_H

// "FASTLED_INTERNAL" disables printing the version string of FastLED
#define FASTLED_INTERNAL
#include <FastLED.h>
#include "ConsoleWidget.h"
#include "GlobalState.h"

#define LED_GRID_COLOR_ORDER GRB
#define LED_GRID_CHIPSET WS2811
#define LED_GRID_NUM_LEDS 50
#define LED_GRID_BRIGHTNESS 20
#define RAINBOW_CYCLE_SPEED 20


class LEDGrid : public ConsoleWidget {
  GlobalState& state;
public:
  LEDGrid(GlobalState& state);
  void setup() override;
  void CheckDataSendHID() override;
  void UpdateAnimationFrame() override;

private:
  CRGB leds[LED_GRID_NUM_LEDS];
  // void showPulsatingBars(uint8_t hue);
};

#endif
