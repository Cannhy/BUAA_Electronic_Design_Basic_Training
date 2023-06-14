const int trig = 13;
const int echo = 12;
const int led = 10;
float distance_cm;
void setup() {
  Serial.begin(9600);
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(led, OUTPUT);
}

void loop() {
  digitalWrite(trig, LOW);
  delay(10);
  digitalWrite(trig, HIGH);
  delay(10);
  digitalWrite(trig, LOW);
  distance_cm = pulseIn(echo, HIGH) / 58.8;
  distance_cm = (int (distance_cm * 100.0)) / 100.0;

  if (distance_cm < 10.00) {
    digitalWrite(led, HIGH);
    delay(100);
    digitalWrite(led, LOW);
    delay(100);
  } else {
    digitalWrite(led, LOW);
  }

  Serial.print("Distance:");
  Serial.print(distance_cm);
  Serial.println("cm");
  delay(100);
}
