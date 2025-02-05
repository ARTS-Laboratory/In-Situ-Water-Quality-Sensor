bool check_error(){
  
}

float check_bat_volt(){
  return analogRead(V_BAT_sense);
}

float read_pH(){
  
}

float read_TDS(){
  
}

bool write2SD(){
  
}

bool transmit(){
  
}

void power_peripheral(bool a){
  digitalWrite(P_En, a);
}
