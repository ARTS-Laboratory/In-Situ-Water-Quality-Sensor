// Debugged by Md Asifuzzaman Khan
#include <SPI.h>
#include <SD.h>
#include <Wire.h>
#include <GravityTDS.h>
#include <OneWire.h>
#include <DallasTemperature.h>

//#include "Libraries/DS323x/DS323x.h"



Gravity_pH pH = Gravity_pH(A0);   


// Pin definitions
#define TdsSensorPin A1   // Pin for TDS sensor

#define SD_CS 10          // SD card chip select pin
#define SENSOR_PIN 7      // Temperature sensor pin
#define LED_PIN 5         // LED pin

// Create a OneWire instance for the temperature sensor
OneWire oneWire(SENSOR_PIN);
DallasTemperature tempSensor(&oneWire);
// Create an instance of the GravityTDS sensor
GravityTDS gravityTds;
// Create an instance of the DS323x RTC
DS323x rtc;
// Create an instance of the Gravity_pH sensor
//Gravity_pH pH(A0);

void setup() {
  pinMode(LED_PIN, OUTPUT);         // Set LED pin as output
  Serial.begin(9600);               // Start serial communication at 9600 baud
  
  gravityTds.setPin(TdsSensorPin);   // Set TDS sensor pin
  gravityTds.setAref(5.0);          // Set reference voltage for TDS sensor
  gravityTds.setAdcRange(1024);     // Set ADC range for TDS sensor
  gravityTds.begin();               // Initialize TDS sensor
  
  // Create DallasTemperature instance for temperature sensor
  
  tempSensor.begin();               // Initialize temperature sensor
  
  Wire.begin();                     // Initialize I2C communication
  
  if (pH.begin()) {                 // Begin pH sensor
    Serial.println(F("Loaded EEPROM"));  // Print message if EEPROM loaded successfully
  }

  rtc.attach(Wire);                 // Attach RTC to I2C bus
  rtc.now(DateTime(2022, 2, 2, 6, 42, 0));  // Set initial time for RTC

  if (!SD.begin(SD_CS)) {           // Initialize SD card
    Serial.println(F("SD card init failed!"));  // Print error message if initialization fails
    //while (true);                   // Hang indefinitely
  }
  Serial.println(F("SD card init."));  // Print message if SD card initialized successfully
}

void loop() {
  float tempCelsius, tdsValue;
  bool newGPSData = false;
  char buffer[64];                  // Buffer to store GPS data line
  int bufferIndex = 0;              // Index for buffer

  delay(3000);                      // Delay before measurements
  
  // Create DallasTemperature instance for temperature sensor
  DallasTemperature tempSensor(&oneWire);
  tempSensor.requestTemperatures(); // Request temperature readings
  tempCelsius = tempSensor.getTempCByIndex(0);  // Read temperature in Celsius
  gravityTds.setTemperature(tempCelsius);  // Set temperature for TDS sensor compensation
  gravityTds.update();              // Update TDS sensor readings
  tdsValue = gravityTds.getTdsValue();  // Get TDS value

  // Read and map turbidity sensor value
  float NTU = map(constrain(analogRead(A7), 0, 750), 0, 750, 100, 0);
  // Read pH value
  float pHValue = pH.read_ph();
  // Get current date and time from RTC
  DateTime now = rtc.now();

  // Log sensor data
  logData(tdsValue, pHValue, NTU, tempCelsius, now);

 
}

// Function to log sensor data to SD card
void logData(float tdsValue, float pHValue, float NTU, float tempCelsius, DateTime now) {
  File dataFile = SD.open("two.csv", FILE_WRITE);  // Open file for data logging
  if (dataFile) {                    // Check if file opened successfully
    digitalWrite(LED_PIN, HIGH);     // Turn on LED to indicate logging
    // Log TDS value
    dataFile.print(tdsValue, 0);
    // CSV separator
    dataFile.print(F(","));
    // Log pH value
    dataFile.print(pHValue);
    // CSV separator
    dataFile.print(F(","));
    // Log turbidity value
    dataFile.print(NTU);
    // CSV separator
    dataFile.print(F(","));
    // Log temperature in Celsius
    dataFile.print(tempCelsius);
    // CSV separator
    dataFile.print(F(","));
    // Log timestamp
    dataFile.println(now.timestamp());
    digitalWrite(LED_PIN, LOW);      // Turn off LED
    dataFile.close();                // Close file
    Serial.println(F("Data logged."));  // Print message
  } else {
    Serial.println(F("Error opening two.csv"));  // Print error message if file not opened
  }
}
