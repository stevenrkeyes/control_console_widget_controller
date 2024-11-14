#ifndef TOGGLE_SWITCHES_H
#define TOGGLE_SWITCHES_H

#include "ConsoleWidget.h"
#include "pins.h"

constexpr int TOGGLE_SWITCHES_COUNT = 4;

class ToggleSwitches : public ConsoleWidget {
public:
  ToggleSwitches();
  void setup() override;
  void CheckDataSendHID() override;
  void UpdateAnimationFrame() override;

private:
    int _toggleSwitchPins[TOGGLE_SWITCHES_COUNT] = { 
        TOGGLE_SWITCH1_PIN,
        TOGGLE_SWITCH2_PIN,
        TOGGLE_SWITCH3_PIN,
        TOGGLE_SWITCH4_PIN,
    };

    int _toggleSwitchValues[TOGGLE_SWITCHES_COUNT] = {0, 0, 0, 0};
};

#endif
