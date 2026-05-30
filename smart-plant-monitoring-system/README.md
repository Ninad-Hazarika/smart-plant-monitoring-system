# 🌱 Smart Plant Monitoring System

A smart IoT-based plant monitoring and irrigation system developed using ESP32. The project monitors environmental conditions such as soil moisture, temperature, and humidity, and can automatically control water supply to plants when required.

## 📌 Features

* Real-time soil moisture monitoring
* Temperature and humidity sensing using DHT11
* Automatic irrigation using relay-controlled water pump
* OLED display for local monitoring
* Human detection alerts using IR sensor
* Wi-Fi connectivity through ESP32
* Telegram notifications for remote monitoring
* Custom PCB design for hardware integration
* 3D CAD enclosure design for project assembly

## 🛠️ Hardware Components

* ESP32 Development Board
* Soil Moisture Sensor
* DHT11 Temperature & Humidity Sensor
* OLED Display (128×64)
* Relay Module
* Mini Water Pump
* IR Sensor
* LEDs and Resistors
* Power Supply
* Connecting Wires

## 💻 Software & Tools

* Arduino IDE
* EasyEDA (Schematic & PCB Design)
* Onshape (CAD Design)
* Git & GitHub

## 📂 Repository Structure

├── Arduino-Code
├── PCB-Design
├── CAD-Design
├── Images
├── Project-Report
└── README.md

## ⚙️ Working Principle

The soil moisture sensor continuously monitors the moisture level of the soil. When the moisture level drops below a predefined threshold, the ESP32 activates a relay that powers the water pump and irrigates the plant automatically.

Environmental data from the DHT11 sensor is displayed on the OLED screen. The system can also send notifications through Telegram and provide remote monitoring capabilities via Wi-Fi.

## 📸 Project Gallery

Screenshots, hardware setup images, PCB layouts, CAD models, and demonstration photographs can be found in the Images folder.

## 🚀 Future Improvements

* Mobile application integration
* Cloud-based data logging
* Weather-aware irrigation scheduling
* AI-powered plant health monitoring
* Battery and solar-powered operation

## 👨‍💻 Author

Ninad Hazarika

Electronics and Communication Engineering Student

Tezpur University
