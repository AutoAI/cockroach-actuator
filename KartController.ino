#include <Servo.h> // for the gas pedal

//system variables
int SteeringVPin = 3;
int SteeringDPin = 2;
int BrakingVPin = 5;
int BrakingDPin = 4;

int SteeringSensePin = 0;
int BrakingSensePin = 1;
int EnginePin = 7;

int SteeringTarget = 0;
int BrakingTarget = 0;

long Acceleration = 0xA0;

int SteeringDistance = 0;
int BrakingDistance = 0;

int SteeringPos = 0;
int BrakingPos = 0;

int SteeringGoal = 512;
int BrakingGoal = 0;
int AccelerationGoal = 0;

Servo gas;
int angle = 0;

//user-defined variables
int threshold = 30; //how much the read in and actual values can differ without causing movement (0-1023)
int power = 255; //how strong the linear actuators can be(0-255)

void setup() {
  pinMode(SteeringVPin, OUTPUT);
  pinMode(SteeringDPin, OUTPUT);
  pinMode(BrakingVPin, OUTPUT);
  pinMode(BrakingDPin, OUTPUT);
  pinMode(EnginePin, OUTPUT);
  digitalWrite(EnginePin, HIGH);
  gas.attach(6);
  Serial.begin(9600);
  Serial.println("Initialization complete!");
}

void loop() {
  // if we have new serial data, grab it and decode it
  if (Serial.available() > 0) {
    decodeInput(getSerial());
  }
  
  // STEERING
  SteeringPos = analogRead(SteeringSensePin); //read in where the actuator is
  SteeringDistance = abs(SteeringGoal-SteeringPos);
  if(SteeringPos < SteeringGoal - threshold) { // always move toward the value
    digitalWrite(SteeringDPin, HIGH);
    analogWrite(SteeringVPin, power);
  } else if (SteeringPos > SteeringGoal + threshold) {
    digitalWrite(SteeringDPin, LOW);
    analogWrite(SteeringVPin, power);
  } else {
    analogWrite(SteeringVPin, 0);
  }
  
  // BRAKING
  BrakingPos = analogRead(BrakingSensePin); //read in where the actuator is
  BrakingDistance = abs(BrakingGoal-BrakingPos);
  if(BrakingPos < BrakingGoal - threshold) { // always move toward the value
    digitalWrite(BrakingDPin, HIGH);
    analogWrite(BrakingVPin, power);
  } else if (BrakingPos > BrakingGoal + threshold) {
    digitalWrite(BrakingDPin, LOW);
    analogWrite(BrakingVPin, power);
  } else {
    analogWrite(BrakingVPin, 0);
  }
  
  // ACCELERATION
  if(angle < AccelerationGoal*2) { // always move toward the value
    gas.write(angle);
    angle++;
  } else if (angle > AccelerationGoal*2) {
    gas.write(angle);
    angle--;
  }
  delay(25);  
}

int getSerial() {
  return Serial.read();
}

int decodeInput(int input) {
  int function = input >> 6; //take only the first 2 bits
  int value = input & 0x3F; //take only the last 6 bits
  if (function == 1) {
    SteeringGoal = value * 16;
  } else if (function == 2) {
      AccelerationGoal = value;
  } else if (function == 3) {
      BrakingGoal = value * 16;
  } else {
    digitalWrite(EnginePin, LOW);
    Serial.println("Killing Engine!");
  }
}
