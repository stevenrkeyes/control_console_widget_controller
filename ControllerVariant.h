#ifndef CONTROLLER_VARIANT_H
#define CONTROLLER_VARIANT_H

// Pin to determine which controller this is (A, B, C)
#define CONTROLLER_VARIANT_PIN 0

enum ControllerVariant {
  CONTROLLER_A,
  CONTROLLER_B,
  CONTROLLER_C
};

int determineControllerVariant();

#endif
