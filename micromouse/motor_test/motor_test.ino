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

const int led = 13;

int leftEncoderPos = 0;
int rightEncoderPos = 0;

void setup() {
  pinMode(rightEnable, OUTPUT);
  pinMode(motor3, OUTPUT);
  pinMode(motor4, OUTPUT);
  pinMode(leftEnable, OUTPUT);
  pinMode(motor1, OUTPUT);
  pinMode(motor2, OUTPUT);
  digitalWrite(rightEnable, LOW);
  digitalWrite(leftEnable, LOW);
  pinMode(led, OUTPUT);
  digitalWrite(led, HIGH);
  
  pinMode(leftEncoderA, INPUT);
  pinMode(leftEncoderB, INPUT);
  pinMode(rightEncoderA, INPUT);
  pinMode(rightEncoderB, INPUT);
  
  attachInterrupt(leftEncoderA, doLeftEncoder, CHANGE);
  attachInterrupt(rightEncoderA, doRightEncoder, CHANGE);
  
  digitalWrite(rightEnable, HIGH);
  digitalWrite(leftEnable, HIGH);
  digitalWrite(motor1, LOW);
  digitalWrite(motor2, HIGH);
  digitalWrite(motor3, LOW);
  digitalWrite(motor4, HIGH);
}

void loop() {

}

void doLeftEncoder() {
  if (digitalRead(leftEncoderA) == digitalRead(leftEncoderB)) {
    leftEncoderPos++;
  } else {
    leftEncoderPos--;
  }
  
  if (leftEncoderPos == 12) {
    //digitalWrite(leftEnable, LOW);
  }
}

void doRightEncoder() {
  if (digitalRead(rightEncoderA) == digitalRead(rightEncoderB)) {
    rightEncoderPos++;
  } else {
    rightEncoderPos--;
  }
  
  if (rightEncoderPos == 12) {
    //digitalWrite(rightEnable, LOW);
  }
}

