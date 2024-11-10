#ifndef JOGWHEEL_H
#define JOGWHEEL_H

#include <Bounce2.h>
#include "ConsoleWidget.h"
#include "pins.h"

constexpr unsigned long DIRECTION_TIMEOUT = 50;  // milliseconds
constexpr unsigned long MOTION_TIMEOUT = 100;    // milliseconds to wait before declaring no motion


class JogWheel : public ConsoleWidget {
public:
  JogWheel();
  void setup() override;
  void CheckDataSendHID() override;
  void UpdateAnimationFrame() override;

private:
  int32_t readPositionDelta();

  static volatile int32_t _position1;      // First position buffer
  static volatile int32_t _position2;      // Second position buffer
  static volatile int32_t* _activePosition;    // Pointer to the currently active position buffer
  static volatile int32_t* _inactivePosition;  // Pointer to the inactive position buffer

  static volatile int8_t _lastState;  // Last state of the encoder

  // Update the position based on encoder state
  static void updatePosition();
};

#endif
