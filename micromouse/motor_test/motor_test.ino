const int rightEnable = 21;
const int motor1 = 20;
const int motor2 = 19;
const int led = 13;

void setup() {
  pinMode(rightEnable, OUTPUT);
  pinMode(motor1, OUTPUT);
  pinMode(motor2, OUTPUT);
  pinMode(led, OUTPUT);
  digitalWrite(led, HIGH);
}

void loop() {
  digitalWrite(motor1, LOW);
  digitalWrite(motor2, HIGH);
  delay(1000);
  digitalWrite(motor1, HIGH);
  digitalWrite(motor2, LOW);
  delay(1000);
}
