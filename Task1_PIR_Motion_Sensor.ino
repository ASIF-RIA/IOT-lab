/*
 * Task 1: Motion Detection using PIR Sensor
 * Sensor: PIR Motion Sensor
 * 
 * Circuit Connections:
 * PIR VCC  -> 5V
 * PIR GND  -> GND
 * PIR OUT  -> D2 (Digital Pin 2)
 * Buzzer + -> D8
 * Buzzer - -> GND
 * LED +    -> D7 (with 220Ω resistor)
 * LED -    -> GND
 */

// Pin Definitions
const int PIR_PIN = 2;      // PIR sensor output pin
const int BUZZER_PIN = 8;   // Buzzer pin
const int LED_PIN = 7;      // LED pin

void setup() {
  // Initialize Serial Monitor
  Serial.begin(9600);
  
  // Set pin modes
  pinMode(PIR_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  
  // Initial state - all OFF
  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(LED_PIN, LOW);
  
  Serial.println("PIR Motion Sensor Initialized");
  Serial.println("Waiting for sensor to stabilize...");
  delay(2000); // Allow PIR sensor to stabilize
  Serial.println("System Ready!");
}

void loop() {
  // Read PIR sensor value
  int motionState = digitalRead(PIR_PIN);
  
  if (motionState == HIGH) {
    // Motion detected
    Serial.println("*** MOTION DETECTED! ***");
    
    // Activate buzzer and LED
    digitalWrite(BUZZER_PIN, HIGH);
    digitalWrite(LED_PIN, HIGH);
    
    delay(1000); // Alert duration
    
  } else {
    // No motion
    Serial.println("No motion - Area clear");
    
    // Deactivate buzzer and LED
    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(LED_PIN, LOW);
  }
  
  delay(500); // Check every 500ms
}
