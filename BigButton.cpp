#include <Arduino.h>
#include "BigButton.h"
#include "pins.h"
#include "GlobalState.h"

BigButton::BigButton(GlobalState& state) : state(state) {
    _lastState = false;
}

void BigButton::setup() {
    Serial.printf("BigButton setup\n");
    pinMode(BIG_BUTTON_PIN, INPUT);
}

void BigButton::CheckDataSendHID() {
  int currentState = digitalRead(BIG_BUTTON_PIN);
  if (currentState != _lastState) {
    // If we went from 0 to 1, set global state to 1
    if (currentState == 1) {
      state.setBigButtonState(1);
    }

    _lastState = currentState;
    Serial.printf("Big button state changed: %d\n", currentState);
    Joystick.button(5, currentState);
  }
}

void BigButton::UpdateAnimationFrame() {
}
