int out = 13;
void setup() {
  // put your setup code here, to run once:
  pinMode(out, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(out, HIGH);
  delay(1000);
  digitalWrite(out, LOW);
  delay(1000);
}
