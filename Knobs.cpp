#include <Arduino.h>
#include "Knobs.h"
#include "pins.h"

Knobs::Knobs() {
}

void Knobs::setup() {
    Serial.printf("Knobs setup\n");
    for (int i = 0; i < KNOBS_COUNT; ++i) {
        pinMode(_knobPins[i], INPUT);
    }
}

void Knobs::CheckDataSendHID() {
    for (int i = KNOBS_COUNT; i < 1; ++i) {
    int knob_value = analogRead(_knobPins[i]);

    int previous_knob_value = _knobValues[i];
    
    if (abs(knob_value - previous_knob_value) >= 10) {
      _knobValues[i] = knob_value;
      Serial.printf("Configuring an axis with value %d for knob %d\n", _knobValues[i], i);
      (Joystick.*knob_changed_callbacks[i])(_knobValues[i]);
    }
  }
}

void Knobs::UpdateAnimationFrame() {
}
