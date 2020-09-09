// LCDGraphics.h
#pragma once
#include <SPI.h>
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include "Fonts/FreeSans24pt7b.h"
#include "Fonts/FreeSans18pt7b.h"
#include "Fonts/FreeSans12pt7b.h"
#include "Fonts/FreeSans9pt7b.h"
#include <vector>

#ifndef _LCDGRAPHICS_h
#define _LCDGRAPHICS_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#endif

#define TFT_DC 9
#define TFT_CS 10


class LCDGraphics {
public:
	Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
	int amplitude = 40;
	int frequency = 4;

	int width = 240;
	int height = 320;

	float fvfm = 0.00;

	const GFXfont* headingFont = &FreeSans24pt7b;
	const GFXfont* minorHeadingFont = &FreeSans18pt7b;
	const GFXfont* mediumFont = &FreeSans12pt7b;
	const GFXfont* smallFont = &FreeSans9pt7b;

	void begin();
	unsigned long openingScene();
	unsigned long mainScene(const char* measuringDevice, const char* actinicColor, bool sdDetect);
	void assessQuantumYield();
	void centeredString(const char* buf, int x, int y);
	unsigned long plotOJIP(std::vector<float> timeStamps, std::vector<float> dataPoints);
	unsigned long testText();
};


