const int led = 13;
const int rightEnable = 19;
const int motor4 = 20;
const int motor3 = 21;
const int leftEnable = 2;
const int motor1 = 3;
const int motor2 = 4;

void setup() {
  pinMode(A4, INPUT);
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  pinMode(rightEnable, OUTPUT);
  pinMode(motor3, OUTPUT);
  pinMode(motor4, OUTPUT);
  pinMode(leftEnable, OUTPUT);
  pinMode(motor1, OUTPUT);
  pinMode(motor2, OUTPUT);
  
  digitalWrite(led, HIGH);

  digitalWrite(motor1, HIGH);
  digitalWrite(motor2, LOW);
  digitalWrite(motor3, HIGH);
  digitalWrite(motor4, LOW);
  digitalWrite(rightEnable, LOW);
  digitalWrite(leftEnable, LOW);
  delay(3000);
  
  digitalWrite(rightEnable, HIGH);
  digitalWrite(leftEnable, HIGH);
}

void loop() {
  if (analogRead(A4) < 900) {
    digitalWrite(rightEnable, LOW);
    digitalWrite(leftEnable, LOW);
  }
}


