
#include "OJIP.h"
#include <vector>


void OJIP::measureOJIP(float microReadLength, float milliReadLength, char actinicColor, bool clearVectors)
{
	//Clears the data from a previous OJIP measurment
	if (clearVectors)
	{
		timeStamps.clear();
		dataPoints.clear();
	}

	// Turns on actinic LED with a specifed color
	//switch (actinicColor)
	//{
	//case 'R':
	//	digitalWriteFast(redPin, HIGH);
	//	break;
	//case 'G':
	//	digitalWriteFast(greenPin, HIGH);
	//	break;
	//case 'B':
	//	digitalWriteFast(bluePin, HIGH);
	//	break;
	//}

	digitalWrite(actinicPin, HIGH);

	unsigned long timer = micros(); // Starts timer

	// Microsecond reads until the defined time (microReadLength) is up
	for (unsigned int i = 0; (micros() / 1000.0 - timer / 1000.0) < microReadLength; i++)
	{
		dataPoints.push_back(analogRead(ojipPin));
		timeStamps.push_back(micros() - timer);
	}

	// Millisecond reads until the defined time (milliReadLength) is up
	for (unsigned int i = 0; (micros() / 1000.0 - timer / 1000.0) < milliReadLength; i++)
	{
		dataPoints.push_back(analogRead(ojipPin));
		timeStamps.push_back(micros() - timer);
		delay(1);
	}

	digitalWrite(actinicPin, LOW);
	digitalWrite(redPin, LOW);
	digitalWrite(greenPin, LOW);
	digitalWrite(bluePin, LOW);

	// Convert data into usable values
	for (unsigned int i = 0; i < timeStamps.size(); i++)
	{
		dataPoints[i] = (dataPoints[i] * 3.33) / 4096; // Convert bits to volts
		timeStamps[i] = timeStamps[i] / 1000; // Convert micros to milliseconds
 	}
}

void OJIP::printOJIPData()
{
	// Converts timestamps to milliseconds and prints out data to the serial output
	for (unsigned int i = 0; i < timeStamps.size(); i++)
	{
		Serial.print(timeStamps[i], 3);
		Serial.print("\t");
		Serial.println(dataPoints[i], 3);
	}
}

void OJIP::calculateParameters(std::vector<float> timeStamps, std::vector<float> dataPoints)
{
	for (unsigned int i = 0; i < timeStamps.size(); i++)
	{
		if (timeStamps[i] == 0.04)
		{
			fo = dataPoints[i];
			Serial.println(fo);
		}
		else if (timeStamps[i] == 0.1)
		{
			f100us = dataPoints[i];
			Serial.println(f100us);
		}
	}
}