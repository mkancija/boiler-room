#include <PZEM004T.h>
PZEM004T* pzem;
IPAddress ip_pzem(192,168,1,1);

// Energy monitor.
// https://github.com/vortigont/pzem-edl/blob/main/docs/PZEM-004T-V3.0-Datasheet-User-Manual.pdf

void pzem_setup() 
{
  Serial.println("Setup PZEM004T");
  
  while(!Serial1) { }

  pzem = new PZEM004T(&Serial1);
  pzem->setAddress(ip_pzem);
  
  Serial.println("PZEM004T  OK");
}

// PZEM_loop
void energy_monitor() 
{
  v = pzem->voltage(ip_pzem);

  if (v < 0.0) {
    Serial.println("nema komunikacije ili 230V napajanja!!!");
  }

  Serial.print(v);
  Serial.print("V; ");

  struja = pzem->current(ip_pzem);

  if(struja >= 0.0) {
    Serial.print(struja);Serial.print("A; ");
  }
  
  p = pzem->power(ip_pzem);

  if(p >= 0.0) {
    Serial.print(p);Serial.print("W; "); 
  }
  
  e = pzem->energy(ip_pzem);

  if(e >= 0.0) { 
    Serial.print(e);Serial.print("Wh; "); 
  }

  Serial.println();
}
