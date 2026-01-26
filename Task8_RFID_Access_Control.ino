/*
 * Task 8: RFID Access Control System
 * Sensor: RFID Module RC522
 * 
 * Circuit Connections (SPI Interface):
 * RC522 SDA  -> D10
 * RC522 SCK  -> D13
 * RC522 MOSI -> D11
 * RC522 MISO -> D12
 * RC522 IRQ  -> Not connected
 * RC522 GND  -> GND
 * RC522 RST  -> D9
 * RC522 3.3V -> 3.3V (IMPORTANT: Use 3.3V, not 5V!)
 * 
 * Green LED + -> D5 (with 220Ω resistor)
 * Red LED +   -> D6 (with 220Ω resistor)
 * Buzzer +    -> D7
 * Relay IN    -> D8 (for door lock)
 */

#include <SPI.h>
#include <MFRC522.h>

// Pin Definitions
#define RST_PIN         9
#define SS_PIN          10
#define GREEN_LED_PIN   5
#define RED_LED_PIN     6
#define BUZZER_PIN      7
#define RELAY_PIN       8

// Create MFRC522 instance
MFRC522 mfrc522(SS_PIN, RST_PIN);

// Authorized RFID UIDs (Add your card/tag UIDs here)
// Format: {0xXX, 0xXX, 0xXX, 0xXX} for 4-byte UID
byte authorizedUIDs[][4] = {
  {0xDE, 0xAD, 0xBE, 0xEF},  // Example UID 1 - Replace with your card UID
  {0xCA, 0xFE, 0xBA, 0xBE},  // Example UID 2 - Replace with your card UID
  {0x12, 0x34, 0x56, 0x78}   // Example UID 3 - Replace with your card UID
};

const int numAuthorizedCards = sizeof(authorizedUIDs) / sizeof(authorizedUIDs[0]);

// Variables
unsigned long accessGrantedTime = 0;
const unsigned long doorOpenDuration = 5000; // Door stays open for 5 seconds

void setup() {
  // Initialize Serial Monitor
  Serial.begin(9600);
  while (!Serial);
  
  // Initialize SPI bus
  SPI.begin();
  
  // Initialize MFRC522
  mfrc522.PCD_Init();
  
  // Set pin modes
  pinMode(GREEN_LED_PIN, OUTPUT);
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(RELAY_PIN, OUTPUT);
  
  // Initial state - all OFF, door locked
  digitalWrite(GREEN_LED_PIN, LOW);
  digitalWrite(RED_LED_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(RELAY_PIN, LOW);
  
  // Display system info
  Serial.println("╔════════════════════════════════════════╗");
  Serial.println("║   RFID Access Control System v1.0     ║");
  Serial.println("╚════════════════════════════════════════╝");
  Serial.println();
  Serial.print("Firmware Version: 0x");
  Serial.println(mfrc522.PCD_ReadRegister(mfrc522.VersionReg), HEX);
  Serial.println();
  Serial.println("System Ready - Waiting for RFID card...");
  Serial.println("Authorized cards: " + String(numAuthorizedCards));
  Serial.println("════════════════════════════════════════");
  
  // Startup beep
  tone(BUZZER_PIN, 1000, 200);
  delay(200);
}

void loop() {
  // Check if door should be locked again
  if (accessGrantedTime > 0 && millis() - accessGrantedTime >= doorOpenDuration) {
    lockDoor();
    accessGrantedTime = 0;
  }
  
  // Look for new cards
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return;
  }
  
  // Select one of the cards
  if (!mfrc522.PICC_ReadCardSerial()) {
    return;
  }
  
  // Show card UID
  Serial.println("\n🔍 Card detected!");
  Serial.print("UID: ");
  String uidString = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    Serial.print(mfrc522.uid.uidByte[i], HEX);
    uidString += String(mfrc522.uid.uidByte[i], HEX);
  }
  Serial.println();
  
  // Check if card is authorized
  if (isAuthorized(mfrc522.uid.uidByte, mfrc522.uid.size)) {
    grantAccess(uidString);
  } else {
    denyAccess(uidString);
  }
  
  // Halt PICC
  mfrc522.PICC_HaltA();
  
  // Stop encryption on PCD
  mfrc522.PCD_StopCrypto1();
}

// Check if UID is in authorized list
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

// Grant access function
void grantAccess(String uid) {
  Serial.println("╔════════════════════════════════════════╗");
  Serial.println("║        ✓ ACCESS GRANTED ✓             ║");
  Serial.println("╚════════════════════════════════════════╝");
  Serial.println("Card ID: " + uid);
  Serial.println("Status: Authorized");
  Serial.println("Action: Door unlocked for 5 seconds");
  
  // Green LED ON
  digitalWrite(GREEN_LED_PIN, HIGH);
  digitalWrite(RED_LED_PIN, LOW);
  
  // Unlock door (activate relay)
  digitalWrite(RELAY_PIN, HIGH);
  
  // Success beep pattern
  tone(BUZZER_PIN, 1500, 100);
  delay(150);
  tone(BUZZER_PIN, 2000, 100);
  delay(150);
  
  // Record access time
  accessGrantedTime = millis();
  
  Serial.println("════════════════════════════════════════\n");
}

// Deny access function
void denyAccess(String uid) {
  Serial.println("╔════════════════════════════════════════╗");
  Serial.println("║        ✗ ACCESS DENIED ✗              ║");
  Serial.println("╚════════════════════════════════════════╝");
  Serial.println("Card ID: " + uid);
  Serial.println("Status: Unauthorized");
  Serial.println("Action: Entry blocked");
  
  // Red LED ON
  digitalWrite(RED_LED_PIN, HIGH);
  digitalWrite(GREEN_LED_PIN, LOW);
  
  // Denial beep pattern (3 short beeps)
  for (int i = 0; i < 3; i++) {
    tone(BUZZER_PIN, 500, 200);
    delay(250);
  }
  
  // Keep red LED on for 2 seconds
  delay(2000);
  digitalWrite(RED_LED_PIN, LOW);
  
  Serial.println("════════════════════════════════════════\n");
}

// Lock door function
void lockDoor() {
  Serial.println("🔒 Door locked - Access timeout");
  digitalWrite(RELAY_PIN, LOW);
  digitalWrite(GREEN_LED_PIN, LOW);
  
  // Lock beep
  tone(BUZZER_PIN, 800, 150);
  delay(150);
}
