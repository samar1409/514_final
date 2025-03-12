# Portable Air Quality Monitoring System

## Overview
This project consists of two devices: a portable air quality sensing device and a desktop display device. The sensing device collects air quality data, including CO2 and PM2.5 levels, and wirelessly transmits the data to the display device. The display device provides a clear, real-time visualization using a stepper motor-driven needle, LEDs, and a tactile button.

## Sketch of the System
<img width="355" alt="sketch" src="https://github.com/user-attachments/assets/6deaa074-9e97-4785-b630-bea4789e9e7e" />


---

## Sensing Device

### Description
The sensing device is a compact handheld unit equipped with the following components:

- **Sensors:**
  - **CO2 Sensor:** [SCD30](https://sensirion.com/products/catalog/SCD30/)
  - **PM2.5 Sensor:** [PMS5003](https://learn.adafruit.com/pm25-air-quality-sensor)
- **Microcontroller:** ESP32 (for wireless communication via Wi-Fi/Bluetooth)
- **Battery:** Rechargeable LiPo battery (3.7V, 2000mAh)
- **Enclosure:** Lightweight and durable plastic case

### How It Works
The CO2 sensor measures the concentration of carbon dioxide in the air, while the PM2.5 sensor measures fine particulate matter. The ESP32 processes the sensor data and transmits it wirelessly to the display device via Wi-Fi. The device is powered by a rechargeable LiPo battery.
<img width="388" alt="sensing" src="https://github.com/user-attachments/assets/2efbbc31-e5a8-48df-9d17-cbc94ffaedf8" />



---

## Display Device

### Description
The display device is a compact desktop unit featuring:

- **Output Devices:**
  - Stepper Motor with Needle Gauge: [28BYJ-48 + ULN2003 Driver](https://lastminuteengineers.com/28byj48-stepper-motor-arduino-tutorial/)
  - RGB LED Indicators
- **Input Device:**
  - Tactile Push Button
- **Microcontroller:** Arduino Nano
- **Battery:** Rechargeable LiPo battery (3.7V, 1200mAh)
- **Enclosure:** Compact plastic housing

### How It Works
The Arduino Nano receives air quality data wirelessly from the sensing device. It drives the stepper motor to move the needle on the gauge, indicating air quality levels. RGB LEDs provide visual alerts for specific pollutant thresholds, and the tactile button resets threshold settings.

<img width="270" alt="display" src="https://github.com/user-attachments/assets/f0c09ff1-0067-49d5-a109-2442e8f0142f" />


---

## System Architecture

### How the Devices Communicate
The ESP32 on the sensing device collects sensor data and transmits it to the Arduino Nano on the display device via Wi-Fi using the MQTT protocol for lightweight and efficient communication.

### Diagram

#### Architecture
<img width="703" alt="architecture" src="https://github.com/user-attachments/assets/1704bb41-8454-499b-af2d-c2b018676822" />


#### Workflow
1. The CO2 and PM2.5 sensors collect air quality data.
2. The ESP32 processes the data and transmits it via Wi-Fi.
3. The Arduino Nano receives the data and drives the stepper motor, RGB LEDs, and tactile button on the display device.

---

## Datasheets

The datasheets for the following components are included in the `datasheets/` directory:

- [SCD30 (CO2 Sensor)](https://www.sensirion.com/en/environmental-sensors/carbon-dioxide-sensors/carbon-dioxide-sensor-scd30/)
- [PMS5003 (PM2.5 Sensor)](https://learn.adafruit.com/pm25-air-quality-sensor)
- [ESP32 Microcontroller](https://www.espressif.com/en/products/socs/esp32)
- [Arduino Nano](https://store.arduino.cc/products/arduino-nano)
- [28BYJ-48 Stepper Motor + ULN2003 Driver](https://lastminuteengineers.com/28byj48-stepper-motor-arduino-tutorial/)
