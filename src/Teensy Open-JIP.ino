/*
 Name:		Teensy_Open_JIP.ino
 Created:	9/2/2020 8:40:48 PM
 Author:	Harvey Bates
*/

#include "SPI.h"
#include <SD.h>
#include "SDRead_Write.h"
#include "LCDGraphics.h"
#include "SystemInformation.h"
#include "OJIP.h"

const int chipSelect = BUILTIN_SDCARD;

const char* sdState;

std::vector<float> timeStamps;
std::vector<float> dataPoints;

float fo;
float f100us;
float f300us;
float fj;
float fi;
float fm;
float fv;
float m0;
float vj;
float fmqa;
float piAbs;

File files;
SDCard sd;
LCDGraphics lcd;
OJIP ojip;

void setup()
{
    Serial.begin(115200);
    pinMode(actinicPin, OUTPUT);
    digitalWrite(actinicPin, LOW);

    while (!Serial);
    if (!SD.begin(chipSelect))
    {
        Serial.println("SD Card: Not Found");
        *&sdState = "Not Found";
        while (true);
    }
    else
    {
        Serial.println("SD Card: Initialised");
        *&sdState = "Initialied";
        sd.sdDetect = true; // Used to see if the SD card is present
    }
    lcd.begin();
    ojip.measureOJIP(2.0, 998.0, 'G', true);
    //files = SD.open("/");
    //sd.printDirectory(files, 0);
    //sd.createTextFile("example.txt");

}

void loop(void)
{
    lcd.mainScene("Plant", "Blue", sdState);
    lcd.plotOJIP(timeStamps, dataPoints);
    ojip.calculateParameters(timeStamps, dataPoints);
    delay(1000);
}
