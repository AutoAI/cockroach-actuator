//CODE FOR CONTROLLING THE GO-KART

#include <Servo.h>

const int ENGINE_PIN = 7;
const int GAS_PIN = 6;

const int BRAKING_VELOCITY_PIN = 3;
const int BRAKING_DIRECTION_PIN = 2;
const int BRAKING_SENSE_PIN = 1;

const int STEERING_VELOCITY_PIN = 5;
const int STEERING_DIRECTION_PIN = 4;
const int STEERING_SENSE_PIN = 0;

int steeringPosition = 0;
int brakingPosition = 0;

int steeringGoal = 512;
int brakingGoal = 512;
int accelerationGoal = 0;

boolean steeringChanged = true;
boolean brakingChanged = true;
boolean accelerationChanged = false;

int power = 255;
int threshold = 25;
int angle = 0;

Servo gas;

void setup() {
     //create the servo object
    gas.attach(GAS_PIN); //bind it to the throttle pin

    pinMode (STEERING_VELOCITY_PIN, OUTPUT); //set all the relevant pins to output
    pinMode (STEERING_DIRECTION_PIN, OUTPUT);
    pinMode (BRAKING_VELOCITY_PIN, OUTPUT);
    pinMode (BRAKING_DIRECTION_PIN, OUTPUT);
    pinMode (ENGINE_PIN, OUTPUT);

    Serial.begin(9600); //start the serial transmitter
    digitalWrite (ENGINE_PIN, LOW);
    Serial.println("Initialization Completed.");
}

void loop() {
  
    if(Serial.available())
        decodeInput(Serial.read());

    if (steeringChanged) {
        setSteering(steeringGoal);
    }

    if (brakingChanged) {
        setBrake(brakingGoal);
    }

    if (accelerationChanged) {
        setAcceleration(accelerationGoal);
    }

    delay(10);
}

void decodeInput(int input) {
  int function = input >> 6; //take only the first 2 bits
  int value = input & 0x3F; //take only the last 6 bits
  if (function == 1) {
    steeringGoal = value * 16;
    steeringChanged = true;
  } else if (function == 2) {
      accelerationGoal = value;
      accelerationChanged = true;
  } else if (function == 3) {
      brakingGoal = value * 16;
      brakingChanged = true;
  } else {
    digitalWrite(ENGINE_PIN, HIGH);
    Serial.println("Killing Engine!");
  }
}

void setSteering(int goal) {
    steeringPosition = analogRead(STEERING_SENSE_PIN);
    
    
    if (steeringPosition < goal - threshold) { // always move toward the value
            digitalWrite(STEERING_DIRECTION_PIN, LOW);
            analogWrite(STEERING_VELOCITY_PIN, power);
            Serial.println("Moving from <");
    } else if (steeringPosition > goal + threshold) {
            digitalWrite(STEERING_DIRECTION_PIN, HIGH);
            analogWrite(STEERING_VELOCITY_PIN, power);
            Serial.println("Moving from >");
    } else {
            analogWrite(STEERING_VELOCITY_PIN, 0);
            steeringChanged = false;
            Serial.println("Flag is now false");
    }
    
}

void setBrake(int goal) {
    brakingPosition = analogRead(BRAKING_SENSE_PIN);
            
      if (brakingPosition < goal - threshold) { // always move toward the value
            digitalWrite(BRAKING_DIRECTION_PIN, LOW);
            analogWrite(BRAKING_VELOCITY_PIN, power);
    } else if (brakingPosition > goal + threshold) {
            digitalWrite(BRAKING_DIRECTION_PIN, HIGH);
            analogWrite(BRAKING_VELOCITY_PIN, power);
    } else {
            analogWrite(BRAKING_VELOCITY_PIN, 0);
            brakingChanged = false; 
    }
}

void setAcceleration(int goal) {
    if (angle < goal*2) { // always move toward the value
        gas.write(angle);
        angle++;
    } else if (angle > goal*2) {
            gas.write(angle);
            angle--;
    }
}
