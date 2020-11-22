/* <Open-JIP Teensy 3.6 Script. Controls "Open-JIP" chlorophyll fluorometer>
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

// Analog Pins
#define readPin 18

// Digital Pins
#define actinicPin 21

// Setup arrays that hold fluorescence data
int microRead [1000];
int milliRead[1000];

// Setup arrays that hold timestamps that correspond to fluorescence values
float microTime[1000]; 
float milliTime[1000];
String command;

int microLength = 1000, milliLength = 1000; // Change these to match the size of the above arrays

// Setup arrays to hold all datapoints and corresponding timestamps
float fluorescenceValues[2000];
float timeStamps[2000];

int fm = 0; // Initalise the fm value so we can calcualte it later

float refVoltage = 3.3; // Set the reference voltage (only applicable with Teensy 3.6)

void setup() {
  Serial.begin(115200); // Initalise serial communications at specific baud rate
  analogReadResolution(12); // Set the resolution of the microcontroller in bits
  set_reference_voltage(refVoltage); // Only applicable with a Teensy 3.6 (disable if using other microcontroller)
  pinMode(actinicPin, OUTPUT); // Set the actinic pin as an output
  digitalWrite(actinicPin, LOW); // Make sure the actinic LED is turned off
  pinMode(13, OUTPUT); // Sets the microcontrollers LED pin as an output
}

void set_reference_voltage(float voltage){
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

void measure_fluorescence() {
  set_reference_voltage(refVoltage); 
  
  digitalWrite(actinicPin, HIGH); // Turn on actinic LED

  long timer = micros(); // Start timer 

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
   float milliReal = microTime[i]/1000; // Convert micros() to ms
   // Find fm value, we do this here while data are still ints
   if (microRead[i] > fm){
    fm = microRead[i];
   }
   fluorescenceValues[i] = (microRead[i] * refVoltage) / 4096; // Convert to volts and append to final array
   timeStamps[i] = milliReal; // Append time to final array
   Serial.print(milliReal, 3); 
   Serial.print("\t");
   Serial.println((microRead[i] * refVoltage) / 4096, 4);
   delay(1);
  }

  // Convert micros() to milliseconds for millsecond values and convert bits to voltage
  for (unsigned int i = 0; i < sizeof(milliRead) / sizeof(int); i++) 
  {
   float milliReal = milliTime[i]/1000; // Convert micros() to ms
   // Find fm value if not in microsecond range
   if (milliRead[i] > fm){
    fm = milliRead[i];
   }
   fluorescenceValues[i + microLength] = (milliRead[i] * refVoltage) / 4096; // Convert to V and append
   timeStamps[i + microLength] = milliReal; // Append to timestamps after microRead data
   Serial.print(milliReal, 3); 
   Serial.print("\t");
   Serial.println((milliRead[i] * refVoltage) / 4096, 4);
   delay(1);
  }
}

void calculate_parameters(){
  float fo = fluorescenceValues[4]; // Gets the minimum level fluorescence (Fo)
  float fj = 0.0f, fi = 0.0f;
  float fj_time = 0.0f, fi_time = 0.0f, fm_time = 0.0f;
  bool fj_found = false, fi_found = false;

  // Next loop gets the Fj and Fi values at 2 and 30 ms respsctively 
  for(unsigned int i = 0; i < sizeof(timeStamps) / sizeof(int); i++){
    // Search for timestamp corresponding to 2 ms
    if(!fj_found && int(timeStamps[i]) == 2){
      fj = fluorescenceValues[i];
      fj_time = timeStamps[i];
      fj_found = true;
    }
    else if(!fi_found && int(timeStamps[i]) == 30){
      fi = fluorescenceValues[i];
      fi_time = timeStamps[i];
      fi_found = true;
    }
  }

  float fm_volts = (fm * refVoltage) / 4096;
  float fv = fm_volts - fo;
  float fvfm = fv / fm;

  Serial.println();
  Serial.print("Fo: \t");
  Serial.println(fo, 4);
  Serial.print("Fj: \t");
  Serial.print(fj, 4);
  Serial.println(" V @ " + String(fj_time) + " ms");
  Serial.print("Fi: \t");
  Serial.print(fi, 4);
  Serial.println(" V @ " + String(fi_time) + " ms");
  Serial.print("Fm: \t");
  Serial.print(fm_volts, 4);
  Serial.println(" V @ " + String(fm_time) + " ms");
  Serial.print("Fv: \t");
  Serial.print(fv, 4);
  Serial.println(" V");
  Serial.print("Quantum yield (Fv/Fm): \t");
  Serial.print(fvfm, 2);
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

void calibrate_fo(){
  /* Calibrate the fo value of the fluorometer, can be used to ensure the concentration of algae
  is not too high
  */ 
  set_reference_voltage(refVoltage); 
  float foread = 0.0f;
  for (int k = 0; k < 5; k++){
    digitalWrite(actinicPin, HIGH);
    delayMicroseconds(20);
    for (int i = 0; i <= 2; i++){
      foread = analogRead(readPin);
      Serial.println((foread/4096) * refVoltage);
    }
    digitalWrite(actinicPin, LOW);
    Serial.print("Final Fo = ");
    Serial.println((foread/4096) * refVoltage);
    delay(2000);
    }
}

void calibrate_rise(){
  // Calibrate the rise time of the flurometer (useful for debugging)
  for (int i = 0; i < 200; i++){
    digitalWrite(actinicPin, HIGH);
    delayMicroseconds(100);
    digitalWrite(actinicPin, LOW);
    delay(200);
  }
}

void measure_light(){
  // Measure light using external 4pi light meter
  digitalWrite(actinicPin, HIGH);
  delay(3000);
  digitalWrite(actinicPin, LOW);
  delay(20);
}

void loop(){
  if(Serial.available()){   
    command = Serial.readStringUntil('\n');
    if(command.equals("MeasureFluorescence") || command.equals("MF")){
      measure_fluorescence();
    }
    else if(command.equals("CP")){
      calculate_parameters();
    }
    else if(command.equals("CFo")){
      calibrate_fo();
    }
    else if(command.equals("ML")){
      measure_light();
    }
    else if(command.equals("Cr")){
      calibrate_rise();
    }
    else{
      delay(100);
    }
  }
  digitalWrite(13, HIGH);
  delay(1000);
  digitalWrite(13, LOW);
  delay(1000);
}
