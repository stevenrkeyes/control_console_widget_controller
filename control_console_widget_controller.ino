#include "ConsoleWidget.h"
#include "NeatButton.h"
#include "PowerButtons.h"
#include "Faders.h"
#include "ControllerVariant.h"
#include "JogWheel.h"
#include "LEDGrid.h"
#include "RedJoystick.h"
#include "Trellis.h"

#define ARRAY_LENGTH(array) (sizeof((array)) / sizeof((array)[0]))

int controllerVariant;

// Add console widgets here
RedJoystick redJoystick;
Trellis trellis;
ConsoleWidget* widgetsA[] = { &redJoystick, &trellis };

NeatButton neatButton;
PowerButtons powerButtons;
Faders faders;
JogWheel jogWheel;
LEDGrid ledGrid;
ConsoleWidget* widgetsB[] = { &neatButton, &powerButtons, &faders, &jogWheel, &ledGrid };

ConsoleWidget* widgetsC[] = {};

ConsoleWidget** widgets = nullptr;
int numWidgets = 0;

void setup() {
  // TODO remove.
  Serial.begin(9600);
  Serial.println("Starting");

  controllerVariant = determineControllerVariant();

  switch (controllerVariant) {
    case CONTROLLER_A:
      widgets = widgetsA;
      numWidgets = ARRAY_LENGTH(widgetsA);
      Serial.println("Configured as Controller A");
      break;
    case CONTROLLER_B:
      widgets = widgetsB;  // Set widgets to widgetsB
      numWidgets = ARRAY_LENGTH(widgetsB);
      Serial.println("Configured as Controller B");
      break;
    case CONTROLLER_C:
      widgets = widgetsC;  // Set widgets to widgetsC
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
  delay(2);
}