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

// Required Imports
#include <SPI.h>
#include <math.h>
#include <Wire.h>
#include <stdlib.h>

// Analog Pins
#define readPin 18

// Digital Pins
#define actinicPin 21

int baseRead[5];
int microRead [1000];
int milliRead[1000];

float h[5];
float t[1000]; 
float p[1000];
String command;

int microMax = 0;
int milliMax = 0;
float foread = 0;

float Fo;
float Fm;
float VarFluoro;
float FvoverFm;

void setup() {
  Serial.begin(115200);
  analogReadResolution(12);
  analogReference(DEFAULT);
  pinMode(actinicPin, OUTPUT);
  digitalWrite(actinicPin, LOW);
}

void measureFluoro() {
  analogReference(DEFAULT);
  delay(10);
  
  analogRead(readPin);
  delay (1000);
  
  digitalWrite(actinicPin, HIGH); 

  long timer = micros();

  for (unsigned int i = 0; i < sizeof(microRead) / sizeof(int); i++) 
  {
    microRead[i] = analogRead(readPin);
    t[i] = micros() - timer;
  }
  
  for (unsigned int o = 0; o < sizeof(milliRead) / sizeof(int); o++) 
  {
    milliRead[o] = analogRead(readPin);
    p[o] = micros() - timer;
    delay(1);
  }
  
  digitalWrite(actinicPin, LOW); 
  delay(10);
  
  int microMax = microRead[1]; 
    for (unsigned int u = 1; u < sizeof(microRead) / sizeof(int); u++){
      if(microRead[u] > microMax){
        microMax = microRead[u];
      }
    }
    
  int milliMax = milliRead[0];
    for (unsigned int i = 0; i < sizeof(milliRead) / sizeof(int); i++){
      if(milliRead[i] > milliMax){
        milliMax = milliRead[i];
      }
    }
  
  for (unsigned int q = 0; q < sizeof(microRead) / sizeof(int); q++)
  {
   float millCounts = t[q];
   float millicountsConverted = millCounts/1000; 
   float milliReal = millicountsConverted;
   Serial.print(milliReal, 3); 
   Serial.print("\t");
   Serial.println(microRead[q]);
   delay(1);
  }
  
  for (unsigned int l = 0; l < sizeof(milliRead) / sizeof(int); l++) 
  {
   float milliTime = p[l];
   float millitimeConverted = milliTime/1000;
   float milliReal = millitimeConverted;
   Serial.print(milliReal, 3); 
   Serial.print("\t");
   Serial.println(milliRead[l]);
   delay(1);
  }

}

void calibrateFo(){
  analogReference(DEFAULT);
  delay(10);
  analogRead(readPin);
  delay(10);
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

void calibrateRise(){
  for (int i = 0; i < 200; i++){
    digitalWrite(actinicPin, HIGH);
    delayMicroseconds(100);
    digitalWrite(actinicPin, LOW);
    delay(200);
  }
}

void measureLight(){
  digitalWrite(actinicPin, HIGH);
  delay(3000);
  digitalWrite(actinicPin, LOW);
  delay(20);
}

void loop(){
  if(Serial.available()){   
    command = Serial.readStringUntil('\n');
    if(command.equals("MeasureFluorescence")){
      measureFluoro();
    }
    else if(command.equals("MF")){
      measureFluoro();
    }
    else if(command.equals("CFo")){
      calibrateFo();
    }
    else if(command.equals("ML")){
      measureLight();
    }
    else if(command.equals("C")){
      calibrateRise();
    }
    else{
      delay(100);
    }
  }
}
