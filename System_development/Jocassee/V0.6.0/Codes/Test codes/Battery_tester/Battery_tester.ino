#define volt_div 2.03
void setup() {
  Serial.begin(9600);// put your setup code here, to run once:
  
}

void loop() {
  float a = (analogRead(A9)*volt_div*5.00)/1023.00;
  Serial.println(a);// put your main code here, to run repeatedly:
  
}
