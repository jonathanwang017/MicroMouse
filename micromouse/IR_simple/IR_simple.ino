void setup() {
  pinMode(A4,INPUT);
  Serial.begin(9600);
  pinMode(13, OUTPUT);
}
void loop() {
  Serial.println(analogRead(A4));
  digitalWrite(13, HIGH);
  delay(500);
  
}


