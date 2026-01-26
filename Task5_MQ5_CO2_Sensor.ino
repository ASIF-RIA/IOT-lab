/*
 * Task 5: CO₂ Detection using MQ5 Gas Sensor
 * Sensor: MQ5 Gas Sensor (LPG, Natural Gas, Coal Gas)
 * Note: MQ5 is primarily for LPG/Natural gas, not CO₂. For CO₂, MQ135 is better.
 * This code demonstrates gas level monitoring.
 * 
 * Circuit Connections:
 * MQ5 VCC  -> 5V
 * MQ5 GND  -> GND
 * MQ5 AO   -> A1 (Analog Pin 1)
 * Buzzer + -> D13
 * Buzzer - -> GND
 * LED +    -> D7 (with 220Ω resistor)
 * LED -    -> GND
 */

// Pin Definitions
const int MQ5_ANALOG_PIN = A1;   // MQ5 analog output
const int BUZZER_PIN = 13;       // Buzzer pin
const int LED_PIN = 7;           // LED pin

// Threshold values (adjust based on calibration)
const int GAS_THRESHOLD = 350;   // Normal threshold
const int HIGH_GAS_THRESHOLD = 550; // High concentration threshold

// Variables
unsigned long lastReadTime = 0;
const unsigned long readInterval = 2000; // Read every 2 seconds

void setup() {
  // Initialize Serial Monitor
  Serial.begin(9600);
  
  // Set pin modes
  pinMode(MQ5_ANALOG_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  
  // Initial state
  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(LED_PIN, LOW);
  
  Serial.println("MQ5 Gas Sensor Initialized");
  Serial.println("Warming up sensor... Please wait 20 seconds");
  
  // MQ5 sensors need warm-up time
  for (int i = 20; i > 0; i--) {
    Serial.print("Warming up: ");
    Serial.print(i);
    Serial.println(" seconds remaining");
    delay(1000);
  }
  
  Serial.println("System Ready - Monitoring gas levels...");
  Serial.println("═══════════════════════════════════════");
}

void loop() {
  unsigned long currentTime = millis();
  
  if (currentTime - lastReadTime >= readInterval) {
    lastReadTime = currentTime;
    
    // Read analog value from MQ5 sensor
    int gasLevel = analogRead(MQ5_ANALOG_PIN);
    
    // Calculate percentage (0-1023 mapped to 0-100%)
    float gasPercentage = (gasLevel / 1023.0) * 100.0;
    
    // Display readings
    Serial.print("Gas Level: ");
    Serial.print(gasLevel);
    Serial.print(" (");
    Serial.print(gasPercentage, 1);
    Serial.print("%) | Status: ");
    
    // Check gas level and trigger alerts
    if (gasLevel >= HIGH_GAS_THRESHOLD) {
      Serial.println("🚨 CRITICAL - HIGH GAS CONCENTRATION!");
      Serial.println("⚠️  EVACUATE AREA IMMEDIATELY!");
      
      // Critical alarm - rapid beeping
      for (int i = 0; i < 5; i++) {
        digitalWrite(BUZZER_PIN, HIGH);
        digitalWrite(LED_PIN, HIGH);
        delay(100);
        digitalWrite(BUZZER_PIN, LOW);
        digitalWrite(LED_PIN, LOW);
        delay(100);
      }
      
    } else if (gasLevel >= GAS_THRESHOLD) {
      Serial.println("⚠️  WARNING - Elevated gas levels detected!");
      
      // Warning - slow beep
      digitalWrite(LED_PIN, HIGH);
      tone(BUZZER_PIN, 800, 300);
      delay(300);
      digitalWrite(LED_PIN, LOW);
      
    } else {
      Serial.println("✓ Gas levels normal");
      
      // All clear
      digitalWrite(BUZZER_PIN, LOW);
      digitalWrite(LED_PIN, LOW);
    }
    
    Serial.println("───────────────────────────────────────");
  }
}
