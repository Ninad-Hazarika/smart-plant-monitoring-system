# PCB Design

Custom PCB layout for the Smart Plant Monitoring System.

## Design Tool

PCB was designed in [EasyEDA](https://easyeda.com/) — free, browser-based, with direct JLCPCB/PCBWay ordering integration.

## Files to Add Here

| File | Description |
|---|---|
| `pcb_design.json` | EasyEDA PCB project file |
| `gerber.zip` | Gerber files for PCB fabrication |
| `pcb_top.png` | Top layer render |
| `pcb_bottom.png` | Bottom layer render |

## PCB Ordering

Export Gerber files from EasyEDA and upload to:
- [JLCPCB](https://jlcpcb.com/) — ~$2 for 5 PCBs
- [PCBWay](https://www.pcbway.com/)

## Design Notes

- Ensure relay footprint matches your specific relay module dimensions
- Add decoupling capacitor (100nF) near ESP32 3.3V pin
- Route I2C lines (SDA/SCL) with short traces to minimize interference
- Separate pump power ground from ESP32 signal ground if possible
