// "FASTLED_INTERNAL" disables printing the version string of FastLED, which is used by Adafruit_NeoTrellis.h
#define FASTLED_INTERNAL
#include "Adafruit_NeoTrellis.h"
#include "Trellis.h"
#include <Wire.h>

// Create NeoTrellis objects for both boards
Adafruit_NeoTrellis trellis_1(0x2E);
Adafruit_NeoTrellis trellis_2(0x2F);

// Create array to store RGB values for all 32 buttons
struct RGB {
  uint8_t r;
  uint8_t g;
  uint8_t b;
} buttonColors[32];

Trellis::Trellis() {}

// Callback function for button presses
TrellisCallback buttonCallback(keyEvent evt) {
  // Get the absolute button number and board number
  uint8_t boardNum = evt.bit.NUM >= 16 ? 1 : 0;
  uint8_t buttonNum = evt.bit.NUM % 16;  // Convert to 0-15 range for each board
  int absoluteButton = boardNum * 16 + buttonNum;
  
  if (evt.bit.EDGE == SEESAW_KEYPAD_EDGE_RISING) {
    Serial.print("Board: ");
    Serial.print(boardNum);
    Serial.print(", Local Button: ");
    Serial.print(buttonNum);
    Serial.print(", Absolute Button: ");
    Serial.println(absoluteButton);
    
    // Light up the button on the appropriate board
    if (boardNum == 0) {
      trellis_1.pixels.setPixelColor(buttonNum, 
        buttonColors[absoluteButton].r,
        buttonColors[absoluteButton].g,
        buttonColors[absoluteButton].b);
      trellis_1.pixels.show();
    } else {
      trellis_2.pixels.setPixelColor(buttonNum,  // Note: using buttonNum, not absoluteButton
        buttonColors[absoluteButton].r,
        buttonColors[absoluteButton].g,
        buttonColors[absoluteButton].b);
      trellis_2.pixels.show();
    }
  }
  return 0;
}


// TODO: Refactor to use Adafruit_MultiTrellis trellis((Adafruit_NeoTrellis *)t_array, Y_DIM/4, X_DIM/4);
void Trellis::setup() {
  Serial.begin(9600);
  while(!Serial) delay(10);
  
  Serial.println("\nDual NeoTrellis Test");
  
  // Initialize first board
  Serial.println("Initializing first NeoTrellis (0x2E)...");
  if (!trellis_1.begin()) {
    Serial.println("Failed to initialize first NeoTrellis");
    while(1);
  }
  
  // Initialize second board
  Serial.println("Initializing second NeoTrellis (0x2F)...");
  if (!trellis_2.begin()) {
    Serial.println("Failed to initialize second NeoTrellis");
    while(1);
  }

  // Generate random colors for all buttons
  randomSeed(analogRead(0));
  for(int i=0; i<32; i++) {
    buttonColors[i].r = random(256);
    buttonColors[i].g = random(256);
    buttonColors[i].b = random(256);
  }

  // Initialize first board's buttons
  Serial.println("Setting up first board buttons...");
  for(int i=0; i<16; i++) {
    trellis_1.activateKey(i, SEESAW_KEYPAD_EDGE_RISING);
    trellis_1.registerCallback(i, buttonCallback);
  }
  
  // Initialize second board's buttons
  Serial.println("Setting up second board buttons...");
  for(int i=0; i<16; i++) {
    trellis_2.activateKey(i, SEESAW_KEYPAD_EDGE_RISING);
    trellis_2.registerCallback(i, buttonCallback);
  }

  // Test pattern - flash each board in sequence
  Serial.println("Running test pattern...");
  
  // Flash first board green
  for(int i=0; i<16; i++) {
    trellis_1.pixels.setPixelColor(i, 0, 255, 0);
  }
  trellis_1.pixels.show();
  delay(500);
  trellis_1.pixels.clear();
  trellis_1.pixels.show();
  
  // Flash second board blue
  for(int i=0; i<16; i++) {
    trellis_2.pixels.setPixelColor(i, 0, 0, 255);
  }
  trellis_2.pixels.show();
  delay(500);
  trellis_2.pixels.clear();
  trellis_2.pixels.show();
  
  Serial.println("Initialization complete!");
}

void Trellis::CheckDataSendHID() {

}

void Trellis::UpdateAnimationFrame() {
  // Read button presses from both boards
  trellis_1.read();
  trellis_2.read();
}