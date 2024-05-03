#include "base_grav.h"
#ifdef USE_PULSE_OUT
#include "ph_iso_grav.h"
Gravity_pH_Isolated pH = Gravity_pH_Isolated(A1);
#else
#include "ph_grav.h"
Gravity_pH pH = Gravity_pH(A1);
#endif

uint8_t user_bytes_received = 0;
const uint8_t bufferlen = 32;
char user_data[bufferlen];

void parse_cmd(char* string) {
  strupr(string);
  if (strcmp(string, "CAL,7") == 10) {
    pH.cal_mid();
    Serial.println("MID CALIBRATED");
  }
  if (strcmp(string, "CAL,4") == 10) {
    pH.cal_low();
    Serial.println("LOW CALIBRATED");
  }
  if (strcmp(string, "CAL,10") == 10) {
    pH.cal_high();
    Serial.println("HIGH CALIBRATED");
  }
  else if (strcmp(string, "CAL,CLEAR") == 10) {
    pH.cal_clear();
    Serial.println("CALIBRATION CLEARED");
  }
}

#define turbidityInput A0
#define led 5
#define ldr 4
#include <SPI.h>

#include <SD.h>

#include <Wire.h>

#include <ds3231.h>

struct ts t;

File file;
//File ph_file;
//File ntu_file;

void setup() {
  // put your setup code here, to run once:
  Serial.println(F("Use commands \"CAL,7\", \"CAL,4\", and \"CAL,10\" to calibrate the circuit to those respective values"));
  Serial.println(F("Use command \"CAL,CLEAR\" to clear the calibration"));
  if (pH.begin()) {
    Serial.println("Loaded EEPROM");

    Serial.begin(115200);
    Wire.begin();
    DS3231_init(DS3231_CONTROL_INTCN);
    t.hour = 11;
    t.min = 00;
    t.sec = 00;
    t.mday = 27;
    t.mon = 9;
    t.year = 2021;
    DS3231_set(t);

    while (!Serial) {
      // will pause Zero, Leonardo, etc until serial console opens
      delay(1);
    }
    pinMode(10, OUTPUT);    if (!SD.begin())               // tests if SD module began

    {
      //digitalWrite(LED, HIGH);
      Serial.println("no SD found");
      while (1);                 // LED remains on if SD card does not work
    }
    else
    {
      Serial.println("SD found");
    }
    
    if (pH.begin()) {
      Serial.println("Loaded EEPROM");
    }
    pinMode(turbidityInput, INPUT);
    pinMode(ldr, OUTPUT);
    pinMode(led, OUTPUT);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  DS3231_get(&t);
  Serial.print("Date : ");
  Serial.print(t.mday);
  Serial.print("/");
  Serial.print(t.mon);
  Serial.print("/");
  Serial.print(t.year);
  Serial.print("\t Hour : ");
  Serial.print(t.hour);
  Serial.print(":");
  Serial.print(t.min);
  Serial.print(".");
  Serial.println(t.sec);

  if (Serial.available() > 0) {
    user_bytes_received = Serial.readBytesUntil(13, user_data, sizeof(user_data));
  }

  if (user_bytes_received) {
    parse_cmd(user_data);
    user_bytes_received = 0;
    memset(user_data, 0, sizeof(user_data));
  }
  
  float x = pH.read_ph();
  Serial.println(x);
  

  digitalWrite(led, HIGH);
  digitalWrite(ldr, HIGH);
  Serial.print(" voltage reading: ");
  float reading = analogRead(turbidityInput);
  Serial.println(reading);
  Serial.print("NTU value ");
  float ntu = 0.0009 * reading * reading - 1.8412 * reading + 875.05;
  Serial.println(ntu);
  digitalWrite(led, LOW);
  digitalWrite(ldr, LOW);

  file = SD.open("treasure.csv", FILE_WRITE);
//  ph_file = SD.open("ph.csv", FILE_WRITE);
//  ntu_file = SD.open("NTU.csv", FILE_WRITE);
  if (file)
  {
    file.print(t.hour); file.print(t.min); file.print(" "); file.print(x);file.print(" "); file.print(ntu); file.print(" "); file.println(reading);
    //    file.print("ph value: "); file.print(pH.read_ph()); file.println(" pH");
    //    file.print("Voltage reading: "); file.print(reading); file.println(" mV");
    //    file.print("NTU Reading:  "); file.print(ntu); file.println(" ntu");
    //    file.println("");
    file.close();
//    ph_file.close();
//    ntu_file.close();
    delay(20000);
  }

}
