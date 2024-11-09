#include "ConsoleWidget.h"
#include "NeatButton.h"
#include "PowerButtons.h"
#include "Faders.h"
#include "ControllerVariant.h"
#include "JogWheel.h"
#include "LEDGrid.h"
#include "RedJoystick.h"

#define ARRAY_LENGTH(array) (sizeof((array)) / sizeof((array)[0]))

int controllerVariant;

// Add console widgets here
RedJoystick redJoystick;
ConsoleWidget* widgetsA[] = { &redJoystick };

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
  Serial.println("starting");

  controllerVariant = determineControllerVariant();

  switch (controllerVariant) {
    case CONTROLLER_A:
      widgets = widgetsA;
      numWidgets = ARRAY_LENGTH(widgetsA);
      break;
    case CONTROLLER_B:
      widgets = widgetsB;  // Set widgets to widgetsB
      numWidgets = ARRAY_LENGTH(widgetsB);
      break;
    case CONTROLLER_C:
      widgets = widgetsC;  // Set widgets to widgetsC
      numWidgets = ARRAY_LENGTH(widgetsC);
      break;
  }

  for (int i = 0; i < numWidgets; i++) {
    widgets[i]->setup();
  }
}

void loop() {
  for (int i = 0; i < numWidgets; i++) {
    widgets[i]->CheckDataSendMIDI();
    widgets[i]->UpdateAnimationFrame();
  }
  usbMIDI.read();  // Process incoming MIDI
  delay(2);
}
