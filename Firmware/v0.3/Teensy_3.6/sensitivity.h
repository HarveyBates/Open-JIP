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
