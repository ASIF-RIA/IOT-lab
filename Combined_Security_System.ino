/*
 * COMBINED SECURITY SYSTEM
 * Integrating Multiple Sensors for Comprehensive Home/Office Security
 * 
 * Sensors Integrated:
 * 1. PIR Motion Sensor - Intrusion detection
 * 2. IR Obstacle Sensor - Perimeter monitoring
 * 3. Flame Sensor - Fire detection
 * 4. MQ2 Smoke Sensor - Smoke/gas detection
 * 5. MQ7 CO Sensor - Carbon monoxide detection
 * 6. FSR Pressure Sensor - Floor pressure monitoring
 * 7. RFID RC522 - Access control
 * 
 * Circuit Connections:
 * PIR OUT    -> D2
 * IR OUT     -> D3
 * Flame OUT  -> D4
 * MQ2 AO     -> A0
 * MQ7 AO     -> A2
 * FSR        -> A3
 * 
 * RFID SDA   -> D10
 * RFID SCK   -> D13
 * RFID MOSI  -> D11
 * RFID MISO  -> D12
 * RFID RST   -> D9
 * 
 * Green LED  -> D5 (System OK)
 * Red LED    -> D6 (Alert)
 * Blue LED   -> D7 (Motion)
 * Buzzer     -> D8
 * Relay      -> A4 (Door lock)
 */

#include <SPI.h>
#include <MFRC522.h>

// ========== PIN DEFINITIONS ==========
// Digital Sensors
#define PIR_PIN         2
#define IR_PIN          3
#define FLAME_PIN       4

// Analog Sensors
#define MQ2_PIN         A0
#define MQ7_PIN         A2
#define FSR_PIN         A3

// RFID
#define RST_PIN         9
#define SS_PIN          10

// Outputs
#define GREEN_LED       5
#define RED_LED         6
#define BLUE_LED        7
#define BUZZER          8
#define RELAY           A4

// ========== RFID SETUP ==========
MFRC522 mfrc522(SS_PIN, RST_PIN);

byte authorizedUIDs[][4] = {
  {0xDE, 0xAD, 0xBE, 0xEF},
  {0xCA, 0xFE, 0xBA, 0xBE},
  {0x12, 0x34, 0x56, 0x78}
};
const int numAuthorizedCards = 3;

// ========== THRESHOLDS ==========
const int SMOKE_THRESHOLD = 400;
const int CO_THRESHOLD = 450;
const int PRESSURE_THRESHOLD = 200;

// ========== SYSTEM STATES ==========
enum SecurityLevel {
  LEVEL_NORMAL,      // All systems normal
  LEVEL_CAUTION,     // Minor alert
  LEVEL_WARNING,     // Moderate alert
  LEVEL_CRITICAL     // Emergency
};

SecurityLevel currentLevel = LEVEL_NORMAL;
bool systemArmed = false;
bool accessGranted = false;

// ========== SENSOR READINGS ==========
struct SensorData {
  bool motion;
  bool obstacle;
  bool flame;
  int smokeLevel;
  int coLevel;
  int pressureLevel;
  String lastRFID;
  unsigned long timestamp;
};

SensorData currentReadings;

// ========== TIMING ==========
unsigned long lastSensorCheck = 0;
unsigned long lastStatusReport = 0;
unsigned long accessGrantedTime = 0;
unsigned long alarmStartTime = 0;

const unsigned long SENSOR_CHECK_INTERVAL = 500;
const unsigned long STATUS_REPORT_INTERVAL = 5000;
const unsigned long DOOR_OPEN_TIME = 5000;
const unsigned long ALARM_DURATION = 30000;

// ========== ALARM FLAGS ==========
bool fireAlarm = false;
bool gasAlarm = false;
bool intrusionAlarm = false;

void setup() {
  Serial.begin(9600);
  while (!Serial);
  
  // Initialize pins
  pinMode(PIR_PIN, INPUT);
  pinMode(IR_PIN, INPUT);
  pinMode(FLAME_PIN, INPUT);
  pinMode(MQ2_PIN, INPUT);
  pinMode(MQ7_PIN, INPUT);
  pinMode(FSR_PIN, INPUT);
  
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(RELAY, OUTPUT);
  
  // Initialize RFID
  SPI.begin();
  mfrc522.PCD_Init();
  
  // Initial state
  digitalWrite(GREEN_LED, HIGH);
  digitalWrite(RED_LED, LOW);
  digitalWrite(BLUE_LED, LOW);
  digitalWrite(BUZZER, LOW);
  digitalWrite(RELAY, LOW);
  
  // Display banner
  displayBanner();
  
  // Warm up gas sensors
  Serial.println("Warming up gas sensors (20 seconds)...");
  for (int i = 20; i > 0; i--) {
    if (i % 5 == 0) {
      Serial.print("  ");
      Serial.print(i);
      Serial.println(" seconds remaining...");
    }
    delay(1000);
  }
  
  Serial.println("\n✓ All systems initialized");
  Serial.println("✓ Security system ready");
  Serial.println("\nType 'ARM' to arm the system");
  Serial.println("Type 'DISARM' to disarm the system");
  Serial.println("════════════════════════════════════════\n");
  
  systemArmed = true; // Auto-arm on startup
  Serial.println("🛡️  SYSTEM ARMED - Full monitoring active");
}

void loop() {
  unsigned long currentTime = millis();
  
  // Check for serial commands
  checkSerialCommands();
  
  // Read all sensors periodically
  if (currentTime - lastSensorCheck >= SENSOR_CHECK_INTERVAL) {
    lastSensorCheck = currentTime;
    readAllSensors();
    evaluateSecurity();
  }
  
  // Check RFID
  checkRFID();
  
  // Handle access control
  if (accessGranted && currentTime - accessGrantedTime >= DOOR_OPEN_TIME) {
    lockDoor();
  }
  
  // Status report
  if (currentTime - lastStatusReport >= STATUS_REPORT_INTERVAL) {
    lastStatusReport = currentTime;
    displayStatusReport();
  }
  
  // Update visual indicators
  updateIndicators();
}

void readAllSensors() {
  currentReadings.motion = digitalRead(PIR_PIN);
  currentReadings.obstacle = !digitalRead(IR_PIN); // IR is LOW when object detected
  currentReadings.flame = !digitalRead(FLAME_PIN); // Flame is LOW when detected
  currentReadings.smokeLevel = analogRead(MQ2_PIN);
  currentReadings.coLevel = analogRead(MQ7_PIN);
  currentReadings.pressureLevel = analogRead(FSR_PIN);
  currentReadings.timestamp = millis();
}

void evaluateSecurity() {
  SecurityLevel previousLevel = currentLevel;
  currentLevel = LEVEL_NORMAL;
  
  // Check for critical conditions
  if (currentReadings.flame) {
    currentLevel = LEVEL_CRITICAL;
    if (!fireAlarm) {
      fireAlarm = true;
      triggerFireAlarm();
    }
  }
  
  if (currentReadings.smokeLevel > SMOKE_THRESHOLD + 200) {
    currentLevel = LEVEL_CRITICAL;
    if (!gasAlarm) {
      gasAlarm = true;
      triggerGasAlarm();
    }
  }
  
  if (currentReadings.coLevel > CO_THRESHOLD + 150) {
    currentLevel = LEVEL_CRITICAL;
    if (!gasAlarm) {
      gasAlarm = true;
      triggerCOAlarm();
    }
  }
  
  // Check for warning conditions
  if (currentLevel != LEVEL_CRITICAL) {
    if (currentReadings.smokeLevel > SMOKE_THRESHOLD || 
        currentReadings.coLevel > CO_THRESHOLD) {
      currentLevel = LEVEL_WARNING;
    }
  }
  
  // Check for intrusion (only if armed)
  if (systemArmed && !accessGranted) {
    if (currentReadings.motion || currentReadings.obstacle || 
        currentReadings.pressureLevel > PRESSURE_THRESHOLD) {
      if (currentLevel < LEVEL_WARNING) {
        currentLevel = LEVEL_WARNING;
      }
      if (!intrusionAlarm) {
        intrusionAlarm = true;
        triggerIntrusionAlarm();
      }
    }
  }
  
  // Clear alarms if conditions normalized
  if (!currentReadings.flame && currentReadings.smokeLevel < SMOKE_THRESHOLD) {
    fireAlarm = false;
    gasAlarm = false;
  }
  
  // Level change notification
  if (currentLevel != previousLevel) {
    Serial.println("\n⚠️  SECURITY LEVEL CHANGED: " + getLevelString(currentLevel));
  }
}

void checkRFID() {
  if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) {
    return;
  }
  
  String uid = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    uid += String(mfrc522.uid.uidByte[i], HEX);
  }
  
  if (isAuthorized(mfrc522.uid.uidByte, mfrc522.uid.size)) {
    grantAccess(uid);
  } else {
    denyAccess(uid);
  }
  
  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
}

bool isAuthorized(byte *uid, byte uidSize) {
  for (int i = 0; i < numAuthorizedCards; i++) {
    bool match = true;
    for (byte j = 0; j < uidSize; j++) {
      if (uid[j] != authorizedUIDs[i][j]) {
        match = false;
        break;
      }
    }
    if (match) return true;
  }
  return false;
}

void grantAccess(String uid) {
  Serial.println("\n╔════════════════════════════════════════╗");
  Serial.println("║        ✓ ACCESS GRANTED ✓             ║");
  Serial.println("╚════════════════════════════════════════╝");
  
  accessGranted = true;
  accessGrantedTime = millis();
  intrusionAlarm = false; // Clear intrusion alarm
  
  digitalWrite(RELAY, HIGH); // Unlock door
  
  tone(BUZZER, 1500, 100);
  delay(120);
  tone(BUZZER, 2000, 100);
  
  Serial.println("Door unlocked for 5 seconds\n");
}

void denyAccess(String uid) {
  Serial.println("\n╔════════════════════════════════════════╗");
  Serial.println("║        ✗ ACCESS DENIED ✗              ║");
  Serial.println("╚════════════════════════════════════════╝\n");
  
  for (int i = 0; i < 3; i++) {
    tone(BUZZER, 400, 200);
    delay(250);
  }
}

void lockDoor() {
  digitalWrite(RELAY, LOW);
  accessGranted = false;
  tone(BUZZER, 800, 100);
  Serial.println("🔒 Door locked");
}

void triggerFireAlarm() {
  Serial.println("\n🔥🔥🔥 FIRE DETECTED! 🔥🔥🔥");
  Serial.println("EVACUATE IMMEDIATELY!");
  alarmStartTime = millis();
}

void triggerGasAlarm() {
  Serial.println("\n💨💨💨 SMOKE/GAS DETECTED! 💨💨💨");
  Serial.println("VENTILATE AREA!");
  alarmStartTime = millis();
}

void triggerCOAlarm() {
  Serial.println("\n☠️☠️☠️ CARBON MONOXIDE DETECTED! ☠️☠️☠️");
  Serial.println("EVACUATE AND CALL EMERGENCY!");
  alarmStartTime = millis();
}

void triggerIntrusionAlarm() {
  if (systemArmed) {
    Serial.println("\n🚨 INTRUSION DETECTED!");
    Serial.println("Motion/Pressure detected in secured area");
    alarmStartTime = millis();
  }
}

void updateIndicators() {
  switch (currentLevel) {
    case LEVEL_NORMAL:
      digitalWrite(GREEN_LED, HIGH);
      digitalWrite(RED_LED, LOW);
      digitalWrite(BLUE_LED, currentReadings.motion && systemArmed);
      noTone(BUZZER);
      break;
      
    case LEVEL_CAUTION:
      digitalWrite(GREEN_LED, LOW);
      digitalWrite(RED_LED, LOW);
      digitalWrite(BLUE_LED, HIGH);
      break;
      
    case LEVEL_WARNING:
      digitalWrite(GREEN_LED, LOW);
      digitalWrite(RED_LED, (millis() / 500) % 2); // Slow blink
      digitalWrite(BLUE_LED, currentReadings.motion);
      if ((millis() / 1000) % 2 == 0) {
        tone(BUZZER, 1000, 200);
      }
      break;
      
    case LEVEL_CRITICAL:
      digitalWrite(GREEN_LED, LOW);
      digitalWrite(RED_LED, (millis() / 200) % 2); // Fast blink
      digitalWrite(BLUE_LED, LOW);
      if ((millis() / 300) % 2 == 0) {
        tone(BUZZER, 2000, 150);
      }
      break;
  }
}

void displayStatusReport() {
  Serial.println("\n═══════ SECURITY STATUS REPORT ═══════");
  Serial.println("System: " + String(systemArmed ? "ARMED 🛡️" : "DISARMED"));
  Serial.println("Level:  " + getLevelString(currentLevel));
  Serial.println();
  Serial.println("Sensors:");
  Serial.println("  Motion:   " + String(currentReadings.motion ? "DETECTED" : "Clear"));
  Serial.println("  Obstacle: " + String(currentReadings.obstacle ? "DETECTED" : "Clear"));
  Serial.println("  Flame:    " + String(currentReadings.flame ? "DETECTED ⚠️" : "Clear"));
  Serial.println("  Smoke:    " + String(currentReadings.smokeLevel) + 
                 (currentReadings.smokeLevel > SMOKE_THRESHOLD ? " ⚠️" : ""));
  Serial.println("  CO Level: " + String(currentReadings.coLevel) + 
                 (currentReadings.coLevel > CO_THRESHOLD ? " ⚠️" : ""));
  Serial.println("  Pressure: " + String(currentReadings.pressureLevel));
  Serial.println("  Door:     " + String(accessGranted ? "UNLOCKED" : "LOCKED"));
  Serial.println("═══════════════════════════════════════\n");
}

void checkSerialCommands() {
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    command.trim();
    command.toUpperCase();
    
    if (command == "ARM") {
      systemArmed = true;
      Serial.println("🛡️  System ARMED");
      tone(BUZZER, 1500, 100);
    } else if (command == "DISARM") {
      systemArmed = false;
      intrusionAlarm = false;
      Serial.println("System DISARMED");
      tone(BUZZER, 1000, 100);
    } else if (command == "STATUS") {
      displayStatusReport();
    }
  }
}

String getLevelString(SecurityLevel level) {
  switch (level) {
    case LEVEL_NORMAL:   return "NORMAL ✓";
    case LEVEL_CAUTION:  return "CAUTION ⚡";
    case LEVEL_WARNING:  return "WARNING ⚠️";
    case LEVEL_CRITICAL: return "CRITICAL 🚨";
    default: return "UNKNOWN";
  }
}

void displayBanner() {
  Serial.println("\n\n");
  Serial.println("╔════════════════════════════════════════╗");
  Serial.println("║                                        ║");
  Serial.println("║   INTEGRATED SECURITY SYSTEM v1.0      ║");
  Serial.println("║                                        ║");
  Serial.println("║   Multi-Sensor Protection Platform     ║");
  Serial.println("║                                        ║");
  Serial.println("╚════════════════════════════════════════╝");
  Serial.println();
  Serial.println("Sensors Active:");
  Serial.println("  ✓ PIR Motion Detection");
  Serial.println("  ✓ IR Obstacle Detection");
  Serial.println("  ✓ Flame Detection");
  Serial.println("  ✓ Smoke/Gas Detection (MQ2)");
  Serial.println("  ✓ CO Detection (MQ7)");
  Serial.println("  ✓ Pressure Detection (FSR)");
  Serial.println("  ✓ RFID Access Control");
  Serial.println();
  Serial.println("════════════════════════════════════════");
}
