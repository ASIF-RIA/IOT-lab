/*
 * Task 2: Object Detection using IR Obstacle Sensor
 * Sensor: IR Obstacle Detection Sensor
 * 
 * Circuit Connections:
 * IR VCC  -> 5V
 * IR GND  -> GND
 * IR OUT  -> D3 (Digital Pin 3)
 * LED +   -> D6 (with 220Ω resistor)
 * LED -   -> GND
 */

// Pin Definitions
const int IR_PIN = 3;       // IR sensor output pin
const int LED_PIN = 6;      // LED indicator pin

void setup() {
  // Initialize Serial Monitor
  Serial.begin(9600);
  
  // Set pin modes
  pinMode(IR_PIN, INPUT);
  pinMode(LED_PIN, OUTPUT);
  
  // Initial state
  digitalWrite(LED_PIN, LOW);
  
  Serial.println("IR Obstacle Detection Sensor Initialized");
  Serial.println("System Ready!");
}

void loop() {
  // Read IR sensor value
  int obstacleState = digitalRead(IR_PIN);
  
  if (obstacleState == LOW) {
    // Object detected (IR sensors typically output LOW when object is detected)
    Serial.println("*** OBJECT DETECTED! ***");
    digitalWrite(LED_PIN, HIGH);
    
    // Send signal for NodeMCU integration
    // This can be used to trigger other actions
    sendSignalToNodeMCU(true);
    
  } else {
    // No object
    Serial.println("Path clear - No object");
    digitalWrite(LED_PIN, LOW);
    
    sendSignalToNodeMCU(false);
  }
  
  delay(300); // Check every 300ms
}

// Function to send signal to NodeMCU or other microcontroller
void sendSignalToNodeMCU(bool objectDetected) {
  // This function can be expanded to send data via serial, I2C, or other protocols
  if (objectDetected) {
    Serial.println("Signal: OBJECT_PRESENT");
  } else {
    Serial.println("Signal: NO_OBJECT");
  }
}
