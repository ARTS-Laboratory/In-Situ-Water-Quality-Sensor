/*
 * This is a demo operating system of In-situ Water Quality Sensor V0.6.0
 * Author: Md. Asifuzzaman Khan
 * Date: January 29, 2025

 © Adaptive Real-Time Systems Laboratory
 University of South Carolina
 300 Main St., Columbia, SC.
 */

#include "Lib_and_def.h";

void setup() {
  //delay(3000);
  pinMode(P_En, OUTPUT);
  pinMode(Red_LED, OUTPUT);
  pinMode(Yellow_LED, OUTPUT);
  digitalWrite(P_En,LOW);
  digitalWrite(Red_LED,LOW);
  digitalWrite(Yellow_LED,LOW);
  //Serial.begin(115200);
}

#include "Functions.h";
void loop() {
  check_bat_volt();
  get_gps_data();
  power_peripheral(1);
  read_pH_and_EC();
  read_TRBDT();
  read_temp();
  //write2SD();
  transmit();
  power_peripheral(0);

  delay(26000);
  
}
