unsigned long i, j;
int led = 13, flag = 0, button = 9, state = 0;
void setup() {
  // put your setup code here, to run once:
  pinMode(button, INPUT);
  pinMode(led, OUTPUT);
  i = millis();
}

void loop() {
  // put your main code here, to run repeatedly:
  j = millis();
  if (digitalRead(button) == HIGH) {
    if ((j - i) > 100 && (flag == 0)) {
    digitalWrite(led, HIGH);
    i = j;
    flag = 1;
  }
    else if ((j - i) > 100 && (flag == 1)) {
    digitalWrite(led, LOW);
    i = j;
    flag = 0;
    }
  } else {
    if ((j - i) > 1000 && (flag == 0)) {
    digitalWrite(led, HIGH);
    i = j;
    flag = 1;
  }
    else if ((j - i) > 1000 && (flag == 1)) {
    digitalWrite(led, LOW);
    i = j;
    flag = 0;
    }
  }
}