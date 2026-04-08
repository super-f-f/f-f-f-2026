#include <WiFi.h>
#include <WebServer.h>

// ===================== 请修改这里的 WiFi 信息 =====================
const char* ssid = "¬¬¬¬¬¬";
const char* password = "zgf666666";
// =================================================================

WebServer server(80);

// 引脚定义
const int LED_PIN = 2;          // 板载LED（GPIO2）
const int TOUCH_PIN = T0;       // 触摸引脚 = GPIO4

// 系统状态
bool isArmed = false;    // 布防状态
bool isAlarming = false; // 报警状态

// 非阻塞计时变量（解决delay卡死问题）
unsigned long previousMillis = 0;
const long blinkInterval = 100; // 闪烁间隔

// 网页HTML代码
String getHTML() {
  String html = "<!DOCTYPE html>";
  html += "<html lang='zh-CN'>";
  html += "<head><meta charset='utf-8'>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1.0'>";
  html += "<title>物联网安防报警器</title>";
  html += "<style>";
  html += "body{text-align:center; font-family:Arial; margin-top:50px; background:#f8f9fa;}";
  html += "h1{color:#2c3e50;}";
  html += ".status{font-size:24px; margin:25px 0; font-weight:bold;}";
  html += ".btn{padding:15px 30px; font-size:20px; margin:10px; border:none; border-radius:10px; cursor:pointer; width:160px;}";
  html += ".arm{background:#e74c3c; color:white;}";
  html += ".disarm{background:#2ecc71; color:white;}";
  html += "</style>";
  html += "</head>";
  html += "<body>";
  html += "<h1>ESP32 安防报警器</h1>";
  
  html += "<div class='status'>当前状态：";
  if (isAlarming) {
    html += "<span style='color:red;'>⚠️ 正在报警！</span>";
  } else if (isArmed) {
    html += "<span style='color:blue;'>✅ 已布防</span>";
  } else {
    html += "<span style='color:gray;'>🛡️ 已撤防</span>";
  }
  html += "</div>";
  
  html += "<a href='/arm'><button class='btn arm'>布防 (Arm)</button></a>";
  html += "<a href='/disarm'><button class='btn disarm'>撤防 (Disarm)</button></a>";
  html += "</body></html>";
  
  return html;
}

// 处理主页
void handleRoot() {
  server.send(200, "text/html", getHTML());
}

// 布防
void handleArm() {
  isArmed = true;
  isAlarming = false;
  digitalWrite(LED_PIN, LOW);
  server.sendHeader("Location", "/", true);
  server.send(302, "text/plain", "");
}

// 撤防
void handleDisarm() {
  isArmed = false;
  isAlarming = false;
  digitalWrite(LED_PIN, LOW);
  server.sendHeader("Location", "/", true);
  server.send(302, "text/plain", "");
}

void setup() {
  Serial.begin(115200);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);

  // 连接WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi 连接成功！");
  Serial.println("IP地址: " + WiFi.localIP().toString());
  
  server.on("/", handleRoot);
  server.on("/arm", handleArm);
  server.on("/disarm", handleDisarm);
  server.begin();
  Serial.println("Web服务器启动");
}

void loop() {
  server.handleClient();

  // ===================== 触摸检测（优化版） =====================
  int touchValue = touchRead(TOUCH_PIN);
  Serial.print("触摸值："); Serial.println(touchValue); // 查看实时值

  // 布防状态下，触摸值 < 30 才触发报警（更稳定）
  if (isArmed && touchValue < 400) {
    isAlarming = true;
  }

  // ===================== 非阻塞LED闪烁（无delay，不卡死） =====================
  if (isAlarming) {
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= blinkInterval) {
      previousMillis = currentMillis;
      digitalWrite(LED_PIN, !digitalRead(LED_PIN)); // 翻转电平
    }
  }
}