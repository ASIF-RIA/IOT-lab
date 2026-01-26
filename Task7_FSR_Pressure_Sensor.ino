/*
 * Task 7: Pressure Detection using FSR (Force Sensitive Resistor)
 * Sensor: FSR (Force Sensitive Resistor)
 * 
 * Circuit Connections (Voltage Divider):
 * FSR Pin 1 -> 5V
 * FSR Pin 2 -> A3 (Analog Pin 3) AND 10kΩ resistor to GND
 * LED +     -> D6 (with 220Ω resistor)
 * LED -     -> GND
 * Buzzer +  -> D10
 * Buzzer -  -> GND
 */

// Pin Definitions
const int FSR_PIN = A3;          // FSR analog input
const int LED_PIN = 6;           // LED indicator
const int BUZZER_PIN = 10;       // Buzzer pin

// Threshold values (adjust based on your FSR and resistor values)
const int PRESSURE_THRESHOLD_LOW = 100;    // Light touch
const int PRESSURE_THRESHOLD_MEDIUM = 300; // Medium pressure
const int PRESSURE_THRESHOLD_HIGH = 600;   // Heavy pressure

// Variables
int pressureValue = 0;
int previousPressure = 0;
bool pressureDetected = false;

void setup() {
  // Initialize Serial Monitor
  Serial.begin(9600);
  
  // Set pin modes
  pinMode(FSR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  
  // Initial state
  digitalWrite(LED_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);
  
  Serial.println("╔════════════════════════════════════════╗");
  Serial.println("║  FSR Pressure Detection System        ║");
  Serial.println("╚════════════════════════════════════════╝");
  Serial.println();
  Serial.println("System Ready - Monitoring pressure...");
  Serial.println("Thresholds:");
  Serial.println("  Light:  " + String(PRESSURE_THRESHOLD_LOW));
  Serial.println("  Medium: " + String(PRESSURE_THRESHOLD_MEDIUM));
  Serial.println("  Heavy:  " + String(PRESSURE_THRESHOLD_HIGH));
  Serial.println("════════════════════════════════════════");
}

void loop() {
  // Read pressure value from FSR
  pressureValue = analogRead(FSR_PIN);
  
  // Display readings
  Serial.print("Pressure: ");
  Serial.print(pressureValue);
  Serial.print(" | ");
  
  // Determine pressure level and respond
  if (pressureValue >= PRESSURE_THRESHOLD_HIGH) {
    // Heavy pressure detected
    Serial.println("Status: 🔴 HEAVY PRESSURE");
    
    if (!pressureDetected || abs(pressureValue - previousPressure) > 50) {
      Serial.println("Event: Someone is standing/sitting with force!");
      tone(BUZZER_PIN, 2000, 200); // High pitch beep
    }
    
    // Rapid LED blink
    digitalWrite(LED_PIN, HIGH);
    delay(100);
    digitalWrite(LED_PIN, LOW);
    delay(100);
    digitalWrite(LED_PIN, HIGH);
    
    pressureDetected = true;
    
  } else if (pressureValue >= PRESSURE_THRESHOLD_MEDIUM) {
    // Medium pressure detected
    Serial.println("Status: 🟡 MEDIUM PRESSURE");
    
    if (!pressureDetected) {
      Serial.println("Event: Someone is sitting/stepping!");
      tone(BUZZER_PIN, 1500, 150);
    }
    
    // Steady LED
    digitalWrite(LED_PIN, HIGH);
    pressureDetected = true;
    
  } else if (pressureValue >= PRESSURE_THRESHOLD_LOW) {
    // Light pressure detected
    Serial.println("Status: 🟢 LIGHT PRESSURE");
    
    if (!pressureDetected) {
      Serial.println("Event: Light touch detected!");
      tone(BUZZER_PIN, 1000, 100);
    }
    
    // Slow LED blink
    digitalWrite(LED_PIN, HIGH);
    delay(300);
    digitalWrite(LED_PIN, LOW);
    delay(300);
    
    pressureDetected = true;
    
  } else {
    // No pressure
    Serial.println("Status: ⚪ NO PRESSURE");
    
    if (pressureDetected) {
      Serial.println("Event: Pressure released!");
      pressureDetected = false;
    }
    
    // Turn off indicators
    digitalWrite(LED_PIN, LOW);
    noTone(BUZZER_PIN);
  }
  
  // Store previous value for change detection
  previousPressure = pressureValue;
  
  // Visual separator
  if (pressureValue < PRESSURE_THRESHOLD_LOW) {
    Serial.println("────────────────────────────────────────");
  }
  
  delay(200); // Check every 200ms for responsive feedback
}

// Additional function to calculate force in grams (optional)
float calculateForce(int sensorValue) {
  // This is an approximation - calibrate with known weights
  // FSR resistance decreases with pressure
  // Convert sensor reading to approximate force
  
  if (sensorValue == 0) return 0;
  
  // Example calibration (adjust based on your FSR model)
  float voltage = sensorValue * (5.0 / 1023.0);
  float resistance = 10000 * (5.0 / voltage - 1.0);
  
  // Approximate force calculation (varies by FSR model)
  float force = 0;
  if (resistance <= 600) force = 1000; // >1kg
  else if (resistance <= 1000) force = 500; // ~500g
  else if (resistance <= 3000) force = 100; // ~100g
  else force = 10; // <10g
  
  return force;
}
