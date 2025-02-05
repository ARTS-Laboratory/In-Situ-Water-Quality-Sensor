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
  pinMode(P_En, OUTPUT);
  pinMode(Red_LED, OUTPUT);
  pinMode(Yellow_LED, OUTPUT);
  digitalWrite(P_En,LOW);
  digitalWrite(Red_LED,LOW);
  digitalWrite(Yellow_LED,LOW);
}

#include "Functions.h";

void loop() {

}
