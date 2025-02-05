
#include <nRF24L01.h>
#include <printf.h>
#include <RF24.h>
#include <RF24_config.h>

#include <Adafruit_GPS.h>
#include <Adafruit_PMTK.h>
#include <NMEA_data.h>

#include <SD.h>

#define SD_CS A2

#define nRF_CS A0
#define nRF_CE A1

#define pH_module_address 0x63
#define TDS_module_address 0x64

#define Yellow_LED 8
#define Red_LED 4
#define V_BAT_sense 9

#define P_En 7
