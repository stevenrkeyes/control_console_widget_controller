#include <Arduino.h>
#include <Bounce2.h>
#include "JogWheel.h"

JogWheel* JogWheel::leftInstance = nullptr;
JogWheel* JogWheel::rightInstance = nullptr;

JogWheel::JogWheel(const char position) {
    if (position == 'L') {
        JogWheel::leftInstance = this;
        _opto1Pin = JOGWHEEL_LEFT_OPTO1_PIN;
        _opto2Pin = JOGWHEEL_LEFT_OPTO2_PIN;
    } else if (position == 'R') {
        JogWheel::rightInstance = this;
        _opto1Pin = JOGWHEEL_RIGHT_OPTO1_PIN;
        _opto2Pin = JOGWHEEL_RIGHT_OPTO2_PIN;
    }

<<<<<<< HEAD
    // Initialize instance-level variables.
=======
    // Initialize member variables.
>>>>>>> ee8ceb4 (static stuff)
    _position1 = 0;
    _position2 = 0;
    _activePosition = &_position1;
    _inactivePosition = &_position2;
    _lastState = 0b00;
}

void JogWheel::setup() {
  pinMode(_opto1Pin, INPUT);
  pinMode(_opto2Pin, INPUT);
  _lastState = (digitalRead(_opto1Pin) << 1) | digitalRead(_opto2Pin);
  
<<<<<<< HEAD
=======
  // attachInterrupt(digitalPinToInterrupt(_opto1Pin), updatePosition, CHANGE);
  // attachInterrupt(digitalPinToInterrupt(_opto2Pin), updatePosition, CHANGE);
>>>>>>> ee8ceb4 (static stuff)
  if (this == leftInstance) {
      attachInterrupt(digitalPinToInterrupt(_opto1Pin), handleLeftInterrupt, CHANGE);
      attachInterrupt(digitalPinToInterrupt(_opto2Pin), handleLeftInterrupt, CHANGE);
  } else {
      attachInterrupt(digitalPinToInterrupt(_opto1Pin), handleRightInterrupt, CHANGE);
      attachInterrupt(digitalPinToInterrupt(_opto2Pin), handleRightInterrupt, CHANGE);
  }
}

void JogWheel::CheckDataSendHID() {
  // Check for no motion
  int32_t delta32 = readPositionDelta();

  // Clamp to the limits of a uint8_t
  int8_t delta = (int8_t)max(INT8_MIN, min(INT8_MAX, delta32));

  if (delta != 0) {
    Mouse.scroll(delta, 0);
    //Serial.println(String(delta) + " delta");
  }
}

void JogWheel::UpdateAnimationFrame() {
  // No LED animation needed for jogwheel
}

void JogWheel::updatePosition() {
  int8_t newState = (digitalRead(_opto1Pin) << 1) | digitalRead(_opto2Pin);

  // Determine direction based on the state transition
  if ((_lastState == 0b11 && newState == 0b10) ||
  (_lastState == 0b01 && newState == 0b11) ||
  (_lastState == 0b11 && newState == 0b10) ||
  (_lastState == 0b10 && newState == 0b00)) {
    (*_activePosition)++;
    Serial.println("+");
  } else if ((_lastState == 0b00 && newState == 0b10) ||
  (_lastState == 0b10 && newState == 0b11) ||
  (_lastState == 0b11 && newState == 0b01) ||
  (_lastState == 0b01 && newState == 0b00)) {
    (*_activePosition)--;
    Serial.println("-");
  }

  _lastState = newState;
}

int32_t JogWheel::readPositionDelta() {
  // Swap the active and inactive position buffers so that an interrupt doesn't change the value after it's read but before we've cleared it
  volatile int32_t* temp = _activePosition;
  _activePosition = _inactivePosition;
  _inactivePosition = temp;

  // Read the previously active position and reset it
  int32_t delta = *_inactivePosition;
  *_inactivePosition = 0;  // Reset the previously active buffer
  return delta;
}