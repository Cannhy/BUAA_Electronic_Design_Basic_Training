#include <TimerOne.h>
#include "DHT.h"
#define FLITER_N 9
float TempHumdTable[15][11] = { { 331.4313, 334.4107, 337.2659, 340.0071, 342.6441, 345.1864, 347.6434, 350.0246, 352.3395, 354.5979, 356.8101 },
                                { 331.447, 334.4334, 337.2982, 340.0525, 342.707, 345.2724, 347.7595, 350.1796, 352.5442, 354.8655, 357.1564 },
                                { 331.4627, 334.4561, 337.3306, 340.0979, 342.7698, 345.3583, 347.8756, 350.3346, 352.7488, 355.1329, 357.5024 },
                                { 331.4783, 334.4787, 337.3629, 340.1433, 342.8327, 345.4442, 347.9916, 350.4895, 352.9533, 355.4, 357.848 },
                                { 331.494, 334.5014, 337.3952, 340.1887, 342.8955, 345.5302, 348.1076, 350.6443, 353.1577, 355.667, 358.1933 },
                                { 331.5097, 334.5241, 337.4275, 340.234, 342.9584, 345.616, 348.2236, 350.799, 353.3619, 355.9338, 358.5383 },
                                { 331.5253, 334.5468, 337.4598, 340.2794, 343.0212, 345.7019, 348.3395, 350.9537, 353.566, 356.2003, 358.8829 },
                                { 331.541, 334.5694, 337.4921, 340.3248, 343.084, 345.7878, 348.4554, 351.1083, 353.7701, 356.4667, 359.2272 },
                                { 331.5567, 334.5921, 337.5244, 340.3701, 343.1468, 345.8736, 348.5713, 351.2629, 353.9739, 356.7329, 359.5712 },
                                { 331.5723, 334.6148, 337.5567, 340.4155, 343.2096, 345.9594, 348.6871, 351.4174, 354.1777, 356.9988, 359.9148 },
                                { 331.588, 334.6375, 337.589, 340.4608, 343.2724, 346.0452, 348.8028, 351.5718, 354.3814, 357.2646, 360.2581 },
                                { 331.6036, 334.6601, 337.6213, 340.5062, 343.3352, 346.1309, 348.9186, 351.7261, 354.5849, 357.5302, 360.6011 },
                                { 331.6193, 334.6828, 337.6536, 340.5515, 343.3979, 346.2167, 349.0343, 351.8804, 354.7884, 357.7955, 360.9437 },
                                { 331.6349, 334.7054, 337.6859, 340.5968, 343.4607, 346.3024, 349.1499, 352.0346, 354.9917, 358.0607, 361.2861 },
                                { 331.6506, 334.7281, 337.7182, 340.6421, 343.5234, 346.3881, 349.2655, 352.1887, 355.1949, 358.3257, 361.6281 } };
boolean blinkLED = false;
int ledState = LOW;
int echo = 12;
int trig = 13;
int led = 10;
const int sega = 2;
const int segb = 3;
const int segc = 4;
const int segd = 5;
#define key0 A0
#define key1 A1
const int sege = 6;
const int segf = 7;
const int segg = 8;
const int segdp = 9;
const int sensor = 11;
DHT dht(sensor, DHT11);
float distance_cm = 0.0;
  int key = -1;
int mode = 0;
float filter_buf[FLITER_N];
void timerIsr() {
  if (blinkLED) {
    ledState = !ledState;
    digitalWrite(led, ledState);
  }
}
void setup() {
  Serial.begin(9600);     // 初始化串口
  pinMode(echo, INPUT);   // 定义超声波输入脚
  pinMode(trig, OUTPUT);  // 定义超声波输出脚
  pinMode(led, OUTPUT);   // 定义报警输出脚
  pinMode(sega, OUTPUT);
  pinMode(segb, OUTPUT);
  pinMode(segc, OUTPUT);
  pinMode(segd, OUTPUT);
  pinMode(sege, OUTPUT);
  pinMode(segf, OUTPUT);
  pinMode(segg, OUTPUT);
  pinMode(segdp, OUTPUT);
  pinMode(sensor, INPUT);
  pinMode(key0,INPUT);
  pinMode(key1,INPUT); 
  dht.begin();
  Timer1.initialize(50000);
  Timer1.attachInterrupt(timerIsr);
}
void inputData() {
  int i, j;float Hum, Tem, speed;
  for (i = 0; i < FLITER_N; i++) {
    Hum = dht.readHumidity();
    Tem = dht.readTemperature();
    Serial.print("hum:");
    Serial.print(Hum);
    Serial.print("% Tem:");
    Serial.print(Tem);
    Serial.println("°C");
    Hum = (Hum - 10.0) / 5.0;
    Tem = Tem / 5.0;
    speed = TempHumdTable[(int)Hum][(int)Tem];
    Serial.print("speed:");
    Serial.print(speed);
    Serial.println("m/s");
    digitalWrite(trig, LOW);
    delayMicroseconds(2);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);
    distance_cm = (pulseIn(echo, HIGH) / 10000.0) * speed / 2.0;
    distance_cm = (int(distance_cm * 100.0)) / 100.0;
    filter_buf[i] = distance_cm;
    Serial.print("start:");
    Serial.println(distance_cm);
    delay(1);
  }
}

float Filter_Md() {
  int i, j;
  float filter_temp;
  float Hum, Tem, speed;

  for (j = 0; j < FLITER_N - 1; j++) {
    for (i = 0; i < FLITER_N - 1 - j; i++) {
      if (filter_buf[i] > filter_buf[i + 1]) {
        filter_temp = filter_buf[i];
        filter_buf[i] = filter_buf[i + 1];
        filter_buf[i + 1] = filter_temp;
      }
    }
  }
  //Serial.println(filter_buf[(FLITER_N - 1) / 2]);
  return filter_buf[(FLITER_N - 1) / 2];
}

float Filter_Av() {
  int i, j;
  float filter_temp=0.0;
  float Hum, Tem, speed;

  for (int i = 0; i < FLITER_N; i++) {
    filter_temp += filter_buf[i];
  }
  return filter_temp / FLITER_N;
}
void loop() {
  int n[11][8] = {
    { 0, 0, 1, 1, 1, 1, 1, 1 },
    { 0, 0, 0, 0, 0, 1, 1, 0 },
    { 0, 1, 0, 1, 1, 0, 1, 1 },
    { 0, 1, 0, 0, 1, 1, 1, 1 },
    { 0, 1, 1, 0, 0, 1, 1, 0 },
    { 0, 1, 1, 0, 1, 1, 0, 1 },
    { 0, 1, 1, 1, 1, 1, 0, 1 },
    { 0, 0, 0, 0, 0, 1, 1, 1 },
    { 0, 1, 1, 1, 1, 1, 1, 1 },
    { 0, 1, 1, 0, 1, 1, 1, 1 },
    { 1, 0, 0, 0, 0, 0, 0, 0 },
  };
 
  int a, b, c, d;
  float distance_Md, distance_Av, res;
  inputData();
  distance_Md = Filter_Md();
  distance_Av = Filter_Av();
  Serial.print("Md:");
  Serial.print(distance_Md);
  Serial.print(" Av:");
  Serial.println(distance_Av);
  int distance;
    if(digitalRead(key0) == 1){
      key = 0;    
  }
  if(digitalRead(key1) == 1){
      key = 1;    
  }
  if (key == 0) distance = int((distance_Md+0.05)*10);
  else if (key == 1) distance = int((distance_Av+0.05)*10);
  Serial.print("res:");
    if (key == 0) {
      res = distance_Md;
      Serial.println(res);
    } else if (key == 1) {
      res = distance_Av;
      Serial.println(res);      
    }
  a = distance % 10;
  b = distance / 10 % 10;
  c = distance / 100 % 10;
  d = distance / 1000 % 10;
  if (distance_cm < 10.00) {
    blinkLED = true;
  } else  {
    blinkLED = false;
    digitalWrite(led, LOW);
  }
  for (int pin = 2; pin <= 9; pin++) {
    digitalWrite(pin, n[0][9 - pin]);
  }
  delay(400);
  for (int pin = 2; pin <= 9; pin++) {
    digitalWrite(pin, n[d][9 - pin]);
  }
  delay(400);
  for (int pin = 2; pin <= 9; pin++) {
    digitalWrite(pin, n[c][9 - pin]);
  }
  delay(400);
  for (int pin = 2; pin <= 9; pin++) {
    digitalWrite(pin, n[b][9 - pin]);
  }
  delay(400);
  for (int pin = 2; pin <= 9; pin++) {
    digitalWrite(pin, n[10][9 - pin]);
  }
  delay(400);
  for (int pin = 2; pin <= 9; pin++) {
    digitalWrite(pin, n[a][9 - pin]);
  }
  delay(500);
}