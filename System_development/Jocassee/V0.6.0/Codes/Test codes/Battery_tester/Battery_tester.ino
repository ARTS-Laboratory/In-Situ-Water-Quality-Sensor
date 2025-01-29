#define volt_div 2
void setup() {
  Serial.begin(9600);// put your setup code here, to run once:
  
}

void loop() {
  float a = (analogRead(9)*volt_div*5)/1024;
  Serial.println(a);// put your main code here, to run repeatedly:
  
}
