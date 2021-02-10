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

#include "actinic.h"

Actinic::Actinic(){
  pinMode(actinicGain1, OUTPUT);
  pinMode(actinicGain2, OUTPUT);
  pinMode(actinicGain3, OUTPUT);
  pinMode(actinicGain4, OUTPUT);
  off();
}

void Actinic::off(){
  digitalWrite(actinicGain1, LOW);
  digitalWrite(actinicGain2, LOW);
  digitalWrite(actinicGain3, LOW);
  digitalWrite(actinicGain4, LOW);
}

void Actinic::define(unsigned int mag){
  intensity = mag;
}

void Actinic::on(){
  switch(intensity){
    case 1:
      digitalWrite(actinicGain1, HIGH);
      break;
    case 2:
      digitalWrite(actinicGain2, HIGH);
      break;
    case 3:
      digitalWrite(actinicGain3, HIGH);
      break;
    case 4:
      digitalWrite(actinicGain4, HIGH);
      break;
  }
}
