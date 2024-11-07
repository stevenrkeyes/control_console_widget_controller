#ifndef CONTROLLER_VARIANT_H
#define CONTROLLER_VARIANT_H

#include "pins.h"

enum ControllerVariant {
  CONTROLLER_A,
  CONTROLLER_B,
  CONTROLLER_C
};

int determineControllerVariant();

#endif
