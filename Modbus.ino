//////// Required for Modbus TCP / IP
#define maxInputRegister 20
#define maxHoldingRegister 20

#define MB_FC_NONE 0
#define MB_FC_READ_REGISTERS 3 //implemented
#define MB_FC_WRITE_REGISTER 6 //implemented
#define MB_FC_WRITE_MULTIPLE_REGISTERS 16 //implemented
//
// MODBUS Error Codes
//
#define MB_EC_NONE 0
#define MB_EC_ILLEGAL_FUNCTION 1
#define MB_EC_ILLEGAL_DATA_ADDRESS 2
#define MB_EC_ILLEGAL_DATA_VALUE 3
#define MB_EC_SLAVE_DEVICE_FAILURE 4
//
// MODBUS MBAP offsets
//
#define MB_TCP_TID 0
#define MB_TCP_PID 2
#define MB_TCP_LEN 4
#define MB_TCP_UID 6
#define MB_TCP_FUNC 7
#define MB_TCP_REGISTER_START 8
#define MB_TCP_REGISTER_NUMBER 10

byte ByteArray[260];
unsigned int MBHoldingRegister[maxHoldingRegister];

unsigned long lastTempRequest_modbus = 0;
int  delayInMillis_modbus = 10000;


void Modbus() {
  
  boolean flagClientConnected = 0;
  byte byteFN = MB_FC_NONE;
  int Start;
  int WordDataLength;
  int ByteDataLength;
  int MessageLength;

  // listen for incoming clients
  EthernetClient client = MBServer.available();
    
  if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();
  }   

  // Modbus TCP/IP
  // while (client.connected()) {
  if (client) {
    if (client.connected()) {

      flagClientConnected = 1;
      int i = 0;

      while (client.available()) {
        ByteArray[i] = client.read();
        i++;
        if (i == 260)break;
      }
      //client.flush();

      ///////// Holding Register [0] A [9] = 10 Holding Registers Escritura
      ///////// Holding Register [0] A [9] = 10 Holding Registers Writing
      union fsend_t floatConvert;
      union fsend_t floatConvert2;
      union fsend_t floatConvert3;
      union fsend_t floatConvert4;
      union fsend_t floatConvert5;
      union fsend_t floatConvert6;
      union fsend_t floatConvert7;
      union fsend_t floatConvert8;
      union fsend_t floatConvert9;
      union fsend_t floatConvert10;
      union fsend_t floatConvert11;
      union fsend_t floatConvert12;
      union fsend_t floatConvert13;

      floatConvert.f = temp_odlaz_topla_voda;
      floatConvert2.f = temp_povrat_hladne_vode;
      floatConvert3.f = temp_pec;
      floatConvert4.f = temp_solar;
      floatConvert5.f = temp_spremnik;
      floatConvert6.f = temp_dimnjak;
      floatConvert7.f = v;
      floatConvert8.f = struja;
      floatConvert9.f = p;
      floatConvert10.f = e;
      floatConvert11.f = flowRate;
      floatConvert12.f = totalMilliLitres_scada;
      floatConvert13.f = voltage_acc;

      MBHoldingRegister[0] = floatConvert.u[0];   //temp_odlaz_topla_voda
      MBHoldingRegister[1] = floatConvert.u[1];   //temp_odlaz_topla_voda
      MBHoldingRegister[2] = floatConvert2.u[0];  //temp_povrat_hladne_vode
      MBHoldingRegister[3] = floatConvert2.u[1];  //temp_povrat_hladne_vode
      MBHoldingRegister[4] = floatConvert3.u[0];  //temp_pec
      MBHoldingRegister[5] = floatConvert3.u[1];  //temp_pec
      MBHoldingRegister[6] = floatConvert4.u[0];  //temp_solar;
      MBHoldingRegister[7] = floatConvert4.u[1];  //temp_solar;
      MBHoldingRegister[8] = floatConvert5.u[0];  //temp_spremnik;
      MBHoldingRegister[9] = floatConvert5.u[1];  //temp_spremnik;
      MBHoldingRegister[10] = floatConvert6.u[0]; //temp_dimnjak
      MBHoldingRegister[11] = floatConvert6.u[1]; //temp_dimnjak
      MBHoldingRegister[12] = floatConvert7.u[0]; //v
      MBHoldingRegister[13] = floatConvert7.u[1]; //v
      MBHoldingRegister[14] = floatConvert8.u[0]; //i
      MBHoldingRegister[15] = floatConvert8.u[1]; //i
      MBHoldingRegister[16] = floatConvert9.u[0]; //p
      MBHoldingRegister[17] = floatConvert9.u[1]; //p
      MBHoldingRegister[18] = floatConvert10.u[0]; //e
      MBHoldingRegister[19] = floatConvert10.u[1]; //e
      MBHoldingRegister[20] = floatConvert11.u[0]; //protok l/min
      MBHoldingRegister[21] = floatConvert11.u[1]; //protok l/min
      MBHoldingRegister[22] = floatConvert12.u[0]; //totalMilliLitres
      MBHoldingRegister[23] = floatConvert12.u[1]; //totalMilliLitres
      MBHoldingRegister[24] = DI_ulazi_modbus; //
      MBHoldingRegister[26] = floatConvert13.u[0]; //totalMilliLitres
      MBHoldingRegister[27] = floatConvert13.u[1]; //totalMilliLitres

      //// routine Modbus TCP
      byteFN = ByteArray[MB_TCP_FUNC];
      Start = word(ByteArray[MB_TCP_REGISTER_START], ByteArray[MB_TCP_REGISTER_START + 1]);
      WordDataLength = word(ByteArray[MB_TCP_REGISTER_NUMBER], ByteArray[MB_TCP_REGISTER_NUMBER + 1]);
      lastTempRequest_modbus = millis();
    }    
  } else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }

  // Handle request
  switch (byteFN) {
    case MB_FC_NONE:
      break;
    case MB_FC_READ_REGISTERS: // 03 Read Holding Registers
      ByteDataLength = WordDataLength * 2;
      ByteArray[5] = ByteDataLength + 3; //Number of bytes after this one.
      ByteArray[8] = ByteDataLength; //Number of bytes after this one (or number of bytes of data).
      
      for (int i = 0; i < WordDataLength; i++) {
        ByteArray[ 9 + i * 2] = highByte(MBHoldingRegister[Start + i]);
        ByteArray[10 + i * 2] = lowByte(MBHoldingRegister[Start + i]);
      }
      
      MessageLength = ByteDataLength + 9;
      client.write((const uint8_t *)ByteArray, MessageLength);
      byteFN = MB_FC_NONE;
      break;

    case MB_FC_WRITE_REGISTER: // 06 Write Holding Register
      MBHoldingRegister[Start] = word(ByteArray[MB_TCP_REGISTER_NUMBER], ByteArray[MB_TCP_REGISTER_NUMBER + 1]);
      ByteArray[5] = 6; //Number of bytes after this one.
      MessageLength = 12;
      client.write((const uint8_t *)ByteArray, MessageLength);

      byteFN = MB_FC_NONE;
      break;

    case MB_FC_WRITE_MULTIPLE_REGISTERS: //16 Write Holding Registers
      ByteDataLength = WordDataLength * 2;
      ByteArray[5] = ByteDataLength + 3; //Number of bytes after this one.

      for (int i = 0; i < WordDataLength; i++) {
        MBHoldingRegister[Start + i] = word(ByteArray[ 13 + i * 2], ByteArray[14 + i * 2]);
      }

      MessageLength = 12;
      client.write((const uint8_t *)ByteArray, MessageLength);
      byteFN = MB_FC_NONE;
      break;
  }
}
