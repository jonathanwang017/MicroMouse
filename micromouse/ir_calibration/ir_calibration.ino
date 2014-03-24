int emitter = 3;
int receiver = 5;
int led = 13;
int buttonState = 0;

void setup() {
  pinMode(led, OUTPUT);
  pinMode(emitter, OUTPUT);  
  pinMode(receiver, INPUT);
  Serial.begin(57600);
}
int irRead(int readPin, int triggerPin)
{
  int halfPeriod = 1000; //one period at 38.5khZ is aproximately 26 microseconds
  digitalWrite(triggerPin, HIGH); 
  delay(halfPeriod);
  int received = 0;
  received = digitalRead(readPin);
  digitalWrite(triggerPin, LOW); 
  delay(halfPeriod - 1);     // - 1 to make up for digitaWrite overhead    
  return received;
}
void testButton() {
  buttonState = digitalRead(receiver);
  if (buttonState == HIGH) {
    digitalWrite(emitter, HIGH);
  }
  else if (buttonState == LOW) {
    digitalWrite(emitter, LOW);
  }
}
void loop() {
  Serial.println(irRead(receiver, emitter));
  delay(1000);
}
