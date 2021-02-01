#ifndef Actnic_H
#define Actnic_H

#pragma once
#include <Arduino.h>

/* Actinic intensity set pins */
/* These pins are backwards compatible between 3.6 and 4.1 */
#define actinicGain1 29
#define actinicGain2 37
#define actinicGain3 36
#define actinicGain4 10


class Actinic{
  unsigned int intensity = 1;
public:
  Actinic();
  void off();
  void define(int mag);
  void on();
};
#endif
