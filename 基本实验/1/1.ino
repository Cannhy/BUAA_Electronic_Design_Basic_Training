int button = 9;
int LED = 13;
void setup() {
  // put your setup code here, to run once:
  pinMode(button, INPUT);
  pinMode(LED, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(button) == HIGH) 
    digitalWrite(LED, HIGH);
  else
    digitalWrite(LED, LOW);  
}
