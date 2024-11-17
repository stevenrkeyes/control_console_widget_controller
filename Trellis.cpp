#include "Trellis.h"
#include "Adafruit_NeoTrellis.h"
#include "GlobalState.h"

#define Y_DIM 8 //number of rows of key
#define X_DIM 4 //number of columns of keys

// Game colors
#define DEFAULT_COLOR 0x03c2fc
#define SNAKE_COLOR 0x00FF00
#define PELLET_COLOR 0xFF0000
#define GAME_SPEED 300

//create a matrix of trellis panels
Adafruit_NeoTrellis t_array[Y_DIM/4][X_DIM/4] = {
    { Adafruit_NeoTrellis(0x2E)},
    { Adafruit_NeoTrellis(0x2F)}
};

//pass this matrix to the multitrellis object
Adafruit_MultiTrellis trellis((Adafruit_NeoTrellis *)t_array, Y_DIM/4, X_DIM/4);

// Snake game state
struct Point {
    int x;
    int y;
    Point(int _x = 0, int _y = 0) : x(_x), y(_y) {}
};
std::vector<Point> snake;
Point pellet(0, 0);

// Input a value 0 to 255 to get a color value.
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
TrellisCallback blink(keyEvent evt) {
    if(evt.bit.EDGE == SEESAW_KEYPAD_EDGE_RISING) {
        trellis.setPixelColor(evt.bit.NUM, Wheel(map(evt.bit.NUM, 0, X_DIM*Y_DIM, 0, 255)));
        Serial.printf("Trellis key %d pressed\n", evt.bit.NUM);
        Joystick.button(evt.bit.NUM, true);
    } else if(evt.bit.EDGE == SEESAW_KEYPAD_EDGE_FALLING) {
        trellis.setPixelColor(evt.bit.NUM, DEFAULT_COLOR);
        Serial.printf("Trellis key %d released\n", evt.bit.NUM);
        Joystick.button(evt.bit.NUM, false);
    }
    trellis.show();
    return 0;
}

Trellis::Trellis(GlobalState& state) : ConsoleWidget(), state(state), _direction('R') {}

void Trellis::setup() {
    if(!trellis.begin()){
        Serial.println("failed to begin trellis");
        while(1) delay(1);
    }

    // Initialize all pixels
    for(int i=0; i<Y_DIM*X_DIM; i++){
        trellis.setPixelColor(i, Wheel(map(i, 0, X_DIM*Y_DIM, 0, 255)));
        trellis.show();
        delay(50);
    }
    
    // Set up key callbacks
    for(int y=0; y<Y_DIM; y++){
        for(int x=0; x<X_DIM; x++){
            trellis.activateKey(x, y, SEESAW_KEYPAD_EDGE_RISING, true);
            trellis.activateKey(x, y, SEESAW_KEYPAD_EDGE_FALLING, true);
            trellis.registerCallback(x, y, blink);
            trellis.setPixelColor(x, y, DEFAULT_COLOR);
            trellis.show();
            delay(50);
        }
    }

    // Initialize snake vector
    initializeSnake();
}

void Trellis::initializeSnake() {
  snake.clear();
  snake.push_back(Point(0, 0)); // Head 
  snake.push_back(Point(0, 1)); // Body
  snake.push_back(Point(0, 2)); // Tail
  Serial.printf("Snake initialized with %d points\n", snake.size());
} 

void Trellis::CheckDataSendHID() {
    bool buttonPressed = state.getBigButtonState();

    if (buttonPressed) { 
      ResetSnake();
      _gameActive = !_gameActive;
      Serial.printf("Game active: %d\n", _gameActive);
      state.setBigButtonState(0);
    }

    if (!_gameActive) {
        trellis.read();
        delay(20);
    } else {
        // Game input handling
        if (millis() - _lastMoveTime >= GAME_SPEED) {
            DrawSnake();
            _lastMoveTime = millis();
        }
        trellis.read();
    }
}

void Trellis::UpdateAnimationFrame() {
    if (!_gameActive) {
        if (state.getBigButtonState() == 1) {
            for (int i = 0; i < Y_DIM * X_DIM; i++) {
                trellis.setPixelColor(i, 0xFF0000);
            }
            trellis.show();
            delay(100);
            
            for (int i = 0; i < Y_DIM * X_DIM; i++) {
                trellis.setPixelColor(i, DEFAULT_COLOR);
            }
            trellis.show();
        }
        state.setBigButtonState(0);
    }
}

void Trellis::DrawSnake() {
    if (!_gameActive) return;

    Serial.printf("Drawing snake!!!\n");
    
    // Calculate new head position
    Point newHead = snake.front();
    _direction = state.getJoystickState();
    switch (_direction) {
        case 'U': newHead.y--; Serial.printf("Moving up\n"); break;
        case 'D': newHead.y++; Serial.printf("Moving down\n"); break;
        case 'L': newHead.x--; Serial.printf("Moving left\n"); break;
        case 'R': newHead.x++; Serial.printf("Moving right\n"); break;
    }
    
    Serial.printf("Checking for out of bounds\n");

    // Check for collisions
    if (newHead.x < 0 || newHead.x >= X_DIM || 
        newHead.y < 0 || newHead.y >= Y_DIM) {
        Serial.printf("Out of bounds: %d, %d\n", newHead.x, newHead.y);
        ResetSnake();
        return;
    }
    
    Serial.printf("Checking if pellet was eaten\n");
    

    // Check self collision
    for (const Point& p : snake) {
        if (p.x == newHead.x && p.y == newHead.y) {
            Serial.printf("Self collision detected: %d, %d\n", newHead.x, newHead.y);
            ResetSnake();
            return;
        }
    }
    
    Serial.printf("Moving snake\n");

    // Move snake
    snake.insert(snake.begin(), newHead);
    
    // Check if pellet was eaten
    if (newHead.x == pellet.x && newHead.y == pellet.y) {
        // Spawn new pellet
        std::vector<bool> available(X_DIM * Y_DIM, true);
        for (const Point& p : snake) {
            available[p.y * X_DIM + p.x] = false;
        }
        
        std::vector<Point> availablePoints;
        for (int y = 0; y < Y_DIM; y++) {
            for (int x = 0; x < X_DIM; x++) {
                if (available[y * X_DIM + x]) {
                    availablePoints.push_back(Point(x, y));
                }
            }
        }
        
        if (!availablePoints.empty()) {
            int index = random(availablePoints.size());
            pellet = availablePoints[index];
            trellis.setPixelColor(pellet.x, pellet.y, PELLET_COLOR);
        }
    } else {
        // Clear last segment if no pellet was eaten
        Point tail = snake.back();
        trellis.setPixelColor(tail.x, tail.y, 0);
        snake.pop_back();
    }
    
    Serial.printf("Drawing snake segments\n");

    // Update display
    for (const Point& p : snake) {
      Serial.printf("Drawing snake segment: %d, %d\n", p.x, p.y);
      // Swap trellis 4x4 grids - 4-7 should be 0-3, 0-3 should be 4-7
      trellis.setPixelColor((p.x + 4) % 8, p.y, SNAKE_COLOR);
    }
    trellis.setPixelColor((newHead.x + 4) % 8, newHead.y, SNAKE_COLOR);
    trellis.show();
}

void Trellis::ResetSnake() {
    // Game over animation
    for (int flash = 0; flash < 3; flash++) {
        for (int i = 0; i < X_DIM * Y_DIM; i++) {
            trellis.setPixelColor(i, 0xFF0000);
        }
        trellis.show();
        delay(200);
        
        for (int i = 0; i < X_DIM * Y_DIM; i++) {
            trellis.setPixelColor(i, 0);
        }
        trellis.show();
        delay(200);
    }
    
    // Reset game state
    initializeSnake();
    _direction = 'R';
    
    // Return to default state
    for (int i = 0; i < X_DIM * Y_DIM; i++) {
        trellis.setPixelColor(i, DEFAULT_COLOR);
    }
    trellis.show();
}

void Trellis::setDirection(char direction) {
  _direction = state.getJoystickState();
}
