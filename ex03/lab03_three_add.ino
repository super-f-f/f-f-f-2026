// lab03: ESP32 三灯同步非线性呼吸灯
const int ledPin1 = 27;
const int ledPin2 =26;
const int ledPin3 =25;

const int freq = 5000;
const int resolution = 8;

void setup() {
  ledcAttach(ledPin1, freq, resolution);
  ledcAttach(ledPin2, freq, resolution);
  ledcAttach(ledPin3, freq, resolution);
  Serial.begin(115200);
  Serial.println("lab03: 3-LED Non-linear Synchronized Breathing Start");
}

void loop() {
  // 正弦函数实现同步柔和呼吸
  for (int i = 0; i < 360; i++) {
    // 正弦函数映射到0-255占空比
    int dutyCycle = (sin(i * PI / 180) + 1) * 127.5;
    ledcWrite(ledPin1, dutyCycle);
    ledcWrite(ledPin2, dutyCycle);
    ledcWrite(ledPin3, dutyCycle);
    delay(10);
  }
  Serial.println("Non-linear synchronized breathing cycle completed");
}
