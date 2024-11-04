// Output pins from the optocouplers
const int opto1OutputPin = 2;  // First optocoupler output connected to Arduino digital pin D2
const int opto2OutputPin = 3;  // Second optocoupler output connected to Arduino digital pin D3

// Store pulse counts and states
volatile int pulseCount1 = 0;
volatile int pulseCount2 = 0;
int lastOptoState1 = LOW;
int lastOptoState2 = LOW;
volatile int lastPulseCount1 = 0;
volatile int lastPulseCount2 = 0;
volatile int lastMillis1 = 0;
volatile int lastMillis2 = 0;

// Direction detection
volatile int direction = 0;  // 1 = clockwise, -1 = counterclockwise, 0 = no motion
volatile unsigned long sensor1Time = 0;
volatile unsigned long sensor2Time = 0;
const unsigned long DIRECTION_TIMEOUT = 50;  // milliseconds
const unsigned long MOTION_TIMEOUT = 100;    // milliseconds to wait before declaring no motion

// Variables for state machine
volatile byte sensorStates = 0;  // Stores current state of both sensors
volatile int8_t prevState = 0;   // Previous combined state
// State sequence for CW rotation:  00 -> 10 -> 11 -> 01 -> 00
// State sequence for CCW rotation: 00 -> 01 -> 11 -> 10 -> 00

void setup() {
  Serial.begin(115200);
  pinMode(opto1OutputPin, INPUT);
  pinMode(opto2OutputPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(opto1OutputPin), sensorChange1, CHANGE);
  attachInterrupt(digitalPinToInterrupt(opto2OutputPin), sensorChange2, CHANGE);
  Serial.print("Hi!");
}

void loop() {
  // Check for no motion
  if (millis() - max(sensor1Time, sensor2Time) > MOTION_TIMEOUT) {
    direction = 0;  // No motion detected
  }

  // Print direction
  if (direction == 1) {
    Serial.print("Clockwise         ");
  } else if (direction == -1) {
    Serial.print("Counter-Clockwise ");
  } else {
    Serial.print("                  ");
  }

  // Print speed as dots based on pulse count
  int pulses = max(pulseCount1 - lastPulseCount1, pulseCount2 - lastPulseCount2);
  for(int i = 0; i < pulses; i++) {
    Serial.print("--");
  }
  Serial.println();

  lastPulseCount1 = pulseCount1;
  lastPulseCount2 = pulseCount2;
  delay(50);
}

void sensorChange1() {
  // Update state machine with current real state
  bitWrite(sensorStates, 0, digitalRead(opto1OutputPin));
  updateDirection();
  if(digitalRead(opto1OutputPin) == HIGH) pulseCount1++;
  sensor1Time = millis();
}

void sensorChange2() {
  // Update state machine with current real state
  bitWrite(sensorStates, 1, digitalRead(opto2OutputPin));
  updateDirection();
  if(digitalRead(opto2OutputPin) == HIGH) pulseCount2++;
  sensor2Time = millis();
}

// Handle direction updates
void updateDirection() {
  int8_t currentState = sensorStates;
  
  // Gray code sequence for quadrature encoder
  switch (prevState) {
    case 0b00:
      direction = (currentState == 0b01) ? -1 : ((currentState == 0b10) ? 1 : direction);
      break;
    case 0b01:
      direction = (currentState == 0b11) ? -1 : ((currentState == 0b00) ? 1 : direction);
      break;
    case 0b11:
      direction = (currentState == 0b10) ? -1 : ((currentState == 0b01) ? 1 : direction);
      break;
    case 0b10:
      direction = (currentState == 0b00) ? -1 : ((currentState == 0b11) ? 1 : direction);
      break;
  }
  
  prevState = currentState;
}
