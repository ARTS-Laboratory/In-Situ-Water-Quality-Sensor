
void power_peripheral(bool a){
  digitalWrite(P_En, a);
}

void led(bool i, bool j){
  digitalWrite(Yellow_LED, i);
  digitalWrite(Red_LED,j);
}
void error_loop(){
  power_peripheral(0);
  digitalWrite(Yellow_LED, 0);
  while(1){
    digitalWrite(Red_LED,1);
    delay(500);
    digitalWrite(Red_LED,0);
    delay(500);
  }
}

void check_bat_volt(){
  v_bat = (analogRead(V_BAT_sense)*volt_div*5)/1023;
  if(v_bat<minimum_V_bat){
    Serial.println("Battery voltage critical!!");
    error_loop();
  }
  Serial.print(v_bat); Serial.print("V, ");
}

void read_pH_and_EC(){
  delay(500);
  Wire.begin();
  delay(500); 
  EC.send_read_cmd();
  delay(1000);
  EC.receive_read_cmd();
  eC=EC.get_last_received_reading(); 
  Serial.print(eC);
  Serial.print(" uS, ");

  PH.send_read_cmd(); 
  delay(1000);
  PH.receive_read_cmd();
  pH=PH.get_last_received_reading(); 
  Serial.print(pH);
  Serial.print(" , ");
  Wire.end();
}


void read_temp(){
  temp_sensor.begin();
  temp_sensor.requestTemperatures();
  temp = temp_sensor.getTempCByIndex(0);
  if (temp == DEVICE_DISCONNECTED_C)
  {
    Serial.println("Error: Could not read temperature data");
    error_loop();
  }
  Serial.print(temp);
  Serial.println("°C");
}


void read_TRBDT(){
  turbidity = (((-(analogRead(TRBDT_pin)*5.0)/1023.0)+3.7)/0.008)-30;
  if(turbidity<0){ // due to to noise sometimes small negative values occur. 
    turbidity = 0;
  }
  Serial.print(turbidity);
  Serial.print(" NTU, ");
}

void write2SD(){
  if (!SD.begin(SD_CS)) {
    Serial.println("SD initialization failed!");
    error_loop();
  }

  myFile = SD.open("Data_log.csv", FILE_WRITE);

  if (myFile) {
//    myFile.print(gps.hdop.hdop());
//    myFile.print(",");
//    myFile.print(gps.location.lat(), 6);
//    myFile.print(",");
//    myFile.print(gps.location.lng(), 6);
//    myFile.print(",");
//    
//    myFile.print(gps.date.month());myFile.print(F("/"));myFile.print(gps.date.day());myFile.print(F("/"));myFile.print(gps.date.year());
//    myFile.print(",");
//    myFile.print(gps.time.hour());myFile.print(F(":"));myFile.print(gps.time.minute());myFile.print(F(":"));myFile.print(gps.time.second());myFile.print(F(":"));
//    myFile.print(",");
    
    myFile.print(v_bat);
    myFile.print(",");
    myFile.print(eC);
    myFile.print(",");
    myFile.print(pH);
    myFile.print(",");
    myFile.print(turbidity);
    myFile.print(",");
    myFile.println(temp);
    myFile.close();
    delay(300);
  } else {
    Serial.println("error opening log file");
    SD.end();
    error_loop();
  }
  SD.end();
}

void read_frm_SD(){
  myFile = SD.open("test.txt");
  if (myFile) {
    // read from the file until there's nothing else in it:
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    // close the file:
    myFile.close();
  } else {
    // if the file didn't open, print an error:
    Serial.println("error opening test.txt");
    error_loop();
  }
}

void transmit(){
  if (!radio.begin()) {
    Serial.println(F("radio hardware is not responding!!"));
    error_loop();
  }
  radio.setPALevel(RF24_PA_LOW);
  radio.setPayloadSize(10);
  radio.openWritingPipe(address[0]);
  radio.openReadingPipe(1, address[1]); 
  radio.stopListening();
  radio.write("Hello", sizeof(float));
  
}

void get_gps_data(){
  Serial1.begin(9600);
  while(1){ 
    led(1,0);
    //delay(100);
    while (Serial1.available() > 0 ){
      if (gps.encode(Serial1.read())){
        if (gps.location.isValid() && gps.date.isValid() && gps.time.isValid()){ 
          /*Serial.print("L: ");
          Serial.print(gps.location.lat(), 6);
          Serial.print(",");
          Serial.print(gps.location.lng(), 6);

         
          Serial.print(", D: ");
          Serial.print(gps.date.month());
          Serial.print(F("/"));
          Serial.print(gps.date.day());
          Serial.print(F("/"));
          Serial.print(gps.date.year());
  
          if (gps.time.hour() < 10) Serial.print(F("0"));
            Serial.print(" T: ");
            Serial.print(gps.time.hour());
            Serial.print(F(":"));
          if (gps.time.minute() < 10) Serial.print(F("0"));
            Serial.print(gps.time.minute());
            Serial.print(F(":"));
          if (gps.time.second() < 10) Serial.print(F("0"));
            Serial.print(gps.time.second());*/

          Serial.print(", HDOP:");
          Serial.println(gps.hdop.hdop());
          if(gps.hdop.hdop()<HDOP_threshold && gps.hdop.hdop()!=0 && gps.date.day()!=0 && gps.time.isUpdated()){
            led(0,0);
            return;
         }
        }
      }    
    }
  }
  led(0,0);
  Serial1.end();
}

void process_string(){

}
