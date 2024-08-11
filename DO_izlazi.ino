
// PL3; iz nekog razloga blesira arduino.

// LOW  = 1
// HIGH = 0

byte Rele_1 = 47;
byte Rele_2 = 46;
byte Rele_3 = 45;
byte Rele_4 = 44;


void setup_DO_izlazi()
{
  pinMode(Rele_1, OUTPUT);  //rele 1
  digitalWrite(Rele_1, HIGH);  // We have an active-low LED attached
  pinMode(Rele_2, OUTPUT);  //rele 2
  digitalWrite(Rele_2, HIGH);  // We have an active-low LED attached
  pinMode(Rele_3, OUTPUT);  //rele 3
  digitalWrite(Rele_3, HIGH);  // We have an active-low LED attached
  pinMode(Rele_4, OUTPUT);  //rele 4
  digitalWrite(Rele_4, HIGH);  // We have an active-low LED attached
}

// loop_DO_izlazi
void digital_output_main()
{
  if(flowRate>0){
    digitalWrite(Rele_1, LOW);  // We have an active-low LED attached
  } else {
    digitalWrite(Rele_1, HIGH);  // We have an active-low LED attached
  }
}