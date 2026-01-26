/*
 * Task 4: Smoke Detection using MQ2 Gas Sensor
 * Sensor: MQ2 Gas Sensor (Smoke, LPG, Propane)
 * 
 * Circuit Connections:
 * MQ2 VCC  -> 5V
 * MQ2 GND  -> GND
 * MQ2 AO   -> A0 (Analog Pin 0)
 * MQ2 DO   -> D5 (Digital Pin 5) [Optional]
 * Buzzer + -> D11
 * Buzzer - -> GND
 * LED +    -> D12 (with 220Ω resistor)
 * LED -    -> GND
 */

// Pin Definitions
const int MQ2_ANALOG_PIN = A0;   // MQ2 analog output
const int MQ2_DIGITAL_PIN = 5;   // MQ2 digital output (optional)
const int BUZZER_PIN = 11;       // Buzzer pin
const int LED_PIN = 12;          // LED pin

// Threshold values
const int SMOKE_THRESHOLD = 400;  // Adjust based on calibration
const int DANGER_THRESHOLD = 600; // High danger level

void setup() {
  // Initialize Serial Monitor
  Serial.begin(9600);
  
  // Set pin modes
  pinMode(MQ2_ANALOG_PIN, INPUT);
  pinMode(MQ2_DIGITAL_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  
  // Initial state
  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(LED_PIN, LOW);
  
  Serial.println("MQ2 Smoke/Gas Sensor Initialized");
  Serial.println("Warming up sensor... Please wait 20 seconds");
  
  // MQ2 sensors need warm-up time
  for (int i = 20; i > 0; i--) {
    Serial.print("Warming up: ");
    Serial.print(i);
    Serial.println(" seconds remaining");
    delay(1000);
  }
  
  Serial.println("System Ready - Monitoring air quality...");
  Serial.println("Threshold: " + String(SMOKE_THRESHOLD));
  Serial.println("Danger Level: " + String(DANGER_THRESHOLD));
}

void loop() {
  // Read analog value from MQ2 sensor
  int smokeLevel = analogRead(MQ2_ANALOG_PIN);
  int digitalValue = digitalRead(MQ2_DIGITAL_PIN);
  
  // Display readings
  Serial.print("Smoke Level: ");
  Serial.print(smokeLevel);
  Serial.print(" | Digital: ");
  Serial.print(digitalValue);
  Serial.print(" | Status: ");
  
  // Check smoke level and trigger alerts
  if (smokeLevel >= DANGER_THRESHOLD) {
    Serial.println("⚠️ DANGER - HIGH SMOKE CONCENTRATION!");
    
    // High danger alarm - continuous beep
    digitalWrite(BUZZER_PIN, HIGH);
    digitalWrite(LED_PIN, HIGH);
    
  } else if (smokeLevel >= SMOKE_THRESHOLD) {
    Serial.println("⚠️ WARNING - Smoke detected!");
    
    // Warning alarm - intermittent beep
    digitalWrite(LED_PIN, HIGH);
    tone(BUZZER_PIN, 1000, 200); // Short beep
    delay(200);
    
  } else {
    Serial.println("✓ Air quality normal");
    
    // All clear
    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(LED_PIN, LOW);
  }
  
  delay(1000); // Check every second
}
