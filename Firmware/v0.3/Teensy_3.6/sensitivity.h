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

#ifndef Sensitivity_H
#define Sensitivity_H

#pragma once
#include <Arduino.h>

/* Fluorescence intensity gain set pins */
/* These pins are backwards compatible between 3.6 and 4.1 */
#define fluoroGain1 23
#define fluoroGain2 6
#define fluoroGain3 7
#define fluoroGain4 22

class Sensitivity {
public:
  Sensitivity();
  void refresh();
  void define(int _gain);
};
#endif
