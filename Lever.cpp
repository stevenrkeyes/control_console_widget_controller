#include <Arduino.h>
#include "Lever.h"
#include "pins.h"

Lever::Lever() {
    _lastState = false;
}

void Lever::setup() {
    Serial.printf("Lever setup\n");
    pinMode(LEVER_PIN, INPUT);
}

void Lever::CheckDataSendHID() {
  int currentState = digitalRead(LEVER_PIN);
  if (currentState != _lastState) {
    _lastState = currentState;
    Serial.printf("Leverstate changed: %d\n", currentState);
    Joystick.button(LEVER_BUTTON, currentState);
  }
}

void Lever::UpdateAnimationFrame() {
}
