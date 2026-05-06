# Real-Time Environmental Monitoring and AQI Alert System using IoT with Rule-Based AI Summary

## Overview

A low-cost, portable IoT solution for smart environmental monitoring that collects real-time sensor data, generates threshold-based alerts, stores data in the cloud, and produces rule-based AI environmental summaries with health recommendations.

**Monitored parameters:**
- Air Quality Index (AQI)
- Temperature
- Humidity
- Harmful gas concentrations
- Dust / smoke levels

---

## Hardware Components

| Component | Purpose |
|---|---|
| ESP8266 / NodeMCU / ESP32 | Microcontroller & Wi-Fi |
| MQ135 Gas Sensor | Gas / AQI measurement |
| DHT11 / DHT22 | Temperature & humidity |
| Dust / Smoke Sensor | Particulate detection |
| LCD / OLED Display | Local readout |
| Buzzer | Audible alert |
| LEDs | Visual alert |

---

## Software Requirements

- Arduino IDE (Embedded C/C++)
- Firebase Realtime Database (cloud storage)
- Blynk / ThingSpeak (optional dashboards)
- Rule-based AI logic (implemented in the cloud function)

---

## Working Principle

1. **Sensor Data Collection** — ESP8266 reads AQI, gas levels, temperature, and humidity continuously.
2. **Data Processing** — The microcontroller compares readings against predefined thresholds.
3. **Rule-Based AI Analysis** — Cloud function generates a human-readable environmental summary.
4. **Alert Generation** — Buzzer, LED, mobile notifications, and cloud alerts are triggered when thresholds are exceeded.
5. **Cloud Monitoring** — Live data, graphs, reports, and historical analysis are available on the remote dashboard.

---

## AQI Classification

| AQI Range | Category |
|---|---|
| 0 – 50 | Good |
| 51 – 100 | Moderate |
| 101 – 150 | Unhealthy for Sensitive Groups |
| 151 – 200 | Unhealthy |
| 201 – 300 | Very Unhealthy |
| 301+ | Hazardous |

---

## Rule-Based AI Summary Logic

```
IF AQI is high AND Temperature is high AND Gas concentration is high
THEN → "Air quality is unhealthy. Pollution and heat levels are elevated.
         Avoid prolonged outdoor exposure."
```

### Sample Output

```
AQI: 178
Temperature: 34°C
Humidity: 42%

AI Summary:
"Air quality is unhealthy for sensitive groups. Elevated pollution and heat
may affect health. Outdoor exposure should be minimized."
```

---

## Applications

- Smart Cities
- Industrial Safety
- Indoor Air Monitoring
- Agriculture
- Educational Institutions
- Public Health Systems

---

## Advantages

- Low cost and portable
- Real-time IoT-enabled monitoring
- User-friendly dashboard
- Preventive threshold alerts
- AI-enhanced environmental insights
- Scalable to multiple sensor nodes

---

## Limitations

- Sensors require periodic calibration
- Internet connectivity required for cloud features
- Sensor accuracy depends on hardware quality
- Rule-based AI logic (not machine learning)

---

## Future Enhancements

- Machine learning–based pollution prediction
- GPS-enabled pollution mapping
- Dedicated mobile application
- Solar power integration
- Advanced analytics and trend reports
- Voice assistant alerts

---

## Deployment Guide

### 1. Setup Firebase

Set up a Firebase Realtime Database and obtain your project keys.

### 2. Prepare Code

1. **Dashboard**: Open `index.html` and fill in your `firebaseConfig` keys.
2. **ESP8266**: Open `esp8266_firebase.ino`, fill in `FIREBASE_HOST` and `FIREBASE_AUTH`, and flash to your NodeMCU.

### 3. Host on GitHub Pages

This allows you to access your dashboard from anywhere (e.g., `https://yourname.github.io/air-quality`).

#### Step 1: Push to GitHub

If you haven't already:
1. Create a new repository on GitHub (e.g., `air-quality-dashboard`).
2. Open a terminal in this folder and run:
    ```bash
    git init
    git add .
    git commit -m "Initial commit"
    git branch -M main
    git remote add origin https://github.com/YOUR_USERNAME/air-quality-dashboard.git
    git push -u origin main
    ```

#### Step 2: Enable GitHub Pages

1. Go to your repository **Settings** on GitHub.
2. Click **Pages** (in the left sidebar).
3. Under **Branch**, select `main` and `/ (root)`.
4. Click **Save**.
5. Wait a minute, and you will see your live URL!

### 4. Verify

- Open your GitHub Pages URL.
- Power on your ESP8266.
- The dashboard should show "● Live" and the "Last Activity" time should update every 2 seconds.

---

## Technical Domains

IoT · Embedded Systems · Sensor Networks · Cloud Computing · Environmental Engineering · Rule-Based AI
