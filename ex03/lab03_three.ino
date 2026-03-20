// lab03: ESP32 三灯同步呼吸灯实验
// 定义3个LED引脚（可根据你的硬件修改，这里用GPIO2、GPIO4、GPIO5示例）
const int ledPin1 = 27;  // 板载LED/第一个灯
const int ledPin2 = 26;  // 第二个灯
const int ledPin3 = 25;  // 第三个灯

// PWM配置（3个灯共用相同参数，保证同步）
const int freq = 5000;
const int resolution = 8;  // 8位分辨率，占空比0-255

void setup() {
  // 为3个引脚分别绑定PWM
  ledcAttach(ledPin1, freq, resolution);
  ledcAttach(ledPin2, freq, resolution);
  ledcAttach(ledPin3, freq, resolution);
  
  Serial.begin(115200);
  Serial.println("lab03: 3-LED Synchronized Breathing Light Start");
}

void loop() {
  // 三灯同步渐亮
  for (int dutyCycle = 0; dutyCycle <= 255; dutyCycle++) {
    ledcWrite(ledPin1, dutyCycle);
    ledcWrite(ledPin2, dutyCycle);
    ledcWrite(ledPin3, dutyCycle);
    delay(10);  // 控制呼吸速度，数值越大越慢
  }
  // 三灯同步渐暗
  for (int dutyCycle = 255; dutyCycle >= 0; dutyCycle--) {
    ledcWrite(ledPin1, dutyCycle);
    ledcWrite(ledPin2, dutyCycle);
    ledcWrite(ledPin3, dutyCycle);
    delay(10);
  }
  
  Serial.println("Synchronized breathing cycle completed");
}
