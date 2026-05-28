<div align="center">

```
 ██████╗ ██████╗ ███████╗███████╗███╗   ██╗    ██████╗ ██╗      █████╗ ███╗   ██╗████████╗
██╔════╝ ██╔══██╗██╔════╝██╔════╝████╗  ██║    ██╔══██╗██║     ██╔══██╗████╗  ██║╚══██╔══╝
██║  ███╗██████╔╝█████╗  █████╗  ██╔██╗ ██║    ██████╔╝██║     ███████║██╔██╗ ██║   ██║   
██║   ██║██╔══██╗██╔══╝  ██╔══╝  ██║╚██╗██║    ██╔═══╝ ██║     ██╔══██║██║╚██╗██║   ██║   
╚██████╔╝██║  ██║███████╗███████╗██║ ╚████║    ██║     ███████╗██║  ██║██║ ╚████║   ██║   
 ╚═════╝ ╚═╝  ╚═╝╚══════╝╚══════╝╚═╝  ╚═══╝    ╚═╝     ╚══════╝╚═╝  ╚═╝╚═╝  ╚═══╝   ╚═╝   
```

<h1>🌿 Smart Plant Monitoring System</h1>

**ESP32 · IoT · Telegram Alerts · Emotional OLED · Real-Time Web Dashboard**

[![Platform](https://img.shields.io/badge/Platform-ESP32-E7352C?style=for-the-badge&logo=espressif&logoColor=white)](https://www.espressif.com/)
[![IDE](https://img.shields.io/badge/Arduino_IDE-2.x-00979D?style=for-the-badge&logo=arduino&logoColor=white)](https://www.arduino.cc/)
[![Telegram](https://img.shields.io/badge/Telegram-Bot_Alerts-2CA5E0?style=for-the-badge&logo=telegram&logoColor=white)](https://telegram.org/)
[![License](https://img.shields.io/badge/License-MIT-27ae60?style=for-the-badge)](./LICENSE)
[![Status](https://img.shields.io/badge/Status-Active-brightgreen?style=for-the-badge)]()
[![Language](https://img.shields.io/badge/Language-C%2B%2B-00599C?style=for-the-badge&logo=cplusplus&logoColor=white)]()

<br/>

> *"Your plant now has feelings — and a Telegram account."*

<br/>

**A full-stack, sensor-fused plant care station** built on ESP32. It monitors soil moisture, ambient temperature & humidity, and water tank level in real time. It controls irrigation automatically or manually via a live web dashboard, fires Telegram push alerts for critical events, reacts to human presence via IR sensing, responds to touch gestures, and expresses five distinct emotions on an OLED face — complete with animated eyes.

</div>

---

## 🧠 System Architecture

```
╔══════════════════════════════════════════════════════════════════════════════╗
║                            SENSOR FUSION LAYER                               ║
║                                                                              ║
║  ┌──────────┐  ┌──────────┐  ┌──────────────┐  ┌──────────┐  ┌──────────┐  ║
║  │  DHT11   │  │   Soil   │  │  Ultrasonic  │  │    IR    │  │  Touch   │  ║
║  │ Temp/Hum │  │ Moisture │  │  HC-SR04     │  │ Detector │  │  Sensor  │  ║
║  │ GPIO 13  │  │ GPIO 34  │  │ TRIG:26 ECHO:25│ │ GPIO 33  │  │ GPIO 32  │  ║
║  └────┬─────┘  └────┬─────┘  └──────┬───────┘  └────┬─────┘  └────┬─────┘  ║
╚═══════╪═════════════╪═══════════════╪════════════════╪═════════════╪════════╝
        │             │               │                │             │
╔═══════▼═════════════▼═══════════════▼════════════════▼═════════════▼════════╗
║                          ESP32 DevKit (240 MHz)                              ║
║                                                                              ║
║   ┌─────────────────────────────────────────────────────────────────────┐   ║
║   │  Core 0: Wi-Fi Stack + WebServer + Telegram HTTPS Client            │   ║
║   │  Core 1: Sensor Reads · Pump Logic · OLED · IR/Touch · Buzzer      │   ║
║   │  ADC: 12-bit (0–4095) for soil moisture                            │   ║
║   │  I2C: GPIO 21 (SDA) / GPIO 22 (SCL) for OLED                      │   ║
║   └─────────────────────────────────────────────────────────────────────┘   ║
╚════════╪══════════════════════════════════╪═══════════════════════╪══════════╝
         │                                  │                       │
╔════════▼═══════════╗            ╔══════════▼═══════╗    ╔═════════▼══════════╗
║   OUTPUT LAYER     ║            ║   CONTROL LAYER  ║    ║  NOTIFICATION      ║
║                    ║            ║                  ║    ║  LAYER             ║
║  ┌──────────────┐  ║            ║  ┌────────────┐  ║    ║  ┌──────────────┐  ║
║  │  OLED 128×64 │  ║            ║  │   Relay    │  ║    ║  │  Telegram    │  ║
║  │  Emotions +  │  ║            ║  │  GPIO 15   │──╫──▶ ║  │  Bot Alerts  │  ║
║  │  Sensor data │  ║            ║  └─────┬──────┘  ║    ║  │  via HTTPS   │  ║
║  └──────────────┘  ║            ║        ▼          ║    ║  └──────────────┘  ║
║  ┌──────────────┐  ║            ║  ┌────────────┐  ║    ║  ┌──────────────┐  ║
║  │    Buzzer    │  ║            ║  │ Water Pump │  ║    ║  │  Web Server  │  ║
║  │  GPIO 27     │  ║            ║  │ (9V ext.)  │  ║    ║  │  Port 80     │  ║
║  └──────────────┘  ║            ║  └────────────┘  ║    ║  │  Dashboard   │  ║
╚════════════════════╝            ╚══════════════════╝    ║  └──────────────┘  ║
                                                          ╚════════════════════╝
```

---

## ✨ Feature Matrix

| Feature | Implementation | Status |
|---|---|:---:|
| 🌱 **Soil Moisture Sensing** | 12-bit ADC on GPIO 34, auto-threshold pump trigger | ✅ |
| 🌡️ **Temperature & Humidity** | DHT11 on GPIO 13, NaN-safe reads | ✅ |
| 💧 **Water Tank Level** | HC-SR04 ultrasonic, distance → level mapping | ✅ |
| 🖥️ **Live OLED Display** | Sensor data + 5 animated face emotions | ✅ |
| 🔌 **Relay Pump Control** | Active-LOW relay, 3 modes: AUTO / MANUAL ON / MANUAL OFF | ✅ |
| 🌐 **Local Web Dashboard** | ESP32-hosted HTTP server, auto-refresh every 2s | ✅ |
| 📱 **Mobile-Responsive UI** | Dark-theme dashboard, progress bars, live sensor cards | ✅ |
| 📲 **Telegram Bot Alerts** | HTTPS push alerts: low water, pump timeout, plant thirsty, human detected | ✅ |
| 👁️ **IR Human Detection** | GPIO 33 PIR/IR sensor, greeting emotion + Telegram ping | ✅ |
| 👆 **Triple-Touch Gesture** | GPIO 32 touch, 3 taps → LAUGHING emotion | ✅ |
| 🔔 **Buzzer Alert** | Beeps when water tank ≤ 3 cm | ✅ |
| 😊 **Emotion Engine** | 5 states: GREETING · HAPPY · SAD · LAUGHING · SLEEPY | ✅ |
| ⏱️ **Smart Alert Cooldowns** | 30s global Telegram cooldown, 5s human alert cooldown | ✅ |
| 🕐 **NTP Time Sync** | pool.ntp.org time sync on boot | ✅ |

---

## 😊 Emotion Engine

The OLED doesn't just show data — the plant *reacts* to the world around it.

```
┌─────────────────────────────────────────────────────────────────────────┐
│                         EMOTION STATE MACHINE                            │
│                                                                          │
│   IR detects human ──────────────────▶  GREETING  "Hello!"             │
│          │                               (3 sec)                        │
│          │                                                               │
│   Pump turns ON (auto or manual) ──────▶  HAPPY   "Ahh... Water!"      │
│                                            (3 sec)                       │
│                                                                          │
│   Water level ≤ 3 cm ──────────────────▶   SAD    "I'm thirsty"        │
│          │                               (3 sec, repeats every 10s)     │
│          │                                                               │
│   3 rapid touches (< 900ms apart) ─────▶ LAUGHING "Hehehe!"            │
│                                            (5 sec)                       │
│                                                                          │
│   No human for 60 seconds ─────────────▶  SLEEPY  "Zzz..."             │
│                                            (3 sec)                       │
│                                                                          │
│   Any emotion expires ─────────────────▶   NONE   [Sensor Data Screen] │
└─────────────────────────────────────────────────────────────────────────┘
```

### OLED Eye Animations

```
  OPEN EYES         HAPPY EYES        SAD EYES          SLEEPY EYES
  (Greeting)        (Watered)         (Thirsty)         (Idle 60s)

  ╭───╮ ╭───╮      ╱╲    ╱╲         ╲    ╱             ────  ────
  │ ● │ │ ● │     ╱  ╲  ╱  ╲         ╲  ╱                            Zz
  ╰───╯ ╰───╯                          ╲╱            (half-closed)
                                      • •
  LAUGHING
  ╱╲    ╱╲
 ╱  ╲  ╱  ╲    ←  happy eyes
  ╲──────╱      ←  wide grin
```

---

## 📲 Telegram Alert System

The bot fires push notifications directly to your phone. No polling — purely event-driven with smart cooldowns to prevent spam.

```
┌────────────────────────────────────────────────────────────────────┐
│                     ALERT TRIGGER CONDITIONS                        │
├─────────────────────────┬──────────────────────┬───────────────────┤
│ Alert                   │ Trigger Condition     │ Cooldown          │
├─────────────────────────┼──────────────────────┼───────────────────┤
│ 💧 Low Water            │ Tank level ≤ 3 cm     │ Once per event    │
│ ⚠️  Pump Running Long   │ Pump ON > 60 seconds  │ Once per event    │
│ 🌵 Plant Thirsty        │ Soil dry + pump OFF   │ Once per event    │
│                         │ for > 60 seconds      │                   │
│ 👤 Human Detected       │ IR sensor triggered   │ 5 seconds         │
│ ✅ System Online        │ On boot               │ Once              │
└─────────────────────────┴──────────────────────┴───────────────────┘
```

**Setup your Telegram bot:**

```
1. Open Telegram → search @BotFather
2. Send /newbot → follow prompts → copy your Bot Token
3. Add your bot to a group OR get your Chat ID via @userinfobot
4. Edit these lines in smart_plant_monitoring.ino:

   String botToken = "YOUR_BOT_TOKEN_HERE";
   String chatID   = "YOUR_CHAT_ID_HERE";
```

---

## 🌐 Web Dashboard

The ESP32 hosts a full dark-themed dashboard on port 80. No internet required — works entirely on your local Wi-Fi.

```
╔═══════════════════════════════════════════╗
║        SMART PLANT DASHBOARD              ║
║                        192.168.x.x        ║
╠═══════════════════════════════════════════╣
║  SENSORS                                  ║
║  ┌───────────────┐  ┌───────────────┐     ║
║  │ Soil Moisture │  │ Temperature   │     ║
║  │    2847       │  │   28.5 °C     │     ║
║  │ ████████░░░░  │  │ ██████░░░░░░  │     ║
║  └───────────────┘  └───────────────┘     ║
║  ┌───────────────┐  ┌───────────────┐     ║
║  │  Humidity     │  │ Water Level   │     ║
║  │   65.0 %      │  │   9.2 cm      │     ║
║  │ ████████████░ │  │ ████████████░ │     ║
║  └───────────────┘  └───────────────┘     ║
╠═══════════════════════════════════════════╣
║  PUMP CONTROL                             ║
║  Pump is OFF  ·  AUTO MODE                ║
║  ✅ System running normally               ║
║                                           ║
║  ╔══════╗  ╔══════╗  ╔══════╗            ║
║  ║  ON  ║  ║  OFF ║  ║ AUTO ║            ║
║  ╚══════╝  ╚══════╝  ╚══════╝            ║
╠═══════════════════════════════════════════╣
║  Auto-refreshes every 2 seconds           ║
╚═══════════════════════════════════════════╝

  Endpoints:
  GET /             → Full dashboard
  GET /pump/on      → Force pump ON  (MANUAL mode)
  GET /pump/off     → Force pump OFF (MANUAL mode)
  GET /pump/auto    → Return to AUTO mode
```

---

## 🛠️ Hardware & Bill of Materials

```
┌─────────────────────────────────────────────────────────────────────┐
│  COMPONENT                   │  QTY │  GPIO       │  PURPOSE        │
├──────────────────────────────┼──────┼─────────────┼─────────────────┤
│  ESP32 DevKit v1             │   1  │  —          │  MCU + Wi-Fi    │
│  DHT11 Sensor                │   1  │  GPIO 13    │  Temp + Humidity│
│  Capacitive Soil Sensor      │   1  │  GPIO 34    │  Soil moisture  │
│  HC-SR04 Ultrasonic          │   1  │  TRIG: 26   │  Tank level     │
│                              │      │  ECHO: 25   │                 │
│  OLED SSD1306 (0.96" I2C)   │   1  │  SDA: 21    │  Display/face   │
│                              │      │  SCL: 22    │                 │
│  5V Relay Module             │   1  │  GPIO 15    │  Pump switch    │
│  Mini DC Water Pump          │   1  │  (via relay)│  Irrigation     │
│  IR Obstacle/PIR Sensor      │   1  │  GPIO 33    │  Human detect   │
│  Touch Sensor Module         │   1  │  GPIO 32    │  Gesture input  │
│  Passive Buzzer              │   1  │  GPIO 27    │  Tank low alert │
│  9V Battery or DC Adapter    │   1  │  —          │  Pump power     │
│  USB Micro Cable             │   1  │  —          │  Program + 3.3V │
│  Jumper Wires (assorted)     │ ~30  │  —          │  Connections    │
│  Breadboard / Custom PCB     │   1  │  —          │  Assembly       │
└──────────────────────────────┴──────┴─────────────┴─────────────────┘
```

> **💡 Tip:** Use a **capacitive** soil moisture sensor over resistive — it doesn't corrode in wet soil and gives more stable analog readings.

---

## 🔌 Complete Pin Wiring Reference

```
                    ┌─────────────────────────┐
                    │       ESP32 DevKit       │
         DHT11 ────▶│ GPIO13          GPIO26  │────▶ HC-SR04 TRIG
    Soil Sensor ───▶│ GPIO34          GPIO25  │◀──── HC-SR04 ECHO
     Relay IN  ────▶│ GPIO15          GPIO27  │────▶ Buzzer (+)
      OLED SDA ────▶│ GPIO21          GPIO33  │◀──── IR Sensor OUT
      OLED SCL ────▶│ GPIO22          GPIO32  │◀──── Touch Sensor
          3.3V ────▶│ 3V3             GND     │────▶ Common GND
           VIN ────▶│ VIN (5V)                │
                    └─────────────────────────┘
```

| Peripheral | Signal | GPIO | Logic |
|---|---|:---:|---|
| **DHT11** | Data | `13` | 3.3V, add 10kΩ pull-up if needed |
| **Soil Sensor** | Analog OUT | `34` | Input-only ADC pin, 12-bit |
| **HC-SR04** | TRIG | `26` | 10µs pulse to trigger |
| **HC-SR04** | ECHO | `25` | pulseIn() measures duration |
| **OLED SSD1306** | SDA | `21` | I2C data, address 0x3C |
| **OLED SSD1306** | SCL | `22` | I2C clock |
| **Relay** | IN | `15` | Active LOW (RELAY_ON = LOW) |
| **IR Sensor** | OUT | `33` | LOW = human/object detected |
| **Touch Sensor** | OUT | `32` | HIGH = touch detected |
| **Buzzer** | + | `27` | digitalWrite HIGH to sound |

> ⚠️ **Critical:** Never power the water pump from ESP32 GPIO. Always use the relay as an isolated switch with a dedicated 9V supply. Connect the negative terminals (GND) of both supplies together.

---

## 📂 Repository Structure

```
smart-plant-monitoring-system/
│
├── 📄 README.md                        ← You are here
├── 📄 LICENSE                          ← MIT License
├── 📄 .gitignore
│
├── 📁 src/
│   ├── 🔧 smart_plant_monitoring.ino   ← Main firmware (FULL system)
│   ├── 🧪 pump_relay_test.ino          ← Isolated relay/pump test
│   └── 🧪 sensor_test.ino             ← DHT11 + soil sensor test
│
├── 📁 hardware/
│   ├── 📋 component_list.md            ← Full BOM with specs
│   └── 🔌 wiring_guide.md             ← Step-by-step connections
│
├── 📁 schematics/
│   └── 📐 README.md                   ← EasyEDA schematic notes
│
├── 📁 pcb/
│   └── 🖨️ README.md                   ← PCB design & fabrication guide
│
├── 📁 docs/
│   └── 📃 project_report.md           ← Technical project report
│
├── 📁 images/
│   └── 🖼️ (add project photos here)
│
└── 📁 website/
    └── 🌐 index.html                  ← Standalone web UI reference
```

---

## 📦 Required Arduino Libraries

Install via **Arduino IDE → Sketch → Include Library → Manage Libraries**:

```
┌─────────────────────────────────────────────────────────────────────┐
│  LIBRARY                     │  AUTHOR     │  PURPOSE               │
├──────────────────────────────┼─────────────┼────────────────────────┤
│  Adafruit GFX Library        │  Adafruit   │  OLED graphics engine  │
│  Adafruit SSD1306            │  Adafruit   │  OLED I2C driver       │
│  DHT sensor library          │  Adafruit   │  DHT11/22 driver       │
│  Adafruit Unified Sensor     │  Adafruit   │  Sensor abstraction    │
│  WiFi (built-in)             │  Espressif  │  Wi-Fi stack           │
│  WebServer (built-in)        │  Espressif  │  HTTP server           │
│  HTTPClient (built-in)       │  Espressif  │  Telegram HTTPS calls  │
│  WiFiClientSecure (built-in) │  Espressif  │  TLS/SSL for Telegram  │
└──────────────────────────────┴─────────────┴────────────────────────┘
```

**ESP32 Board Package** (add to Arduino IDE → Boards Manager URLs):
```
https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
```

---

## 🚀 Getting Started

### 1. Clone the Repository

```bash
git clone https://github.com/YOUR_USERNAME/smart-plant-monitoring-system.git
cd smart-plant-monitoring-system
```

### 2. Configure Credentials

Open `src/smart_plant_monitoring.ino` and edit these lines:

```cpp
// Wi-Fi credentials
const char* ssid     = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

// Telegram bot (see Telegram Setup section above)
String botToken = "YOUR_BOT_TOKEN";
String chatID   = "YOUR_CHAT_ID";

// Calibration
int threshold   = 3000;    // ADC value above which soil is "dry"
float tankHeight = 13.7;   // Height of your water tank in cm
```

### 3. Upload to ESP32

```
1. Open src/smart_plant_monitoring.ino in Arduino IDE
2. Tools → Board → ESP32 Arduino → "ESP32 Dev Module"
3. Tools → Port → Select your COM port
4. Tools → Upload Speed → 115200
5. Click Upload ▶
6. Open Serial Monitor at 115200 baud
7. Wait for "WiFi Connected" and note the IP address
8. Open that IP in any browser on the same Wi-Fi
```

### 4. Test Components Individually

Before running the full system, verify hardware with isolated tests:

```
Relay/Pump Test:   src/pump_relay_test.ino
                   → Pump toggles ON/OFF every 3 seconds

Sensor Test:       src/sensor_test.ino
                   → Soil, temperature, humidity printed to Serial every 1s
```

---

## ⚙️ Pump Control Modes

```
┌──────────────────────────────────────────────────────────────────┐
│  MODE         │  BEHAVIOR                          │  pumpMode   │
├───────────────┼────────────────────────────────────┼─────────────┤
│  AUTO         │  Pump ON if soilValue > threshold  │     0       │
│               │  Pump OFF when soil is moist again │             │
├───────────────┼────────────────────────────────────┼─────────────┤
│  MANUAL ON    │  Pump forced ON regardless of soil │     1       │
│               │  HAPPY emotion triggered on switch │             │
├───────────────┼────────────────────────────────────┼─────────────┤
│  MANUAL OFF   │  Pump forced OFF regardless        │     2       │
└───────────────┴────────────────────────────────────┴─────────────┘
```

---

## 📈 Sensor Data Reference

### Soil Moisture ADC Scale (GPIO 34, 12-bit)

```
  WET  ░░░░░░░░░░░░░░░░░████████████████  0    – 1500
  MOIST░░░░░░░░████████████████░░░░░░░░░  1500 – 3000
  DRY  ████████████████████░░░░░░░░░░░░░  3000 – 4095  ← pump triggers here

  Default dryThreshold = 3000  (calibrate for your soil + sensor type)
  Lower reading = more water in soil (inverse relationship)
```

### DHT11 Operating Ranges

```
  Temperature :  0°C – 50°C    (±2°C accuracy)
  Humidity    :  20% – 90% RH  (±5% accuracy)
  Sample rate :  1 Hz max       (1 reading/second)
  Power       :  3.3V or 5V
```

### HC-SR04 Water Level Formula

```
  distance (cm) = pulseIn(ECHO, HIGH) × 0.034 / 2
  waterLevel    = tankHeight − distance

  tankHeight = physical height of tank (default: 13.7 cm)
  waterLevel = 0 when empty, tankHeight when full
  Alert fires when waterLevel ≤ 3 cm
```

---

## 🧠 Firmware Loop Overview

```
BOOT
 │
 ├─ Init: Serial, GPIO, DHT, OLED, Wi-Fi, WebServer, NTP
 ├─ Send Telegram: "SMART_PLANT_SYSTEM_ONLINE"
 │
 └─ LOOP (every 50ms)
      │
      ├─ server.handleClient()         ← serve web dashboard requests
      │
      ├─ handleIR()                    ← detect human → GREETING emotion
      ├─ handleTouch()                 ← 3 taps → LAUGHING emotion
      │
      └─ (every 1000ms)
           ├─ readSoil()               ← ADC read GPIO 34
           ├─ readDHT()                ← temperature + humidity
           ├─ readWaterLevel()         ← HC-SR04 pulse timing
           ├─ controlPump()            ← AUTO / MANUAL logic + relay
           ├─ checkTankLevel()         ← buzzer beep if water ≤ 3cm
           ├─ updateOLED()             ← emotion or sensor data screen
           └─ checkTelegramAlerts()    ← push alerts with cooldowns
```

---

## 🔭 Roadmap

- [x] Soil moisture sensing + auto pump control
- [x] DHT11 temperature & humidity
- [x] HC-SR04 water tank level monitoring
- [x] OLED animated emotion display
- [x] Relay pump: AUTO / MANUAL ON / MANUAL OFF modes
- [x] Local Wi-Fi web dashboard (dark theme, auto-refresh)
- [x] Telegram bot alerts (low water, pump timeout, thirsty, human)
- [x] IR human detection + greeting emotion
- [x] Triple-touch gesture → laughing emotion
- [x] Buzzer low-water alert
- [x] NTP time synchronization
- [ ] MQTT / Home Assistant integration
- [ ] Data logging to SD card or Firebase
- [ ] OTA (Over-The-Air) firmware updates
- [ ] Battery backup with solar charging
- [ ] Custom PCB with enclosure
- [ ] Daily summary Telegram report

---

## 🤝 Contributing

1. Fork the repository
2. Create a feature branch: `git checkout -b feature/mqtt-integration`
3. Commit your changes: `git commit -m 'Add MQTT support for Home Assistant'`
4. Push the branch: `git push origin feature/mqtt-integration`
5. Open a Pull Request

---

## 👤 Author

**Ninad Hazarika**  
📧 [ninadhazarika@gmail.com](mailto:ninadhazarika@gmail.com)  
🌍 Built with curiosity, an ESP32, and a slightly dramatic plant 🌱

---

## 📜 License

This project is licensed under the **MIT License** — see the [LICENSE](./LICENSE) file for details.

---

<div align="center">

**⭐ Found this useful? Star the repo and share it with a fellow plant parent!**

```
        .     .
       /|\   /|\
      / | \ / | \
     /  |  X  |  \
    / 🌡️ |/ \| 💧 \
   /    |   |    \
  /_____|___|_____\
  | 🌿 SMART  🌿 |
  |  PLANT LOVE  |
  |______________|
```

*For every plant that ever wilted because no one was watching.*  
*Not anymore.* 🌿

</div>
