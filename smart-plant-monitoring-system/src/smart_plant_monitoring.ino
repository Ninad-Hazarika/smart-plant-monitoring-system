#include <WiFi.h>
#include <WebServer.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <DHT.h>

// ================= WIFI =================
const char* ssid     = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

WebServer server(80);

// ================= TELEGRAM =================
String botToken = "YOUR_BOT_TOKEN";
String chatID   = "YOUR_CHAT_ID";

// ================= OLED =================
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// ================= PINS =================
#define DHTPIN      13
#define DHTTYPE     DHT11
#define SOIL_PIN    34
#define RELAY_PIN   15
#define TRIG_PIN    26
#define ECHO_PIN    25
#define BUZZER_PIN  27
#define IR_PIN      33
#define TOUCH_PIN   32

DHT dht(DHTPIN, DHTTYPE);

// ================= SETTINGS =================
int   threshold  = 3000;   // ADC value above which soil is "dry"
float tankHeight = 13.7;   // Height of water tank in cm

#define RELAY_ON  LOW
#define RELAY_OFF HIGH

// 0 = AUTO, 1 = MANUAL ON, 2 = MANUAL OFF
int pumpMode = 0;

// ================= SENSOR VALUES =================
int   soilValue  = 0;
float temperature = 0;
float humidity   = 0;
float waterLevel = 0;
bool  pumpState  = false;

// ================= TIMERS =================
unsigned long lastSensorRead      = 0;
unsigned long lastTelegramAlert   = 0;
unsigned long telegramCooldown    = 30000;
unsigned long lastHumanAlertTime  = 0;
unsigned long humanAlertCooldown  = 5000;
unsigned long pumpStartTime       = 0;
unsigned long dryStartTime        = 0;

bool lowWaterAlertSent  = false;
bool pumpLongAlertSent  = false;
bool thirstyAlertSent   = false;

int  humanDetectCount = 0;

// ================= OLED EMOTION ENGINE =================
enum Emotion { NONE, GREETING, HAPPY, SAD, LAUGHING, SLEEPY };

Emotion       currentEmotion  = NONE;
unsigned long emotionUntil    = 0;
unsigned long lastHumanSeen   = 0;
unsigned long lastSadReminder = 0;
unsigned long lastTouchTime   = 0;
int           touchCount      = 0;
bool          lastTouchState  = LOW;
bool          lastIRState     = HIGH;

// ================= URL ENCODE =================
String urlEncode(String text) {
  text.replace("%",  "%25");
  text.replace(" ",  "%20");
  text.replace("\n", "%0A");
  text.replace(":",  "%3A");
  text.replace("/",  "%2F");
  text.replace("?",  "%3F");
  text.replace("&",  "%26");
  return text;
}

// ================= TELEGRAM =================
void sendTelegramMessage(String message) {
  if (WiFi.status() != WL_CONNECTED) return;

  WiFiClientSecure client;
  client.setInsecure();

  HTTPClient https;
  https.setTimeout(15000);

  String url = "https://api.telegram.org/bot" + botToken +
               "/sendMessage?chat_id=" + chatID +
               "&text=" + urlEncode(message);

  if (!https.begin(client, url.c_str())) {
    Serial.println("HTTPS begin failed");
    return;
  }

  int httpCode = https.GET();
  Serial.print("Telegram response: ");
  Serial.println(httpCode);
  https.end();
}

// ================= WEB DASHBOARD =================
String makeWebPage() {
  String pumpText = pumpState ? "Pump is ON" : "Pump is OFF";
  String modeText;
  if      (pumpMode == 0) modeText = "AUTO MODE";
  else if (pumpMode == 1) modeText = "MANUAL ON";
  else                    modeText = "MANUAL OFF";

  String html = R"rawliteral(
<!DOCTYPE html><html>
<head>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1">
<title>Smart Plant Dashboard</title>
<style>
*{box-sizing:border-box;margin:0;padding:0}
body{font-family:Arial,sans-serif;background:#0d1f1a;color:#e8f5e9;min-height:100vh}
.topbar{background:#0a2e20;border-bottom:1px solid #1a4a30;padding:14px 20px;display:flex;align-items:center;justify-content:space-between}
.topbar-title{font-size:18px;font-weight:700;letter-spacing:1px;color:#4caf80}
.topbar-ip{font-size:12px;color:#6a9a80;font-family:monospace}
.main{padding:16px}
.section-label{font-size:11px;letter-spacing:2px;color:#6a9a80;text-transform:uppercase;margin:18px 0 10px}
.grid2{display:grid;grid-template-columns:1fr 1fr;gap:12px}
.card{background:#0f2e1e;border:1px solid #1e4a30;border-radius:16px;padding:16px}
.card-label{font-size:11px;color:#6a9a80;letter-spacing:1px;text-transform:uppercase}
.card-value{font-size:28px;font-weight:700;margin-top:4px;color:#e8f5e9}
.card-unit{font-size:14px;color:#6a9a80;font-weight:400}
.progress-bar{height:5px;border-radius:3px;background:#1a3a28;margin-top:10px;overflow:hidden}
.progress-fill{height:100%;border-radius:3px}
.pump-card{background:#0f2e1e;border:1px solid #1e4a30;border-radius:16px;padding:18px}
.pump-label{font-size:18px;font-weight:700}
.pump-sub{font-size:13px;color:#6a9a80;margin-top:4px}
.btn-row{display:flex;gap:10px;margin-top:14px}
.btn{flex:1;padding:12px 8px;border:none;border-radius:40px;font-size:14px;font-weight:600;text-decoration:none;text-align:center;color:white}
.btn-on{background:#27ae60}.btn-off{background:#c0392b}.btn-auto{background:#2980b9}
.warn-box{background:#2a1a00;border:1px solid #5a3800;border-radius:12px;padding:12px;margin-top:12px;font-size:13px;color:#f0a000}
.ok-box{background:#0a2e14;border:1px solid #1a5a28;border-radius:12px;padding:12px;margin-top:12px;font-size:13px;color:#4caf80}
.footer{text-align:center;font-size:12px;color:#3a6a50;padding:18px 0 10px}
</style>
</head>
<body>
<div class="topbar">
<div class="topbar-title">SMART PLANT DASHBOARD</div>
<div class="topbar-ip">)rawliteral";

  html += WiFi.localIP().toString();

  html += R"rawliteral(</div></div>
<div class="main">
<div class="section-label">Sensors</div>
<div class="grid2">)rawliteral";

  int soilPct = map(constrain(soilValue, 0, 4095), 0, 4095, 100, 0);
  html += "<div class='card'><div class='card-label'>Soil Moisture</div>";
  html += "<div class='card-value'>" + String(soilValue) + "<span class='card-unit'>/4095</span></div>";
  html += "<div class='progress-bar'><div class='progress-fill' style='width:" + String(soilPct) + "%;background:#27ae60'></div></div></div>";

  int tempPct = constrain(map((int)temperature, 0, 50, 0, 100), 0, 100);
  html += "<div class='card'><div class='card-label'>Temperature</div>";
  html += "<div class='card-value'>" + String(temperature, 1) + "<span class='card-unit'> C</span></div>";
  html += "<div class='progress-bar'><div class='progress-fill' style='width:" + String(tempPct) + "%;background:#e67e22'></div></div></div>";

  int humPct = constrain((int)humidity, 0, 100);
  html += "<div class='card'><div class='card-label'>Humidity</div>";
  html += "<div class='card-value'>" + String(humidity, 1) + "<span class='card-unit'> %</span></div>";
  html += "<div class='progress-bar'><div class='progress-fill' style='width:" + String(humPct) + "%;background:#2980b9'></div></div></div>";

  html += "<div class='card'><div class='card-label'>Water Level</div>";
  if (waterLevel == -1) {
    html += "<div class='card-value' style='font-size:18px;color:#888'>No Echo</div>";
  } else {
    int waterPct = constrain((int)((waterLevel / tankHeight) * 100), 0, 100);
    html += "<div class='card-value'>" + String(waterLevel, 1) + "<span class='card-unit'> cm</span></div>";
    html += "<div class='progress-bar'><div class='progress-fill' style='width:" + String(waterPct) + "%;background:#3498db'></div></div>";
  }
  html += "</div></div>";

  html += "<div class='section-label'>Pump Control</div>";
  html += "<div class='pump-card'>";
  html += "<div class='pump-label'>" + pumpText + "</div>";
  html += "<div class='pump-sub'>" + modeText + "</div>";

  if (waterLevel != -1 && waterLevel <= 3)
    html += "<div class='warn-box'>⚠ Water tank is low — refill soon</div>";
  else
    html += "<div class='ok-box'>✅ System running normally</div>";

  html += "<div class='btn-row'>";
  html += "<a href='/pump/on'   class='btn btn-on'>ON</a>";
  html += "<a href='/pump/off'  class='btn btn-off'>OFF</a>";
  html += "<a href='/pump/auto' class='btn btn-auto'>AUTO</a>";
  html += "</div></div>";

  html += "<div class='footer'>Auto-refreshes every 2 seconds</div>";
  html += R"rawliteral(</div>
<script>setTimeout(function(){location.reload();},2000);</script>
</body></html>)rawliteral";

  return html;
}

// ================= WEB HANDLERS =================
void handleRoot()    { server.send(200, "text/html", makeWebPage()); }
void handlePumpOn()  { pumpMode = 1; currentEmotion = HAPPY; emotionUntil = millis() + 3000; server.sendHeader("Location", "/"); server.send(303); }
void handlePumpOff() { pumpMode = 2; server.sendHeader("Location", "/"); server.send(303); }
void handleAuto()    { pumpMode = 0; server.sendHeader("Location", "/"); server.send(303); }

// ================= SENSOR READS =================
void readSoil() { soilValue = analogRead(SOIL_PIN); }

void readDHT() {
  float t = dht.readTemperature();
  float h = dht.readHumidity();
  if (!isnan(t)) temperature = t;
  if (!isnan(h)) humidity = h;
}

void readWaterLevel() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH, 30000);
  if (duration == 0) { waterLevel = -1; return; }

  float distance = duration * 0.034 / 2;
  waterLevel = tankHeight - distance;
  if (waterLevel < 0) waterLevel = 0;
}

// ================= PUMP CONTROL =================
void controlPump() {
  bool oldState = pumpState;

  if      (pumpMode == 1) { digitalWrite(RELAY_PIN, RELAY_ON);  pumpState = true;  }
  else if (pumpMode == 2) { digitalWrite(RELAY_PIN, RELAY_OFF); pumpState = false; }
  else {
    if (soilValue > threshold) { digitalWrite(RELAY_PIN, RELAY_ON);  pumpState = true;  }
    else                       { digitalWrite(RELAY_PIN, RELAY_OFF); pumpState = false; }
  }

  if (!oldState && pumpState) { currentEmotion = HAPPY; emotionUntil = millis() + 3000; }
}

// ================= BUZZER =================
void checkTankLevel() {
  if (waterLevel == -1) { digitalWrite(BUZZER_PIN, LOW); return; }
  if (waterLevel <= 3)  { digitalWrite(BUZZER_PIN, HIGH); delay(80); digitalWrite(BUZZER_PIN, LOW); }
  else                  { digitalWrite(BUZZER_PIN, LOW); }
}

// ================= IR + TOUCH =================
void handleIR() {
  bool irState = digitalRead(IR_PIN);
  if (irState == LOW) {
    lastHumanSeen = millis();
    if (lastIRState == HIGH) { currentEmotion = GREETING; emotionUntil = millis() + 3000; }
  }
  lastIRState = irState;
}

void handleTouch() {
  bool touchState = digitalRead(TOUCH_PIN);
  if (touchState == HIGH && lastTouchState == LOW) {
    if (millis() - lastTouchTime < 900) touchCount++;
    else touchCount = 1;
    lastTouchTime = millis();
    if (touchCount >= 3) { currentEmotion = LAUGHING; emotionUntil = millis() + 5000; touchCount = 0; }
  }
  lastTouchState = touchState;
}

// ================= OLED DRAWING =================
void drawOpenEyes()   { display.fillCircle(38,22,12,WHITE); display.fillCircle(90,22,12,WHITE); display.fillCircle(38,22,5,BLACK); display.fillCircle(90,22,5,BLACK); display.fillCircle(34,18,2,WHITE); display.fillCircle(86,18,2,WHITE); }
void drawHappyEyes()  { display.drawLine(28,25,36,17,WHITE); display.drawLine(36,17,46,25,WHITE); display.drawLine(78,25,86,17,WHITE); display.drawLine(86,17,96,25,WHITE); }
void drawSadEyes()    { display.drawLine(26,18,46,26,WHITE); display.drawLine(78,26,98,18,WHITE); display.fillCircle(38,34,2,WHITE); display.fillCircle(90,34,2,WHITE); }
void drawSleepyEyes() { display.drawLine(25,24,48,24,WHITE); display.drawLine(78,24,101,24,WHITE); display.setCursor(96,6); display.print("Z"); display.setCursor(106,0); display.print("z"); }
void drawLaughEyes()  { display.drawLine(28,27,36,17,WHITE); display.drawLine(36,17,46,27,WHITE); display.drawLine(78,27,86,17,WHITE); display.drawLine(86,17,96,27,WHITE); display.drawLine(50,40,58,46,WHITE); display.drawLine(58,46,70,46,WHITE); display.drawLine(70,46,78,40,WHITE); }

void showEmotion() {
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);

  if      (currentEmotion == GREETING) { drawOpenEyes();   display.setCursor(43,48); display.print("Hello!"); }
  else if (currentEmotion == HAPPY)    { drawHappyEyes();  display.setCursor(22,48); display.print("Ahh... Water!"); }
  else if (currentEmotion == SAD)      { drawSadEyes();    display.setCursor(25,48); display.print("I'm thirsty"); }
  else if (currentEmotion == LAUGHING) { drawLaughEyes();  display.setCursor(38,54); display.print("Hehehe!"); }
  else if (currentEmotion == SLEEPY)   { drawSleepyEyes(); display.setCursor(48,48); display.print("Zzz..."); }

  display.display();
}

void showSensorData() {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);

  display.setCursor(0, 0);  display.print("Soil: ");  display.println(soilValue);
  display.setCursor(0,13);  display.print("Water: ");
  if (waterLevel == -1)     display.println("No Echo");
  else                      { display.print(waterLevel,1); display.println(" cm"); }
  display.setCursor(0,26);  display.print("Temp: ");  display.print(temperature,1); display.println(" C");
  display.setCursor(0,39);  display.print("Hum: ");   display.print(humidity,1);    display.println(" %");
  display.setCursor(0,52);  display.print("Pump: ");  display.print(pumpState ? "ON" : "OFF");
  display.display();
}

void updateOLED() {
  if (currentEmotion != NONE) {
    showEmotion();
    if (millis() > emotionUntil) currentEmotion = NONE;
  } else {
    showSensorData();
  }
}

// ================= TELEGRAM ALERTS =================
void checkTelegramAlerts() {
  if (millis() - lastTelegramAlert >= telegramCooldown) {
    if (waterLevel != -1 && waterLevel <= 3 && !lowWaterAlertSent) {
      sendTelegramMessage("💧 LOW WATER ALERT: Tank level below 3 cm. Please refill.");
      lowWaterAlertSent = true; lastTelegramAlert = millis();
    }
    if (waterLevel > 5) lowWaterAlertSent = false;

    if (pumpState) {
      if (pumpStartTime == 0) pumpStartTime = millis();
      if (millis() - pumpStartTime > 60000 && !pumpLongAlertSent) {
        sendTelegramMessage("⚠️ WARNING: Pump has been running for over 60 seconds.");
        pumpLongAlertSent = true; lastTelegramAlert = millis();
      }
    } else { pumpStartTime = 0; pumpLongAlertSent = false; }

    if (soilValue > threshold && !pumpState) {
      if (dryStartTime == 0) dryStartTime = millis();
      if (millis() - dryStartTime > 60000 && !thirstyAlertSent) {
        sendTelegramMessage("🌵 PLANT THIRSTY: Soil is dry but pump is OFF. Check system.");
        thirstyAlertSent = true; lastTelegramAlert = millis();
      }
    } else { dryStartTime = 0; thirstyAlertSent = false; }
  }

  if (digitalRead(IR_PIN) == LOW) {
    humanDetectCount++;
    if (humanDetectCount >= 2 && millis() - lastHumanAlertTime > humanAlertCooldown) {
      sendTelegramMessage("👤 HUMAN DETECTED near your plant.");
      lastHumanAlertTime = millis(); humanDetectCount = 0;
    }
  } else { humanDetectCount = 0; }
}

// ================= SETUP =================
void setup() {
  Serial.begin(115200);

  pinMode(RELAY_PIN,  OUTPUT); digitalWrite(RELAY_PIN, RELAY_OFF);
  pinMode(BUZZER_PIN, OUTPUT); digitalWrite(BUZZER_PIN, LOW);
  pinMode(SOIL_PIN,   INPUT);
  pinMode(TRIG_PIN,   OUTPUT);
  pinMode(ECHO_PIN,   INPUT);
  pinMode(IR_PIN,     INPUT);
  pinMode(TOUCH_PIN,  INPUT);

  dht.begin();

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED failed — check wiring and I2C address");
    while (1);
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 20);
  display.println("Smart Plant");
  display.println("Starting...");
  display.display();

  WiFi.begin(ssid, password);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) { delay(500); Serial.print("."); }

  Serial.println();
  Serial.println("WiFi Connected!");
  Serial.print("Dashboard: http://");
  Serial.println(WiFi.localIP());

  configTime(0, 0, "pool.ntp.org", "time.nist.gov");
  delay(3000);

  server.on("/",          handleRoot);
  server.on("/pump/on",   handlePumpOn);
  server.on("/pump/off",  handlePumpOff);
  server.on("/pump/auto", handleAuto);
  server.begin();

  lastHumanSeen = millis();
  sendTelegramMessage("✅ SMART_PLANT_SYSTEM_ONLINE\nDashboard: http://" + WiFi.localIP().toString());
}

// ================= LOOP =================
void loop() {
  server.handleClient();
  handleIR();
  handleTouch();

  if (millis() - lastSensorRead > 1000) {
    readSoil();
    readDHT();
    readWaterLevel();
    controlPump();
    checkTankLevel();

    if (waterLevel != -1 && waterLevel <= 3 && millis() - lastSadReminder > 10000) {
      currentEmotion = SAD; emotionUntil = millis() + 3000; lastSadReminder = millis();
    }

    if (millis() - lastHumanSeen > 60000 && currentEmotion == NONE) {
      currentEmotion = SLEEPY; emotionUntil = millis() + 3000; lastHumanSeen = millis();
    }

    checkTelegramAlerts();

    Serial.printf("Soil:%d | Water:%.1f | Temp:%.1f | Hum:%.1f | Pump:%s | Mode:%d | IR:%d\n",
      soilValue, waterLevel, temperature, humidity,
      pumpState ? "ON" : "OFF", pumpMode, digitalRead(IR_PIN));

    lastSensorRead = millis();
  }

  updateOLED();
  delay(50);
}
