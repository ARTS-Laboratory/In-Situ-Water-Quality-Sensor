#define HDOP_threshold 1.2 //HDOP is the measure of circular error in GPS position, less than one is ideal.

#define minimum_V_bat 7

#define SD_CS A2

#define nRF_CS A0
#define nRF_CE A1

#define pH_module_address 0x63
#define TDS_module_address 0x64
#define TRBDT_pin A7

#define Yellow_LED 8
#define Red_LED 4
#define V_BAT_sense A9
#define volt_div 2.05

#define P_En 7

#define TEMP_BUS 5


#include <OneWire.h>
#include <DallasTemperature.h>
OneWire oneWire(TEMP_BUS);
DallasTemperature temp_sensor(&oneWire);

#include <TinyGPSPlus.h>
TinyGPSPlus gps;

#include <Ezo_i2c.h>
#include <Wire.h>    
#include <Ezo_i2c_util.h> 
Ezo_board PH = Ezo_board(99, "PH");       //create a PH circuit object, who's address is 99 and name is "PH"
Ezo_board EC = Ezo_board(100, "EC");      //create an EC circuit object who's address is 100 and name is "EC"

#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>
RF24 radio(nRF_CE, nRF_CS);
uint8_t address[][6] = { "TNode", "RNode" }; //single node demo

#include <SD.h>
File myFile;

//Declaring global variables

float v_bat=6;

struct payload_struct{

  uint8_t month(); //1 byte
  uint8_t day();   //1 byte
  uint16_t year(); //2 byte
  
  uint8_t hour();  //1 byte
  uint8_t minute();//1 byte
  uint8_t second();//1 byte
  
  double lat();    //4 byte
  double lng();    //4 byte
  
  float temp, pH, eC, turbidity; //16 bytes
  
};

payload_struct payload; // total 31 bytes
