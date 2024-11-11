#include <Arduino.h>
#include "Faders.h"

Faders::Faders() {}

void Faders::setup() {
}

int MapFaderToNoteVelocity(int fader_value) {
  return max(MIN_MIDI_VELOCITY, int((fader_value * 1.0 - MIN_FADER_VALUE) / MAX_FADER_VALUE * MAX_MIDI_VELOCITY));
}

void Faders::CheckDataSendHID() {
  for (int i = 0; i < FADER_COUNT; ++i) {
    if (fader_changed[i]) {
      int note = fader_notes[i];
      //Serial.printf("Sending note %d with velocity %d for fader %d\n", note, note_velocity, i);
      fader_changed_callbacks[i](fader_values[i]);
      // todo: add in sending joystick values (or something else)
      fader_changed[i] = false;
    }
  }
}

void Faders::UpdateAnimationFrame() {
  // Remove if unused.
  unsigned long currentTimeMs = millis();
  
  for (int i = 0; i < FADER_COUNT; ++i) {
    int fader_pin = FADER_PIN_OFFSET + i;
    int fader_value = analogRead(fader_pin);

    int previous_fader_value = fader_values[i];
    
    if (abs(fader_value - previous_fader_value) >= 10) {
      fader_values[i] = fader_value;
      fader_changed[i] = true;
    } else {
      fader_changed[i] = false;
    }
  }
}
