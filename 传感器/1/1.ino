#include <DHT.h>

#define DHTPIN 8     //DATA接数字引脚4
#define DHTTYPE DHT11   // DHT11
DHT dht(DHTPIN, DHTTYPE);
void setup() {  
Serial.begin(9600);  
Serial.println(F("DHT11 test!"));  dht.begin();
}
void loop() {  
delay(2000); // 各次测量
// 读取温度或湿度需约250毫秒 
 // 传感器读数滞后可达2秒  
float h = dht.readHumidity();  
float t = dht.readTemperature(); 
Serial.print(F("Humidity: "));  Serial.print(h);  
Serial.print(F("%  Temperature: "));  Serial.print(t);  
Serial.println(F("°C "));
}
