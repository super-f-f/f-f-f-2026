// lab02: ESP32 基础LED闪烁控制（最终版）
// 实验目标：掌握ESP32 GPIO输出控制，实现LED基础闪烁
// 硬件：ESP32开发板，板载LED连接GPIO2
// 作者：你的名字
// 日期：2026-03-20

const int ledPin = 27;          // LED引脚定义
const long blinkInterval = 1000; // 闪烁间隔（ms）

void setup() {
  // 配置GPIO为输出模式
  pinMode(ledPin, OUTPUT);
  // 初始化串口，用于调试
  Serial.begin(115200);
  
  // 实验启动信息
  Serial.println("=====================================");
  Serial.println("  Embedded System Design - lab02");
  Serial.println("  Basic IO Experiment: LED Blink");
  Serial.println("  LED Pin: GPIO" + String(ledPin));
  Serial.println("  Blink Frequency: 1Hz (1s ON, 1s OFF)");
  Serial.println("=====================================");
}

void loop() {
  // 点亮LED
  digitalWrite(ledPin, HIGH);
  Serial.println("[STATUS] LED -> ON");
  delay(blinkInterval);

  // 熄灭LED
  digitalWrite(ledPin, LOW);
  Serial.println("[STATUS] LED -> OFF");
  delay(blinkInterval);
}
