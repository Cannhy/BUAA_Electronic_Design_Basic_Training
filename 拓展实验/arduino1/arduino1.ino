#include <Servo.h>
Servo myservo;
int val;

void setup() {
  // put your setup code here, to run once:
  myservo.attach(7); Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("Servo:");
  Serial.print(val);
  delay(15);
  val = analogRead(A0);
  val = map(val, 0, 1023, 0, 180);
  myservo.write(val);
  delay(15);
}
