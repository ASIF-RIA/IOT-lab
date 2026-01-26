/*
 * BONUS TASK: Motion-Based Smart Entry System
 * Sensors: PIR Motion Sensor + RFID RC522
 * 
 * Concept: Energy-efficient access control that only activates RFID reader
 * when motion is detected, saving power and improving security.
 * 
 * Circuit Connections:
 * PIR VCC    -> 5V
 * PIR GND    -> GND
 * PIR OUT    -> D2
 * 
 * RC522 SDA  -> D10
 * RC522 SCK  -> D13
 * RC522 MOSI -> D11
 * RC522 MISO -> D12
 * RC522 RST  -> D9
 * RC522 GND  -> GND
 * RC522 3.3V -> 3.3V
 * 
 * Green LED  -> D5 (with 220Ω resistor)
 * Red LED    -> D6 (with 220Ω resistor)
 * Blue LED   -> D3 (with 220Ω resistor) - Motion indicator
 * Buzzer     -> D7
 * Relay      -> D8 (Door lock)
 */

#include <SPI.h>
#include <MFRC522.h>

// Pin Definitions
#define PIR_PIN         2
#define RST_PIN         9
#define SS_PIN          10
#define GREEN_LED_PIN   5
#define RED_LED_PIN     6
#define BLUE_LED_PIN    3
#define BUZZER_PIN      7
#define RELAY_PIN       8

// Create MFRC522 instance
MFRC522 mfrc522(SS_PIN, RST_PIN);

// Authorized RFID UIDs
byte authorizedUIDs[][4] = {
  {0xDE, 0xAD, 0xBE, 0xEF},  // Replace with your card UID
  {0xCA, 0xFE, 0xBA, 0xBE},  // Replace with your card UID
  {0x12, 0x34, 0x56, 0x78}   // Replace with your card UID
};

const int numAuthorizedCards = sizeof(authorizedUIDs) / sizeof(authorizedUIDs[0]);

// System states
enum SystemState {
  IDLE,           // No motion, RFID reader off
  MOTION_DETECTED, // Motion detected, RFID reader active
  ACCESS_GRANTED,  // Valid card scanned
  ACCESS_DENIED    // Invalid card scanned
};

SystemState currentState = IDLE;

// Timing variables
unsigned long motionDetectedTime = 0;
unsigned long accessGrantedTime = 0;
const unsigned long rfidActiveTime = 10000;    // RFID stays active for 10 seconds after motion
const unsigned long doorOpenDuration = 5000;    // Door stays open for 5 seconds
const unsigned long deniedDisplayTime = 3000;   // Show denied status for 3 seconds

// Flags
bool rfidReaderActive = false;
bool motionActive = false;

void setup() {
  // Initialize Serial Monitor
  Serial.begin(9600);
  while (!Serial);
  
  // Initialize SPI bus
  SPI.begin();
  
  // Initialize MFRC522
  mfrc522.PCD_Init();
  
  // Set pin modes
  pinMode(PIR_PIN, INPUT);
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(BLUE_LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(RELAY_PIN, OUTPUT);
  
  // Initial state - all OFF
  setAllLEDsOff();
  digitalWrite(RELAY_PIN, LOW);
  
  // Display system info
  Serial.println("╔════════════════════════════════════════╗");
  Serial.println("║  Motion-Based Smart Entry System      ║");
  Serial.println("║  PIR + RFID Access Control v2.0       ║");
  Serial.println("╚════════════════════════════════════════╝");
  Serial.println();
  Serial.println("Features:");
  Serial.println("  • Energy-efficient design");
  Serial.println("  • Motion-activated RFID scanning");
  Serial.println("  • Automatic timeout and locking");
  Serial.println();
  Serial.print("RFID Firmware: 0x");
  Serial.println(mfrc522.PCD_ReadRegister(mfrc522.VersionReg), HEX);
  Serial.println("Authorized cards: " + String(numAuthorizedCards));
  Serial.println();
  Serial.println("System Ready - Monitoring for motion...");
  Serial.println("════════════════════════════════════════");
  
  // Startup sequence
  startupSequence();
  
  // Allow PIR to stabilize
  delay(2000);
}

void loop() {
  // Read PIR sensor
  int motionState = digitalRead(PIR_PIN);
  
  // State machine
  switch (currentState) {
    case IDLE:
      handleIdleState(motionState);
      break;
      
    case MOTION_DETECTED:
      handleMotionDetectedState(motionState);
      break;
      
    case ACCESS_GRANTED:
      handleAccessGrantedState();
      break;
      
    case ACCESS_DENIED:
      handleAccessDeniedState();
      break;
  }
  
  delay(100); // Small delay for stability
}

void handleIdleState(int motionState) {
  if (motionState == HIGH) {
    // Motion detected - activate RFID reader
    Serial.println("\n👤 Motion detected - Activating RFID reader...");
    
    currentState = MOTION_DETECTED;
    motionDetectedTime = millis();
    rfidReaderActive = true;
    
    // Blue LED indicates motion detected
    digitalWrite(BLUE_LED_PIN, HIGH);
    
    // Activation beep
    tone(BUZZER_PIN, 1200, 100);
    
    Serial.println("Please present your RFID card...");
    Serial.println("Reader active for 10 seconds");
  }
}

void handleMotionDetectedState(int motionState) {
  // Keep blue LED blinking while waiting for card
  static unsigned long lastBlink = 0;
  if (millis() - lastBlink > 500) {
    digitalWrite(BLUE_LED_PIN, !digitalRead(BLUE_LED_PIN));
    lastBlink = millis();
  }
  
  // Check for timeout
  if (millis() - motionDetectedTime > rfidActiveTime) {
    Serial.println("⏱️  Timeout - No card presented");
    Serial.println("Returning to idle mode...\n");
    
    currentState = IDLE;
    rfidReaderActive = false;
    setAllLEDsOff();
    
    // Timeout beep
    tone(BUZZER_PIN, 600, 200);
    return;
  }
  
  // Look for RFID card
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return;
  }
  
  if (!mfrc522.PICC_ReadCardSerial()) {
    return;
  }
  
  // Card detected - process it
  processRFIDCard();
  
  // Halt PICC
  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
}

void handleAccessGrantedState() {
  // Check if door should be locked
  if (millis() - accessGrantedTime >= doorOpenDuration) {
    lockDoor();
    currentState = IDLE;
    rfidReaderActive = false;
  }
}

void handleAccessDeniedState() {
  // Return to motion detected state after showing denied status
  if (millis() - accessGrantedTime >= deniedDisplayTime) {
    Serial.println("Returning to scan mode...\n");
    currentState = MOTION_DETECTED;
    setAllLEDsOff();
    digitalWrite(BLUE_LED_PIN, HIGH);
  }
}

void processRFIDCard() {
  // Show card UID
  Serial.println("\n🔍 Card scanned!");
  Serial.print("UID: ");
  String uidString = "";
  
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    uidString += String(mfrc522.uid.uidByte[i], HEX);
  }
  Serial.println();
  
  // Check authorization
  if (isAuthorized(mfrc522.uid.uidByte, mfrc522.uid.size)) {
    grantAccess(uidString);
  } else {
    denyAccess(uidString);
  }
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
  Serial.println("╔════════════════════════════════════════╗");
  Serial.println("║        ✓ ACCESS GRANTED ✓             ║");
  Serial.println("╚════════════════════════════════════════╝");
  Serial.println("Welcome! Entry authorized.");
  Serial.println("Door unlocking...");
  
  currentState = ACCESS_GRANTED;
  accessGrantedTime = millis();
  
  // Green LED ON, others OFF
  setAllLEDsOff();
  digitalWrite(GREEN_LED_PIN, HIGH);
  
  // Unlock door
  digitalWrite(RELAY_PIN, HIGH);
  
  // Success melody
  tone(BUZZER_PIN, 1500, 100);
  delay(120);
  tone(BUZZER_PIN, 1800, 100);
  delay(120);
  tone(BUZZER_PIN, 2200, 150);
  
  Serial.println("Door will lock in 5 seconds...");
  Serial.println("════════════════════════════════════════\n");
}

void denyAccess(String uid) {
  Serial.println("╔════════════════════════════════════════╗");
  Serial.println("║        ✗ ACCESS DENIED ✗              ║");
  Serial.println("╚════════════════════════════════════════╝");
  Serial.println("Unauthorized card!");
  Serial.println("Entry blocked.");
  
  currentState = ACCESS_DENIED;
  accessGrantedTime = millis();
  
  // Red LED ON, others OFF
  setAllLEDsOff();
  digitalWrite(RED_LED_PIN, HIGH);
  
  // Denial alarm
  for (int i = 0; i < 3; i++) {
    tone(BUZZER_PIN, 400, 200);
    delay(250);
  }
  
  Serial.println("════════════════════════════════════════\n");
}

void lockDoor() {
  Serial.println("🔒 Door locked - System returning to idle");
  digitalWrite(RELAY_PIN, LOW);
  setAllLEDsOff();
  
  // Lock beep
  tone(BUZZER_PIN, 800, 150);
  
  Serial.println("Monitoring for motion...\n");
}

void setAllLEDsOff() {
  digitalWrite(GREEN_LED_PIN, LOW);
  digitalWrite(RED_LED_PIN, LOW);
  digitalWrite(BLUE_LED_PIN, LOW);
}

void startupSequence() {
  // LED sequence
  digitalWrite(RED_LED_PIN, HIGH);
  delay(200);
  digitalWrite(RED_LED_PIN, LOW);
  digitalWrite(BLUE_LED_PIN, HIGH);
  delay(200);
  digitalWrite(BLUE_LED_PIN, LOW);
  digitalWrite(GREEN_LED_PIN, HIGH);
  delay(200);
  digitalWrite(GREEN_LED_PIN, LOW);
  
  // Startup tone
  tone(BUZZER_PIN, 1000, 100);
  delay(150);
  tone(BUZZER_PIN, 1500, 100);
}
