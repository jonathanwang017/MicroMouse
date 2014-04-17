const int rightEnable = 19;
const int motor4 = 20;
const int motor3 = 21;
const int leftEnable = 2;
const int motor1 = 3;
const int motor2 = 4;
const int leftEncoderA = 9;
const int leftEncoderB = 8;
const int rightEncoderA = 22;
const int rightEncoderB = 23;

void setup() {
  pinMode(A4, INPUT);
  Serial.begin(9600);
  pinMode(rightEnable, OUTPUT);
  pinMode(motor3, OUTPUT);
  pinMode(motor4, OUTPUT);
  pinMode(leftEnable, OUTPUT);
  pinMode(motor1, OUTPUT);
  pinMode(motor2, OUTPUT);
  
  digitalWrite(rightEnable, HIGH);
  digitalWrite(leftEnable, HIGH);
  digitalWrite(motor1, LOW);
  digitalWrite(motor2, HIGH);
  digitalWrite(motor3, HIGH);
  digitalWrite(motor4, LOW);
}
void loop() {
//  if (analogRead(A4) < 1000) {
//    digitalWrite(rightEnable, LOW);
//    digitalWrite(leftEnable, LOW);
//  }
}


