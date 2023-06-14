String comData = "";
char chr = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  while (Serial.available() > 0) {
    chr = Serial.read();
    comData += chr;
  } 
  if (comData.length() > 0) {
    Serial.print("I have received:");
    Serial.println(comData);
    comData = "";
  }
  delay(200);
}
