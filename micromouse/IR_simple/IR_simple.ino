void setup() {
  pinMode(4,INPUT);
  pinMode(13,OUTPUT);
  Serial.begin(9600);
}
void loop() {
  digitalWrite(13, HIGH);
  Serial.println(digitalRead(4));
  delay(1000);
}
