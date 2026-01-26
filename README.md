# IoT Lab Tasks - Complete Security System Project

## Project Overview
This project implements a comprehensive multi-sensor security system using Arduino/NodeMCU/ESP32. It integrates 7 different sensors for complete environmental monitoring and access control.

## Table of Contents
1. [Components Required](#components-required)
2. [Task Descriptions](#task-descriptions)
3. [Circuit Diagrams](#circuit-diagrams)
4. [Installation Guide](#installation-guide)
5. [Usage Instructions](#usage-instructions)
6. [Sensor Analysis](#sensor-analysis)
7. [Practical Applications](#practical-applications)

---

## Components Required

### Microcontroller
- Arduino UNO / NodeMCU / ESP32 (1x)
- USB Cable for programming

### Sensors
1. **PIR Motion Sensor** (HC-SR501) - 1x
2. **IR Obstacle Detection Sensor** - 1x
3. **Flame Sensor** - 1x
4. **MQ2 Gas Sensor** (Smoke/LPG) - 1x
5. **MQ5 Gas Sensor** (Natural Gas) - 1x
6. **MQ7 Gas Sensor** (Carbon Monoxide) - 1x
7. **FSR (Force Sensitive Resistor)** - 1x
8. **RFID Module RC522** - 1x
9. **RFID Tags/Cards** - 3-5x

### Output Components
- Buzzer (Active or Passive) - 1-2x
- LEDs (Red, Green, Blue) - 3-5x
- 220Ω Resistors for LEDs - 3-5x
- 10kΩ Resistor for FSR - 1x
- 5V Relay Module (for door lock) - 1x

### Other Components
- Breadboard (830 points recommended)
- Jumper Wires (Male-to-Male, Male-to-Female)
- Power Supply (5V, 2A recommended)

---

## Task Descriptions

### Task 1: Motion Detection (PIR Sensor)
**Objective:** Detect human motion and trigger alerts

**How it works:**
- PIR sensor detects infrared radiation changes
- Outputs HIGH when motion detected
- Triggers buzzer and LED for visual/audio alert

**Applications:**
- Automatic lighting systems
- Security intrusion detection
- Occupancy monitoring

---

### Task 2: Object Detection (IR Sensor)
**Objective:** Detect obstacles in proximity

**How it works:**
- IR sensor emits infrared light
- Detects reflection from nearby objects
- Outputs LOW when object detected

**Applications:**
- Automatic door opening
- Robot obstacle avoidance
- Parking sensors

---

### Task 3: Fire Detection (Flame Sensor)
**Objective:** Detect fire/flames for safety

**How it works:**
- Detects infrared wavelengths emitted by flames
- Typically outputs LOW when flame detected
- Triggers immediate fire alarm

**Applications:**
- Fire alarm systems
- Industrial safety monitoring
- Kitchen safety systems

---

### Task 4: Smoke Detection (MQ2 Sensor)
**Objective:** Detect smoke and combustible gases

**How it works:**
- Analog sensor measures gas concentration
- Higher values indicate more smoke/gas
- Threshold-based alerting system

**Detects:**
- Smoke
- LPG
- Propane
- Methane
- Hydrogen

**Applications:**
- Home fire safety
- Gas leak detection
- Air quality monitoring

---

### Task 5: Gas Detection (MQ5 Sensor)
**Objective:** Detect natural gas and LPG

**How it works:**
- Measures gas concentration in air
- Analog output (0-1023)
- Multi-level threshold alerts

**Detects:**
- Natural Gas
- LPG
- Coal Gas

**Applications:**
- Kitchen gas leak detection
- Industrial gas monitoring
- Safety systems

---

### Task 6: CO Detection (MQ7 Sensor)
**Objective:** Detect deadly carbon monoxide

**How it works:**
- Specifically calibrated for CO detection
- Requires 60-second warm-up time
- Critical safety thresholds

**Applications:**
- Home CO safety
- Garage monitoring
- Heating system safety

---

### Task 7: Pressure Detection (FSR)
**Objective:** Detect force/pressure application

**How it works:**
- Resistance decreases with applied pressure
- Voltage divider circuit converts to readable value
- Multi-level pressure detection

**Applications:**
- Floor mat sensors
- Weight detection
- Touch-sensitive controls
- Seat occupancy detection

---

### Task 8: RFID Access Control
**Objective:** Secure access control system

**How it works:**
- RFID reader scans card/tag UID
- Compares with authorized list
- Grants/denies access accordingly

**Applications:**
- Door access control
- Attendance systems
- Secure entry points
- Vehicle access

---

### Bonus Task: Motion-Based Smart Entry
**Objective:** Energy-efficient access control

**How it works:**
1. PIR detects person approaching
2. Activates RFID reader (saves power)
3. Scans card and grants/denies access
4. Auto-timeout if no card presented

**Advantages:**
- Power efficient (RFID only active when needed)
- Better user experience
- Enhanced security

---

## Circuit Diagrams

### Task 1: PIR Motion Sensor
```
PIR Sensor          Arduino
──────────          ───────
VCC     ────────────  5V
GND     ────────────  GND
OUT     ────────────  D2

Buzzer              Arduino
──────              ───────
+       ────────────  D8
-       ────────────  GND

LED                 Arduino
───                 ───────
+ (Anode) ──[220Ω]── D7
- (Cathode) ─────────  GND
```

### Task 2: IR Obstacle Sensor
```
IR Sensor           Arduino
─────────           ───────
VCC     ────────────  5V
GND     ────────────  GND
OUT     ────────────  D3

LED                 Arduino
───                 ───────
+ (Anode) ──[220Ω]── D6
- (Cathode) ─────────  GND
```

### Task 3: Flame Sensor
```
Flame Sensor        Arduino
────────────        ───────
VCC     ────────────  5V
GND     ────────────  GND
DO      ────────────  D4

Buzzer              Arduino
──────              ───────
+       ────────────  D9
-       ────────────  GND

Red LED             Arduino
───────             ───────
+ (Anode) ──[220Ω]── D10
- (Cathode) ─────────  GND
```

### Task 4: MQ2 Smoke Sensor
```
MQ2 Sensor          Arduino
──────────          ───────
VCC     ────────────  5V
GND     ────────────  GND
AO      ────────────  A0
DO      ────────────  D5 (optional)

Buzzer              Arduino
──────              ───────
+       ────────────  D11
-       ────────────  GND

LED                 Arduino
───                 ───────
+ (Anode) ──[220Ω]── D12
- (Cathode) ─────────  GND
```

### Task 5: MQ5 Gas Sensor
```
MQ5 Sensor          Arduino
──────────          ───────
VCC     ────────────  5V
GND     ────────────  GND
AO      ────────────  A1

Buzzer              Arduino
──────              ───────
+       ────────────  D13
-       ────────────  GND

LED                 Arduino
───                 ───────
+ (Anode) ──[220Ω]── D7
- (Cathode) ─────────  GND
```

### Task 6: MQ7 CO Sensor
```
MQ7 Sensor          Arduino
──────────          ───────
VCC     ────────────  5V
GND     ────────────  GND
AO      ────────────  A2

Buzzer              Arduino
──────              ───────
+       ────────────  D8
-       ────────────  GND

Red LED             Arduino
───────             ───────
+ (Anode) ──[220Ω]── D9
- (Cathode) ─────────  GND
```

### Task 7: FSR Pressure Sensor
```
FSR Circuit (Voltage Divider):

        5V
         │
         │
        FSR
         │
         ├──────────── A3 (Arduino)
         │
       10kΩ
         │
        GND

LED                 Arduino
───                 ───────
+ (Anode) ──[220Ω]── D6
- (Cathode) ─────────  GND

Buzzer              Arduino
──────              ───────
+       ────────────  D10
-       ────────────  GND
```

### Task 8: RFID RC522
```
RC522 Module        Arduino
────────────        ───────
SDA     ────────────  D10
SCK     ────────────  D13
MOSI    ────────────  D11
MISO    ────────────  D12
IRQ     ────────────  (Not Connected)
GND     ────────────  GND
RST     ────────────  D9
3.3V    ────────────  3.3V ⚠️ IMPORTANT!

Green LED           Arduino
─────────           ───────
+ (Anode) ──[220Ω]── D5
- (Cathode) ─────────  GND

Red LED             Arduino
───────             ───────
+ (Anode) ──[220Ω]── D6
- (Cathode) ─────────  GND

Buzzer              Arduino
──────              ───────
+       ────────────  D7
-       ────────────  GND

Relay Module        Arduino
────────────        ───────
VCC     ────────────  5V
GND     ────────────  GND
IN      ────────────  D8
```

### Combined Security System Wiring
```
All sensors connected as per individual tasks
Shared components:
- Green LED (D5) - System OK
- Red LED (D6) - Alert
- Blue LED (D7) - Motion
- Buzzer (D8) - Alarms
- Relay (A4) - Door Lock
```

---

## Installation Guide

### 1. Arduino IDE Setup
1. Download and install Arduino IDE from [arduino.cc](https://www.arduino.cc/en/software)
2. Install required libraries:
   - Go to **Sketch → Include Library → Manage Libraries**
   - Search and install:
     - `MFRC522` by GithubCommunity (for RFID)
     - `SPI` (usually pre-installed)

### 2. Hardware Assembly
1. Connect components according to circuit diagrams
2. Double-check all connections
3. Ensure proper power supply (5V, adequate current)
4. **IMPORTANT:** Connect RFID to 3.3V, NOT 5V!

### 3. Code Upload
1. Open the desired `.ino` file in Arduino IDE
2. Select correct board: **Tools → Board → Arduino UNO** (or your board)
3. Select correct port: **Tools → Port → COM X**
4. Click **Upload** button (→)
5. Wait for "Done uploading" message

### 4. RFID Card Setup
1. Upload `Task8_RFID_Access_Control.ino`
2. Open Serial Monitor (Ctrl+Shift+M)
3. Set baud rate to **9600**
4. Scan your RFID cards to see their UIDs
5. Copy the UID values
6. Replace the example UIDs in the code:
   ```cpp
   byte authorizedUIDs[][4] = {
     {0xYOUR, 0xUID, 0xHERE, 0xXXXX},  // Your actual UID
   };
   ```
7. Re-upload the code

---

## Usage Instructions

### Individual Task Testing
1. Upload the specific task code
2. Open Serial Monitor (9600 baud)
3. Observe sensor readings
4. Test with appropriate stimulus:
   - PIR: Wave hand in front
   - IR: Place object nearby
   - Flame: Use lighter (carefully!)
   - MQ2/MQ5/MQ7: Wait for warm-up, test with safe gas source
   - FSR: Press with finger/weight
   - RFID: Scan cards

### Combined Security System
1. Upload `Combined_Security_System.ino`
2. Wait for gas sensor warm-up (20 seconds)
3. System auto-arms on startup
4. Serial commands:
   - Type `ARM` to arm the system
   - Type `DISARM` to disarm
   - Type `STATUS` for full status report
5. Monitor all sensors simultaneously
6. Scan RFID card to unlock door

### Bonus Task (Motion-Based Entry)
1. Upload `Bonus_Task_PIR_RFID_Smart_Entry.ino`
2. System starts in idle mode
3. Approach the sensor (PIR detects motion)
4. Blue LED activates - RFID reader is now active
5. Scan your card within 10 seconds
6. Door unlocks for 5 seconds if authorized

---

## Sensor Analysis

### Reliability Assessment

#### PIR Motion Sensor
**Reliability: ★★★★☆ (4/5)**
- **Pros:**
  - Very reliable for motion detection
  - Low false positive rate
  - Wide detection range (up to 7m)
  - Low power consumption
- **Cons:**
  - Can be triggered by pets
  - Affected by temperature changes
  - Requires stabilization time
- **Best Use:** Indoor security, automatic lighting

#### IR Obstacle Sensor
**Reliability: ★★★☆☆ (3/5)**
- **Pros:**
  - Fast response time
  - Good for short-range detection
  - Not affected by ambient light (most models)
- **Cons:**
  - Limited range (2-30cm typically)
  - Can miss dark/absorbing objects
  - Requires calibration
- **Best Use:** Proximity detection, line following robots

#### Flame Sensor
**Reliability: ★★★★☆ (4/5)**
- **Pros:**
  - Detects flames at specific IR wavelengths
  - Fast response
  - Good detection range
- **Cons:**
  - Can be triggered by sunlight
  - May miss small flames
  - Requires line of sight
- **Best Use:** Fire detection in controlled environments

#### MQ2 Smoke Sensor
**Reliability: ★★★☆☆ (3/5)**
- **Pros:**
  - Detects multiple gas types
  - Analog output for concentration measurement
  - Relatively inexpensive
- **Cons:**
  - Requires long warm-up (20+ seconds)
  - Affected by humidity and temperature
  - Not highly selective
  - Needs calibration
- **Best Use:** General smoke/gas detection, not critical safety

#### MQ5 Gas Sensor
**Reliability: ★★★☆☆ (3/5)**
- **Pros:**
  - Good for LPG/natural gas detection
  - Analog output
- **Cons:**
  - Similar to MQ2 limitations
  - Cross-sensitivity to other gases
  - Drift over time
- **Best Use:** Kitchen gas leak detection

#### MQ7 CO Sensor
**Reliability: ★★★★☆ (4/5)**
- **Pros:**
  - Specifically designed for CO
  - Critical safety application
  - Better selectivity than MQ2/MQ5
- **Cons:**
  - Requires longer warm-up (60 seconds)
  - Needs regular calibration
  - Temperature dependent
- **Best Use:** CO safety monitoring (with regular calibration)

#### FSR (Force Sensitive Resistor)
**Reliability: ★★★☆☆ (3/5)**
- **Pros:**
  - Simple to use
  - Flexible and thin
  - Wide pressure range
- **Cons:**
  - Not very accurate
  - Hysteresis effects
  - Degrades over time
  - Temperature sensitive
- **Best Use:** Presence detection, not precision measurement

#### RFID RC522
**Reliability: ★★★★★ (5/5)**
- **Pros:**
  - Very reliable identification
  - Fast read speed
  - Secure (encrypted communication)
  - Long tag lifespan
- **Cons:**
  - Limited range (few cm)
  - Requires SPI interface
  - Tags can be cloned (security consideration)
- **Best Use:** Access control, identification systems

---

## Practical Applications

### 1. Smart Home Security System
**Components:** PIR + Flame + MQ2 + RFID
- Motion detection for intrusion
- Fire and smoke detection
- Authorized access control
- Automated emergency response

### 2. Industrial Safety Monitor
**Components:** MQ5 + MQ7 + Flame
- Gas leak detection in facilities
- CO monitoring in enclosed spaces
- Fire detection in warehouses
- Automated ventilation control

### 3. Smart Office Entry
**Components:** PIR + RFID + FSR
- Motion-activated access control
- Occupancy tracking
- Energy-efficient lighting
- Attendance logging

### 4. Elderly Care System
**Components:** PIR + FSR + MQ7
- Fall detection (FSR in floor)
- Movement monitoring
- CO safety in living spaces
- Emergency alert system

### 5. Parking Management
**Components:** IR + RFID + FSR
- Vehicle detection (IR/FSR)
- Automated gate control (RFID)
- Parking space monitoring
- Access logging

### 6. Fire Safety System
**Components:** Flame + MQ2 + Buzzer
- Multi-point fire detection
- Smoke detection
- Automated alarm system
- Emergency notification

### 7. Smart Kitchen Safety
**Components:** MQ5 + Flame + MQ2
- Gas leak detection
- Stove fire detection
- Smoke monitoring
- Automated gas shutoff

---

## Troubleshooting

### Common Issues

**RFID not reading cards:**
- Check 3.3V connection (NOT 5V!)
- Verify SPI wiring
- Ensure MFRC522 library is installed
- Check card is compatible (13.56MHz)

**Gas sensors always showing high values:**
- Allow proper warm-up time (20-60 seconds)
- Check if sensor needs calibration
- Verify analog pin connection

**PIR constantly triggering:**
- Adjust sensitivity potentiometer
- Ensure stable mounting
- Check for heat sources nearby
- Allow stabilization time

**FSR not responding:**
- Check voltage divider circuit
- Verify 10kΩ resistor value
- Test with multimeter
- Ensure good contact

---

## Safety Warnings

⚠️ **IMPORTANT SAFETY NOTES:**

1. **Gas Sensors:** These are NOT certified safety devices. Do not rely solely on them for life-safety applications.

2. **Flame Sensor:** Test carefully with controlled flame sources. Keep fire extinguisher nearby.

3. **RFID Power:** Always use 3.3V for RC522, NOT 5V! 5V will damage the module.

4. **High Voltage:** If using relay for actual door locks, ensure proper electrical safety.

5. **Testing:** Always test in safe, controlled environments first.

---

## Future Enhancements

1. **IoT Integration:**
   - Add WiFi (ESP32/NodeMCU)
   - Cloud data logging
   - Mobile app notifications
   - Remote monitoring

2. **Advanced Features:**
   - Machine learning for anomaly detection
   - Camera integration
   - Voice alerts
   - SMS/Email notifications

3. **Power Management:**
   - Battery backup
   - Solar power option
   - Sleep modes for energy efficiency

4. **Data Analytics:**
   - Historical data logging
   - Pattern recognition
   - Predictive maintenance
   - Usage statistics

---

## Credits

**Prepared By:** Sudipto Ghosh  
**Department:** CSE, BUBT  
**Course:** IoT Laboratory

**Student Implementation:**  
[Your Name]  
[Your ID]  
[Date]

---

## License

This project is for educational purposes. Feel free to modify and enhance for your learning.

---

## References

1. Arduino Official Documentation: https://www.arduino.cc/reference/en/
2. MFRC522 Library: https://github.com/miguelbalboa/rfid
3. Sensor Datasheets (refer to manufacturer specifications)

---

**End of Documentation**
