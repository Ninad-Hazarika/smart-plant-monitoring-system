# Schematics

Circuit schematics for the Smart Plant Monitoring System were designed using [EasyEDA](https://easyeda.com/).

## Files Added

| Format | Use |
|---|---|
| `.svg` | Preview in GitHub directly |
| `.json` | EasyEDA native project file |
| `.pdf` | High-res printable schematic |
| `.png` | Quick documentation embed |

## Key Connections Summary

- **DHT11** → GPIO 13 (data), 3.3V, GND
- **Soil Sensor** → GPIO 34 (analog), 3.3V, GND
- **OLED SSD1306** → GPIO 21 (SDA), GPIO 22 (SCL), 3.3V, GND
- **Relay** → GPIO 15 (IN), 5V/VIN, GND
- **Pump** → Relay COM/NO terminals, powered by external 9V supply

See `hardware/wiring_guide.md` for the complete step-by-step guide.
