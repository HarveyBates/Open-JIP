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

#include "sensitivity.h"

Sensitivity::Sensitivity(){
  pinMode(fluoroGain1, OUTPUT);
  pinMode(fluoroGain2, OUTPUT);
  pinMode(fluoroGain3, OUTPUT);
  pinMode(fluoroGain4, OUTPUT);
}

void Sensitivity::refresh(){
  digitalWrite(fluoroGain1, LOW);
  digitalWrite(fluoroGain2, LOW);
  digitalWrite(fluoroGain3, LOW);
  digitalWrite(fluoroGain4, LOW);
}

void Sensitivity::define(int _gain){
  refresh();
  switch(_gain){
    case 1:
      digitalWrite(fluoroGain1, HIGH);
      break;
    case 2:
      digitalWrite(fluoroGain2, HIGH);
      break;
    case 3:
      digitalWrite(fluoroGain3, HIGH);
      break;
    case 4:
      digitalWrite(fluoroGain4, HIGH);
      break;
  }
}
