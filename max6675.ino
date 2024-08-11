// note: max6675!
/*
  gnd plava
  vcc crvena
  sck zelena
  cs zuta
  so naranđasta
*/

const int dataPin   = 23;
const int clockPin  = 27;
const int selectPin = 25;

MAX6675 thermoCouple;
uint32_t start, stop;

void max6675_setup() {
  thermoCouple.begin(clockPin, selectPin, dataPin); 
   thermoCouple.setSPIspeed(4000000);
}

void max6675()
{

  start = micros();
  int status = thermoCouple.read();
  
  stop = micros();
  temp_dimnjak = thermoCouple.getTemperature();
  
  Serial.print(millis());
  Serial.print("\tstatus: ");
  Serial.print(status);
  Serial.print("\ttemp: ");
  Serial.print(temp_dimnjak);
  Serial.print("\tus: ");
  Serial.println(stop - start);
  
}
