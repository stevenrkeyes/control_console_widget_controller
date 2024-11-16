#include "Adafruit_NeoTrellis.h"
#include "Trellis.h"
#include "GlobalState.h"

#define Y_DIM 8 //number of rows of key
#define X_DIM 4 //number of columns of keys

// Define a default color value
#define DEFAULT_COLOR 0x03c2fc

//create a matrix of trellis panels
Adafruit_NeoTrellis t_array[Y_DIM/4][X_DIM/4] = {

    { Adafruit_NeoTrellis(0x2E)},
    { Adafruit_NeoTrellis(0x2F)}

};

//pass this matrix to the multitrellis object
Adafruit_MultiTrellis trellis((Adafruit_NeoTrellis *)t_array, Y_DIM/4, X_DIM/4);

Trellis::Trellis(GlobalState& state) : state(state) {}

// Input a value 0 to 255 to get a color value.
// The colors are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  if(WheelPos < 85) {
   return seesaw_NeoPixel::Color(WheelPos * 3, 255 - WheelPos * 3, 0);
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   return seesaw_NeoPixel::Color(255 - WheelPos * 3, 0, WheelPos * 3);
  } else {
   WheelPos -= 170;
   return seesaw_NeoPixel::Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  return 0;
}

//define a callback for key presses
TrellisCallback blink(keyEvent evt){
  if(evt.bit.EDGE == SEESAW_KEYPAD_EDGE_RISING) {
    trellis.setPixelColor(evt.bit.NUM, Wheel(map(evt.bit.NUM, 0, X_DIM*Y_DIM, 0, 255))); //on rising
    Serial.printf("Trellis key %d pressed\n", evt.bit.NUM);
    Joystick.button(evt.bit.NUM, true);
  } else if(evt.bit.EDGE == SEESAW_KEYPAD_EDGE_FALLING) {
    trellis.setPixelColor(evt.bit.NUM, DEFAULT_COLOR); //off falling
    Serial.printf("Trellis key %d released\n", evt.bit.NUM);
    Joystick.button(evt.bit.NUM, false);
  }  

  trellis.show();
  return 0;
}

void Trellis::setup() {
  if(!trellis.begin()){
    Serial.println("failed to begin trellis");
    while(1) delay(1);
  }

  /* the array can be addressed as x,y or with the key number */
  for(int i=0; i<Y_DIM*X_DIM; i++){
      trellis.setPixelColor(i, Wheel(map(i, 0, X_DIM*Y_DIM, 0, 255))); //addressed with keynum
      trellis.show();
      delay(50);
  }
  
  for(int y=0; y<Y_DIM; y++){
    for(int x=0; x<X_DIM; x++){
      //activate rising and falling edges on all keys
      trellis.activateKey(x, y, SEESAW_KEYPAD_EDGE_RISING, true);
      trellis.activateKey(x, y, SEESAW_KEYPAD_EDGE_FALLING, true);
      trellis.registerCallback(x, y, blink);
      trellis.setPixelColor(x, y, DEFAULT_COLOR); //addressed with x,y
      trellis.show(); //show all LEDs
      delay(50);
    }
  }
}

void Trellis::FlashRed() {
  for (int i =0; i <3; i++) {
    for (int i = 0; i < Y_DIM * X_DIM; i++) {
      trellis.setPixelColor(i, 0xFF0000);
    }
    trellis.show();
    delay(100);
  }
  for (int i = 0; i < Y_DIM * X_DIM; i++) {
    trellis.setPixelColor(i, DEFAULT_COLOR);
  }
  trellis.show();
}

void Trellis::CheckDataSendHID() {
  trellis.read();
  delay(20);
}

void Trellis::UpdateAnimationFrame() {
  if (state.getBigButtonState() == 1) {
    FlashRed();
  }
  state.setBigButtonState(0);
}
