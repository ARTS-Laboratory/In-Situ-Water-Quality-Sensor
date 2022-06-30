#include <SPI.h>
#include <SD.h>
#include <Wire.h>
#include <EEPROM.h>
#include <GravityTDS.h>
#define TdsSensorPin A1
#include <DS323x.h>
#ifdef USE_PULSE_OUT
  #include "ph_iso_grav.h"       
  Gravity_pH_Isolated pH = Gravity_pH_Isolated(A0);         
#else
  #include "ph_grav.h"             
  Gravity_pH pH = Gravity_pH(A0);   
#endif
                

uint8_t user_bytes_received = 0;                
const uint8_t bufferlen = 32;                   
char user_data[bufferlen];                     

void parse_cmd(char* string) {                   
  strupr(string);                                
}
int sensorPin = A7;
float volt;
float ntu;
DS323x rtc;
GravityTDS gravityTds;
const int chipSelect = 10;
float temperature = 25, tdsValue = 0;
File myFile;
void save_temperature() {}

void setup ()
{
  

  Serial.begin(115200);
  gravityTds.setPin(TdsSensorPin);
  gravityTds.setAref(5.0);  //reference voltage on ADC, default 5.0V on Arduino UNO
  gravityTds.setAdcRange(1024);  //1024 for 10bit ADC;4096 for 12bit ADC
  gravityTds.begin();  //initialization
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
  volt = 0;
    for(int i=0; i<800; i++)
    {
        volt += ((float)analogRead(sensorPin)/1023)*5;
    }
    volt = volt/800;
    volt = round_to_dp(volt,2);
    if(volt < 2.5){
      ntu = 3000;
    }else{
      ntu = -1120.4*square(volt)+5742.3*volt-4353.8;
      delay(1000);
      }
 gravityTds.setTemperature(temperature);  // set the temperature and execute temperature compensation
  gravityTds.update();  //sample and calculate
  tdsValue = gravityTds.getTdsValue();  // then get the value
  if (Serial.available() > 0) {                                                      
    user_bytes_received = Serial.readBytesUntil(13, user_data, sizeof(user_data));   
  }

  if (user_bytes_received) {                                                      
    parse_cmd(user_data);                                                          
    user_bytes_received = 0;                                                        
    memset(user_data, 0, sizeof(user_data));                                         
  }
  Serial.print(tdsValue, 0);
  Serial.print("ppm");
  Serial.print(",");
  Serial.print(" ");
  Serial.print(pH.read_ph());
  Serial.print("ph.m");
  Serial.print(",");
  Serial.print(" ");
  Serial.print(ntu);
  Serial.print("ntu");
  Serial.print(",");
  Serial.print(" ");
   DateTime now = rtc.now();
    Serial.println(now.timestamp());
  //delay(300000);                                                      
  delay(1000);

  File dataFile = SD.open("test.csv", FILE_WRITE);
  if (dataFile) {
    dataFile.print(tdsValue, 0);
    dataFile.print(",");
    dataFile.print(" ");
    dataFile.print(pH.read_ph());
    dataFile.print(",");
    dataFile.print(" ");
    dataFile.print(ntu);
    dataFile.print(",");
    dataFile.print(" ");
    dataFile.println(now.timestamp());
    dataFile.close();
  }
  else {
    Serial.println("error opening datalog.txt");
  }
}
float round_to_dp( float in_value, int decimal_place )
{
  float multiplier = powf( 10.0f, decimal_place );
  in_value = roundf( in_value * multiplier ) / multiplier;
  return in_value;
}
