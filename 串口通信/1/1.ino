char x = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (Serial.available() > 0) {
    x = Serial.read();
    Serial.print("I have received:");
    Serial.println(x);
  }
  delay(200);
}
