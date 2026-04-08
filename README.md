🐣 Smart Incubator System (IoT + Automation + Manual Control)
📌 Overview

This project is a Smart Egg Incubator System that combines Automation, IoT, and Manual Control to maintain optimal conditions for egg hatching. The system monitors temperature and humidity and automatically controls devices like a fan, bulb, and water pump. It also includes IoT-based remote control and manual override switches for reliability.

⚙️ Features
🌡️ Automatic temperature control using DHT11 sensor
💧 Automatic humidity control
🔄 Automatic egg rotation every 2 hours using servo motor
📱 IoT-based monitoring and control using MQTT
🔘 Manual control switches for backup operation
🔁 Mode switching (Auto ↔ Manual) with buzzer indication
📊 Real-time dashboard for temperature & humidity
💡 LED indicators for system mode
🧠 Working Principle
1. Automation Mode

The system uses a DHT11 sensor to continuously monitor temperature and humidity.

🌡️ Temperature Control:
If temperature > 37°C → Fan ON
If temperature < 37°C → Fan OFF & Bulb ON
💧 Humidity Control:
If humidity < 50% → Water Pump ON
Else → Water Pump OFF
🔄 Egg Rotation:
Servo motor rotates eggs every 2 hours automatically
2. IoT Control (MQTT)
MQTT protocol is used for remote monitoring and control
Broker: test.mosquitto.org
Software used: MQTTX
Mobile app (IoT Panel) connected to MQTT server
📱 IoT Features:
Control Bulb, Fan, Pump, Servo Motor
View Temperature & Humidity in real-time
Switch between Auto Mode and Manual Mode
Override automation (force ON/OFF devices anytime)
3. Manual Mode
3 physical switches are used to control:
Bulb
Fan
Water Pump
Works when:
IoT fails
Automation fails
Ensures system reliability
4. Mode Switching System
Two modes:
🔵 Automation Mode
🟢 Manual Mode
Indicators:
LEDs indicate current mode
Buzzer gives sound when mode changes
🔌 Hardware Components
DHT11 Temperature & Humidity Sensor
Servo Motor (Egg rotation)
Relay Module
Fan
Bulb (Heating)
Water Pump
NodeMCU (ESP8266)
Manual Switches (3)
LEDs (Mode indication)
Buzzer
7V Battery
🧩 Software & Tools
Embedded C / Arduino IDE
MQTT Protocol
MQTTX Software
IoT Panel Mobile App
🔄 System Workflow
System starts and initializes sensors
Reads temperature and humidity from DHT11
Applies automation logic:
Controls fan, bulb, pump
Checks MQTT commands for IoT control
Checks manual switches for override
Rotates eggs every 2 hours
Updates dashboard with live data
Indicates mode using LED & buzzer
🛡️ Reliability Features
Works in three modes:
Automation
IoT Control
Manual Control
Manual switches act as backup system
IoT allows remote override anytime
🚀 Future Improvements
Use more accurate sensors (DHT22)
Add LCD/OLED display
Mobile app with custom UI
Battery backup with charging system
AI-based incubation optimization
📷 Project Demonstration

(Add images/videos here)

👨‍💻 Author
Goutam kumar
main email=suthargautam7777@gmail.com
Electronics & Communication Engineering (ECE)