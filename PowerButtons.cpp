#include <Arduino.h>
#include "PowerButtons.h"
#include "led_utils.h"

PowerButtons::PowerButtons() {
  for (int i = 0; i < POWER_BUTTONS_NUM; i++) {
    buttons[i] = Bounce(POWER_BUTTONS_PINS[i], 10);
  }
}

void PowerButtons::setup() {
  for (int i = 0; i < POWER_BUTTONS_NUM; i++) {
    pinMode(POWER_BUTTONS_PINS[i], INPUT_PULLUP);
    pinMode(POWER_BUTTONS_LED_PINS[i], OUTPUT);
  }
}

void PowerButtons::CheckDataSendHID() {
  for (int i = 0; i < POWER_BUTTONS_NUM; i++) {
    buttons[i].update();

    if (buttons[i].fell()) {
      if (not activated[i]) {
        Joystick.button(31, 1);
        pressTimesMs[i] = millis();
        activated[i] = true;
      } else {
        Joystick.button(31, 0);
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

void PowerButtons::UpdateAnimationFrame() {
  unsigned long currentTimeMs = millis();
  unsigned long timeSincePressMs;
  char led_brightness;

  for (int i = 0; i < POWER_BUTTONS_NUM; i++) {
    timeSincePressMs = ULONG_MAX;
    // Check that the current time is after the button press time to check that the button has ever been pressed
    if (currentTimeMs > pressTimesMs[i]) {
      timeSincePressMs = currentTimeMs - pressTimesMs[i];

      if (activated[i]) {
        led_brightness = RampToValue(50, 255, 200, timeSincePressMs);
      } else {
        led_brightness = RampToValue(255, 0, 250, timeSincePressMs);
      }
      analogWrite(POWER_BUTTONS_LED_PINS[i], led_brightness);
    }
  }
}
