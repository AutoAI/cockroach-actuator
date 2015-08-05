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
		decodeSerial();
		
	read in the steering sensor position
	if (steering is not at the goal position) {
		move towards the goal position
		if we are at the goal position, stop
	}
	
	read in the prake sensor position
	if (braking is not at the goal position) {
		move towards the goal position
		if we are at the goal position, stop
	
	}
	if (accelerator is not at the goal position) {
		increment the servo angle towards the goal
		write the current angle to the servo
	}
	
	delay(something small ike 25)
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
	
```
