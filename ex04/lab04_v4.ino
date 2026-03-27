// 引脚与阈值定义（请放在代码最顶部）
#define TOUCH_PIN 4
#define LED_PIN   2
#define THRESHOLD 600 // 触摸阈值，可根据硬件微调

bool ledState = false;
bool isTouched = false;      // 标记是否正在触摸
unsigned long lastTouchTime = 0;
const unsigned long debounceDelay = 50;  // 防抖延时 50ms

// 改进版中断函数（加入防抖）
void gotTouch() {
  unsigned long now = millis();
  
  // 防抖：距离上次触发不足50ms，直接忽略
  if (now - lastTouchTime < debounceDelay) {
    return;
  }
  lastTouchTime = now;

  int val = touchRead(TOUCH_PIN);
  // 只有从"没触摸"变成"触摸"时，才翻转LED
  if (val < THRESHOLD && !isTouched) {
    ledState = !ledState;
    digitalWrite(LED_PIN, ledState);
    isTouched = true;
  } 
  // 松开时重置标记，不碰LED
  else if (val >= THRESHOLD && isTouched) {
    isTouched = false;
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, ledState);
  touchAttachInterrupt(TOUCH_PIN, gotTouch, THRESHOLD);
}

void loop() {
  delay(100);  // 主循环空转，保持程序运行
}

