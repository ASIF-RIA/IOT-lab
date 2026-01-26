/*
 * Task 6: Methane / CO Detection using MQ7 Gas Sensor
 * Sensor: MQ7 Gas Sensor (Carbon Monoxide)
 * Note: MQ7 is specifically for CO detection, not methane (use MQ4 for methane)
 * 
 * Circuit Connections:
 * MQ7 VCC  -> 5V
 * MQ7 GND  -> GND
 * MQ7 AO   -> A2 (Analog Pin 2)
 * Buzzer + -> D8
 * Buzzer - -> GND
 * LED Red+ -> D9 (with 220Ω resistor)
 * LED Red- -> GND
 */

// Pin Definitions
const int MQ7_ANALOG_PIN = A2;   // MQ7 analog output
const int BUZZER_PIN = 8;        // Buzzer pin
const int LED_PIN = 9;           // Red LED pin

// CO Safety Thresholds (in analog values, adjust based on calibration)
const int CO_SAFE_LEVEL = 300;      // Below this is safe
const int CO_WARNING_LEVEL = 450;   // Warning level
const int CO_DANGER_LEVEL = 600;    // Dangerous level

// Variables
int coLevel = 0;
String safetyStatus = "";

void setup() {
  // Initialize Serial Monitor
  Serial.begin(9600);
  
  // Set pin modes
  pinMode(MQ7_ANALOG_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  
  // Initial state
  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(LED_PIN, LOW);
  
  Serial.println("╔════════════════════════════════════════╗");
  Serial.println("║  MQ7 Carbon Monoxide (CO) Detector    ║");
  Serial.println("╚════════════════════════════════════════╝");
  Serial.println();
  Serial.println("Warming up sensor... Please wait 60 seconds");
  Serial.println("(MQ7 requires longer warm-up time)");
  
  // MQ7 sensors need longer warm-up time (60 seconds recommended)
  for (int i = 60; i > 0; i--) {
    if (i % 10 == 0 || i <= 5) {
      Serial.print("Warming up: ");
      Serial.print(i);
      Serial.println(" seconds remaining");
    }
    delay(1000);
  }
  
  Serial.println();
  Serial.println("System Ready - Monitoring CO levels...");
  Serial.println("Safety Thresholds:");
  Serial.println("  Safe:    < " + String(CO_SAFE_LEVEL));
  Serial.println("  Warning: " + String(CO_WARNING_LEVEL));
  Serial.println("  Danger:  " + String(CO_DANGER_LEVEL));
  Serial.println("════════════════════════════════════════");
}

void loop() {
  // Read analog value from MQ7 sensor
  coLevel = analogRead(MQ7_ANALOG_PIN);
  
  // Determine safety status and take action
  if (coLevel >= CO_DANGER_LEVEL) {
    safetyStatus = "🚨 DANGER";
    handleDangerLevel();
    
  } else if (coLevel >= CO_WARNING_LEVEL) {
    safetyStatus = "⚠️  WARNING";
    handleWarningLevel();
    
  } else if (coLevel >= CO_SAFE_LEVEL) {
    safetyStatus = "⚡ CAUTION";
    handleCautionLevel();
    
  } else {
    safetyStatus = "✓ SAFE";
    handleSafeLevel();
  }
  
  // Display readings
  displayReadings();
  
  delay(1500); // Check every 1.5 seconds
}

void handleDangerLevel() {
  Serial.println("⚠️⚠️⚠️ CRITICAL CO LEVELS DETECTED! ⚠️⚠️⚠️");
  Serial.println("ACTION REQUIRED: Evacuate immediately!");
  Serial.println("Open windows and ventilate area!");
  
  // Continuous rapid alarm
  for (int i = 0; i < 3; i++) {
    digitalWrite(BUZZER_PIN, HIGH);
    digitalWrite(LED_PIN, HIGH);
    delay(150);
    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(LED_PIN, LOW);
    delay(150);
  }
}

void handleWarningLevel() {
  Serial.println("⚠️  Elevated CO levels - Ventilate area");
  
  // Intermittent alarm
  digitalWrite(LED_PIN, HIGH);
  tone(BUZZER_PIN, 1500, 500);
  delay(500);
  digitalWrite(LED_PIN, LOW);
}

void handleCautionLevel() {
  Serial.println("⚡ CO detected - Monitor closely");
  
  // LED blink only
  digitalWrite(LED_PIN, HIGH);
  delay(200);
  digitalWrite(LED_PIN, LOW);
  noTone(BUZZER_PIN);
}

void handleSafeLevel() {
  // All clear
  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(LED_PIN, LOW);
}

void displayReadings() {
  Serial.print("CO Level: ");
  Serial.print(coLevel);
  Serial.print(" | Status: ");
  Serial.println(safetyStatus);
  Serial.println("────────────────────────────────────────");
}
