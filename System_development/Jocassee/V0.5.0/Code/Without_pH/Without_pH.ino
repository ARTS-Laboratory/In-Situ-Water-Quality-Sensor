// Debugged by Md Asifuzzaman Khan
#include <SPI.h>
#include <SD.h>
#include <Wire.h>
#include <GravityTDS.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#include "Libraries/DS323x/DS323x.h"

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

bool SD_on=true;
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

  rtc.attach(Wire);                 // Attach RTC to I2C bus

  if (!SD.begin(SD_CS)) {           // Initialize SD card
    Serial.println(F("SD card init failed!"));  // Print error message if initialization fails
    SD_on=false;                   // Hang indefinitely
  }else{
    Serial.println(F("SD card init."));  // Print message if SD card initialized successfully
  }
}

void loop() {
  float tempCelsius, tdsValue;
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
  
  // Get current date and time from RTC
  DateTime now = rtc.now();

  // Log sensor data
  if(SD_on){
    serial_log(tdsValue, NTU, tempCelsius, now);
    logData(tdsValue, NTU, tempCelsius, now);
  }else{ 
    serial_log(tdsValue, NTU, tempCelsius, now);
    for(int i=0; i<=5; i++){ //indicate error blink
      digitalWrite(LED_PIN, HIGH);  
      delay(50);
      digitalWrite(LED_PIN, LOW);
      delay(50);
    }
  }
}

// Function to log sensor data to SD card
void logData(float tdsValue, float NTU, float tempCelsius, DateTime now) {
  File dataFile = SD.open("two.csv", FILE_WRITE);  // Open file for data logging
  if (dataFile) {                    // Check if file opened successfully
    digitalWrite(LED_PIN, HIGH);     // Turn on LED to indicate logging
    // Log TDS value
    dataFile.print(tdsValue, 0);
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

void serial_log(float tdsValue, float NTU, float tempCelsius, DateTime now){
digitalWrite(LED_PIN, HIGH);     // Turn on LED to indicate logging
    // Log TDS value
    Serial.print(tdsValue, 0);
    // CSV separator
    Serial.print(F(","));
    // Log turbidity value
    Serial.print(NTU);
    // CSV separator
    Serial.print(F(","));
    // Log temperature in Celsius
    Serial.print(tempCelsius);
    // CSV separator
    Serial.print(F(","));
    // Log timestamp
    Serial.println(now.timestamp());
}
