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
  int buttonID;
  
  // Determine which board the button is on and calculate total button ID
  if (evt.bit.EDGE == SEESAW_KEYPAD_EDGE_RISING) {
    if (evt.bit.NUM < 16) {
      buttonID = evt.bit.NUM;  // First board
    } else {
      buttonID = evt.bit.NUM + 16;  // Second board
    }
    
    // Print button press info to serial
    Serial.print("Button pressed: ");
    Serial.print(buttonID);
    Serial.print(" (RGB: ");
    Serial.print(buttonColors[buttonID].r);
    Serial.print(",");
    Serial.print(buttonColors[buttonID].g);
    Serial.print(",");
    Serial.print(buttonColors[buttonID].b);
    Serial.println(")");
    
    // Light up the corresponding LED
    if (buttonID < 16) {
      trellis_1.pixels.setPixelColor(buttonID, 
        buttonColors[buttonID].r,
        buttonColors[buttonID].g,
        buttonColors[buttonID].b);
      trellis_1.pixels.show();
    } else {
      trellis_2.pixels.setPixelColor(buttonID - 16,
        buttonColors[buttonID].r,
        buttonColors[buttonID].g,
        buttonColors[buttonID].b);
      trellis_2.pixels.show();
    }
  }
  return 0;
}


void Trellis::setup() {
  Serial.begin(9600);
  
  // Initialize both NeoTrellis boards
  if (!trellis_1.begin()) {
    Serial.println("Failed to initialize NeoTrellis 1");
    while(1);
  }
  if (!trellis_2.begin()) {
    Serial.println("Failed to initialize NeoTrellis 2");
    while(1);
  }

   Serial.println("\nNeoTrellis 0x2F Test");
  
  Wire.begin();
  
  // Test direct I2C communication first
  Serial.print("Testing I2C connection to 0x2F: ");
  Wire.beginTransmission(0x2F);
  byte error = Wire.endTransmission();
  
  if (error == 0) {
    Serial.println("Device responded!");
  } else {
    Serial.print("Error code: ");
    Serial.print(error);
    Serial.println(" (0=success, 2=addr NAK, 3=data NAK, 4=other error)");
  }

  // Generate random RGB values for all buttons
  randomSeed(analogRead(0));
  for(int i=0; i<32; i++) {
    buttonColors[i].r = random(256);
    buttonColors[i].g = random(256);
    buttonColors[i].b = random(256);
  }

  // Activate all keys and register callbacks
  for(int i=0; i<16; i++) {
    trellis_1.activateKey(i, SEESAW_KEYPAD_EDGE_RISING);
    trellis_1.registerCallback(i, buttonCallback);
    trellis_2.activateKey(i, SEESAW_KEYPAD_EDGE_RISING);
    trellis_2.registerCallback(i, buttonCallback);
  }
  
  // Start both boards
  trellis_1.pixels.clear();
  trellis_2.pixels.clear();
  trellis_1.pixels.show();
  trellis_2.pixels.show();
  
  Serial.println("NeoTrellis initialization complete");
}

void Trellis::CheckDataSendMIDI() {

}

void Trellis::UpdateAnimationFrame() {
  // Read button presses from both boards
  trellis_1.read();
  trellis_2.read();
}