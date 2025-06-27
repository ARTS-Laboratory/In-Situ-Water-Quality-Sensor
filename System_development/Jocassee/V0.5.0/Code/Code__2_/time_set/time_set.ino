
#include <Wire.h>

#include <DS323x.h>




// Create an instance of the GravityTDS sensor
GravityTDS gravityTds;
// Create an instance of the DS323x RTC
DS323x rtc;
// Create an instance of the Gravity_pH sensor
Gravity_pH pH(A0);

void setup() {
  pinMode(LED_PIN, OUTPUT);         // Set LED pin as output
  Serial.begin(9600);               // Start serial communication at 9600 baud
  
  Wire.begin();                     // Initialize I2C communication
  
                   // Delay for stabilization
  

  rtc.attach(Wire);                 // Attach RTC to I2C bus
  rtc.now(DateTime(2025, 2, 2, 6, 42, 0));  // Set initial time for RTC

}

void loop() {

  DateTime now = rtc.now();
  Serial.print(now);

  
