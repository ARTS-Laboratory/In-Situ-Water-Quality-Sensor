#include <Ezo_i2c.h> //include the EZO I2C library from https://github.com/Atlas-Scientific/Ezo_I2c_lib
#include <Wire.h>    //include arduinos i2c library 
#include <Ezo_i2c_util.h> //brings in common print statements

Ezo_board PH = Ezo_board(99, "PH");       //create a PH circuit object, who's address is 99 and name is "PH"
Ezo_board EC = Ezo_board(100, "EC");      //create an EC circuit object who's address is 100 and name is "EC"

char EC_data[32];          //we make a 32-byte character array to hold incoming data from the EC sensor.
char *EC_str;                     //char pointer used in string parsing.
char *TDS;                       //char pointer used in string parsing.
char *SAL;                       //char pointer used in string parsing (the sensor outputs some text that we don't need).
char *SG;                       //char pointer used in string parsing.

void setup() {
  pinMode(7,OUTPUT);
  digitalWrite(7,HIGH);
  Wire.begin();                           //start the I2C
  Serial.begin(9600);                     //start the serial communication to the computer
  EC.send_cmd("o,tds,1");        //send command to enable TDS output
  delay(300);
  EC.send_cmd("o,s,1");        //send command to enable salinity output
  delay(300);
  EC.send_cmd("o,sg,1");      //send command to enable specific gravity output
  delay(300);
}

void loop() {
  Read_EC();
}

void Read_EC(){
   //send a read command. we use this command instead of PH.send_cmd("R"); 
  //to let the library know to parse the reading
  //PH.send_read_cmd();                      
  EC.send_read_cmd();
  delay(3000);
  EC.receive_cmd(EC_data, 32);       //put the response into the buffer

  EC_str = strtok(EC_data, ",");       //let's parse the string at each comma.
  TDS = strtok(NULL, ",");                  //let's parse the string at each comma.
  SAL = strtok(NULL, ",");                  //let's parse the string at each comma 
  SG = strtok(NULL, ",");                  //let's parse the string at each comma.

  Serial.print("EC: ");                      //we now print each value we parsed separately.
  Serial.print(EC_str);                     //this is the EC value.

  Serial.print(" TDS: ");                  //we now print each value we parsed separately.
  Serial.print(TDS);                       //this is the TDS value.

  Serial.print(" SAL: ");                      //we now print each value we parsed separately.
  Serial.print(SAL);                       //this is the salinity point.
  
  Serial.print(" SG: ");                      //we now print each value we parsed separately.
  Serial.println(SG);                       //this is the specific gravity point.
}
