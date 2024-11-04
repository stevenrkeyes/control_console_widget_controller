#include <Arduino.h>
#include "ControllerVariant.h"

int determineControllerVariant() {
  int controllerVariant;

  // Check pin 0 to determine whether this is controller A, B, or C.
  pinMode(CONTROLLER_VARIANT_PIN, INPUT_PULLUP);
  delay(10);
  int stateWithPullUp = digitalRead(CONTROLLER_VARIANT_PIN);
  pinMode(CONTROLLER_VARIANT_PIN, INPUT_PULLDOWN);
  delay(10);
  int stateWithPullDown = digitalRead(CONTROLLER_VARIANT_PIN);

  if (stateWithPullDown == LOW && stateWithPullUp == HIGH) {
    // Floating
    controllerVariant = CONTROLLER_B;
  } else if (stateWithPullDown == HIGH) {
    // Connected to 3.3V
    controllerVariant = CONTROLLER_C;
  } else {
    // Connected to 0V
    controllerVariant = CONTROLLER_A;
  }

  return controllerVariant;
}
