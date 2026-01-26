# Quick Start Guide - IoT Lab Security System

## 🚀 Getting Started in 5 Minutes

This guide will help you quickly set up and test your IoT security system.

---

## Prerequisites Checklist

Before starting, ensure you have:

- [ ] Arduino UNO / NodeMCU / ESP32
- [ ] USB cable for programming
- [ ] Arduino IDE installed
- [ ] All required sensors (see components list)
- [ ] Breadboard and jumper wires
- [ ] MFRC522 library installed (for RFID tasks)

---

## Step 1: Install Arduino IDE (5 minutes)

1. **Download Arduino IDE:**
   - Visit: https://www.arduino.cc/en/software
   - Download for Windows/Mac/Linux
   - Install with default settings

2. **Install RFID Library:**
   ```
   Arduino IDE → Sketch → Include Library → Manage Libraries
   Search: "MFRC522"
   Install: "MFRC522 by GithubCommunity"
   ```

3. **Select Your Board:**
   ```
   Tools → Board → Arduino AVR Boards → Arduino UNO
   ```

4. **Select COM Port:**
   ```
   Tools → Port → COM X (your Arduino port)
   ```

---

## Step 2: Test Individual Sensors (30 minutes)

### Task 1: PIR Motion Sensor (5 min)

**Wiring:**
```
PIR VCC → 5V
PIR GND → GND
PIR OUT → D2
Buzzer+ → D8
LED+    → D7 (with 220Ω resistor)
```

**Upload & Test:**
1. Open `Task1_PIR_Motion_Sensor.ino`
2. Click Upload (→ button)
3. Open Serial Monitor (Ctrl+Shift+M)
4. Set baud rate to 9600
5. Wave hand in front of sensor
6. ✅ Should see "MOTION DETECTED" and hear buzzer

---

### Task 2: IR Obstacle Sensor (3 min)

**Wiring:**
```
IR VCC → 5V
IR GND → GND
IR OUT → D3
LED+   → D6 (with 220Ω resistor)
```

**Upload & Test:**
1. Open `Task2_IR_Obstacle_Sensor.ino`
2. Upload code
3. Place object 5-10cm from sensor
4. ✅ Should see "OBJECT DETECTED" and LED lights up

---

### Task 3: Flame Sensor (3 min)

**Wiring:**
```
Flame VCC → 5V
Flame GND → GND
Flame DO  → D4
Buzzer+   → D9
LED+      → D10 (with 220Ω resistor)
```

**Upload & Test:**
1. Open `Task3_Flame_Sensor.ino`
2. Upload code
3. Use lighter CAREFULLY near sensor (10-20cm away)
4. ✅ Should see "FIRE DETECTED" and alarm sounds

⚠️ **Safety:** Keep fire extinguisher nearby!

---

### Task 4: MQ2 Smoke Sensor (5 min)

**Wiring:**
```
MQ2 VCC → 5V
MQ2 GND → GND
MQ2 AO  → A0
Buzzer+ → D11
LED+    → D12 (with 220Ω resistor)
```

**Upload & Test:**
1. Open `Task4_MQ2_Smoke_Sensor.ino`
2. Upload code
3. **WAIT 20 seconds** for sensor warm-up
4. Test with safe smoke source (incense stick)
5. ✅ Should see increasing smoke level values

---

### Task 5: MQ5 Gas Sensor (5 min)

**Wiring:**
```
MQ5 VCC → 5V
MQ5 GND → GND
MQ5 AO  → A1
Buzzer+ → D13
LED+    → D7 (with 220Ω resistor)
```

**Upload & Test:**
1. Open `Task5_MQ5_CO2_Sensor.ino`
2. Upload code
3. **WAIT 20 seconds** for warm-up
4. Monitor readings in Serial Monitor
5. ✅ Should see gas level readings

---

### Task 6: MQ7 CO Sensor (5 min)

**Wiring:**
```
MQ7 VCC → 5V
MQ7 GND → GND
MQ7 AO  → A2
Buzzer+ → D8
LED+    → D9 (with 220Ω resistor)
```

**Upload & Test:**
1. Open `Task6_MQ7_CO_Methane_Sensor.ino`
2. Upload code
3. **WAIT 60 seconds** for warm-up (MQ7 needs longer)
4. Monitor CO levels
5. ✅ Should see "SAFE" status in clean air

---

### Task 7: FSR Pressure Sensor (3 min)

**Wiring:**
```
FSR Circuit (Voltage Divider):
5V → FSR → A3 → 10kΩ → GND

LED+    → D6 (with 220Ω resistor)
Buzzer+ → D10
```

**Upload & Test:**
1. Open `Task7_FSR_Pressure_Sensor.ino`
2. Upload code
3. Press FSR with finger
4. ✅ Should see pressure levels and LED/buzzer response

---

### Task 8: RFID Access Control (10 min)

**Wiring (IMPORTANT - Use 3.3V!):**
```
RC522 SDA  → D10
RC522 SCK  → D13
RC522 MOSI → D11
RC522 MISO → D12
RC522 RST  → D9
RC522 GND  → GND
RC522 3.3V → 3.3V ⚠️ NOT 5V!

Green LED+ → D5 (with 220Ω resistor)
Red LED+   → D6 (with 220Ω resistor)
Buzzer+    → D7
```

**Upload & Test:**
1. Open `Task8_RFID_Access_Control.ino`
2. Upload code
3. Scan your RFID card
4. Note the UID shown in Serial Monitor
5. Replace UIDs in code with your card's UID:
   ```cpp
   byte authorizedUIDs[][4] = {
     {0xYOUR, 0xUID, 0xHERE, 0xXXXX},
   };
   ```
6. Re-upload code
7. Scan card again
8. ✅ Should see "ACCESS GRANTED" with green LED

---

## Step 3: Test Combined System (15 minutes)

### Wiring for Combined System

**Digital Sensors:**
```
PIR OUT   → D2
IR OUT    → D3
Flame OUT → D4
```

**Analog Sensors:**
```
MQ2 AO → A0
MQ7 AO → A2
FSR    → A3 (with 10kΩ to GND)
```

**RFID (SPI):**
```
SDA  → D10
SCK  → D13
MOSI → D11
MISO → D12
RST  → D9
3.3V → 3.3V
```

**Outputs:**
```
Green LED → D5
Red LED   → D6
Blue LED  → D7
Buzzer    → D8
Relay     → A4
```

### Upload & Test

1. Open `Combined_Security_System.ino`
2. Update RFID UIDs with your cards
3. Upload code
4. **WAIT 20 seconds** for gas sensor warm-up
5. System will auto-arm

**Test Each Function:**
- [ ] Wave hand (PIR) → Blue LED + "INTRUSION DETECTED"
- [ ] Place object (IR) → Intrusion alarm
- [ ] Press FSR → Intrusion alarm
- [ ] Test flame sensor → "FIRE DETECTED"
- [ ] Scan RFID card → "ACCESS GRANTED" + door unlock

**Serial Commands:**
```
Type "ARM" → Arms the system
Type "DISARM" → Disarms the system
Type "STATUS" → Shows full status report
```

---

## Step 4: Test Bonus Task (10 minutes)

### Motion-Based Smart Entry

**Upload & Test:**
1. Open `Bonus_Task_PIR_RFID_Smart_Entry.ino`
2. Update RFID UIDs
3. Upload code
4. System starts in IDLE mode

**Test Sequence:**
1. Approach sensor → PIR detects motion
2. Blue LED blinks → RFID reader activated
3. Scan card within 10 seconds
4. ✅ Green LED + door unlocks (if authorized)
5. ✅ Red LED + alarm (if unauthorized)
6. Wait 10 seconds without scanning → Timeout

---

## Common Issues & Solutions

### ❌ RFID Not Working

**Problem:** No response when scanning card

**Solutions:**
- ✅ Check you're using 3.3V, NOT 5V!
- ✅ Verify SPI wiring (especially MOSI/MISO)
- ✅ Ensure MFRC522 library is installed
- ✅ Try different jumper wires
- ✅ Check card is 13.56MHz (MIFARE)

---

### ❌ Gas Sensors Always High

**Problem:** MQ2/MQ5/MQ7 showing high values

**Solutions:**
- ✅ Allow proper warm-up time (20-60 seconds)
- ✅ Wait 24-48 hours for optimal performance
- ✅ Calibrate in clean air environment
- ✅ Check analog pin connections
- ✅ Adjust threshold values in code

---

### ❌ PIR Constantly Triggering

**Problem:** Motion sensor always detecting

**Solutions:**
- ✅ Adjust sensitivity potentiometer (turn counter-clockwise)
- ✅ Increase delay time potentiometer
- ✅ Allow 30-60 second stabilization after power-on
- ✅ Keep away from heat sources
- ✅ Ensure stable mounting

---

### ❌ FSR Not Responding

**Problem:** No reading from pressure sensor

**Solutions:**
- ✅ Check voltage divider circuit (5V → FSR → A3 → 10kΩ → GND)
- ✅ Verify 10kΩ resistor value with multimeter
- ✅ Ensure good contact on breadboard
- ✅ Test FSR resistance with multimeter (should change when pressed)

---

### ❌ Compilation Errors

**Problem:** Code won't compile

**Solutions:**
- ✅ Install MFRC522 library (for RFID tasks)
- ✅ Install SPI library (usually pre-installed)
- ✅ Select correct board (Tools → Board)
- ✅ Update Arduino IDE to latest version

---

### ❌ Upload Failed

**Problem:** Can't upload code to Arduino

**Solutions:**
- ✅ Select correct COM port (Tools → Port)
- ✅ Close Serial Monitor before uploading
- ✅ Try different USB cable
- ✅ Restart Arduino IDE
- ✅ Press reset button on Arduino before upload

---

## Testing Checklist

### Individual Tasks
- [ ] Task 1: PIR Motion - Working ✓
- [ ] Task 2: IR Obstacle - Working ✓
- [ ] Task 3: Flame Sensor - Working ✓
- [ ] Task 4: MQ2 Smoke - Working ✓
- [ ] Task 5: MQ5 Gas - Working ✓
- [ ] Task 6: MQ7 CO - Working ✓
- [ ] Task 7: FSR Pressure - Working ✓
- [ ] Task 8: RFID Access - Working ✓

### Combined System
- [ ] All sensors connected
- [ ] PIR detection working
- [ ] IR detection working
- [ ] Flame detection working
- [ ] Smoke detection working
- [ ] CO detection working
- [ ] Pressure detection working
- [ ] RFID access working
- [ ] ARM/DISARM commands working
- [ ] STATUS report working
- [ ] Multi-level alerts working

### Bonus Task
- [ ] Motion activates RFID reader
- [ ] Blue LED indicates active state
- [ ] Authorized card grants access
- [ ] Unauthorized card denied
- [ ] Timeout working (10 seconds)
- [ ] Door lock/unlock working

---

## Video/Screenshot Capture Guide

For your lab submission, capture:

### Screenshots Needed:
1. **Serial Monitor Output** - Each task showing sensor readings
2. **Circuit Photos** - Clear view of wiring for each task
3. **LED Indicators** - Show different states (green/red/blue)
4. **RFID UID Reading** - Show card being scanned
5. **Combined System Status** - Full status report

### Video Recording Tips:
1. **Individual Tasks (8 videos):**
   - Show circuit setup
   - Demonstrate sensor triggering
   - Show Serial Monitor output
   - Duration: 30-60 seconds each

2. **Combined System (1 video):**
   - Show complete setup
   - Demonstrate all sensors
   - Show ARM/DISARM
   - Test RFID access
   - Duration: 2-3 minutes

3. **Bonus Task (1 video):**
   - Show motion detection
   - RFID activation
   - Access granted/denied
   - Duration: 1-2 minutes

---

## Submission Checklist

For your lab submission, prepare:

### Code Files
- [ ] Task1_PIR_Motion_Sensor.ino
- [ ] Task2_IR_Obstacle_Sensor.ino
- [ ] Task3_Flame_Sensor.ino
- [ ] Task4_MQ2_Smoke_Sensor.ino
- [ ] Task5_MQ5_CO2_Sensor.ino
- [ ] Task6_MQ7_CO_Methane_Sensor.ino
- [ ] Task7_FSR_Pressure_Sensor.ino
- [ ] Task8_RFID_Access_Control.ino
- [ ] Bonus_Task_PIR_RFID_Smart_Entry.ino
- [ ] Combined_Security_System.ino

### Documentation
- [ ] README.md (circuit diagrams, instructions)
- [ ] SENSOR_ANALYSIS.md (reliability analysis)
- [ ] Circuit diagrams (hand-drawn or digital)
- [ ] Screenshots of all tasks working
- [ ] Videos of system operation

### Analysis Report
- [ ] Sensor reliability discussion
- [ ] Practical applications
- [ ] Challenges faced
- [ ] Solutions implemented
- [ ] Future improvements

---

## Next Steps

After completing all tasks:

1. **Experiment:** Try modifying thresholds and behaviors
2. **Combine:** Create your own sensor combinations
3. **Enhance:** Add WiFi (ESP32/NodeMCU) for IoT features
4. **Document:** Write detailed report of your findings
5. **Present:** Prepare demonstration for lab submission

---

## Support & Resources

### Documentation
- Arduino Reference: https://www.arduino.cc/reference/en/
- MFRC522 Library: https://github.com/miguelbalboa/rfid
- Sensor Datasheets: Check manufacturer websites

### Troubleshooting
- Check README.md for detailed circuit diagrams
- Review SENSOR_ANALYSIS.md for sensor limitations
- Test components individually before combining

---

## Safety Reminders

⚠️ **IMPORTANT:**
- Use 3.3V for RFID (NOT 5V!)
- Test flame sensor carefully with fire extinguisher nearby
- Gas sensors are NOT certified for safety-critical applications
- Always use certified detectors for real fire/gas safety
- Disconnect power when changing wiring

---

## Congratulations! 🎉

You've completed the IoT Lab Security System project!

You now understand:
- ✅ Multiple sensor types and their applications
- ✅ Digital and analog sensor interfacing
- ✅ SPI communication (RFID)
- ✅ Multi-sensor integration
- ✅ Real-world IoT system design

**Good luck with your lab submission!**

---

**Document Version:** 1.0  
**Last Updated:** 2026-01-27  
**Prepared for:** IoT Lab - BUBT CSE Department
