const int outPort1 = 3; // 输出波形1：3口
const int outPort2 = 5; // 输出波形1：5口
const int outPort3 = 6; // 输出波形1：6口
const int ldrPin1 = A1; // 检测波形1：A1口
const int ldrPin2 = A2; // 检测波形2：A2口
const int ldrPin3 = A3; // 检测波形3：A3口
int ii = 0; // 周期循环变量
int i = 0; //
int j = 0; //
int k = 0; //
int PRI = 512-1; // 基准脉冲重复周期
int K0 = 1; // 信号1波数
int K1 = 2; // 信号2波数
int K2 = 4; // 信号3波数
int bis1 = -1024; // 信号1绘图偏置
int bis2 = 0; // 信号2绘图偏置
int bis3 = 1024; // 信号3绘图偏置
int value = 0; // 输出至串口的值
void setup() {
  // put your setup code here, to run once:
  pinMode(outPort1, OUTPUT); // 输出口1
pinMode(outPort2, OUTPUT); // 输出口2
pinMode(outPort3, OUTPUT); // 输出口3
Serial.begin(115200); // 打开串口
}

void loop() {
for(ii = 0; ii <= PRI; ii += 1) {
// 原始波形1：三角窗，周期PRI/K0
i = 2*K0*ii/PRI;
if(i%2 == 0)
value = 2*K0*ii%PRI; // 上升沿
else
value = PRI-2*K0*ii%PRI; // 下降沿
analogWrite(outPort1, value); // 输出端口
Serial.print(value+bis1);Serial.print(","); // 原始波形1，
// 原始波形2：三角窗，周期PRI/K1
j = 2*K1*ii/PRI;
if(j%2 == 0)
value = 2*K1*ii%PRI; // 上升沿
else
value = PRI-2*K1*ii%PRI; // 下降沿
analogWrite(outPort2, value); // 输出端口
Serial.print(value+bis2);Serial.print(","); // 原始波形2，
k = 2*K2*ii/PRI;
if (k%2 == 0)
value = 2*K2*ii%PRI; // 上升沿
else
value = PRI-2*K2*ii%PRI; // 下降沿
analogWrite(outPort3, value); // 输出端口
Serial.print(value+bis3);Serial.print(","); // 原始波形3，
// 测量波形1
value = analogRead(ldrPin1)/2;
Serial.print(value+bis1);Serial.print(","); // 数据中止补
// 测量波形2
value = analogRead(ldrPin2)/2;
Serial.print(value+bis2);Serial.print(","); // 数据中止补
// 测量波形3
value = analogRead(ldrPin3)/2;
Serial.print(value+bis3);Serial.print("\n"); // 本行数据结
delay(10);
}
delay(10);
}
