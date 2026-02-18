#  AI-Based Elderly Fall Detection & Emergency Alert System

An AI-powered IoT system designed to detect elderly falls in real time and send emergency alerts to caregivers using sensor data and machine learning.

---

##  Problem Statement
Falls are a major risk for elderly patients living alone. Delayed medical response after a fall can lead to severe injuries or fatalities. Traditional systems often generate false alarms.

---

##  AI Angle
- AI classifies **normal movement vs fall events**
- Uses **accelerometer + vibration patterns**
- Reduces **false alarms** using trained ML model

---

##  Components Used
- ESP32
- MPU6050 (Accelerometer & Gyroscope)
- Vibration Sensor (SW-420)
- Buzzer
- Wi-Fi connectivity

---

##  Working
1. Sensors detect sudden acceleration and vibration
2. Data is sent to AI model for pattern analysis
3. If fall is confirmed:
   - Emergency SMS is sent
   - Emergency call is triggered
4. Local buzzer alerts nearby people

---

##  Healthcare Applications
- Elder care & assisted living
- Home monitoring
- Rehabilitation centers
- Remote patient monitoring

---
##  Simulation with Wokwi

You can try out the fall detection system on a virtual ESP32 using Wokwi simulation!

 **Live Simulation:**  
https://wokwi.com/projects/456193674115960833

Click the link above to open the simulation — no hardware required.

---

##  Tech Stack
- ESP32 (IoT)
- Python (AI model)
- Twilio API (SMS & Call alerts)
- FastAPI / Flask (Backend)
- Wokwi (Simulation)

---

##  Security Note
Sensitive credentials (Twilio API keys) are managed using **environment variables** and are **not committed** to GitHub.

---

##  Future Enhancements
- Mobile app for caregivers
- Cloud dashboard
- GPS-based location tracking
- Wearable integration

---

##  Author
**Nevil**  
AI / ML & IoT Enthusiast
