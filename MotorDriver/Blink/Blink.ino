int brakeDirection = 2;
int brakeVelocity = 3;

int steeringDirection = 4;
int steeringVelocity = 5;

void setup() {                
  pinMode(steeringDirection, OUTPUT);
  pinMode(steeringVelocity, OUTPUT);
  
  pinMode(brakeDirection, OUTPUT);
  pinMode(brakeVelocity, OUTPUT);
  
  digitalWrite(brakeVelocity, HIGH);
  digitalWrite(steeringVelocity, HIGH);
}

void loop() {
  digitalWrite(steeringDirection, HIGH);
  digitalWrite(brakeDirection, LOW);
  delay(500);
  digitalWrite(steeringDirection, LOW);
  digitalWrite(brakeDirection, HIGHT);
  delay(500);
}
