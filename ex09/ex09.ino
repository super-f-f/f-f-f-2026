#include <WiFi.h>
#include <WebServer.h>

// ===================== 请修改你的 WiFi =====================
const char* ssid = "¬¬¬¬¬¬";
const char* password = "zgf666666";
// ==========================================================

WebServer server(80);

// 触摸传感器引脚 T0 = GPIO4
const int TOUCH_PIN = T0;

// 主页（带 AJAX 实时刷新）
String getHTML() {
  String html = "<!DOCTYPE html>";
  html += "<html lang='zh-CN'>";
  html += "<head>";
  html += "<meta charset='UTF-8'>";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1.0'>";
  html += "<title>实时传感器仪表盘</title>";
  html += "<style>";
  html += "body{text-align:center; font-family:Arial; background:#f0f4f8; margin-top:100px;}";
  html += ".title{font-size:32px; color:#2d3436;}";
  html += ".value{font-size:80px; font-weight:bold; color:#e74c3c; margin:50px 0;}";
  html += ".tip{font-size:20px; color:#636e72;}";
  html += "</style>";
  
  // AJAX 定时获取传感器值（核心！）
  html += "<script>";
  html += "function updateValue(){";
  html += "  var xhr = new XMLHttpRequest();";
  html += "  xhr.open('GET','/value',true);";
  html += "  xhr.onload=function(){";
  html += "    if(this.status==200){";
  html += "      document.getElementById('val').innerText = this.responseText;";
  html += "    }";
  html += "  };";
  html += "  xhr.send();";
  html += "}";
  html += "setInterval(updateValue, 100);"; // 每100ms刷新一次
  html += "</script>";
  
  html += "</head>";
  html += "<body>";
  html += "<h1 class='title'>ESP32 实时触摸传感器仪表盘</h1>";
  html += "<div id='val' class='value'>0</div>";
  html += "<p class='tip'>手靠近引脚 → 数值变小 | 手离开 → 数值变大</p>";
  html += "</body></html>";
  return html;
}

// 根路径
void handleRoot() {
  server.send(200, "text/html", getHTML());
}

// 返回传感器纯数值（AJAX 访问）
void handleValue() {
  int val = touchRead(TOUCH_PIN);
  server.send(200, "text/plain", String(val));
}

void setup() {
  Serial.begin(115200);

  // 连接WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi 连接成功");
  Serial.println("IP地址：" + WiFi.localIP().toString());

  // 路由
  server.on("/", handleRoot);
  server.on("/value", handleValue); // 提供数值接口

  server.begin();
}

void loop() {
  server.handleClient();
}