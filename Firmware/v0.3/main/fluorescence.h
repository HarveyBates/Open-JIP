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

#ifndef Fluorescence_H
#define Fluorescence_H

#include <Arduino.h>
#include "actinic.h"
#include "sensitivity.h"

#define readPin 14 // Fluorescence read pin

class Fluorescence{
  /*  Length specifies the number of data points captured at two different 
   *  acquisition frequencies. 
   *  Microsecond (micro) = readings every 8 us
   *  Millisecond (milli) = readings every 1 ms
  */
  static const unsigned int microLength = 1000; // Set number of microsecond datapoints (default 1000)
  int microRead [microLength];
  int milliRead[microLength];
  
  static const unsigned int milliLength = 1000; // Set number of millisecond datapoints (default 1000)
  int microTime[milliLength]; 
  int milliTime[milliLength];
  
  /* These arrays represent the final array size of OJIP fluorescence acquisitions.
   *  They hold the full OJIP acquisition (time stamps and values) in volts
   *  and milliseconds.
   */
  float fluorescenceValues[microLength + milliLength];
  float timeStamps[microLength + milliLength];
  
  /* Setup arrays for a single J-Step acquisitions.
   *  These are used to capture a single 2 ms rise from Fo to Fj.
   *  The same rules as noted above for the array size apply.
   *  E.g. Keep the array size of each component the same.
   *  
   *  Default: 250 acquisitions (2 ms) at 8 us per measurment
   */
  static const unsigned int micorReadJLength = 250;
  int microReadJ[micorReadJLength];
  int microTimeJ[micorReadJLength];
  float jValues[micorReadJLength];
  float jTime[micorReadJLength];
  
  /* Setup for the wave feature of J-step acquisitions (Multiple O-J rises). 
   * Large arrays are used to store consecutive O-J rises with (waveInterval) ms between  
   * measurments. 
   * 
   * Where waveAqu is the number of microsecond acquisitions used to resolve the
   * J-step and the number of waves represent your desired number of consecutive
   * O-J rises.
   */
  unsigned int numWaves = 10; // Number of consecutive acquisitions
  unsigned int waveInterval = 5; // Time between each O-J rise
  static const unsigned int waveLength = 2550; // Array size of wave acquisitions
  int waveRead[waveLength];
  int waveTime[waveLength];
  unsigned int waveAqu = 400; // Number of acquisitions in each O-J rise

  int fm = 0; // Initalise the fm value so we can calcualte it later
  int foPos = 4; // Location of Fo in the measured array
  
  float refVoltage = 3.3; // Set the reference voltage (only applicable with Teensy 3.6)
  unsigned int readResolution = 12; // Analog read resolution (default = 12-bit)

public:
  Fluorescence();
  void set_resolution(unsigned int resolution);
  float get_bit_resoltuion();
  void set_reference_voltage(float voltage);
  void measure_j_step(Actinic actinic);
  void calculate_parameters();
  void wave(Actinic actinic);
  void measure_fluorescence(unsigned int actinicPin);

  // Debugging commands
  void calibrate_fo(Actinic actinic);
  void calibrate_rise(Actinic actinic);
  void measure_light(Actinic actinic);
};

#endif
