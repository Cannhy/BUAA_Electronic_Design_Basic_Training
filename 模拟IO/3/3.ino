#define led_red 9
#define led_green 10
#define led_blue 11
#define key0 6
#define key1 7
void setup() {
  // put your setup code here, to run once:
  pinMode(led_red, OUTPUT);
  pinMode(led_green, OUTPUT);
  pinMode(led_blue, OUTPUT);
  pinMode(key0, INPUT);
  pinMode(key1, INPUT);
}
int key = -1;
void loop() {
  // put your main code here, to run repeatedly:
 if(digitalRead(key1)==1)
 {
  key = 1;
 }
 if(digitalRead(key0)==1)
 {
  key = 0;
 }
 if(key==0)
 {
  for(int i = 200;i > 0;i--)
  {
    analogWrite(led_red, i);
    analogWrite(led_green, i);
    analogWrite(led_blue, 255);
    delay(10);
      if(digitalRead(key1)==1){break;}
  }
  for(int i = 0;i < 200;i++)
  {
    analogWrite(led_red, 255);
    analogWrite(led_green, i);
    analogWrite(led_blue, i);
    delay(10);
      if(digitalRead(key1)==1){break;}
 }
}

  if(key == 1)
  {
    analogWrite(led_red, 0);
    analogWrite(led_green, 0);
    analogWrite(led_blue, 255);
    delay(500);
    analogWrite(led_red, 255);
    analogWrite(led_green, 0);
    analogWrite(led_blue, 0);
    delay(500);
    analogWrite(led_red, 0);
    analogWrite(led_green, 255);
    analogWrite(led_blue, 0);
    delay(500);
    
  }
}