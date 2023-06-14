int led = 13;
char x = 0;
int cnt = 0;
String str = "";
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(led, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  cnt = Serial.parseInt();
  while (cnt > 0) {
    digitalWrite(led, HIGH);
    delay(500);
    digitalWrite(led, LOW);
    delay(500);
    cnt--;
  }
  /*while (Serial.available() > 0) {
    x = Serial.read();
    if (isDigit(x)) {
      str += x;
    }
  }
  if (str.length() > 0) {
    Serial.print("I have received:");
    Serial.println(str);
    str = "";
  }
  delay(200);*/
}
