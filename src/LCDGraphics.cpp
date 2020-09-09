
#include "LCDGraphics.h"
#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include "SDRead_Write.h"
#include "SystemInformation.h"
#include <algorithm>
#include <iostream>
#include <vector>
#include <cmath>

SDCard sdCard;

extern const char* sdState;

void LCDGraphics::begin()
{
    tft.begin();
}

unsigned long LCDGraphics::openingScene()
{
    // Opening graphic which displays the devices name and version
    tft.fillScreen(ILI9341_BLACK);
    tft.setTextColor(ILI9341_GREEN);
    tft.setFont(headingFont);
    tft.setCursor((width / 2) - 105, (height / 2) - 30);
    tft.println("Open-JIP");
    
    tft.setTextColor(ILI9341_WHITE);
    tft.setFont(smallFont);
    tft.setCursor((width / 2) + 75, (height / 2) - 25);
    tft.println(versionNumber);

    tft.setTextColor(ILI9341_WHITE);
    tft.setFont(smallFont);
    tft.setCursor((width / 2) - 60, (height / 2) + 10);
    tft.println("An open-source");
    tft.setCursor((width / 2) - 90, (height / 2) + 30);
    tft.println("chlorophyll fluorometer");

    tft.setTextColor(ILI9341_CYAN);
    tft.setFont(smallFont);
    tft.setCursor((width / 2) - 70, (height / 2) + 70);
    tft.println("Bates et al. 2019");

    return(0);
}

unsigned long LCDGraphics::mainScene(const char* measuringDevice, const char* actinicColor, bool sdDetect)
{
    tft.fillScreen(ILI9341_BLACK);

    // Selected measuring device
    if (strcmp(measuringDevice, "Algae") == 0)
    {
        tft.fillRect(5, 0, 80, 30, ILI9341_DARKGREEN);
        tft.drawRect(5, 0, 80, 30, ILI9341_WHITE);
        tft.setFont(smallFont);
        tft.setTextColor(ILI9341_WHITE);
        centeredString(measuringDevice, 45, 20);
    }
    else if (strcmp(measuringDevice, "Plant") == 0)
    {
        tft.fillRect(5, 0, 80, 30, ILI9341_GREEN);
        tft.drawRect(5, 0, 80, 30, ILI9341_WHITE);
        tft.setFont(smallFont);
        tft.setTextColor(ILI9341_BLACK);
        centeredString(measuringDevice, 45, 20);
    }
    else if (strcmp(measuringDevice, "Coral") == 0)
    {
        tft.fillRect(5, 0, 80, 30, ILI9341_GREENYELLOW);
        tft.drawRect(5, 0, 80, 30, ILI9341_WHITE);
        tft.setFont(smallFont);
        tft.setTextColor(ILI9341_BLACK);
        centeredString(measuringDevice, 45, 20);
    }

    // Selected actinic color
    if (strcmp(actinicColor, "Red") == 0)
    {
        tft.fillRect(5, 35, 80, 30, ILI9341_RED);
        tft.drawRect(5, 35, 80, 30, ILI9341_WHITE);
        tft.setFont(smallFont);
        tft.setTextColor(ILI9341_WHITE);
        centeredString(actinicColor, 45, 55);
    }
    else if (strcmp(actinicColor, "Green") == 0)
    {
        tft.fillRect(5, 35, 80, 30, ILI9341_GREEN);
        tft.drawRect(5, 35, 80, 30, ILI9341_WHITE);
        tft.setFont(smallFont);
        tft.setTextColor(ILI9341_BLACK);
        centeredString(actinicColor, 45, 55);
    }
    else if (strcmp(actinicColor, "Blue") == 0)
    {
        tft.fillRect(5, 35, 80, 30, ILI9341_BLUE);
        tft.drawRect(5, 35, 80, 30, ILI9341_WHITE);
        tft.setFont(smallFont);
        tft.setTextColor(ILI9341_WHITE);
        centeredString(actinicColor, 45, 55);
    }

    // Open-JIP title and version
    tft.setFont(smallFont);
    tft.setTextColor(ILI9341_WHITE);
    tft.setCursor(100, 20);
    tft.println("Open-JIP " + String(versionNumber));

    // Sd card state
    tft.fillRect(5, 70, 80, 30, ILI9341_MAGENTA);
    tft.drawRect(5, 70, 80, 30, ILI9341_WHITE);
    tft.setFont(smallFont);
    tft.setTextColor(ILI9341_WHITE);
    centeredString("SD Card:", 45, 90);
    tft.setCursor(90, 90);
    tft.print(*&sdState);

    // Print quantum yeild
    tft.setCursor(100, height - 35);
    tft.setFont(smallFont);
    tft.setTextColor(ILI9341_WHITE);
    tft.print("Fv/Fm = ");
    assessQuantumYield();
    tft.print(fvfm);

    // Create Graph
    tft.drawRect(30, height - 30, 180, -180, ILI9341_WHITE);
    tft.setFont(smallFont);
    tft.setTextColor(ILI9341_WHITE);
    centeredString("Log10(time)", width / 2, height - 10);
    centeredString("V", 10, height - 120);

    return(0);
}

void LCDGraphics::assessQuantumYield()
{
    if (fvfm >= 0.65)
    {
        tft.setTextColor(ILI9341_GREEN);
    }
    else if (0.5 < fvfm && fvfm < 0.65)
    {
        tft.setTextColor(ILI9341_YELLOW);
    }
    else { tft.setTextColor(ILI9341_RED); }
}


void LCDGraphics::centeredString(const char* buf, int x, int y)
{
    int16_t x1, y1;
    uint16_t w, h;
    tft.setTextSize(1);
    tft.getTextBounds(buf, x, y, &x1, &y1, &w, &h);
    tft.setCursor(x - w / 2, y);
    tft.print(buf);
}

unsigned long LCDGraphics::plotOJIP(std::vector<float> timeStamps, std::vector<float> dataPoints)
{
    // Normalsie data between the graphs limits
    // Width = 180, Height = -180
    std::vector<float> xData, yData;
    float maxDataPoint = *std::max_element(dataPoints.begin() + 3, dataPoints.end()); //Get max datapoint (Fm)
    float minDataPoint = *std::min_element(dataPoints.begin() + 3, dataPoints.end()); //Get min datapoint (Fo)

    //Plot OJIP data within the confines of the rectangular plotting area
    for (unsigned int i = 0; i < timeStamps.size(); i++)
    {
        // Append normalised xdata with log10 converson
        xData.push_back((180) * ((log10(timeStamps[i]) - log10(timeStamps[3])) / (log10(timeStamps[timeStamps.size()-1]) - log10(timeStamps[3]))) + 30);
        // Append normalised ydata
        yData.push_back((180) * ((dataPoints[i] - minDataPoint) / (maxDataPoint - minDataPoint)) + 110);
    }
    
    // Plots data from Fo
    for (unsigned int i = 3; i < xData.size(); i++)
    {
        tft.fillCircle(xData[i], yData[i], 2, ILI9341_CYAN); // Plot datapoints as a series of circles
        delay(1);
    }


    return(0);
}


unsigned long LCDGraphics::testText()
{
    int w = tft.width(), h = tft.height();
    tft.fillScreen(ILI9341_BLACK);
    unsigned long start = micros();
    tft.setCursor(35, 40);
    tft.setTextColor(ILI9341_WHITE);
    tft.setTextSize(3);
    tft.print(w);
    tft.print("x");
    tft.println(h);

    tft.drawRect(20, 100, 200, 180, ILI9341_WHITE);

    // Create X Labels
    int x_label_pos = 20;
    for (int i = 0; i < 10; i++)
    {
        tft.setCursor(x_label_pos, h - 35);
        tft.setTextColor(ILI9341_WHITE);
        tft.setTextSize(1);
        tft.println(i);
        x_label_pos += 20;
    }

    // Create Y Labels
    int y_label_pos = h - 40;
    for (int i = 0; i < 10; i++)
    {
        tft.setCursor(10, y_label_pos);
        tft.setTextColor(ILI9341_WHITE);
        tft.setTextSize(1);
        tft.println(i);
        y_label_pos -= 20;
    }

    // Create data
    for (int i = 1; i < 200; i++)
    {
        int prev_xPoint = 20 + i - 1;
        int prev_yPoint = 180 - (amplitude * sin(prev_xPoint / frequency));
        int curr_xPoint = 20 + i;
        int curr_yPoint = 180 - (amplitude * sin(curr_xPoint / frequency));
        tft.drawLine(prev_xPoint, prev_yPoint, curr_xPoint, curr_yPoint, ILI9341_GREEN);
    }

    return micros() - start;
}
