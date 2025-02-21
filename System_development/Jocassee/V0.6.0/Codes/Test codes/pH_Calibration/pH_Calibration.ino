#include <Ezo_i2c.h> //include the EZO I2C library from https://github.com/Atlas-Scientific/Ezo_I2c_lib
#include <Wire.h>    //include arduinos i2c library 
#include <Ezo_i2c_util.h> //brings in common print statements

Ezo_board PH = Ezo_board(99, "PH");       //create a PH circuit object, who's address is 99 and name is "PH"


char rcv_data[32];

void setup() {
 pinMode(7,OUTPUT);
 digitalWrite(7,1);
  Wire.begin();                           //start the I2C
  Serial.begin(115200);                     //start the serial communication to the computer
  delay(2000);
  Serial.println("key: Mid Cal - M, Low cal - L, High cal - H, check cal status - ?, clear cal - C");
}

void loop() {
  while(Serial.available()){
    char a= Serial.read();
    if(a=='?'){
      PH.send_cmd("Cal,?");
      delay(900);
      PH.receive_cmd(rcv_data, 32);
      Serial.println(rcv_data);
    }else if(a=='M'){
      PH.send_cmd("Cal,mid,7.00");
      delay(1000);
      PH.receive_cmd(rcv_data, 32);
      Serial.print(rcv_data);Serial.println("Mid calibrated");
    }else if(a=='L'){
      PH.send_cmd("Cal,low,4.00");
      delay(1000);
      PH.receive_cmd(rcv_data, 32);
      Serial.print(rcv_data);Serial.println("Low calibrated");
    }
    else if(a=='H'){
      PH.send_cmd("Cal,high,10.00");
      delay(1000);
      PH.receive_cmd(rcv_data, 32);
      Serial.print(rcv_data);Serial.println("High calibrated");
    }
    else if(a=='C'){
      PH.send_cmd("Cal,clear");
      delay(300);
      PH.receive_cmd(rcv_data, 32);
      Serial.print(rcv_data);Serial.println("Calibration Cleared");
    }
    else if(a=='S'){
      PH.send_cmd("Slope,?");
      delay(300);
      PH.receive_cmd(rcv_data, 32);
      Serial.print(rcv_data);Serial.println("");
    }
  }
  
  PH.send_read_cmd();
  delay(1000);
  PH.receive_cmd(rcv_data, 32);
  Serial.print(rcv_data);Serial.println("");



}
