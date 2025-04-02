    /*
  modified on Sep 28, 2020
  Modified by MohammedDamirchi from Arduino Examples
  Home
*/


// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(115200);
  pinMode(7,OUTPUT);
  pinMode(6,INPUT);
  digitalWrite(7,HIGH);
}

// the loop routine runs over and over again forever:
void loop() {
  // read the input on analog pin 0:
  digitalWrite(7,HIGH);

  Serial.print(((-(analogRead(A7)*5.00)/1023.00)+4.36)/0.008);
  Serial.print("  /  ");
  Serial.println((analogRead(A7)*5.00)/1023.00);
  delay(200);
  }
