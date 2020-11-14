// SDRead_Write.h
#pragma once
#include <SD.h>

#ifndef _SDREAD_WRITE_h
#define _SDREAD_WRITE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#endif

class SDCard {
public:
	Sd2Card card;
	SdVolume volume;
	File root;

	bool sdDetect = false;

	void printDirectory(File dir, int numTabs);
	void createTextFile(const char* fileName);
	void writeOJIPToFile(const char* fileName);
	void writeParametersToFile(const char* fileName);
	void printFileContents(const char* fileName);
	
};
