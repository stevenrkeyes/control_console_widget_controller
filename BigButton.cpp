#include <Arduino.h>
#include "BigButton.h"
#include "pins.h"

BigButton::BigButton() {
    _lastState = false;
}

void BigButton::setup() {
    Serial.printf("BigButton setup\n");
    pinMode(BIG_BUTTON_PIN, INPUT);
}

void BigButton::CheckDataSendHID() {
  int currentState = digitalRead(BIG_BUTTON_PIN);
  if (currentState != _lastState) {
    _lastState = currentState;
    Serial.printf("Big button state changed: %d\n", currentState);
    Joystick.button(1, currentState);
  }
}

void BigButton::UpdateAnimationFrame() {
}
