# 🚗 Narrow Road Robot — Autonomous Obstacle Avoidance

**Teknofest Unmanned Ground Vehicle (Mini) Project**
Spring Semester 2025–2026

> Developed by: Tuba Nisa USLU, Zikreddin DURMUŞ, Gülsima TAVUŞ

---

## 📖 About the Project

An autonomous robot that navigates through narrow paths using three ultrasonic sensors.
Unlike basic obstacle-avoidance robots, this system interprets its environment to make
smarter decisions — including dead-end detection and U-turns.

The project evolved from a single-sensor design to a three-sensor architecture with
an improved decision algorithm.

---

## 🛠️ Components

| # | Component | Qty | Description |
|---|-----------|-----|-------------|
| 1 | Arduino UNO R3 | 1 | Main controller |
| 2 | HC-SR04 Ultrasonic Sensor | 3 | Front, right, left distance measurement |
| 3 | L298N Motor Driver | 1 | Motor control |
| 4 | DC Motor (TT Motor) | 2 | Drive system |
| 5 | Robot Chassis (2WD) | 1 | Mechanical frame |
| 6 | Wheel | 2 | Movement |
| 7 | Caster Wheel | 1 | Balance |
| 8 | Battery Pack | 1 | Power supply |

---

## 📌 Pin Configuration

### Ultrasonic Sensors

| Sensor | Trig Pin | Echo Pin |
|--------|----------|----------|
| Right  | D2       | D3       |
| Left   | D4       | D11      |
| Front  | D12      | D13      |

### Motor Driver (L298N)

| Driver Pin | Arduino Pin |
|------------|-------------|
| IN1        | D5          |
| IN2        | D6          |
| IN3        | D7          |
| IN4        | D8          |
| ENA        | D9          |
| ENB        | D10         |

---

## 🧠 Decision Algorithm
```
If front distance > 25 cm     → Move forward (full speed)
If front distance 15–25 cm    → Move forward (slow)
If front distance ≤ 15 cm:
    If right > left            → Turn right
    If left > right            → Turn left
    If both sides blocked      → Check for dead-end → U-turn
```

### Dead-End Detection

The robot takes **5 consecutive sensor readings**.
If at least **4 out of 5** readings show all three directions blocked, it performs a 180° U-turn.
This prevents false positives from noisy sensor data.

---

## 🚀 Getting Started

1. Clone or download this repository
2. Open the `.ino` file in Arduino IDE
3. Install required libraries (if any)
4. Upload to Arduino UNO
5. Power on and place the robot in a narrow corridor

---

## 📄 License

Open source — free to use for educational and competition purposes.
```

---

Bunu `README.md` olarak kaydet, commit mesajını da şöyle yazabilirsin:
```
Add narrow road robot project with 3-sensor obstacle avoidance
