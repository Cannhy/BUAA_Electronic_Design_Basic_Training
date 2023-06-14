#define speaker 3
unsigned int duration = 1000;
int button = 2;

void setup(){
pinMode(button,INPUT);
uint32_t fTransmit = 1000;// KHZ
TCCR1A = 0b01000000;
TCCR1B = 0b00001001; // CTC模式
OCR1A = F_CPU / (2000* fTransmit) - 1;
pinMode (9 ,OUTPUT);
//OCRIA为整型，所以实际载波频率与预设可能不同
char strbuf [255];
sprintf(strbuf,"设置载波频率：%d KHz",(F_CPU / (2* (1+OCR1A))/ 1000));
Serial.println(strbuf);
}
void loop(){
if(digitalRead(button)== HIGH){
tone(speaker,1000,duration);
}
}