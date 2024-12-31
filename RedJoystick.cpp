#include <Arduino.h>
#include "RedJoystick.h"
#include "pins.h"

RedJoystick::RedJoystick(GlobalState& state) : state(state) {}

void RedJoystick::setup() {
  Serial.println("setting up joystick");
  pinMode(RED_JOYSTICK_TOP_LEFT_PIN, INPUT_PULLUP);
  pinMode(RED_JOYSTICK_TOP_RIGHT_PIN, INPUT_PULLUP);
  pinMode(RED_JOYSTICK_BOT_LEFT_PIN, INPUT_PULLUP);
  pinMode(RED_JOYSTICK_BOT_RIGHT_PIN, INPUT_PULLUP);
}

void RedJoystick::CheckDataSendHID() {
  // Note: the top-left switch on the joystick actually reads the left axis, etc
  bool left = digitalRead(RED_JOYSTICK_TOP_LEFT_PIN) == LOW;
  bool top = digitalRead(RED_JOYSTICK_TOP_RIGHT_PIN) == LOW;
  bool bot = digitalRead(RED_JOYSTICK_BOT_LEFT_PIN) == LOW;
  bool right = digitalRead(RED_JOYSTICK_BOT_RIGHT_PIN) == LOW;

  // Create a byte that contains the array of booleans
  int buttonStates = (left << 3) | (top << 2) | (right << 1) | bot;

  int angle = -1;

  switch (buttonStates) {
    case 0b0100: angle = 0;  state.setJoystickState('U'); break;    // up
    case 0b0110: angle = 45; break;   // up-right
    case 0b0010: angle = 90; state.setJoystickState('R'); break;   // right
    case 0b0011: angle = 135; break;  // down-right
    case 0b0001: angle = 180; state.setJoystickState('D'); break;  // down
    case 0b1001: angle = 225; break;  // down-left
    case 0b1000: angle = 270; state.setJoystickState('L'); break;  // left
    case 0b1100: angle = 315; break;  // up-left
    default: angle = -1; break;       // No button pressed or invalid combination
  }

  if (angle != previousAngle) {
    Joystick.hat(angle);
    Serial.printf("Red Joystick sending angle %d \n", angle);
    previousAngle = angle;
  }
}

void RedJoystick::UpdateAnimationFrame() {
  // this widget does not have any LEDs etc to animate
}
