# Circuit Diagram Guide - Visual Reference

This document provides visual ASCII circuit diagrams for all tasks in the IoT Lab Security System project.

---

## General Symbols Used

```
→  Wire connection
┌─ Corner connection
├─ T-junction
│  Vertical wire
─  Horizontal wire
[R] Resistor
LED Light Emitting Diode
🔊  Buzzer
📡  Sensor
🔌  Power connection
```

---

## Task 1: PIR Motion Sensor Circuit

```
                    ┌─────────────────┐
                    │   ARDUINO UNO   │
                    │                 │
    PIR SENSOR      │                 │      BUZZER
    ┌─────────┐     │                 │      ┌───┐
    │  HC-SR501│     │                 │      │ 🔊│
    │         │     │                 │      │   │
    │   VCC ──┼─────┤ 5V              │      │   │
    │   GND ──┼─────┤ GND             │      │   │
    │   OUT ──┼─────┤ D2              │      │   │
    │         │     │                 │      │   │
    └─────────┘     │                 │      │   │
                    │ D8 ─────────────┼──────┤ + │
                    │                 │      │   │
                    │ GND ────────────┼──────┤ - │
                    │                 │      └───┘
                    │                 │
                    │                 │      LED (Red)
                    │                 │      ┌───┐
                    │                 │      │ │ │
                    │ D7 ─────[220Ω]──┼──────┤ + │
                    │                 │      │   │
                    │ GND ────────────┼──────┤ - │
                    │                 │      └───┘
                    └─────────────────┘
```

**Pin Connections:**
- PIR VCC → Arduino 5V
- PIR GND → Arduino GND
- PIR OUT → Arduino D2
- Buzzer + → Arduino D8
- Buzzer - → Arduino GND
- LED + → Arduino D7 (through 220Ω resistor)
- LED - → Arduino GND

---

## Task 2: IR Obstacle Detection Circuit

```
                    ┌─────────────────┐
                    │   ARDUINO UNO   │
    IR SENSOR       │                 │
    ┌─────────┐     │                 │      LED (Green)
    │  IR-FC51 │     │                 │      ┌───┐
    │         │     │                 │      │ │ │
    │   VCC ──┼─────┤ 5V              │      │   │
    │   GND ──┼─────┤ GND             │      │   │
    │   OUT ──┼─────┤ D3              │      │   │
    │         │     │                 │      │   │
    └─────────┘     │ D6 ─────[220Ω]──┼──────┤ + │
                    │                 │      │   │
                    │ GND ────────────┼──────┤ - │
                    │                 │      └───┘
                    └─────────────────┘
```

---

## Task 3: Flame Sensor Circuit

```
                    ┌─────────────────┐
                    │   ARDUINO UNO   │
    FLAME SENSOR    │                 │      BUZZER
    ┌─────────┐     │                 │      ┌───┐
    │  Flame   │     │                 │      │ 🔊│
    │  Module  │     │                 │      │   │
    │   VCC ──┼─────┤ 5V              │      │   │
    │   GND ──┼─────┤ GND             │      │   │
    │   DO  ──┼─────┤ D4              │      │   │
    │         │     │                 │      │   │
    └─────────┘     │ D9 ─────────────┼──────┤ + │
                    │                 │      │   │
                    │ GND ────────────┼──────┤ - │
                    │                 │      └───┘
                    │                 │
                    │                 │      LED (Red)
                    │                 │      ┌───┐
                    │ D10 ────[220Ω]──┼──────┤ + │
                    │                 │      │   │
                    │ GND ────────────┼──────┤ - │
                    │                 │      └───┘
                    └─────────────────┘
```

---

## Task 4: MQ2 Smoke Sensor Circuit

```
                    ┌─────────────────┐
                    │   ARDUINO UNO   │
    MQ2 SENSOR      │                 │      BUZZER
    ┌─────────┐     │                 │      ┌───┐
    │   MQ-2   │     │                 │      │ 🔊│
    │  Module  │     │                 │      │   │
    │   VCC ──┼─────┤ 5V              │      │   │
    │   GND ──┼─────┤ GND             │      │   │
    │   AO  ──┼─────┤ A0              │      │   │
    │   DO  ──┼─────┤ D5 (optional)   │      │   │
    │         │     │                 │      │   │
    └─────────┘     │ D11 ────────────┼──────┤ + │
                    │                 │      │   │
                    │ GND ────────────┼──────┤ - │
                    │                 │      └───┘
                    │                 │
                    │                 │      LED (Yellow)
                    │                 │      ┌───┐
                    │ D12 ────[220Ω]──┼──────┤ + │
                    │                 │      │   │
                    │ GND ────────────┼──────┤ - │
                    │                 │      └───┘
                    └─────────────────┘
```

---

## Task 7: FSR Pressure Sensor Circuit (Voltage Divider)

```
                    ┌─────────────────┐
                    │   ARDUINO UNO   │
                    │                 │
        5V ─────────┤ 5V              │
         │          │                 │
         │          │                 │      LED (Blue)
        FSR         │                 │      ┌───┐
         │          │                 │      │ │ │
         ├──────────┤ A3              │      │   │
         │          │                 │      │   │
       10kΩ         │ D6 ─────[220Ω]──┼──────┤ + │
         │          │                 │      │   │
        GND ────────┤ GND ────────────┼──────┤ - │
                    │                 │      └───┘
                    │                 │
                    │                 │      BUZZER
                    │                 │      ┌───┐
                    │ D10 ────────────┼──────┤ + │
                    │                 │      │   │
                    │ GND ────────────┼──────┤ - │
                    │                 │      └───┘
                    └─────────────────┘

Voltage Divider Formula:
V_out = V_in × (R2 / (R1 + R2))
Where:
  V_in = 5V
  R1 = FSR resistance (variable)
  R2 = 10kΩ (fixed)
  V_out = Voltage at A3
```

---

## Task 8: RFID RC522 Circuit (SPI Interface)

```
                    ┌─────────────────┐
    RFID RC522      │   ARDUINO UNO   │
    ┌─────────┐     │                 │
    │  RC522   │     │                 │
    │  Module  │     │                 │
    │         │     │                 │
    │  SDA  ──┼─────┤ D10 (SS)        │
    │  SCK  ──┼─────┤ D13 (SCK)       │
    │  MOSI ──┼─────┤ D11 (MOSI)      │
    │  MISO ──┼─────┤ D12 (MISO)      │
    │  IRQ  ──┼     │ (Not Connected) │
    │  GND  ──┼─────┤ GND             │
    │  RST  ──┼─────┤ D9              │
    │  3.3V ──┼─────┤ 3.3V ⚠️         │
    │         │     │                 │
    └─────────┘     │                 │      LED (Green)
                    │                 │      ┌───┐
                    │ D5 ─────[220Ω]──┼──────┤ + │
                    │                 │      │   │
                    │ GND ────────────┼──────┤ - │
                    │                 │      └───┘
                    │                 │
                    │                 │      LED (Red)
                    │                 │      ┌───┐
                    │ D6 ─────[220Ω]──┼──────┤ + │
                    │                 │      │   │
                    │ GND ────────────┼──────┤ - │
                    │                 │      └───┘
                    │                 │
                    │                 │      BUZZER
                    │                 │      ┌───┐
                    │ D7 ─────────────┼──────┤ + │
                    │                 │      │   │
                    │ GND ────────────┼──────┤ - │
                    │                 │      └───┘
                    │                 │
                    │                 │      RELAY
                    │                 │      ┌───┐
                    │ D8 ─────────────┼──────┤ IN│
                    │ 5V ─────────────┼──────┤VCC│
                    │ GND ────────────┼──────┤GND│
                    │                 │      └───┘
                    └─────────────────┘

⚠️ CRITICAL: RC522 uses 3.3V, NOT 5V! 5V will damage the module!
```

**SPI Pin Mapping:**
- SDA (SS) → D10
- SCK → D13
- MOSI → D11
- MISO → D12
- RST → D9

---

## Combined Security System - Complete Wiring

```
                        ┌─────────────────────────┐
                        │     ARDUINO UNO         │
                        │                         │
DIGITAL SENSORS         │                         │    ANALOG SENSORS
                        │                         │
PIR OUT ────────────────┤ D2                  A0 ─┼──── MQ2 AO
IR OUT ─────────────────┤ D3                  A1 ─┼──── MQ5 AO
Flame DO ───────────────┤ D4                  A2 ─┼──── MQ7 AO
                        │                     A3 ─┼──── FSR (with 10kΩ)
                        │                     A4 ─┼──── Relay IN
RFID (SPI)              │                         │
RC522 SDA ──────────────┤ D10 (SS)                │
RC522 SCK ──────────────┤ D13 (SCK)               │    OUTPUT INDICATORS
RC522 MOSI ─────────────┤ D11 (MOSI)              │
RC522 MISO ─────────────┤ D12 (MISO)          D5 ─┼──[220Ω]── Green LED
RC522 RST ──────────────┤ D9                  D6 ─┼──[220Ω]── Red LED
                        │                     D7 ─┼──[220Ω]── Blue LED
                        │                     D8 ─┼────────── Buzzer
                        │                         │
POWER                   │                         │
All VCC ────────────────┤ 5V (except RC522)       │
RC522 VCC ──────────────┤ 3.3V ⚠️                │
All GND ────────────────┤ GND                     │
                        │                         │
                        └─────────────────────────┘

LED Indicators:
  Green  - System Normal / Access Granted
  Red    - Alert / Access Denied
  Blue   - Motion Detected

Buzzer Patterns:
  Single beep    - Normal event
  Slow beep      - Warning
  Rapid beep     - Critical alert
  Continuous     - Emergency
```

---

## Breadboard Layout Example (Task 1 - PIR)

```
    Power Rails                 Arduino UNO
    + ─────────────────────────── 5V
    - ─────────────────────────── GND

    Breadboard Connections:
    
    Row  A  B  C  D  E    F  G  H  I  J
    ─────────────────────────────────────
    1    +  +  +  +  +    +  +  +  +  +   ← 5V Rail
    2    -  -  -  -  -    -  -  -  -  -   ← GND Rail
    3
    4    [PIR VCC]────────→ Row 1 (5V)
    5    [PIR GND]────────→ Row 2 (GND)
    6    [PIR OUT]────────→ D2
    7
    8    [Buzzer +]───────→ D8
    9    [Buzzer -]───────→ Row 2 (GND)
    10
    11   [LED +]──[220Ω]──→ D7
    12   [LED -]──────────→ Row 2 (GND)
```

---

## Power Distribution Diagram

```
    USB Power (5V from Computer)
           │
           ├──→ Arduino 5V Pin
           │    │
           │    ├──→ PIR Sensor (5V)
           │    ├──→ IR Sensor (5V)
           │    ├──→ Flame Sensor (5V)
           │    ├──→ MQ2 Sensor (5V)
           │    ├──→ MQ5 Sensor (5V)
           │    ├──→ MQ7 Sensor (5V)
           │    ├──→ Relay Module (5V)
           │    └──→ Breadboard + Rail
           │
           └──→ Arduino 3.3V Pin
                │
                └──→ RFID RC522 (3.3V) ⚠️

    Ground (GND) - Common for all components
           │
           ├──→ All Sensor GND
           ├──→ All LED Cathodes (-)
           ├──→ All Buzzer (-)
           └──→ Breadboard - Rail

⚠️ Current Requirements:
   - Arduino UNO: Max 500mA from USB
   - Total sensor current: ~300-400mA
   - For multiple gas sensors, use external 5V 2A power supply
```

---

## External Power Supply Connection (Recommended for Combined System)

```
    External 5V 2A Power Supply
           │
           ├──→ Arduino VIN Pin (or 5V Pin)
           │
           └──→ GND Pin

    OR use DC Barrel Jack:
    
    7-12V DC Adapter
           │
           └──→ Arduino DC Jack
                (Internal regulator provides 5V and 3.3V)

⚠️ When using external power:
   - Remove USB connection or use USB for programming only
   - Ensure common ground between all components
   - Use adequate current rating (2A minimum for all sensors)
```

---

## Relay Module Connection for Door Lock

```
    RELAY MODULE                    DOOR LOCK
    ┌──────────┐                   ┌──────────┐
    │          │                   │          │
    │  VCC ────┼──→ 5V             │          │
    │  GND ────┼──→ GND            │          │
    │  IN  ────┼──→ D8 (or A4)     │          │
    │          │                   │          │
    │  COM ────┼───────────────────┤ +12V     │
    │  NO  ────┼───────────────────┤ Lock +   │
    │  NC  ────┼ (Not used)        │          │
    │          │                   │ Lock -   │
    └──────────┘                   └────┬─────┘
                                        │
                                       GND

COM = Common
NO  = Normally Open (closes when relay activated)
NC  = Normally Closed (opens when relay activated)

⚠️ For AC door locks, use appropriate isolation and safety measures!
```

---

## Testing Points and Measurements

```
Test Point Locations:

1. Power Rails:
   - Measure 5V between + rail and - rail
   - Measure 3.3V at RFID VCC pin

2. Sensor Outputs:
   - PIR OUT: Should be 0V (LOW) or 5V (HIGH)
   - IR OUT: Should be 0V or 5V
   - Flame DO: Should be 0V or 5V
   - MQ2/5/7 AO: Should be 0-5V (analog)
   - FSR at A3: Should be 0-5V (analog)

3. LED Voltages:
   - Forward voltage: ~2V for Red, ~3V for Blue/Green
   - Current: ~10-20mA (with 220Ω resistor)

4. RFID Communication:
   - SDA, SCK, MOSI, MISO should show activity when scanning
   - Use logic analyzer or oscilloscope to verify SPI signals
```

---

## Common Wiring Mistakes to Avoid

```
❌ WRONG                          ✅ CORRECT

1. RFID Power:
   RC522 VCC → 5V                RC522 VCC → 3.3V
   (Will damage module!)         (Correct voltage)

2. LED Connection:
   LED + → GND                   LED + → Digital Pin (through resistor)
   LED - → Digital Pin           LED - → GND
   (Reversed polarity)           (Correct polarity)

3. FSR Circuit:
   FSR → A3 → Nothing            5V → FSR → A3 → 10kΩ → GND
   (No voltage divider)          (Proper voltage divider)

4. Sensor Power:
   Multiple sensors → Single     Multiple sensors → Breadboard rails
   Arduino pin                   → Arduino 5V pin
   (Exceeds pin current)         (Proper power distribution)

5. Ground:
   Separate grounds for          Common ground for all components
   different components          (Proper ground reference)
   (Ground loops, noise)
```

---

## Wire Color Coding (Recommended)

```
Standard Color Code:
  Red    → 5V / VCC / Positive
  Black  → GND / Ground / Negative
  Yellow → Digital Signals
  Green  → Analog Signals
  Blue   → SPI/I2C Communication
  White  → Special Functions

Example for PIR:
  Red    → PIR VCC to 5V
  Black  → PIR GND to GND
  Yellow → PIR OUT to D2
```

---

## Troubleshooting Flowchart

```
                    [System Not Working]
                            │
                            ▼
                    [Check Power]
                    5V present? ──NO──→ [Check USB/Power Supply]
                            │
                           YES
                            ▼
                    [Check Ground]
                    Common GND? ──NO──→ [Connect all GNDs]
                            │
                           YES
                            ▼
                    [Check Sensor]
                    Sensor powered? ──NO──→ [Check VCC/GND wiring]
                            │
                           YES
                            ▼
                    [Check Connections]
                    Pins correct? ──NO──→ [Verify pin assignments]
                            │
                           YES
                            ▼
                    [Check Code]
                    Uploaded? ──NO──→ [Upload correct sketch]
                            │
                           YES
                            ▼
                    [Check Serial Monitor]
                    Output shown? ──NO──→ [Check baud rate (9600)]
                            │
                           YES
                            ▼
                    [Test Individual Components]
```

---

## Safety Checklist

Before powering on:

- [ ] All connections secure
- [ ] No short circuits (check with multimeter)
- [ ] RFID using 3.3V (NOT 5V)
- [ ] LED resistors in place (220Ω)
- [ ] FSR voltage divider correct (10kΩ)
- [ ] Power supply adequate (2A for combined system)
- [ ] No loose wires touching
- [ ] Breadboard connections firm
- [ ] Code uploaded successfully
- [ ] Serial monitor ready (9600 baud)

---

## Quick Reference - Pin Summary

```
╔════════════════════════════════════════════════════╗
║  COMBINED SYSTEM PIN ASSIGNMENTS                  ║
╠════════════════════════════════════════════════════╣
║  Digital Pins:                                     ║
║    D2  - PIR Motion Sensor OUT                     ║
║    D3  - IR Obstacle Sensor OUT                    ║
║    D4  - Flame Sensor DO                           ║
║    D5  - Green LED (System OK)                     ║
║    D6  - Red LED (Alert)                           ║
║    D7  - Blue LED (Motion)                         ║
║    D8  - Buzzer                                    ║
║    D9  - RFID RST                                  ║
║    D10 - RFID SDA (SS)                             ║
║    D11 - RFID MOSI                                 ║
║    D12 - RFID MISO                                 ║
║    D13 - RFID SCK                                  ║
║                                                    ║
║  Analog Pins:                                      ║
║    A0  - MQ2 Smoke Sensor AO                       ║
║    A1  - MQ5 Gas Sensor AO                         ║
║    A2  - MQ7 CO Sensor AO                          ║
║    A3  - FSR Pressure Sensor                       ║
║    A4  - Relay Module IN (Door Lock)               ║
║                                                    ║
║  Power:                                            ║
║    5V  - All sensors except RFID                   ║
║    3.3V- RFID RC522 only                           ║
║    GND - Common ground for all                     ║
╚════════════════════════════════════════════════════╝
```

---

**End of Circuit Diagram Guide**

For more information, refer to:
- README.md - Complete project documentation
- QUICK_START_GUIDE.md - Step-by-step setup instructions
- SENSOR_ANALYSIS.md - Detailed sensor specifications
