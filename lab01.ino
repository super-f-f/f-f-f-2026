#define LED_PIN 2

void setup() {
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_PIN, HIGH);
  delay(500);  // 从 1000 改成 500，0. 5 秒
  digitalWrite(LED_PIN, LOW);
  delay(500);  // 灭 0.5 秒
}