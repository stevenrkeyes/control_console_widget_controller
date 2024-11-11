#include <Arduino.h>
#include "Faders.h"

Faders::Faders() {}

void Faders::setup() {
  Serial.printf("Faders setup\n");
}

// int MapFaderToNoteVelocity(int fader_value) {
//   return max(MIN_MIDI_VELOCITY, int((fader_value * 1.0 - MIN_FADER_VALUE) / MAX_FADER_VALUE * MAX_MIDI_VELOCITY));
// }

void Faders::CheckDataSendHID() {
  // TODO: figure out what to do with the last two faders
  for (int i = 0; i < 2; ++i) {
    if (fader_changed[i]) {
      Serial.printf("Configuring an axis with value %d for fader %d\n", fader_values[i], i);
      (Joystick.*fader_changed_callbacks[i])(fader_values[i]);
      fader_changed[i] = false;
    }
  }
}

void Faders::UpdateAnimationFrame() {
  // Remove if unused.
  unsigned long currentTimeMs = millis();
  
  // TODO change 2 back to FADER_COUNT
  for (int i = 0; i < 2; ++i) {
    int fader_value = analogRead(fader_pins[i]);

    // Serial.printf("Fader %d has value %d\n", i, fader_value);

    int previous_fader_value = fader_values[i];
    
    if (abs(fader_value - previous_fader_value) >= 10) {
      fader_values[i] = fader_value;
      fader_changed[i] = true;
    } else {
      fader_changed[i] = false;
    }
  }
}
