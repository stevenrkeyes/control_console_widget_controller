#include <Arduino.h>
#include "NeatButton.h"

NeatButton::NeatButton() : button(NEAT_BUTTON_PIN, 50) {}

void NeatButton::setup() {
    pinMode(NEAT_BUTTON_PIN, INPUT_PULLUP);
    pinMode(NEAT_BUTTON_LED_PIN, OUTPUT);
}

void NeatButton::CheckDataSendMIDI() {
    const int note = 65;
    const int velocity = 99;

    button.update();

    if (button.fallingEdge()) {
        usbMIDI.sendNoteOn(note, velocity, NEAT_BUTTON_MIDI_CHANNEL);
        pressTimeMs = millis();
    }
    if (button.risingEdge()) {
        usbMIDI.sendNoteOff(note, velocity, NEAT_BUTTON_MIDI_CHANNEL);
        releaseTimeMs = millis();
    }
}

unsigned char RampToValue(char startValue, char endValue, long endTime, long currentTime) {
  if (currentTime < 0) {
    return 0;
  } else if (currentTime >= 0 && currentTime < endTime) {
    // Interpolate on the line from (0, startValue) to (endTime, endValue)
    return (unsigned char) (startValue - (1.0 * (startValue - endValue) * currentTime / endTime));
  } else {
    return endValue;
  }
}

void NeatButton::UpdateAnimationFrame() {
  unsigned long currentTimeMs = millis();
  unsigned long timeSincePressMs = ULONG_MAX;
  unsigned long timeSinceReleaseMs = ULONG_MAX;
  char led_brightness;

  // Check that the current time is after the button press time to check that the button has ever been pressed
  if (currentTimeMs > pressTimeMs) {
    timeSincePressMs = currentTimeMs - pressTimeMs;
    
    if (currentTimeMs > releaseTimeMs) {
      timeSinceReleaseMs = currentTimeMs - releaseTimeMs;
    }
    // Check which one was more recent
    if (timeSincePressMs < timeSinceReleaseMs) {
      // Do press animation
      led_brightness = RampToValue(NEAT_BUTTON_MAX_BRIGHTNESS, NEAT_BUTTON_MID_BRIGHTNESS, NEAT_BUTTON_PRESS_DURATION, timeSincePressMs);
      analogWrite(NEAT_BUTTON_LED_PIN, led_brightness);
    } else {
      // Do release animation
      led_brightness = RampToValue(NEAT_BUTTON_MID_BRIGHTNESS, NEAT_BUTTON_MIN_BRIGHTNESS, NEAT_BUTTON_RELEASE_DURATION, timeSinceReleaseMs);
      analogWrite(NEAT_BUTTON_LED_PIN, led_brightness);
    }
  }
}
