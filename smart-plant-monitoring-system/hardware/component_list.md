# Component List — Smart Plant Monitoring System

## Core Components

| Component | Spec | Qty | Notes |
|---|---|:---:|---|
| ESP32 DevKit v1 | Dual-core, 240MHz, Wi-Fi + BT | 1 | Any ESP32 DevKit works |
| DHT11 Sensor | 0–50°C, 20–90% RH | 1 | DHT22 for better accuracy |
| Soil Moisture Sensor | Analog resistive/capacitive | 1 | Capacitive preferred (no corrosion) |
| OLED Display | SSD1306, 0.96", I2C, 128×64 | 1 | I2C address: 0x3C |
| 5V Relay Module | Single channel, active LOW | 1 | Most modules are active LOW |
| Mini DC Water Pump | 3V–6V, submersible | 1 | Powered by external supply |

## Power & Passives

| Component | Spec | Qty | Notes |
|---|---|:---:|---|
| 9V Battery or DC Adapter | For pump power | 1 | Do not power pump from ESP32 |
| Micro USB Cable | For ESP32 power + programming | 1 | |
| Jumper Wires | M-M, M-F | ~20 | Assorted |
| Breadboard | 830 tie-point | 1 | Or use custom PCB |

## Optional / Expansion

| Component | Spec | Qty | Purpose |
|---|---|:---:|---|
| Ultrasonic Sensor | HC-SR04 | 1 | Water tank level monitoring |
| Buzzer | 5V passive | 1 | Audio alerts |
| LED + 220Ω Resistor | Any color | 1 | Status indicator |
| SD Card Module | SPI | 1 | Data logging |
| LiPo Battery + TP4056 | For battery backup | 1 | Portable operation |

## Where to Buy

- [Robu.in](https://robu.in/) — India, fast shipping
- [AliExpress](https://aliexpress.com/) — Cheapest, 2–4 week shipping
- [Amazon India](https://amazon.in/) — Convenient, Prime eligible
