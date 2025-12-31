/*
 * Soil Moisture Sensor with Arduino
 * Measures soil moisture using a capacitive soil moisture sensor (v1.2 or similar)
 * Outputs moisture percentage to Serial Monitor
 * Hardware: Arduino Uno, Capacitive Soil Moisture Sensor
 * Connections: AOUT -> A0, VCC -> 5V, GND -> GND
 */

// Define the analog pin for the soil moisture sensor
const int sensorPin = A0;

// Calibration values (adjust based on your sensor and soil)
const int dryValue = 600;  // Sensor value in dry soil (calibrate by testing)
const int wetValue = 300;  // Sensor value in wet soil (calibrate by testing)

void setup() {
  // Initialize serial communication at 9600 baud rate
  Serial.begin(9600);
  Serial.println("Soil Moisture Sensor Reading...");
}

void loop() {
  // Read the analog value from the sensor
  int sensorValue = analogRead(sensorPin);
  
  // Map the sensor value to a percentage (0% = dry, 100% = wet)
  int moisturePercentage = map(sensorValue, dryValue, wetValue, 0, 100);
  
  // Constrain the percentage to avoid negative or >100% values
  moisturePercentage = constrain(moisturePercentage, 0, 100);
  
  // Print the moisture percentage to Serial Monitor
  Serial.print("Moisture: ");
  Serial.print(moisturePercentage);
  Serial.println("%");
  
  // Delay for 1 second before next reading
  delay(1000);}