#include "ConsoleWidget.h"
#include "NeatButton.h"
#include "PowerButtons.h"
#include "Faders.h"
#include "ControllerVariant.h"
#include "JogWheel.h"
#include "LEDGrid.h"
#include "RedJoystick.h"
#include "Trellis.h"
#include "TriangleButtons.h"

#define ARRAY_LENGTH(array) (sizeof((array)) / sizeof((array)[0]))
#define LOOP_DELAY_MS 2

int controllerVariant;

// Add console widgets here
NeatButton neatButton;
RedJoystick redJoystick;
Trellis trellis;
ConsoleWidget* widgetsA[] = { &neatButton, &redJoystick, &trellis };

PowerButtons powerButtons;
Faders faders;
JogWheel jogWheel;
LEDGrid ledGrid;
ConsoleWidget* widgetsB[] = { &neatButton, &powerButtons, &faders, &jogWheel, &ledGrid };

TriangleButtons triangleButtons;
ConsoleWidget* widgetsC[] = { &neatButton, &triangleButtons, &faders };

ConsoleWidget** widgets = nullptr;
int numWidgets = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Starting");

  // Set joystick controls to defaults to prevent them from sending weird messages if they are unused
  Joystick.hat(-1);
  Joystick.X(512);
  Joystick.Y(512);
  Joystick.Z(512);
  Joystick.Zrotate(512);
  Joystick.sliderLeft(512);
  Joystick.sliderRight(512);

  controllerVariant = determineControllerVariant();

  switch (controllerVariant) {
    case CONTROLLER_A:
      widgets = widgetsA;
      numWidgets = ARRAY_LENGTH(widgetsA);
      Serial.println("Configured as Controller A");
      break;
    case CONTROLLER_B:
      widgets = widgetsB;
      numWidgets = ARRAY_LENGTH(widgetsB);
      Serial.println("Configured as Controller B");
      break;
    case CONTROLLER_C:
      widgets = widgetsC;
      numWidgets = ARRAY_LENGTH(widgetsC);
      Serial.println("Configured as Controller C");
      break;
  }

  for (int i = 0; i < numWidgets; i++) {
    widgets[i]->setup();
  }
}

void loop() {
  for (int i = 0; i < numWidgets; i++) {
    widgets[i]->CheckDataSendHID();
    widgets[i]->UpdateAnimationFrame();
  }
  delay(LOOP_DELAY_MS);
}
