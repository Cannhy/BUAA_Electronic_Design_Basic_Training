const int ldrPin = A0;
const int ledPin = 6;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
 
  
  int potVal = analogRead(ldrPin);
  Serial.print("Value= ");
  Serial.println(potVal);
  potVal = potVal / 4;
  analogWrite(ledPin,potVal);
  delay(100);
}