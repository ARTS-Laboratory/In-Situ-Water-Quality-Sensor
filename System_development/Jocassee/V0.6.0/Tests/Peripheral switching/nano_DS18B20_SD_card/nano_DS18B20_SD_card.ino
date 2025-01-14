// nano_DS18B20_SD_card_nn
// 
// checks if SD card available
// collects 16 float temperature readings in array named 'squares'
// writes 16 temperatures to file
// increments file counter in the filename
// reads the result from file
// repeats  - 1,000 increments before starting all over again
//
// SD card attached to SPI bus as follows:
// MOSI - Uno pin 11
// MISO - Uno pin 12
// CLK  - Uno pin 13
// CS   - Uno pin 4 
//
// thanks to inspiration: sketch by David A. Mellis - modified by Tom Igoe
// Floris Wouterlood
// September 01, 2022
// public domain


   #include <SPI.h>
   #include <SD.h>
   

   const int chipSelect = 4;                                                       // pin 10 for the UNO SD shield -use D8 for SD card reader on Wemos D1 Mini
   File myFile;
   String stringOne;
   float tempC; 
   float squares [16];                                                             // this array will contain temperature readings
   int i,j;
   int iteration;

   
void setup() {

   Serial.begin(9600);
   while (!Serial)
      {
       ;                                                                           // wait for serial port to connect. Needed for native USB port only
      }  

   Serial.print ("\r\nwaiting for SD card to initialise...");
   if (!SD.begin (chipSelect)) 
      { 
       Serial.println("SD failed!");
       delay (2000);
       return;
      }
   Serial.println ("SD initialisation completed");
   delay(4000);
}

void loop() {

   Serial.println ("now doing SD write operations  --  be careful! . . . . . ");
   if (!SD.begin (chipSelect)) 
      { 
       Serial.println("SD failed!");
       delay (2000);
       return;
      }
   myFile = SD.open("test.txt", FILE_WRITE);

   if (myFile)                                                                     // if the file opened okay, write to it:
     {
      Serial.println ("Success opening file");
     
      myFile.close( );                                                             // close the file:
  
     } else 
        {
         Serial.println ("error opening ");                                          // if the file didn't open, print an error:  
        }
         
        delay(5000);
                                

} 
