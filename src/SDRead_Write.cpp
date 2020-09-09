
#include "SDRead_Write.h"
#include "LCDGraphics.h"
#include <SD.h>

extern const char* sdState;

void SDCard::printDirectory(File dir, int numTabs)
{
    Serial.println("SD File Contents:");
    while (true)
    {
        File entry = dir.openNextFile();
        if (!entry)
        {
            break; // Breaks if no more files are found
        }
        for (uint8_t i = 0; i < numTabs; i++)
        {
            Serial.print('\t');
        }
        Serial.print(entry.name());
        if (entry.isDirectory())
        {
            Serial.println("/");
            printDirectory(entry, numTabs + 1);
        }
        else
        {
            Serial.print("\t\t");
            Serial.println(entry.size(), DEC);
        }
        entry.close();
    }
}

void SDCard::createTextFile(const char* fileName)
{
    // If a file does not exist it creates it and the closes it
    if (!SD.exists(fileName))
    {
        root = SD.open(fileName, FILE_WRITE);
        root.close();
        Serial.print("Created: ");
        Serial.println(fileName);
        *&sdState = "File created";
    }
    else
    {
        Serial.println("File already exists");
        *&sdState = "File exists";
    }
}

void SDCard::writeOJIPToFile(const char* fileName)
{
    // Append recent raw OJIP data to file
    root = SD.open(fileName, FILE_WRITE);
    if (root)
    {
        Serial.println("Writing to: " + String(fileName));
        for (int i = 0; i < 10; i++)
        {
            root.println(String(i));
        }
        Serial.println("Written to " + String(fileName));
        root.close();
    }
    else
    {
        Serial.println("Could not write to SD card");
    }
}

void SDCard::writeParametersToFile(const char* fileName)
{
    // Append recent parameter measurment to file
    root = SD.open(fileName, FILE_WRITE);
    if (root)
    {
        Serial.println("Writing to: " + String(fileName));
        for (int i = 0; i < 10; i++)
        {
            root.println(String(i));
        }
        Serial.println("Written to " + String(fileName));
        root.close();
    }
    else
    {
        Serial.println("Could not write to SD card");
    }
}

void SDCard::printFileContents(const char* fileName)
{
    root = SD.open(fileName, FILE_READ);
    if (root)
    {
        Serial.println(String(fileName) + ": ");
        while (root.available())
        {
            String buffer = root.readStringUntil('\n');
            Serial.println(buffer);
        }
        root.close();
    }
    else
    {
        Serial.println("Error Reading File");
    }
}



