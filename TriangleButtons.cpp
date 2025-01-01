#include <Arduino.h>
#include "TriangleButtons.h"
#include "led_utils.h"

TriangleButtons::TriangleButtons() {
  for (int i = 0; i < TRIANGLE_BUTTONS_NUM; i++) {
    buttons[i] = Bounce(TRIANGLE_BUTTONS_PINS[i], 10);
  }
}

void TriangleButtons::setup() {
  for (int i = 0; i < TRIANGLE_BUTTONS_NUM; i++) {
    pinMode(TRIANGLE_BUTTONS_PINS[i], INPUT_PULLUP);
    pinMode(TRIANGLE_BUTTONS_LED_PINS[i], OUTPUT);
  }
}

void TriangleButtons::CheckDataSendHID() {
  for (int i = 0; i < TRIANGLE_BUTTONS_NUM; i++) {
    buttons[i].update();

    if (buttons[i].fell()) {
      if (not activated[i]) {
        Joystick.button(31 - i, 1);
        pressTimesMs[i] = millis();
        activated[i] = true;
        Serial.printf("Triangle button %d pressed\n", i);
      } else {
        Joystick.button(31 - i, 0);
        pressTimesMs[i] = millis();
        activated[i] = false;
      }
    }
    if (buttons[i].rose()) {
      // do nothing; just checking to clear the flag
      // todo: this might not be necessary, might want to check
    }
  }
}

void TriangleButtons::UpdateAnimationFrame() {
  unsigned long currentTimeMs = millis();
  unsigned long timeSincePressMs;
  char led_brightness;

  for (int i = 0; i < TRIANGLE_BUTTONS_NUM; i++) {
    timeSincePressMs = ULONG_MAX;
    // Check that the current time is after the button press time to check that the button has ever been pressed
    if (currentTimeMs > pressTimesMs[i]) {
      timeSincePressMs = currentTimeMs - pressTimesMs[i];

      if (activated[i]) {
        led_brightness = RampToValue(50, 255, 200, timeSincePressMs);
      } else {
        led_brightness = RampToValue(255, 0, 150, timeSincePressMs);
      }
      analogWrite(TRIANGLE_BUTTONS_LED_PINS[i], led_brightness);
    }
  }
  // sorry steven I will refactor this later.
  // Keep blue and yellow lights always on.
  analogWrite(TRIANGLE_BUTTONS_LED_PINS[0], 255);
  analogWrite(TRIANGLE_BUTTONS_LED_PINS[1], 255);
}
