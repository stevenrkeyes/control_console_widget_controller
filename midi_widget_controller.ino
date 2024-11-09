#include "ConsoleWidget.h"
#include "NeatButton.h"
#include "PowerButtons.h"
#include "Faders.h"
#include "ControllerVariant.h"
#include "JogWheel.h"
#include "LEDGrid.h"
#include "Trellis.h"
#include "Joystick.h"

int controllerVariant;

// Add console widgets here
Joystick joystick;
Trellis trellis;
ConsoleWidget* widgetsA[] = {&joystick, &trellis };

NeatButton neatButton;
PowerButtons powerButtons;
Faders faders;
JogWheel jogWheel;
LEDGrid ledGrid;
Joystick joystick;
Trellis trellis;
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
      numWidgets = sizeof(widgetsA) / sizeof(widgetsA[0]);
      break;
    case CONTROLLER_B:
      widgets = widgetsB;  // Set widgets to widgetsB
      numWidgets = sizeof(widgetsB) / sizeof(widgetsB[0]);
      break;
    case CONTROLLER_C:
      widgets = widgetsC;  // Set widgets to widgetsC
      numWidgets = sizeof(widgetsC) / sizeof(widgetsC[0]);
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
