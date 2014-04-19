const int rightEnable = 19;
const int motor4 = 20;
const int motor3 = 21;
const int leftEnable = 2;
const int motor1 = 3;
const int motor2 = 4;
const int leftEncoderA = 8;
const int leftEncoderB = 9;
const int rightEncoderA = 23;
const int rightEncoderB = 22;

const int led = 13;

volatile int leftEncoderPos;
volatile int rightEncoderPos;

volatile int leftMotorState;
volatile int rightMotorState;

void setup() {
  leftEncoderPos = 0;
  rightEncoderPos = 0;
  leftMotorState = HIGH;
  rightMotorState = HIGH;
  
  pinMode(rightEnable, OUTPUT);
  pinMode(motor3, OUTPUT);
  pinMode(motor4, OUTPUT);
  pinMode(leftEnable, OUTPUT);
  pinMode(motor1, OUTPUT);
  pinMode(motor2, OUTPUT);
  digitalWrite(rightEnable, LOW);
  digitalWrite(leftEnable, LOW);
  Serial.begin(9600);
  
  pinMode(led, OUTPUT);
  digitalWrite(led, HIGH);
  
  pinMode(leftEncoderA, INPUT);
  pinMode(leftEncoderB, INPUT);
  pinMode(rightEncoderA, INPUT);
  pinMode(rightEncoderB, INPUT);
  digitalWrite(leftEncoderA, HIGH);
  digitalWrite(leftEncoderB, HIGH);
  digitalWrite(rightEncoderA, HIGH);
  digitalWrite(rightEncoderB, HIGH);
  
  attachInterrupt(rightEncoderA, checkEncoder, CHANGE);
  
  delay(3000);
  
  moveForward();
  delay(1000);
  moveForward();
  
}

void loop() {
//  digitalWrite(rightEnable, rightMotorState);
//  digitalWrite(leftEnable, leftMotorState);
}

void moveForward() {
  digitalWrite(motor1, HIGH);
  digitalWrite(motor2, LOW);
  digitalWrite(motor3, HIGH);
  digitalWrite(motor4, LOW);
  digitalWrite(rightEnable, HIGH);
  digitalWrite(leftEnable, HIGH);
  delay(215);
  digitalWrite(rightEnable, LOW);
  digitalWrite(leftEnable, LOW);
}

void turnRight() {
  digitalWrite(motor1, HIGH);
  digitalWrite(motor2, LOW);
  digitalWrite(motor3, LOW);
  digitalWrite(motor4, HIGH);
  digitalWrite(rightEnable, HIGH);
  digitalWrite(leftEnable, HIGH);
  delay(95);
  digitalWrite(rightEnable, LOW);
  digitalWrite(leftEnable, LOW);
}

void turnLeft() {
  digitalWrite(motor1, LOW);
  digitalWrite(motor2, HIGH);
  digitalWrite(motor3, HIGH);
  digitalWrite(motor4, LOW);
  digitalWrite(rightEnable, HIGH);
  digitalWrite(leftEnable, HIGH);
  delay(95);
  digitalWrite(rightEnable, LOW);
  digitalWrite(leftEnable, LOW);
}

void checkEncoder() {
  if (digitalRead(rightEncoderA) == HIGH) {   
    if (digitalRead(rightEncoderB) == LOW) {  
      rightEncoderPos--;        
    } 
    else {
      rightEncoderPos++;
    }
  }
  else { 
    if (digitalRead(rightEncoderB) == LOW) {   
      rightEncoderPos++;         
    } 
    else {
      rightEncoderPos--;         
    }
  }
  if (rightEncoderPos == -20) {
    leftMotorState = LOW;
    rightMotorState = LOW;
  }
}
