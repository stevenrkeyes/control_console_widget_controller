#ifndef RED_JOYSTICK_H
#define RED_JOYSTICK_H

#include "ConsoleWidget.h"
#include "GlobalState.h"

class RedJoystick : public ConsoleWidget {
  GlobalState& state;
public:
  RedJoystick(GlobalState& state);
  void setup() override;
  void CheckDataSendHID() override;
  void UpdateAnimationFrame() override;

private:
  int previousAngle = -1;
};

#endif
