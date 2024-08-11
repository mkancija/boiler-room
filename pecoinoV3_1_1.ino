
//v3.1.0 dodan mjerač protoka i arduino preseljen u OG ormarič
//       -Dodani izlazi DO         
//V3.1.1 -Dodan_AI_ulaz za mjerenje napona na akumulatoru 



// Include the libraries we need
#include <OneWire.h>
#include <DallasTemperature.h>
#include <Ethernet.h>
#include <PZEM004T.h>
#include "MAX6675.h"

String verzija="pecoino V3.1.1";

float v, struja, p, e, voltage,voltage_acc;

float temp_odlaz_topla_voda = 0.0;
float temp_pec = 0.0;
float temp_solar = 0.0;
float temp_spremnik = 0.0;
float temp_povrat_hladne_vode = 0.0;
float temp_dimnjak = 0.0;

float temp_odlaz_topla_voda_h = 0.0;
float temp_pec_h = 0.0;
float temp_solar_h = 0.0;
float temp_spremnik_h = 0.0;
float temp_povrat_hladne_vode_h = 0.0;
  

int temp_odlaz_topla_voda_ctu = 0;
int temp_pec_ctu = 0;
int temp_solar_ctu = 0;
int temp_spremnik_ctu = 0;
int temp_povrat_hladne_vode_ctu = 0;

//********************* mj. protoka *******************************************

byte statusLed    = 13;

byte sensorInterrupt = 1;  // 1 = digital pin 3
byte sensorPin       = 3;

// The hall-effect flow sensor outputs approximately 4.5 pulses per second per
// litre/minute of flow.
float calibrationFactor = 6.5163;  //6.5163;
float calibrationDifference = 2.7;  //2.7;

volatile byte pulseCount;  

float flowRate;
unsigned long flowMilliLitres;
unsigned long totalMilliLitres;
float totalMilliLitres_scada;

unsigned long oldTime;

//******************DI_ULAZI******************
int DI_ulazi_modbus=0;


String httpreq;
// Temp sensors-i2c adrese:
DeviceAddress sonda_odlaz_topla_voda = {0x28, 0xFF, 0x72, 0xB3, 0xB2, 0x17, 0x01, 0x90  }; // temp odlaz tople  vode
DeviceAddress sonda_pec = {0x28, 0xFF, 0x5A, 0xB8, 0xB2, 0x17, 0x01, 0xC2  }; //peč
DeviceAddress sonda_solar = {0x28, 0xFF, 0x81, 0x09, 0xC0, 0x17, 0x05, 0x33  }; //solar
DeviceAddress sonda_spremnik = {0x28, 0xFF, 0x1F, 0xBA, 0xB2, 0x17, 0x01, 0xFE  }; //spremnik
DeviceAddress sonda_povrat_hladne_vode = {0x28, 0xFF, 0x5F, 0xB9, 0xB2, 0x17, 0x01, 0x9F  }; //temp povrat hladne

union fsend_t {
  float f;
  uint16_t u[2];
};

int ModbusTCP_port = 502;
EthernetServer MBServer(ModbusTCP_port);

void (*softReset) (void) = 0; //declare reset function @ address 0

void setup() {
  // while(!Serial) { }
  Serial.begin(115200);
  Serial.println(String(verzija));

  temp_setup();
  pzem_setup();
  Eth_setup();
  max6675_setup();
  MBServer.begin();

  setup_mj_protoka();
  setup_DO_izlazi();
  setup_DI_ulazi();
  napon_ACC_setup();
  
  Serial.println(String("--------------STARTING------------------"));
}

void loop() {
  mjerac_protoka();
  energy_monitor();
  temperature_sensors();
  
  //Eth_loop(); - skip
  max6675();
  Modbus();

  digital_output_main(); 
  digital_input_main();
  
  napon_ACC_loop();
}
