// <Open-JIP Teensy 3.6 Script. Controls "Open-JIP" chlorophyll fluorometer>
     // Copyright (C) <2020>  <Harvey Bates>

     // This program is free software: you can redistribute it and/or modify
     // it under the terms of the GNU General Public License as published by
     // the Free Software Foundation, either version 3 of the License, or
     // (at your option) any later version.

     // This program is distributed in the hope that it will be useful,
     // but WITHOUT ANY WARRANTY; without even the implied warranty of
     // MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
     // GNU General Public License for more details.

     // You should have received a copy of the GNU General Public License
     // along with this program.  If not, see <https://www.gnu.org/licenses/>
    
     // For more information contact: harvey.bates@student.uts.edu.au

// Analog Pins
#define readPin 18

// Digital Pins
#define actinicPin 21

// Setup arrays that hold fluorescence data
int baseRead[5];
int microRead [1000];
int milliRead[1000];

// Setup arrays that hold timestamps that correspond to fluorescence values
float h[5];
float t[1000]; 
float p[1000];
String command;

int fluorescenceValues[2000];
double timeStamps[2000];

// Initialse some variables
int microMax = 0, milliMax = 0;

void setup() {
  Serial.begin(115200);
  analogReadResolution(12);
  set_reference_voltage(3.3); // Only applicable with a Teensy 3.6 (disable if using other microcontroller)
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
  set_reference_voltage(3.3); 
  
  digitalWrite(actinicPin, HIGH); // Turn on actinic LED

  long timer = micros(); // Start timer 

  // Read microsecond fluorescence values and corresponding timestamps
  for (unsigned int i = 0; i < sizeof(microRead) / sizeof(int); i++) 
  {
    microRead[i] = analogRead(readPin);
    t[i] = micros() - timer;
  }

  // Read millisecond fluorescence values and corresponding timestamps
  for (unsigned int i = 0; i < sizeof(milliRead) / sizeof(int); i++) 
  {
    milliRead[i] = analogRead(readPin);
    p[i] = micros() - timer;
    delay(1);
  }
  
  digitalWrite(actinicPin, LOW); // Turn off actinic LED
  delay(10);

  // Convert micros() to milliseconds for microsecond values
  for (unsigned int i = 0; i < sizeof(microRead) / sizeof(int); i++)
  {
   float milliReal = t[i]/1000;
   fluorescenceValues[i] = microRead[i];
   timeStamps[i] = milliReal;
   Serial.print(milliReal, 3); 
   Serial.print("\t");
   Serial.println(microRead[i]);
   delay(1);
  }

  // Convert micros() to milliseconds for millsecond values
  for (unsigned int i = 0; i < sizeof(milliRead) / sizeof(int); i++) 
  {
   float milliReal = p[i]/1000;
   fluorescenceValues[i + 1000] = milliRead[i];
   timeStamps[i] = milliReal;
   Serial.print(milliReal, 3); 
   Serial.print("\t");
   Serial.println(milliRead[i]);
   delay(1);
  }
}

void calculate_parameters(){
  float fo = fluorescenceValues[4]; // Gets the minimum level fluorescence (Fo)
  int fj = 0, fi = 0;
  bool fj_found = false, fi_found = false;
  int fm = 0, fm_time = 0;
  for(unsigned int i = 0; i < sizeof(timeStamps) / sizeof(int); i++){
    // Search for timestamp corresponding to 2 ms
    if(!fj_found && int(t[i] == 2)){
      fj = fluorescenceValues[i];
      fj_found = true;
    }
    else if(!fi_found && int(p[i] == 30)){
      fi = fluorescenceValues[i];
      fi_found = true;
    }
    else if(fluorescenceValues[i] > fm){
      fm = fluorescenceValues[i];
      fm_time = timeStamps[i];
    }
  }

  float fv = fm - fo;
  float fvfm = fv/fm;

  Serial.print("Fo: \t");
  Serial.println(fo);
  Serial.print("Fj: \t");
  Serial.println(fj);
  Serial.print("Fi: \t");
  Serial.println(fi);
  Serial.print("Fm: \t");
  Serial.println(fm);
  Serial.print("Fv: \t");
  Serial.println(fv);
  Serial.print("Fv/Fm: \t");
  Serial.print(fvfm);
  Serial.println(" @ " + fm_time + " ms");
}

void calibrate_fo(){
  set_reference_voltage(3.3); 
  float foread = 0.0f;
  for (int k = 0; k < 5; k++){
    digitalWrite(actinicPin, HIGH);
    delayMicroseconds(20);
    for (int i = 0; i <= 2; i++){
      foread = analogRead(readPin);
      Serial.println((foread/4096) * 3.3);
    }
    digitalWrite(actinicPin, LOW);
    Serial.print("Final Fo = ");
    Serial.println((foread/4096) * 3.3);
    delay(2000);
    }
}

void calibrate_rise(){
  for (int i = 0; i < 200; i++){
    digitalWrite(actinicPin, HIGH);
    delayMicroseconds(100);
    digitalWrite(actinicPin, LOW);
    delay(200);
  }
}

void measure_light(){
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
