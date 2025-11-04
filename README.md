# Sumo-Bot
# 🛡️ ShieldBot SumBot  
**Author:** Yousef  
**Date:** 2024.10.10  

---

## 📘 Overview  
ShieldBot SumBot is an Arduino-based robot built for sumo-style competitions.  
It detects opponents, avoids boundaries, and moves autonomously using IR, ultrasonic, and QTI sensors.  

---

## ⚙️ Features  

- **Opponent detection:** Uses infrared and ultrasonic sensors to locate other robots.  
- **Boundary detection:** QTI sensors prevent the robot from driving out of the ring.  
- **Autonomous movement:** Makes real-time turns, reversals, and attacks based on sensor feedback.  

---

## 🔩 Hardware Components  

- **Servos:**  
  - Left servo — pin **12**  
  - Right servo — pin **13**  

- **QTI sensors:**  
  - Left — pin **3**  
  - Right — pin **2**  

- **IR sensors:**  
  - Left IR LED — pin **9**  
  - Left IR receiver — pin **10**  
  - Right IR LED — pin **4**  
  - Right IR receiver — pin **5**  

- **Ultrasonic sensor:**  
  - Trigger — pin **8**  
  - Echo — pin **7**  

---

## 🧠 How It Works  

1. **Startup:** Initializes sensors and servos.  
2. **Scanning:** IR sensors look for opponents while the ultrasonic sensor measures distance.  
3. **Decision-making:**  
   - Moves forward if no boundary is detected.  
   - Turns toward detected opponents.  
   - Reverses and turns if it detects the ring edge.
      - **The robot tracks the last side where an opponent was detected and turns in that direction when scanning for new targets**
   - Charges forward when an opponent is within range.

---

## 💻 Code Highlights  

- Simple logic flow in the main loop for clear debugging.  
- Random seed initialization adds slight behavioral variation.  
- Direct servo control via `writeMicroseconds()` for precise movement.  

---

## 🧰 Setup  

1. Connect all components according to the pin layout above.  
2. Upload the `.ino` file to your Arduino board.  
3. Place the robot in the sumo ring and power it on.  

---

## 📝 Notes  

- Adjust servo microsecond values if your robot drifts.  
- Clean sensor lenses regularly for consistent detection.  

---

## 🚀 Future Improvements  

- Add a gyro or accelerometer for smoother turns.  
- Integrate adaptive speed control based on distance.  

---

## 📄 Example Code Snippet  

```cpp
    //if US sensor detects another robot, go full speed
  if (distance <= 50) {
      servoLeft.writeMicroseconds(1300);
      servoRight.writeMicroseconds(1700);
    }
  } else if (Left_QTI_sensorValue == 0 || Right_QTI_sensorValue == 0 && Last_Detection_Left == true; ) { // if one QTI detect white (boundary) then reverse and turn around in the direction of last opponent detection
    //reverse
    servoLeft.writeMicroseconds(1600);
    servoRight.writeMicroseconds(1400);
    delay(500);
    //turn around
    servoLeft.writeMicroseconds(1600); //left motor backward
    servoRight.writeMicroseconds(1600); //right motor forward
    delay(550);
  } else if (Left_QTI_sensorValue == 0 || Right_QTI_sensorValue == 0 && Last_Detection_Right == true; ) { // if one QTI detect white (boundary) then reverse and turn around in the direction of last opponent detection
    //reverse
    servoLeft.writeMicroseconds(1600);
    servoRight.writeMicroseconds(1400);
    delay(500);
    //turn around
    servoLeft.writeMicroseconds(1400); //left motor forward
    servoRight.writeMicroseconds(1300); //right motor backward
    delay(550);
  } 
