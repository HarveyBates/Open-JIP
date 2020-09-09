// OJIP.h
#pragma once
#ifndef _OJIP_h
#define _OJIP_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#endif
#include <util/delay.h>
#include <vector>

#define actinicPin 21
#define redPin 38
#define greenPin 37
#define bluePin 36

#define ojipPin 33

extern float fo;
extern float f100us;
extern float f300us;
extern float fj;
extern float fi;
extern float fm;
extern float fv;
extern float m0;
extern float vj;
extern float fmqa;
extern float piAbs;

extern std::vector<float> timeStamps;
extern std::vector<float> dataPoints;

class OJIP {
public:
	void measureOJIP(float microReadLength, float milliReadLength, char actinicColor, bool clearVectors);
	void printOJIPData();
	void calculateParameters(std::vector<float> timeStamps, std::vector<float> dataPoints);
};
