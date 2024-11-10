#ifndef LEDGRID_H
#define LEDGRID_H

#include <FastLED.h>
#include "ConsoleWidget.h"

#define LED_GRID_COLOR_ORDER GRB
#define LED_GRID_CHIPSET WS2811
#define LED_GRID_NUM_LEDS 50
#define LED_GRID_BRIGHTNESS 20
#define RAINBOW_CYCLE_SPEED 20


class LEDGrid : public ConsoleWidget {
public:
  LEDGrid();
  void setup() override;
  void CheckDataSendMIDI() override;
  void UpdateAnimationFrame() override;

private:
  CRGB leds[LED_GRID_NUM_LEDS];
};

#endif