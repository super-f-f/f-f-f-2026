#include <Arduino.h>

// 引脚定义
#define LED_PIN_A  26   // 第一个LED引脚
#define LED_PIN_B  25   // 第二个LED引脚

// PWM参数
const int freq = 5000;
const int resolution = 8;  // 占空比范围 0~255
int step = 5;              // 渐变步长，控制过渡速度

// 占空比变量
int dutyA = 0;    // LED A的占空比（初始为0，最暗）
int dutyB = 255;  // LED B的占空比（初始为255，最亮）
bool aIncreasing = true;  // LED A的变化方向

void setup() {
  Serial.begin(115200);
  
  // 初始化两个独立PWM通道
  ledcAttach(LED_PIN_A, freq, resolution);
  ledcAttach(LED_PIN_B, freq, resolution);
  
  // 初始状态
  ledcWrite(LED_PIN_A, dutyA);
  ledcWrite(LED_PIN_B, dutyB);
}

void loop() {
  // 更新LED A的占空比
  if (aIncreasing) {
    dutyA += step;
    if (dutyA >= 255) {
      dutyA = 255;
      aIncreasing = false;
    }
  } else {
    dutyA -= step;
    if (dutyA <= 0) {
      dutyA = 0;
      aIncreasing = true;
    }
  }
  
  // LED B的占空比与A反相：dutyB = 255 - dutyA
  dutyB = 255 - dutyA;
  
  // 输出到两个LED
  ledcWrite(LED_PIN_A, dutyA);
  ledcWrite(LED_PIN_B, dutyB);
  
  delay(20);  // 控制渐变速度，数值越小变化越快
}
