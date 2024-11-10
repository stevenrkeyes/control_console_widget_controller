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
  // Store pulse counts and states
  static volatile int pulseCount1;
  static volatile int pulseCount2;
  static volatile int lastPulseCount1;
  static volatile int lastPulseCount2;

  // Direction detection
  static volatile int direction;  // 1 = clockwise, -1 = counterclockwise, 0 = no motion
  static volatile unsigned long sensor1Time;
  static volatile unsigned long sensor2Time;

  // Variables for state machine
  static volatile uint8_t sensorStates;  // Stores current state of both sensors
  static volatile int8_t prevState;      // Previous combined state

  static void sensorChange1();
  static void sensorChange2();
  static void updateDirection();
};

#endif
