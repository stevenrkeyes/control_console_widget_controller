#include "Trellis.h"
#include "Adafruit_NeoTrellis.h"
#include "GlobalState.h"

#define Y_DIM 8 //number of rows of key
#define X_DIM 4 //number of columns of keys

// Game colors
#define DEFAULT_COLOR 0x42a4f5
#define SNAKE_COLOR 0x00FF00
#define PELLET_COLOR 0xFF0000
#define GAME_SPEED 300

//create a matrix of trellis panels
Adafruit_NeoTrellis t_array[Y_DIM/4][X_DIM/4] = {
    { Adafruit_NeoTrellis(0x2F)},
    { Adafruit_NeoTrellis(0x2E)}
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

Trellis::Trellis(GlobalState& state) : ConsoleWidget(), state(state), _direction('R') {}

void Trellis::setup() {
    if(!trellis.begin()){
        Serial.println("failed to begin trellis");
        while(1) delay(1);
    }

    // Initialize all pixels
    for(int i=0; i<Y_DIM*X_DIM; i++) {
        trellis.setPixelColor(i, DEFAULT_COLOR);
        trellis.show();
        delay(50);
    }

    // Initialize snake vector
    initializeSnake();
    state.setJoystickState('D');
}

void Trellis::initializeSnake() {
  snake.clear();
  snake.push_back(Point(0, 2)); // Head
  snake.push_back(Point(0, 1)); // Body
  snake.push_back(Point(0, 1)); // Tail
} 

void Trellis::CheckDataSendHID() {
    _direction = state.getJoystickState();

    // TODO: Move this to UpdateAnimationFrame()
    // Game input handling
    if (millis() - _lastMoveTime >= GAME_SPEED) {
        for (int i = 0; i < Y_DIM * X_DIM; i++) {
            trellis.setPixelColor(i, DEFAULT_COLOR);
        }
        DrawSnake();
        trellis.show();
        _lastMoveTime = millis();
    }
    trellis.read();
}

void Trellis::UpdateAnimationFrame() {    
}

void Trellis::DrawSnake() {
    // Calculate new head position
    Point newHead = snake.front();

    _direction = state.getJoystickState();
    switch (_direction) {
        case 'U': newHead.y--; break;
        case 'D': newHead.y++; break;
        case 'L': newHead.x--; break;
        case 'R': newHead.x++; break;
    }
    // Check for OOB
    if (newHead.x < 0 || newHead.x >= X_DIM || 
        newHead.y < 0 || newHead.y >= Y_DIM) {
        ResetSnake();
        return;
    }

    // Check self collision
    for (const Point& p : snake) {
        if (p.x == newHead.x && p.y == newHead.y) {
            Serial.printf("Self collision detected: %d, %d\n", newHead.x, newHead.y);
            ResetSnake();
            return;
        }
    }

    // Move snake
    snake.insert(snake.begin(), newHead);
    
    // Check if pellet was eaten
    if ((newHead.y * X_DIM + newHead.x) == (pellet.y * X_DIM + pellet.x)) {
        Serial.printf("Pellet eaten at: %d, %d\n", pellet.x, pellet.y);
        
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
            Serial.printf("Spawning pellet at: %d, %d\n", availablePoints[index].x, availablePoints[index].y);
            pellet = availablePoints[index];
            trellis.setPixelColor(pellet.x, pellet.y, PELLET_COLOR);
        }
    } else {
        // Clear last segment if no pellet was eaten
        Point tail = snake.back();
        trellis.setPixelColor(tail.x, tail.y, DEFAULT_COLOR);
        snake.pop_back();
    }

    // Update display
    for (const Point& p : snake) {
      trellis.setPixelColor(p.x, p.y, SNAKE_COLOR);
    }
    trellis.setPixelColor(newHead.x, newHead.y, SNAKE_COLOR);
    trellis.show();
}

void Trellis::ResetSnake() {
    // Game over animation
    for (int flash = 0; flash < 1; flash++) {
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
    state.setJoystickState('D');
    
    // Return trellis to default state
    for (int i = 0; i < X_DIM * Y_DIM; i++) {
        trellis.setPixelColor(i, DEFAULT_COLOR);
    }
    trellis.show();
}