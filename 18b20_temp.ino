//
// Dallas Temperature Sensors
//
#include <OneWire.h>
#include <DallasTemperature.h>

// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS 40

// Setup a oneWire instance to communicate with any OneWire devices 
// (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

DeviceAddress tempDeviceAddress;

int resolution = 12;
unsigned long lastTempRequest = 0;
int delayInMillis = 0;

//
// SETUP
//
void temp_setup(void)
{
  sensors.begin();
  
  // Adrese definirane u main! 
  // todo: (odvoji u env)

  //sensors.getAddress(tempDeviceAddress, 0);

  sensors.setResolution(sonda_odlaz_topla_voda, resolution);
  sensors.setResolution(sonda_pec, resolution);
  sensors.setResolution(sonda_solar, resolution);
  sensors.setResolution(sonda_spremnik, resolution);
  sensors.setResolution(sonda_povrat_hladne_vode, resolution);

  sensors.setWaitForConversion(false);
  sensors.requestTemperatures();

  delayInMillis = 750 / (1 << (12 - resolution));
  lastTempRequest = millis();
}

// Temperature sensors loop.
void temperature_sensors(void)
{

  if (millis() - lastTempRequest >= delayInMillis) // waited long enough??
  {

    //Serial.print(" Temperature: ");

    temp_odlaz_topla_voda = sensors.getTempC(sonda_odlaz_topla_voda);
    
    if (temp_odlaz_topla_voda == -127.0) {
      temp_odlaz_topla_voda = temp_odlaz_topla_voda_h;
      temp_odlaz_topla_voda_ctu = temp_odlaz_topla_voda_ctu + 1;
      if (temp_odlaz_topla_voda_ctu == 10) {
        temp_odlaz_topla_voda = -127.0;
      }
    } else {
      temp_odlaz_topla_voda_h = temp_odlaz_topla_voda;
      temp_odlaz_topla_voda_ctu = 0;
    }

    //
    temp_pec = sensors.getTempC(sonda_pec);

    if (temp_pec == -127.0) {
      temp_pec = temp_pec_h;
      temp_pec_ctu = temp_pec_ctu + 1;
      
      if (temp_pec_ctu == 10) {
        temp_pec = -127.0;
      }
    } else {
      temp_pec_h = temp_pec;
      temp_pec_ctu = 0;
    }

    //
    temp_solar = sensors.getTempC(sonda_solar);

    if (temp_solar == -127.0) {
      temp_solar = temp_solar_h;
      temp_solar_ctu = temp_solar_ctu + 1;

      if (temp_solar_ctu == 10) {
        temp_odlaz_topla_voda = -127.0;
      }
    } else {
      temp_solar_h = temp_solar;
      temp_solar_ctu = 0;
    }

    //
    temp_spremnik = sensors.getTempC(sonda_spremnik );

    if (temp_spremnik == -127.0) {
      temp_spremnik = temp_spremnik_h;
      temp_spremnik_ctu = temp_spremnik_ctu + 1;
      if (temp_spremnik_ctu == 10) {
        temp_odlaz_topla_voda = -127.0;
      }
    } else {
      temp_spremnik_h = temp_spremnik;
      temp_spremnik_ctu = 0;
    }

    //
    temp_povrat_hladne_vode = sensors.getTempC(sonda_povrat_hladne_vode);

    if (temp_povrat_hladne_vode == -127.0) {
      temp_povrat_hladne_vode = temp_povrat_hladne_vode_h;
      temp_povrat_hladne_vode_ctu = temp_povrat_hladne_vode_ctu + 1;
      if (temp_povrat_hladne_vode_ctu == 10) {
        temp_odlaz_topla_voda = -127.0;
      }
    } else {
      temp_povrat_hladne_vode_h = temp_povrat_hladne_vode;
      temp_povrat_hladne_vode_ctu = 0;
    }

    //sensors.setResolution(tempDeviceAddress, resolution);
    
    sensors.requestTemperatures();

    delayInMillis = 750 / (1 << (12 - resolution));
    delayInMillis = delayInMillis + 500;
    
    Serial.println(temp_odlaz_topla_voda);
    Serial.println(temp_pec);
    Serial.println(temp_solar);
    Serial.println(temp_spremnik);
    Serial.println(temp_povrat_hladne_vode);
    
    lastTempRequest = millis();
  }

}
