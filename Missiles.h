#ifndef MISSILES_H
#define MISSILES_H

#include "ConsoleWidget.h"
#include "pins.h"
#include "GlobalState.h"

constexpr int MISSILES_COUNT = 3;

class Missiles : public ConsoleWidget {
  GlobalState& state;
public:
  Missiles(GlobalState& state);
  void setup() override;
  void CheckDataSendHID() override;
  void UpdateAnimationFrame() override;

private:
    int _missilePins[MISSILES_COUNT] = { 
        MISSILE_SWITCH_A_PIN,
        MISSILE_SWITCH_B_PIN,
        MISSILE_SWITCH_C_PIN,
    };

    int _missileValues[MISSILES_COUNT] = {0, 0, 0};
};

#endif
