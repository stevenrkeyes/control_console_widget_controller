#include <Arduino.h>
#include "Faders.h"

Faders::Faders(GlobalState& state) : state(state) {}

void Faders::setup() {
  Serial.printf("Faders setup\n");
}

uint8_t mapFaderValueToHueOrSaturation(int fader_value) {
  return map(fader_value, 0, 1023, 0, 255);
}

void Faders::CheckDataSendHID() {
  for (int i = 0; i < FADER_COUNT; ++i) {
    int fader_value = analogRead(fader_pins[i]);

    int previous_fader_value = fader_values[i];
    
    if (abs(fader_value - previous_fader_value) >= 30) {
      fader_values[i] = fader_value;
      
      if (i < FADER_COUNT - 2) {
        (Joystick.*fader_changed_callbacks[i])(fader_values[i]);
        // TODO: Guard these behind a flag.
        Serial.printf("Configuring an axis with value %d for fader %d\n", fader_values[i], i);
      } else {
        Serial.printf("Setting LED grid value to %d for fader %d\n", mapFaderValueToHueOrSaturation(fader_values[i]), i);
      }
    }
  }

  // Set global state values based on last two faders
  state.setLEDGridHue(mapFaderValueToHueOrSaturation(fader_values[FADER_COUNT - 2]));
  state.setLEDGridSaturation(mapFaderValueToHueOrSaturation(fader_values[FADER_COUNT - 1]));
}

void Faders::UpdateAnimationFrame() {
  // No animation to update
}
