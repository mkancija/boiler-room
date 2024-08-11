
// ULAZ JE INVERTIRAN OD STRANE MODULA

byte UVJET_RADA_PEC_AUTO = A6;
byte UVJET_RADA_PEC_RUCNO = A7;
byte CRPKA_SPREMNIK_VODE_AUTO = A5;
byte CRPKA_SPREMNIK_VODE_RUCNO = A4;
byte CRPKA_RADIJATORA_AUTO = A3;
byte CRPKA_RADIJATORA_RUCNO = A2;
byte GRESKA_PLAMENIKA = A0;
byte NAPAJANJE = A1;


byte SIGNAL_TERMOSTATA = 37;
byte SIGNAL_CRPKA_RADIJATORA = 36;
byte SIGNAL_CRPKA_SANITATNI_KOTEL = 35;
byte SIGNAL_RECIRKULACIJA = 34;
//33
//32
byte SIGNAL_UPRAVLJANJE_ARDUINO =31;
byte SIGNAL_UPTAVLJANJE_TERMOSTATI =30;


void setup_DI_ulazi()
{
  //KABEL 1 - grebenasta.
  pinMode(UVJET_RADA_PEC_AUTO, INPUT);  // temperatura kod koje pumpe moraju početi raditi
  pinMode(UVJET_RADA_PEC_RUCNO, INPUT); //
  pinMode(CRPKA_SPREMNIK_VODE_AUTO, INPUT);  // CRPKA SPREMINKA
  pinMode(CRPKA_SPREMNIK_VODE_RUCNO, INPUT); //
  pinMode(CRPKA_RADIJATORA_AUTO, INPUT);  // CRPKA RADIJATORA
  pinMode(CRPKA_RADIJATORA_RUCNO, INPUT); //
  pinMode(GRESKA_PLAMENIKA, INPUT); // GRESKA_PLAMENIKA
  pinMode(NAPAJANJE, INPUT);        // NAPAJANJE
 
  //KABEL 2
  pinMode(SIGNAL_TERMOSTATA, INPUT);  // 8
  pinMode(SIGNAL_CRPKA_RADIJATORA, INPUT);  //9
  pinMode(SIGNAL_CRPKA_SANITATNI_KOTEL, INPUT);  // 10
  pinMode(SIGNAL_RECIRKULACIJA, INPUT);  //11
  pinMode(33, INPUT);  // 12
  pinMode(32, INPUT);  //13
  pinMode(SIGNAL_UPRAVLJANJE_ARDUINO, INPUT);  // 14
  pinMode(SIGNAL_UPTAVLJANJE_TERMOSTATI, INPUT);  //  15
}

void digital_input_main()
{

  Serial.print("UVJET_RADA_PEC_AUTO:");
  Serial.println(!digitalRead(UVJET_RADA_PEC_AUTO));

  Serial.print("UVJET_RADA_PEC_RUCNO:");
  Serial.println(!digitalRead(UVJET_RADA_PEC_RUCNO));

  Serial.print("CRPKA_SPREMNIK_VODE_AUTO:");
  Serial.println(!digitalRead(CRPKA_SPREMNIK_VODE_AUTO));

  Serial.print("CRPKA_SPREMNIK_VODE_RUCNO:");
  Serial.println(!digitalRead(CRPKA_SPREMNIK_VODE_RUCNO));

  Serial.print("CRPKA_RADIJATORA_AUTO:");
  Serial.println(!digitalRead(CRPKA_RADIJATORA_AUTO));

  Serial.print("CRPKA_RADIJATORA_RUCNO:");
  Serial.println(!digitalRead(CRPKA_RADIJATORA_RUCNO));

  Serial.print("GRESKA_PLAMENIKA:");
  Serial.println(!digitalRead(GRESKA_PLAMENIKA));

  Serial.print("NAPAJANJE:");
  Serial.println(!digitalRead(NAPAJANJE));

  Serial.print("SIGNAL_TERMOSTATA:");
  Serial.println(!digitalRead(SIGNAL_TERMOSTATA));

  Serial.print("SIGNAL_CRPKA_RADIJATORA:");
  Serial.println(!digitalRead(SIGNAL_CRPKA_RADIJATORA));

  Serial.print("SIGNAL_CRPKA_SANITATNI_KOTEL:");
  Serial.println(!digitalRead(SIGNAL_CRPKA_SANITATNI_KOTEL));

  Serial.print("SIGNAL_RECIRKULACIJA:");
  Serial.println(!digitalRead(SIGNAL_RECIRKULACIJA));

  Serial.print("SIGNAL_UPRAVLJANJE_ARDUINO:");
  Serial.println(!digitalRead(SIGNAL_UPRAVLJANJE_ARDUINO));

  Serial.print("SIGNAL_UPTAVLJANJE_TERMOSTATI:");
  Serial.println(!digitalRead(SIGNAL_UPTAVLJANJE_TERMOSTATI));

  DI_ulazi_modbus=!digitalRead(UVJET_RADA_PEC_AUTO);
  Serial.print("DI_ulazi_modbus0:");
  Serial.println(DI_ulazi_modbus);

  DI_ulazi_modbus+=!digitalRead(UVJET_RADA_PEC_RUCNO)<<1;
  Serial.print("DI_ulazi_modbus1:");
  Serial.println(DI_ulazi_modbus);

  DI_ulazi_modbus+=!digitalRead(CRPKA_SPREMNIK_VODE_AUTO)<<2;
  Serial.print("DI_ulazi_modbus2:");
  Serial.println(DI_ulazi_modbus);

  DI_ulazi_modbus+=!digitalRead(CRPKA_SPREMNIK_VODE_RUCNO)<<3;
  Serial.print("DI_ulazi_modbus3:");
  Serial.println(DI_ulazi_modbus);

  DI_ulazi_modbus+=!digitalRead(CRPKA_RADIJATORA_AUTO)<<4;  
  Serial.print("DI_ulazi_modbus4:");
  Serial.println(DI_ulazi_modbus);

  DI_ulazi_modbus+=!digitalRead(CRPKA_RADIJATORA_RUCNO)<<5;  
  Serial.print("DI_ulazi_modbus5:");
  Serial.println(DI_ulazi_modbus);

  DI_ulazi_modbus+=!digitalRead(GRESKA_PLAMENIKA)<<6;  
  Serial.print("DI_ulazi_modbus6:");
  Serial.println(DI_ulazi_modbus);

  DI_ulazi_modbus+=!digitalRead(NAPAJANJE)<<7;  
  Serial.print("DI_ulazi_modbus7:");
  Serial.println(DI_ulazi_modbus);

  DI_ulazi_modbus+=!digitalRead(SIGNAL_TERMOSTATA)<<8;
  Serial.print("DI_ulazi_modbus8:");
  Serial.println(DI_ulazi_modbus);

  DI_ulazi_modbus+=!digitalRead(SIGNAL_CRPKA_RADIJATORA)<<9;
  Serial.print("DI_ulazi_modbus9:");
  Serial.println(DI_ulazi_modbus);

  DI_ulazi_modbus+=!digitalRead(SIGNAL_CRPKA_SANITATNI_KOTEL)<<10;
  Serial.print("DI_ulazi_modbus10:");
  Serial.println(DI_ulazi_modbus);

  DI_ulazi_modbus+=!digitalRead(SIGNAL_RECIRKULACIJA)<<11;
  Serial.print("DI_ulazi_modbus11:");
  Serial.println(DI_ulazi_modbus);

  DI_ulazi_modbus+=!digitalRead(0)<<12;
  Serial.print("DI_ulazi_modbus12:");
  Serial.println(DI_ulazi_modbus);

  DI_ulazi_modbus+=!digitalRead(0)<<13;
  Serial.print("DI_ulazi_modbus13:");
  Serial.println(DI_ulazi_modbus);

  DI_ulazi_modbus+=!digitalRead(SIGNAL_UPRAVLJANJE_ARDUINO)<<14;
  Serial.print("DI_ulazi_modbus14:");
  Serial.println(DI_ulazi_modbus);

  DI_ulazi_modbus+=!digitalRead(SIGNAL_UPTAVLJANJE_TERMOSTATI)<<15;
  Serial.print("DI_ulazi_modbus15:");
  Serial.println(DI_ulazi_modbus);

  Serial.print("DI_ulazi_modbus:");
  Serial.println(DI_ulazi_modbus);
}