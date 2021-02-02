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

#pragma once
#include <Arduino.h>
#include "actinic.h"
#include "sensitivity.h"

/* Fluorescence analogread pin */
#define readPin 14

class Fluorescence{

  /* Setup for OJIP analysis 
   *  Length specifies the number of data points captured at two different 
   *  acquisition frequencies. 
   *  Microsecond (micro) = readings every 8 us
   *  Millisecond (milli) = readings every 1 ms
   *  
   *  Each value is stored with its corresponding timestamp. Thus, the length
   *  of each array must match their corresponding number of acquisitions. 
   *  E.g. microLength of 1000 means 1000 data points will be captured at 8 us 
   *  intervals, this must match the array size of microRead and microTime.
  */
  int microLength = 1000;
  int microRead [1000];
  int milliRead[1000];
  
  int milliLength = 1000;
  float microTime[1000]; 
  float milliTime[1000];
  
  /* These arrays represent the final array size of OJIP fluorescence acquisitions.
   *  Thus they are calculated as:
   *  array size = microLength + milliLength
   *  
   *  They hold the full OJIP acquisition (time stamps and values) in volts
   *  and milliseconds.
   */
  float fluorescenceValues[2000];
  float timeStamps[2000];
  
  /* Setup arrays for a single J-Step acquisitions.
   *  These are used to capture a single 2 ms rise from Fo to Fj.
   *  The same rules as noted above for the array size apply.
   *  E.g. Keep the array size of each component the same.
   *  
   *  Default: 250 acquisitions (2 ms) at 8 us per measurment
   */
  unsigned int micorReadJLength = 250;
  int microReadJ[250];
  int microTimeJ[250];
  float jValues[250];
  float jTime[250];
  
  /* Setup for the wave feature of J-step acquisitions (Multiple O-J rises). 
   * Large arrays are used to store consecutive O-J rises with (waveInterval) ms between  
   * measurments. 
   * 
   * Array sizes are calculated as follows:
   * array size = numWaves * waveAqu
   * 
   * Where waveAqu is the number of microsecond acquisitions used to resolve the
   * J-step and the number of waves represent your desired number of consecutive
   * O-J rises.
   */
  unsigned int numWaves = 100; // Number of consecutive acquisitions
  unsigned int waveInterval = 5; // Time between each O-J rise
  unsigned int waveLength = 25000; // Array size of wave acquisitions
  unsigned int waveAqu = 250; // Number of acquisitions in each O-J rise
  int waveRead[25000];
  int waveTime[25000];
  
  int fm = 0; // Initalise the fm value so we can calcualte it later
  int fo_pos = 4; // Location of Fo in the measured array
  
  float refVoltage = 3.3; // Set the reference voltage (only applicable with Teensy 3.6)

public:
  Fluorescence();
  void set_reference_voltage(float voltage);
  void measure_j_step(Actinic actinic);
  void calculate_parameters();
  void wave(Actinic actinic);
  void measure_fluorescence(Actinic actinic);

  // Debugging commands
  void calibrate_fo(Actinic actinic);
  void calibrate_rise(Actinic actinic);
  void measure_light(Actinic actinic);
};

#endif
