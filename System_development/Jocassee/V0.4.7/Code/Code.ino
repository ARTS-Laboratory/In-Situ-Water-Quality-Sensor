#include <SPI.h>
#include <SD.h>
#include <Wire.h>
#include <EEPROM.h>
#include <GravityTDS.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#define TdsSensorPin A1
#include <DS323x.h>
#ifdef USE_PULSE_OUT
  #include "ph_iso_grav.h"       
  Gravity_pH_Isolated pH = Gravity_pH_Isolated(A0);         
#else
  #include "ph_grav.h"             
  Gravity_pH pH = Gravity_pH(A0);   
#endif
const int led = 5;
const int SENSOR_PIN = 7;
OneWire oneWire(SENSOR_PIN);         
DallasTemperature tempSensor(&oneWire);             
float tempCelsius;
uint8_t user_bytes_received = 0;                
const uint8_t bufferlen = 32;                   
char user_data[bufferlen];                     

void parse_cmd(char* string) {                   
  strupr(string);                                
}

DS323x rtc;
GravityTDS gravityTds;
const int chipSelect = 10;
float temperature = 25, tdsValue = 0;
File myFile;
void save_temperature() {}

void setup ()
{
  pinMode(led,OUTPUT);

  Serial.begin(115200);
  gravityTds.setPin(TdsSensorPin);
  gravityTds.setAref(5.0);  //reference voltage on ADC, default 5.0V on Arduino UNO
  gravityTds.setAdcRange(1024);  //1024 for 10bit ADC;4096 for 12bit ADC
  gravityTds.begin();  //initialization
  tempSensor.begin();
   Wire.begin();
    delay(1000);
  if (pH.begin()) {                                     
    Serial.println("Loaded EEPROM");
  }
    rtc.attach(Wire);
    rtc.now(DateTime(2022, 2, 2, 6, 42,0));
  Wire.begin();
  while (!Serial);

  Serial.print("Initializing SD card...");

  if (!SD.begin(chipSelect)) {
    Serial.println("initialization failed. Things to check:");
    while (true);
  }

  Serial.println("initialization done.");
}

void loop ()
{
  delay(3000);
   
  gravityTds.setTemperature(temperature);  // set the temperature and execute temperature compensation
  gravityTds.update();  //sample and calculate
  tdsValue = gravityTds.getTdsValue();  // then get the value
  
   tempSensor.requestTemperatures();             // send the command to get temperatures
  tempCelsius = tempSensor.getTempCByIndex(0);  // read temperature in Celsius
  
  if (Serial.available() > 0) {                                                      
    user_bytes_received = Serial.readBytesUntil(13, user_data, sizeof(user_data));   
  }

  if (user_bytes_received) {                                                      
    parse_cmd(user_data);                                                          
    user_bytes_received = 0;                                                        
    memset(user_data, 0, sizeof(user_data));                                         
  }
  int x = analogRead(A7);
  x = constrain (x,0,750);
  float NTU = map(x,0,750,100,0);
  float y = pH.read_ph();
  
  DateTime now = rtc.now();
  Serial.print(tdsValue, 0);
    Serial.print(",");
    Serial.print(" ");
    Serial.print(y);
    Serial.print(",");
    Serial.print(" ");
    Serial.print(NTU);
    Serial.print(",");
    Serial.print(" ");
    Serial.print(tempCelsius);
    Serial.print(",");
    Serial.print(" ");
    Serial.println(now.timestamp());
  File dataFile = SD.open("two.csv", FILE_WRITE);
  if (dataFile) {
    digitalWrite(led, HIGH);  
    dataFile.print(tdsValue, 0);
    dataFile.print(",");
    dataFile.print(" ");
    dataFile.print(y);
    dataFile.print(",");
    dataFile.print(" ");
    dataFile.print(NTU);
    dataFile.print(",");
    dataFile.print(" ");
    dataFile.print(tempCelsius);
    dataFile.print(",");
    dataFile.print(" ");
    dataFile.println(now.timestamp());
    delay(1000);
    digitalWrite(led, LOW);
    dataFile.close();
  }
  else {
    Serial.println("error opening datalog.txt");
  }
  //delay(3000);
}
