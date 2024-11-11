#include <Arduino.h>
#include "Faders.h"

Faders::Faders(GlobalState& state) : state(state) {}

void Faders::setup() {
  Serial.printf("Faders setup\n");
}

void Faders::CheckDataSendHID() {
  // TODO change 2 back to FADER_COUNT
  for (int i = 0; i < FADER_COUNT; ++i) {
    int fader_value = analogRead(fader_pins[i]);

    int previous_fader_value = fader_values[i];
    
    if (abs(fader_value - previous_fader_value) >= 10) {
      fader_values[i] = fader_value;
      fader_changed[i] = true;
    } else {
      fader_changed[i] = false;
    }
  }
  
  // TODO: figure out what to do with the last two faders
  // TODO: Consolidate this into a single loop with a check on i?
  for (int i = 0; i < FADER_COUNT - 2; ++i) {
    if (fader_changed[i]) {
      Serial.printf("Configuring an axis with value %d for fader %d\n", fader_values[i], i);
      (Joystick.*fader_changed_callbacks[i])(fader_values[i]);
      fader_changed[i] = false;
    }
  }

  // Set global state values based on last two faders
  state.setLEDGridHue(fader_values[FADER_COUNT - 2]);
  state.setLEDGridSaturation(fader_values[FADER_COUNT - 1]);
}

void Faders::UpdateAnimationFrame() {
  // No animation to update
}
