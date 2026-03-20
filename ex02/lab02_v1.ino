// lab02: ESP32 基础LED闪烁控制（优化版）
// 板载LED默认连接GPIO2，可根据开发板修改
const int ledPin = 27;
// 闪烁间隔（单位：ms），1000ms=1秒
const long interval = 1000;

void setup() {
  pinMode(ledPin, OUTPUT);
  Serial.begin(115200);
  Serial.println("=================================");
  Serial.println("lab02: ESP32 LED Blink Experiment");
  Serial.println("LED Pin: " + String(ledPin));
  Serial.println("Blink Interval: " + String(interval) + "ms");
  Serial.println("=================================");
}

void loop() {
  // 点亮LED
  digitalWrite(ledPin, HIGH);
  Serial.println("[INFO] LED State: ON");
  delay(interval);

  // 熄灭LED
  digitalWrite(ledPin, LOW);
  Serial.println("[INFO] LED State: OFF");
  delay(interval);
}
