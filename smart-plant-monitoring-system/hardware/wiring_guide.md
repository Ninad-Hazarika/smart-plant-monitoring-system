# Wiring Guide — Smart Plant Monitoring System

> ⚠️ **Safety First:** Always disconnect power before changing wiring. Never connect the pump directly to ESP32 GPIO pins.

---

## 1. DHT11 Temperature & Humidity Sensor

| DHT11 Pin | Connect To |
|---|---|
| VCC | ESP32 3.3V |
| GND | ESP32 GND |
| OUT / Data | ESP32 GPIO 13 |

*If your DHT11 module doesn't have a built-in pull-up resistor, add a 10kΩ resistor between VCC and DATA pin.*

---

## 2. Soil Moisture Sensor

| Sensor Pin | Connect To |
|---|---|
| VCC | ESP32 3.3V |
| GND | ESP32 GND |
| AO (Analog Out) | ESP32 GPIO 34 |

*GPIO 34 is an input-only pin — perfect for analog readings. Do not connect DO (digital out) unless you want a simple threshold trigger.*

---

## 3. OLED Display (SSD1306, I2C)

| OLED Pin | Connect To |
|---|---|
| VCC | ESP32 3.3V |
| GND | ESP32 GND |
| SDA | ESP32 GPIO 21 |
| SCL | ESP32 GPIO 22 |

*Default I2C address is 0x3C. If display doesn't initialize, try 0x3D.*

---

## 4. Relay Module

| Relay Pin | Connect To |
|---|---|
| VCC | ESP32 5V / VIN |
| GND | ESP32 GND |
| IN | ESP32 GPIO 15 |

*Most relay modules are active LOW — the relay activates when IN is pulled LOW. The firmware already handles this (`RELAY_ON = LOW`).*

---

## 5. Water Pump via Relay

```
  9V Battery (+) ──────▶ Relay COM
  Relay NO ────────────▶ Pump (+)
  Pump (–) ────────────▶ 9V Battery (–)
  9V Battery (–) ──────▶ ESP32 GND  (common ground)
```

> **COM** = Common terminal  
> **NO** = Normally Open (pump is OFF when relay is OFF)  
> **NC** = Normally Closed (pump is ON when relay is OFF — don't use this)

---

## Quick Reference Diagram

```
ESP32          DHT11        Soil Sensor     OLED          Relay
──────         ─────        ───────────     ────          ─────
3.3V  ────────▶ VCC          VCC    ◀────── 3.3V          VCC ◀── 5V/VIN
GND   ────────▶ GND          GND    ◀────── GND           GND ◀── GND
GPIO13 ───────▶ OUT          AO     ◀────── GPIO34        IN  ◀── GPIO15
GPIO21 ─────────────────────────────────── SDA
GPIO22 ─────────────────────────────────── SCL
3.3V  ─────────────────────────────────── VCC
GND   ─────────────────────────────────── GND
```
