// to use the Atlas surveyor circuits with 
// the surveyor isolator board's pulse output 
// uncomment line 8: #define USE_PULSE_OUT
// you can use any pins instead of just the analog ones
// but it must be recalibrated
// note that the isolator's analog output also provides isolation

// #define USE_PULSE_OUT

#ifdef USE_PULSE_OUT
  #include "orp_iso_surveyor.h"       
  Surveyor_ORP_Isolated ORP = Surveyor_ORP_Isolated(A0);         
#else
  #include "orp_surveyor.h"
  Surveyor_ORP ORP = Surveyor_ORP(A0);
#endif

uint8_t user_bytes_received = 0;
const uint8_t bufferlen = 32;
char user_data[bufferlen];


void parse_cmd(char* string) {
  strupr(string);
  String cmd = String(string);
  if(cmd.startsWith("CAL")){
    int index = cmd.indexOf(',');
    if(index != -1){
      String param = cmd.substring(index+1, cmd.length());
      if(param.equals("CLEAR")){
        ORP.cal_clear();
        Serial.println("CALIBRATION CLEARED");
      }
      else{
        int cal_param = param.toInt();
        ORP.cal(cal_param);
        Serial.println("ORP CALIBRATED");
      }
    }
  }
}

void setup() {
  Serial.begin(9600);
  delay(200);
  Serial.println(F("Use command \"CAL,xxx\" to calibrate the circuit to the value xxx \n\"CAL,CLEAR\" clears the calibration"));
  if(ORP.begin()){
    Serial.println("Loaded EEPROM");
  }
}

void loop() {
  if (Serial.available() > 0) {
    user_bytes_received = Serial.readBytesUntil(13, user_data, sizeof(user_data));
  }

  if (user_bytes_received) {
    parse_cmd(user_data);
    user_bytes_received = 0;
    memset(user_data, 0, sizeof(user_data));
  }
  
  Serial.println((int)ORP.read_orp());
  delay(1000);
}
