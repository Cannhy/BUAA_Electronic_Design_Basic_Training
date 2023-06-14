int duration=1000;
int d=100, b;
int das=3*d;
void setup() {
  Serial.begin(9600);
  uint32_t fTransmit = 1000;
  TCCR1A = 0b01000000;
  TCCR1B = 0b00001001;
  OCR1A = F_CPU / (2000*fTransmit)-1;
  pinMode(9,OUTPUT);
  pinMode(2,INPUT);
  pinMode(3,OUTPUT);
}
void dot(){
  tone(3,duration);
  delay(d);
  noTone(3);
}
void dash()
{
  tone(3,duration);
  delay(das);
  noTone(3);
}
void loop() {
  if(Serial.available()>0){
    char data=Serial.read();
    switch(data)
    {
    case 'A':
    Serial.println(".-");
    dot();dash();
    delay(3*d);
    break;
    case 'B':
    Serial.println("-...");
    dash();dot();dot();dot();
    delay(3*d);
    break;
    case 'U':
    Serial.println("..-");
    dot();dot();dash();
    delay(3*d);
    break;
    case 'C':
    Serial.println("-.-.");
    dash();dot();dash();dot();
    break;
    case 'N':
    Serial.println("-.");
    dash();dot();
    break;
    case ' ':
    delay(7*d);
    break;
    }
  }
  if(digitalRead(2)==HIGH){
    tone(3,2000);
  } 
  else{
    noTone(3);
  }
}