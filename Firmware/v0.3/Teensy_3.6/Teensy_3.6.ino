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
  pinMode(13, OUTPUT); // Sets the microcontrollers LED pin as an output
  
  sensitivity.refresh(); // Switch off all gain pathways
  sensitivity.define(4); // Set the detection senstivity: 1 (lowest) - 4 (highest)

  actinic.off(); // Switch off all actinic pathways
  actinic.define(4); // Define desired actinic intensity: 1 (lowest) - 4 (highest)
}

void loop(){
  if(Serial.available()){
    String command = Serial.readStringUntil('\n');
    if(command.equals("MF")){
      fluorescence.measure_fluorescence(actinic.intensity_pin);
    }
    else if(command.startsWith("A")){
      unsigned int intensity = command.substring(1, command.length()).toInt();
      actinic.define(intensity);
    }
    else if(command.startsWith("F")){
      unsigned int detection = command.substring(1, command.length()).toInt();
      sensitivity.define(detection);
    }
    else if(command.equals("CP")){
      fluorescence.calculate_parameters();
    }
    else if(command.startsWith("R")){
      unsigned int resolution = command.substring(1, command.length()).toInt();
      fluorescence.set_resolution(resolution);
    }
    else if(command.equals("CFo")){
      fluorescence.calibrate_fo(actinic);
    }
    else if(command.equals("MJ")){
      fluorescence.measure_j_step(actinic);
    }
    else if(command.equals("ML")){
      fluorescence.measure_light(actinic);
    }
    else if(command.equals("MW")){
      fluorescence.wave(actinic);
    }
    else if(command.equals("Cr")){
      fluorescence.calibrate_rise(actinic);
    }
  }
  delay(10);
}
