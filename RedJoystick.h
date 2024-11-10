#ifndef RED_JOYSTICK_H
#define RED_JOYSTICK_H

#include "ConsoleWidget.h"

class RedJoystick : public ConsoleWidget {
public:
  RedJoystick();
  void setup() override;
  void CheckDataSendHID() override;
  void UpdateAnimationFrame() override;

private:
  int previousAngle = -1;
};

#endif
