
#define turbidityInput A0
#define led 5
#define ldr 4
#include <SPI.h>
#include <SD.h>
#include <Wire.h>
#include <ds3231.h>
struct ts t;
File file;
#include <SoftwareSerial.h>                           //we have to include the SoftwareSerial library, or else we can't use it
#define rx 6                                          //define what pin rx is going to be
#define tx 7                                          //define what pin tx is going to be


SoftwareSerial myserial(rx, tx);                      //define how the soft serial port is going to work


String inputstring = "";                              //a string to hold incoming data from the PC
String sensorstring = "";                             //a string to hold the data from the Atlas Scientific product
boolean input_string_complete = false;                //have we received all the data from the PC
boolean sensor_string_complete = false;               //have we received all the data from the Atlas Scientific product
float pH;                                             //used to hold a floating point number that is the pH

void setup() {
  Serial.begin(9600);                                 //set baud rate for the hardware serial port_0 to 9600
  myserial.begin(9600);                               //set baud rate for the software serial port to 9600
  inputstring.reserve(10);                            //set aside some bytes for receiving data from the PC
  sensorstring.reserve(30);  //set aside some bytes for receiving data from Atlas Scientific product
  pinMode(turbidityInput, INPUT);
  pinMode(ldr, OUTPUT);
  pinMode(led, OUTPUT);
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
}
void serialEvent() {                                  //if the hardware serial port_0 receives a char
  inputstring = Serial.readStringUntil(13);           //read the string until we see a <CR>
  input_string_complete = true;                       //set the flag used to tell if we have received a completed string from the PC
}

void loop() {                                         //here we go...

  if (input_string_complete == true) {                //if a string from the PC has been received in its entirety
    myserial.print(inputstring);                      //send that string to the Atlas Scientific product
    myserial.print('\r');                             //add a <CR> to the end of the string
    inputstring = "";                                 //clear the string
    input_string_complete = false;                    //reset the flag used to tell if we have received a completed string from the PC
  }

  if (myserial.available() > 0) {                     //if we see that the Atlas Scientific product has sent a character
    char inchar = (char)myserial.read();              //get the char we just received
    sensorstring += inchar;                           //add the char to the var called sensorstring
    if (inchar == '\r') {                             //if the incoming character is a <CR>
      sensor_string_complete = true;                  //set the flag
      Serial.println("true");
    }
  }


  if (sensor_string_complete == true) {               //if a string from the Atlas Scientific product has been received in its entirety
    Serial.println(sensorstring);                     //send that string to the PC's serial monitor
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
    file = SD.open("PCB2.csv", FILE_WRITE);
//  ph_file = SD.open("ph.csv", FILE_WRITE);
//  ntu_file = SD.open("NTU.csv", FILE_WRITE);
  if (file)
  {
    file.print(t.hour); file.print(t.min); file.print(" "); file.print(reading);file.print(" "); file.print(ntu); file.print(" "); file.println(sensorstring);
    //    file.print("ph value: "); file.print(pH.read_ph()); file.println(" pH");
    //    file.print("Voltage reading: "); file.print(reading); file.println(" mV");
    //    file.print("NTU Reading:  "); file.print(ntu); file.println(" ntu");
    //    file.println("");
    file.close();
//    ph_file.close();
//    ntu_file.close();
    delay(5000);
    /*                                                //uncomment this section to see how to convert the pH reading from a string to a float 
    if (isdigit(sensorstring[0])) {                   //if the first character in the string is a digit
      pH = sensorstring.toFloat();                    //convert the string to a floating point number so it can be evaluated by the Arduino
      if (pH >= 7.0) {                                //if the pH is greater than or equal to 7.0
        Serial.println("high");                       //print "high" this is demonstrating that the Arduino is evaluating the pH as a number and not as a string
      }
      if (pH <= 6.999) {                              //if the pH is less than or equal to 6.999
        Serial.println("low");                        //print "low" this is demonstrating that the Arduino is evaluating the pH as a number and not as a string
      }
    }
    */
    sensorstring = "";                                //clear the string
    sensor_string_complete = false;                   //reset the flag used to tell if we have received a completed string from the Atlas Scientific product
  }
}
}
