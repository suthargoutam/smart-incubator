# 🐣 Smart Incubator System  
*(IoT + Automation + Manual Control)*

---

📌 Overview
This project is a **Smart Egg Incubator System** that combines **Automation, IoT, and Manual Control** to maintain optimal conditions for egg hatching.

The system continuously monitors **temperature and humidity** and automatically controls devices like **fan, bulb, and water pump**. It also supports **IoT-based remote control** and **manual override switches** for high reliability.

---

 ⚙️ Features
- 🌡️ Automatic temperature control using DHT11 sensor  
- 💧 Automatic humidity control  
- 🔄 Automatic egg rotation every 2 hours (Servo Motor)  
- 📱 IoT-based monitoring & control using MQTT  
- 🔘 Manual control switches (backup system)  
- 🔁 Mode switching (Auto ↔ Manual) with buzzer indication  
- 📊 Real-time dashboard (Temperature & Humidity)  
- 💡 LED indicators for system mode  

---

 🧠 Working Principle

 🔵 1. Automation Mode
The system continuously reads data from the **DHT11 sensor**.

🌡️ Temperature Control:**
- If temperature > 37°C → Fan ON  
- If temperature < 37°C → Fan OFF & Bulb ON  

💧 Humidity Control:**
- If humidity < 50% → Water Pump ON  
- Else → Water Pump OFF  

🔄 Egg Rotation:**
- Servo motor rotates eggs every 2 hours automatically  

---

 📡 2. IoT Control (MQTT)
- Protocol: MQTT  
- Broker: `test.mosquitto.org`  
- Software: MQTTX  
- Mobile App: IoT Panel  

📱 IoT Features:**
- Control Bulb, Fan, Pump, Servo  
- View real-time temperature & humidity  
- Switch between Auto & Manual modes  
- Override automation anytime  

---

 🟢 3. Manual Mode
Physical switches are used to control:
- Bulb  
- Fan  
- Water Pump  

**Used when:**
- IoT fails  
- Automation fails  

 Ensures maximum system reliability  

---

 🔁 4. Mode Switching System
Two operating modes:
- 🔵 Automation Mode  
- 🟢 Manual Mode  

Indicators:**
- LEDs show current mode  
- Buzzer alerts when mode changes  

---

🔌 Hardware Components
- NodeMCU (ESP8266)  
- DHT11 Temperature & Humidity Sensor  
- Servo Motor (Egg Rotation)  
- Relay Module  
- Fan  
- Bulb (Heating)  
- Water Pump  
- Manual Switches (3)  
- LEDs (Mode Indication)  
- Buzzer  
- 7V Battery  

---
🧩 Software & Tools
- Arduino IDE (Embedded C)  
- MQTT Protocol  
- MQTTX Software  
- IoT Panel Mobile App  

---

🔄 System Workflow
1. System initializes sensors  
2. Reads temperature & humidity  
3. Applies automation logic  
4. Controls fan, bulb, and pump  
5. Checks MQTT commands (IoT control)  
6. Checks manual switches (override)  
7. Rotates eggs every 2 hours  
8. Updates dashboard in real-time  
9. Indicates mode via LED & buzzer  

---

🛡️ Reliability Features
- Works in 3 modes:
  - Automation  
  - IoT Control  
  - Manual Control  
- Manual switches act as backup  
- IoT allows remote override anytime  

---

🚀 Future Improvements
- Use more accurate sensor (DHT22)  
- Add LCD/OLED display  
- Custom mobile app UI  
- Battery backup with charging system  
- AI-based incubation optimization  


👨‍💻 Author
**Gautam Suthar**  
📧 Main Email: suthargautam7777@gmail.com  
🎓 Electronics & Communication Engineering (ECE)

