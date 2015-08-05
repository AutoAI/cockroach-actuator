```
//CODE FOR CONTROLLING THE GO-KART

<include servo.h>

const int ENGINE_PIN = 7;
const int GAS_PIN = 6;

const int BRAKE_VELOCITY_PIN = 3;
const int BRAKE_DIRECTION_PIN = 2;
const int BRAKE_SENSE_PIN = 1;

const int STEERING_VELOCITY_PIN = 5;
const int STEERING_DIRECTION_PIN = 4;
const int STEERING_SENSE_PIN = 0;

int steeringPosition = 0;
int brakingPosition = 0;

int steeringGoal = 512;
int brakingGoal = 0;
int accelerationGoal = 0;

boolean steeringChanged = false;
boolean brakingChanged = false;
boolean accelerationChanged = false;

int power = 255;
int threshold = 25;
int angle = 0;

void setup {
	Servo gas; //create the servo object
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

void loop {
	if(Serial.available())
		decodeInput(Serial.read());
		
	if (steeringChanged) {
		setSteering(steeringGoal);
	}
	
	if (brakingChanged) {
		setBrake(brakingGoal);
	}
	
	if (accelerationChanged) {
		setAcceleration(acclerationGoal);
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
	if (abs(steeringPosition-goal) <= threshold) {
    		analogWrite(STEERING_VELOCITY_PIN, 0);
    		steeringChanged = false;
	} else if (steeringPosition < goal) { // always move toward the value
    		digitalWrite(STEERING_DIRECTION_PIN, HIGH);
    		analogWrite(STEERING_VELOCITY_PIN, power);
  	} else {
    		digitalWrite(STEERING_DIRECTION_PIN, LOW);
    		analogWrite(STEERING_VELOCITY_PIN, power);
	} 
}

void setBrake(int goal) {
	brakingPosition = analogRead(BRAKING_SENSE_PIN);
	if (abs(brakingPosition-goal) <= threshold) {
    		analogWrite(BRAKING_VELOCITY_PIN, 0);
    		brakingChanged = false;	
	} else if (brakingPosition < goal) { // always move toward the value
    		digitalWrite(BRAKING_DIRECTION_PIN, HIGH);
    		analogWrite(BRAKING_VELOCITY_PIN, power);
  	} else {
    		digitalWrite(BRAKING_DIRECTION_PIN, LOW);
    		analogWrite(BRAKING_VELOCITY_PIN, power);
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
```
