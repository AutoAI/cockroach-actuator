```
//PSEUDOCODE FOR CONTROLLING THE GO-KART

<include servo lib>

bind pins for all outputs
create gas servo

setup {
	start the serial com port
	attach the gas servo
}

loop {
	if(serial is available for reading)
		decodeInput(read in serial);
		
	if (steeringFlag) {
		read in the steering sensor position
		if (steering is not at the goal position) {
			move towards the goal position
			if we are at the goal position, stop and set the steeringFlag to false
		}
	}
	
	if (brakingFlag) {
		read in the prake sensor position
		if (braking is not at the goal position) {
			move towards the goal position
			if we are at the goal position, stop and set the brakingFlag to false
		}
	}
	
	if (accelerationFlag) {
		if (accelerator is not at the goal position) {
			increment the servo angle towards the goal
			write the current angle to the servo
			if we are at the goal position, set the accelerationFlag to false
		}
	}
	
	delay(something small like 10)
}

int decodeInput(int input) {
  int function = input >> 6; //take only the first 2 bits
  int value = input & 0x3F; //take only the last 6 bits
  if (function == 1) {
    steeringGoal = value * 16;
    steeringFlag = true;
  } else if (function == 2) {
      accelerationGoal = value;
      accelerationFlag = true;
  } else if (function == 3) {
      brakingGoal = value * 16;
      brakingFlag = true;
  } else {
    digitalWrite(enginePin, LOW);
    Serial.println("Killing Engine!");
  }
}
	
```
