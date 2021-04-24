/* <Open-JIP (v0.3) Teensy 3.6 Script. Controls "Open-JIP" chlorophyll fluorometer v0.3>
     Copyright (C) <2020>  <Harvey Bates>

     This program is free software: you can redistribute it and/or modify
     it under the terms of the GNU General Public License as published by
     the Free Software Foundation, either version 3 of the License, or
     (at your option) any later version.
     
     This program is distributed in the hope that it will be useful,
     but WITHOUT ANY WARRANTY; without even the implied warranty of
     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
     GNU General Public License for more details.
     
     You should have received a copy of the GNU General Public License
     along with this program.  If not, see <https://www.gnu.org/licenses/>
     
     For more information contact: harvey.bates@student.uts.edu.au or see
     https://github.com/HarveyBates/Open-JIP 
*/ 

#include "fluorescence.h"

Fluorescence::Fluorescence(){
  set_reference_voltage(refVoltage); // Only applicable with a Teensy 3.6 (disable if using other microcontroller)
  set_resolution(readResolution);
}

void Fluorescence::set_resolution(unsigned int resolution){
  readResolution = resolution;
  analogReadResolution(resolution);
  analogRead(readPin); // Initalise resolution
}

float Fluorescence::get_bit_resoltuion(){
  return (float)pow(2, readResolution);
}

void Fluorescence::set_reference_voltage(float voltage){
  // Sets and initalises the required reference voltage for measurments
  if(voltage == 3.3){
    analogReference(DEFAULT); // Set to 3.3 V
  }
  else if(voltage == 1.1){
    analogReference(INTERNAL1V1); // Set to 1.1 V
  }
  else{
    analogReference(DEFAULT); // Set to default (3.3 V) if unknown value is found
  }
  analogRead(readPin); // Initalise reference voltage
}

void Fluorescence::measure_j_step(Actinic actinic){
  /* Measures up to the J-Step (2 ms) and prints the values in the serial output*/
  set_reference_voltage(refVoltage);
  
  actinic.on();
  long timer = micros();

  /* Read the values */
  for(unsigned int i = 0; i < sizeof(microReadJ) / sizeof(int); i++){
    microReadJ[i] = analogRead(readPin);
    microTimeJ[i] = micros() - timer;
  }

  actinic.off();

  /* Convert and print out the values */
  for(unsigned int i = 0; i < sizeof(microReadJ) / sizeof(int); i++){
    jTime[i] = microTimeJ[i] / 1000.0; // Convert to ms
    jValues[i] = (microReadJ[i] * refVoltage) / get_bit_resoltuion(); // Convert bits to V
    Serial.print(jTime[i], 3); 
    Serial.print("\t");
    Serial.println(jValues[i], 4);
    delay(5);
  }
}


void Fluorescence::wave(Actinic actinic){
  set_reference_voltage(refVoltage); 
  unsigned int wavePos = 0; // Keeps track of position in wave acquisition array
  for(unsigned int i = 0; i < numWaves; i++){
    
    actinic.on();
    long timer = micros();
      
    for(unsigned int x = 0; x < waveAqu; x++){
      waveRead[wavePos] = analogRead(readPin);
      waveTime[wavePos] = micros() - timer;
      wavePos++;
    }
    
    actinic.off();
    for(unsigned int x = 0; x <= 5; x++){
      actinic.on();
      delayMicroseconds(100);
      waveRead[wavePos] = analogRead(readPin);
      waveTime[wavePos] = micros() - timer;
      actinic.off();
      delayMicroseconds(200);
    }
    delay(waveInterval); // Delay for specified interval
  }

  // Prints out the data
  for(unsigned int i = 0; i < waveLength; i++){
    Serial.print(waveTime[i] / 1000.0, 3); 
    Serial.print("\t");
    Serial.println((waveRead[i] * refVoltage) / get_bit_resoltuion(), 4);
  }
}

void Fluorescence::measure_fluorescence(unsigned int actinicPin) {
  digitalWrite(actinicPin, HIGH);
  
  long long timer = micros(); // Start timer 

  // Read microsecond fluorescence values and corresponding timestamps
  for (unsigned int i = 0; i < sizeof(microRead) / sizeof(int); i++) 
  {
    microRead[i] = analogRead(readPin);
    microTime[i] = micros() - timer;
  }

  // Read millisecond fluorescence values and corresponding timestamps
  for (unsigned int i = 0; i < sizeof(milliRead) / sizeof(int); i++) 
  {
    milliRead[i] = analogRead(readPin);
    milliTime[i] = micros() - timer;
    delay(1);
  }
  
  digitalWrite(actinicPin, LOW); // Turn off actinic LED
  delay(10);

  // Convert micros() to milliseconds (ms) for microsecond values and convert bits to voltage
  for (unsigned int i = 0; i < sizeof(microRead) / sizeof(int); i++)
  {
   float milliReal = microTime[i]/1000.0; // Convert micros() to ms
   // Find fm value, we do this here while the data is an interger
   if (microRead[i] > fm){
    fm = microRead[i];
   }
   fluorescenceValues[i] = (microRead[i] * refVoltage) / get_bit_resoltuion(); // Convert to volts and append to final array
   timeStamps[i] = milliReal; // Append time to final array
   Serial.print(milliReal, 3); 
   Serial.print("\t");
   Serial.println((microRead[i] * refVoltage) / get_bit_resoltuion(), 4);
   delay(1);
  }

  // Convert micros() to milliseconds for millsecond values and convert bits to voltage
  for (unsigned int i = 0; i < sizeof(milliRead) / sizeof(int); i++) 
  {
   float milliReal = milliTime[i]/1000.0; // Convert micros() to ms
   // Find fm value if not in microsecond range
   if (milliRead[i] > fm){
    fm = milliRead[i];
   }
   fluorescenceValues[i + microLength] = (milliRead[i] * refVoltage) / get_bit_resoltuion(); // Convert to V and append
   timeStamps[i + microLength] = milliReal; // Append to timestamps after microRead data
   Serial.print(milliReal, 3); 
   Serial.print("\t");
   Serial.println((milliRead[i] * refVoltage) / get_bit_resoltuion(), 4);
   delay(1);
  }
}

void Fluorescence::calculate_parameters(){
  float fo = fluorescenceValues[foPos]; // Gets the minimum level fluorescence (Fo)
  float fj = 0.0f, fi = 0.0f;
  float  fjTime = 0.0f, fiTime = 0.0f, fmTime = 0.0f;
  bool fjFound = false, fiFound = false;

  // Next loop gets the Fj and Fi values at 2 and 30 ms respsctively 
  for(unsigned int i = 0; i < sizeof(timeStamps) / sizeof(int); i++){
    // Search for timestamp corresponding to 2 ms
    if(!fjFound && int(timeStamps[i]) == 2){
      fj = fluorescenceValues[i];
      fjTime = timeStamps[i];
      fjFound = true;
    }
    else if(!fiFound && int(timeStamps[i]) == 30){
      fi = fluorescenceValues[i];
      fiTime = timeStamps[i];
      fiFound = true;
    }
  }

  float fmVolts = (fm * refVoltage) / get_bit_resoltuion();
  float fv = fmVolts - fo;
  float fvfm = fv / fmVolts;

  Serial.println();
  Serial.print("Fo: \t");
  Serial.print(fo, 4);
  Serial.print(" V @ ");
  Serial.print(timeStamps[foPos], 4);
  Serial.println(" ms");
  Serial.print("Fj: \t");
  Serial.print(fj, 4);
  Serial.println(" V @ " + String(fjTime) + " ms");
  Serial.print("Fi: \t");
  Serial.print(fi, 4);
  Serial.println(" V @ " + String(fiTime) + " ms");
  Serial.print("Fm: \t");
  Serial.print(fmVolts, 4);
  Serial.println(" V @ " + String(fmTime) + " ms");
  Serial.print("Fv: \t");
  Serial.print(fv, 4);
  Serial.println(" V");
  Serial.print("Quantum yield (Fv/Fm): \t");
  Serial.print(fvfm, 3);
  if(fvfm < 0.5){
    Serial.println(" Poor health");
  }
  else if(fvfm >= 0.5 && fvfm < 0.7){
    Serial.println(" Moderately healthy");
  }
  else if(fvfm >= 0.7){
    Serial.println(" Healthy");
  }
}

void Fluorescence::calibrate_fo(Actinic actinic){
  /* Calibrate the fo value of the fluorometer, can be used to ensure the concentration of algae
  is not too high
  */  
  float foread = 0.0f;
  for (int k = 0; k < 5; k++){
    actinic.on();
    delayMicroseconds(20);
    for (int i = 0; i <= 2; i++){
      foread = analogRead(readPin);
      Serial.println((foread / get_bit_resoltuion()) * refVoltage);
    }
    actinic.off();
    Serial.print("Final Fo = ");
    Serial.println((foread / get_bit_resoltuion()) * refVoltage);
    delay(2000);
    }
}

void Fluorescence::calibrate_rise(Actinic actinic){
  // Calibrate the rise time of the fluorometer (useful for debugging)
  for (int i = 0; i < 200; i++){
    actinic.on();
    delayMicroseconds(100);
    actinic.off();
    delay(200);
  }
}

void Fluorescence::measure_light(Actinic actinic){
  // Measure light using an external light meter
  actinic.on();
  delay(3000);
  actinic.off();
  delay(20);
}
