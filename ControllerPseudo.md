```
//PSEUDOCODE FOR CONTROLLING THE GO-KART

<include servo.h>

final int ENGINEPIN = 7;
final int GASPIN = 6;

final int BRAKEVPIN = 3;
final int BRAKEDPIN = 2;
final int BRAKESENSEPIN = 1;

final int STEERINGVPIN = 5;
final int STEERINGDPIN = 4;
final int STEERINGSENSEPIN = 0;

int steeringPos = 0;
int brakingPos = 0;

int steeringGoal = 512;
int brakingGoal = 0;
int accelerationGoal = 0;

boolean steeringChanged = false;
boolean brakingChanged = false;
boolean accelerationChanged = false;

int power = 255;
int threshold = 25;
int angle = 0;

setup {
	Servo gas; //create the servo object
	gas.attach(GASPIN); //bind it to the throttle pin
	
	pinMode (STEERINGVPIN, OUTPUT); //set all the relevant pins to output
	pinMode (STEERINGDPIN, OUTPUT);
	pinMode (BRAKINGVPIN, OUTPUT);
	pinMode (BRAKINGVPIN, OUTPUT);
	pinMode (ENGINEPIN, OUTPUT);
	
	Serial.begin(9600); //start the serial transmitter
	Serial.println("Initialization Completed.");
}

loop {
	if(serial is available for reading)
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

int decodeInput(int input) {
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
    digitalWrite(enginePin, LOW);
    Serial.println("Killing Engine!");
  }
}

void setSteering(int goal) {
	steeringPos = analogRead(STEERINGSENSEPIN);
	if (steeringPos < goal - threshold) { // always move toward the value
    		digitalWrite(STEERINGDPIN, HIGH);
    		analogWrite(STEERINGVPIN, power);
  	} else if (steeringPos > goal + threshold) {
    		digitalWrite(STEERINGDPIN, LOW);
    		analogWrite(STEERINGVPIN, power);
	} else {
    		analogWrite(STEERINGVPIN, 0);
    		steeringFlag = false;
    	}
}

void setBrake(int goal) {
	brakingPos = analogRead(BRAKINGSENSEPIN);
	if (brakingPos < goal - threshold) { // always move toward the value
    		digitalWrite(BRAKINGDPIN, HIGH);
    		analogWrite(BRAKINGVPIN, power);
  	} else if (brakingPos > goal + threshold) {
    		digitalWrite(BRAKINGDPIN, LOW);
    		analogWrite(BRAKINGVPIN, power);
	} else {
    		analogWrite(BRAKINGVPIN, 0);
    		brakingFlag = false;
    	}
}

void setAcceleration(int goal) {
	if (angle < AccelerationGoal*2) { // always move toward the value
		gas.write(angle);
   		angle++;
  	} else if (angle > AccelerationGoal*2) {
    		gas.write(angle);
    		angle--;
  	}
}
```
