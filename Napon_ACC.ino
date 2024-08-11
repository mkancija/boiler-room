const int numReadings = 500;

int readings[numReadings]; // the readings from the analog input
long readIndex = 0;        // the index of the current reading
long total = 0;            // the running total
long average = 0;          // the average

int inputPin = A8;

void napon_ACC_setup() {  
  // initialize all the readings to 0:
  for (int thisReading = 0; thisReading < numReadings; thisReading++) {
    readings[thisReading] = 0;
  }
}

void napon_ACC_loop() {
  while(true){ 
    // subtract the last reading:
    total = total - readings[readIndex];
    
    // read from the sensor:
    readings[readIndex] = analogRead(inputPin);
    
    // add the reading to the total:
    total = total + readings[readIndex];
    
    // advance to the next position in the array:
    readIndex = readIndex + 1;

    // if we're at the end of the array...
    if (readIndex >= numReadings) {      
      // ...wrap around to the beginning:
      readIndex = 0;

      // calculate the average:
      average = total / numReadings;
      voltage_acc = average * (5.0 / 1023.0)*3.86645;
      
      Serial.print("Napon na ACC: ");
      Serial.print(voltage_acc);
      Serial.println(" V");
      Serial.println(" ");
      
        break;
    }

    delay(1);        // delay in between reads for stability
    
  }
}
