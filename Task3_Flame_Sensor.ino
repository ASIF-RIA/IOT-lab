/*
 * Task 3: Fire Detection using Flame Sensor
 * Sensor: Flame Sensor
 * 
 * Circuit Connections:
 * Flame VCC  -> 5V
 * Flame GND  -> GND
 * Flame DO   -> D4 (Digital Pin 4)
 * Buzzer +   -> D9
 * Buzzer -   -> GND
 * LED Red +  -> D10 (with 220Ω resistor)
 * LED Red -  -> GND
 */

// Pin Definitions
const int FLAME_PIN = 4;     // Flame sensor digital output pin
const int BUZZER_PIN = 9;    // Buzzer pin
const int LED_PIN = 10;      // Red LED pin

// Variables
bool fireDetected = false;

void setup() {
  // Initialize Serial Monitor
  Serial.begin(9600);
  
  // Set pin modes
  pinMode(FLAME_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  
  // Initial state - all OFF
  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(LED_PIN, LOW);
  
  Serial.println("Flame Sensor Fire Detection System Initialized");
  Serial.println("System Ready - Monitoring for fire...");
}

void loop() {
  // Read flame sensor value
  int flameState = digitalRead(FLAME_PIN);
  
  // Most flame sensors output LOW when flame is detected
  if (flameState == LOW) {
    // Fire detected!
    if (!fireDetected) {
      fireDetected = true;
      Serial.println("╔════════════════════════════════╗");
      Serial.println("║   🔥 FIRE DETECTED! 🔥        ║");
      Serial.println("║   EMERGENCY ALERT ACTIVATED   ║");
      Serial.println("╚════════════════════════════════╝");
    }
    
    // Activate fire alarm (buzzer with pattern)
    fireAlarm();
    
  } else {
    // No fire detected
    if (fireDetected) {
      fireDetected = false;
      Serial.println("Fire cleared - System normal");
    }
    
    // Turn off alarm
    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(LED_PIN, LOW);
    
    Serial.println("Monitoring... No fire detected");
  }
  
  delay(500);
}

// Fire alarm function with pattern
void fireAlarm() {
  // Rapid beeping pattern
  for (int i = 0; i < 3; i++) {
    digitalWrite(BUZZER_PIN, HIGH);
    digitalWrite(LED_PIN, HIGH);
    delay(100);
    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(LED_PIN, LOW);
    delay(100);
  }
}
