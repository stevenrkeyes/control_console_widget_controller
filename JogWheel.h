#ifndef JOGWHEEL_H
#define JOGWHEEL_H

#include <Bounce2.h>
#include "ConsoleWidget.h"
#include "pins.h"

constexpr unsigned long DIRECTION_TIMEOUT = 50;  // milliseconds
constexpr unsigned long MOTION_TIMEOUT = 100;    // milliseconds to wait before declaring no motion


class JogWheel : public ConsoleWidget {
public:
  JogWheel(const char position);
  void setup() override;
  void CheckDataSendHID() override;
  void UpdateAnimationFrame() override;

private:
  int32_t readPositionDelta();

  // Static instances of the jogwheel for each direction.
  // Used in the static interrupt handlers.
  static JogWheel *leftInstance, *rightInstance;

  // attachInterrupt demands static functions, but we want separate instances for each direction.
  // Therefore, declare the interrupt handlers as static functions.
  static void handleLeftInterrupt() {
      if (leftInstance) leftInstance->updatePosition();
  }

  static void handleRightInterrupt() {
      if (rightInstance) rightInstance->updatePosition();
  }

  // Initialized differently for left and right jogwheels.
  int _opto1Pin;
  int _opto2Pin;

  volatile int32_t _position1;      // First position buffer
  volatile int32_t _position2;      // Second position buffer
  volatile int32_t* _activePosition;    // Pointer to the currently active position buffer
  volatile int32_t* _inactivePosition;  // Pointer to the inactive position buffer

  volatile int8_t _lastState;  // Last state of the encoder

  // Update the position based on encoder state
  void updatePosition();
};

#endif
