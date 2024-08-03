# Gas-Detection-and-Alert-System
# Gas Leakage Detection System

This project is a gas leakage and environmental monitoring system using Arduino Nano, MQ2 gas sensor, I2C LCD, and RTC module. It is designed to detect LPG, CO, and smoke levels in its environment and provide time-stamped alerts if a gas leak is detected.

## Components Used
- Arduino Nano
- Male to Male and Male to Female connection wires.
- MQ2 Gas Sensor
- I2C LCD (16x2)
- RTC_DS3231 Module
- Breadboard.
- Buzzer(optional)

## Photos
![WhatsApp Image 2024-08-03 at 18 50 12_d9a99bb4](https://github.com/user-attachments/assets/bc7b0297-0cbb-484c-950f-8163fb2048b4)

![WhatsApp Image 2024-08-03 at 19 59 50_1df91f56](https://github.com/user-attachments/assets/3a8c49ad-7eb4-4a97-a7cc-b8e26aa3ecfd)

## Code Explanation
The code performs the following functions:
- Initializes the LCD and RTC modules.
- Reads real time gas levels and temperature by collecting data from the sensors at regular intervals.
- Displays data on the LCD.
- Logs gas leakage events with timestamps.

## Setup Instructions
1. Connect the components as shown in the photo.
2. Upload the `GasLeakageDetection.ino` sketch to your Arduino Nano.
3. Monitor the Serial Monitor for debugging information and the LCD for real-time data.

## Usage
The device will display temperature and gas levels on the LCD. It will alert if a gas leak is detected, showing a warning message and logging the event with the date and time.Scaled more, it can be used for:
- Industrial Safety
- Residential Security
- Laboratory Safety
- Environmental Monitoring 

