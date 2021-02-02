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
#include "actinic.h"
#include "fluorescence.h"

Fluorescence fluorescence;
Sensitivity sensitivity;
Actinic actinic;

void setup() {
  Serial.begin(115200); // Initalise serial communications at specific baud rate
  analogReadResolution(12); // Set the resolution of the microcontroller in bits
  pinMode(13, OUTPUT); // Sets the microcontrollers LED pin as an output
  
  sensitivity.refresh(); // Switch off all gain pathways
  sensitivity.define(1); // Set the detection senstivity: 1 (lowest) - 4 (highest)

  actinic.off(); // Switch off all actinic pathways
  actinic.define(1); // Define desired actinic intensity: 1 (lowest) - 4 (highest)
}

void loop(){
  if(Serial.available()){   
    char cmd = Serial.read();
    
    switch(cmd){
      case 'M':
        fluorescence.measure_fluorescence(actinic);
        break;
      case 'P':
        fluorescence.calculate_parameters();
        break;
      case 'L':
        fluorescence.measure_light(actinic);
        break;
      case 'O':
        fluorescence.calibrate_fo(actinic);
        break;
      case 'R':
        fluorescence.calibrate_rise(actinic);
        break;
    }
  }
}
