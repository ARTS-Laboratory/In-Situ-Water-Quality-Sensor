#include <Wire.h>
#include "Libraries/DS323x/DS323x.h"#include <DS323x.h>  

DS323x rtc;

void setup() {
  Serial.begin(9600);                       
  Wire.begin();                             
  rtc.attach(Wire);                         
  rtc.now(DateTime(2025, 6, 30, 15, 51, 0));  // Set initial time
}

void loop() {
  DateTime now = rtc.now();

  // Manually format date/time if .timestamp() is unavailable
  Serial.print(now.year());
  Serial.print('/');
  Serial.print(now.month());
  Serial.print('/');
  Serial.print(now.day());
  Serial.print(' ');
  Serial.print(now.hour());
  Serial.print(':');
  Serial.print(now.minute());
  Serial.print(':');
  Serial.println(now.second());

  delay(1000);  // Optional: wait 1 second between prints
}
