// ALL WITHOUT ASSISTANCE OTHER THAN THE GIVEN MERKLEREX CODE TO FRAMEWORK OFF OF
#include <iomanip>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <cmath>
#include "CandleStickManager.h"

CandleStickManager::CandleStickManager(std::vector<CandleStick> sticks)
{
    //initialize both values as 0
    minLow = 0;
    maxHigh = 0;
    //initialize values by the vector passed to constructor
    candlesticks = sticks;
};

void CandleStickManager::setStats()
{
    // set the maxHigh minLow and range for the draw function to use
    for (CandleStick stick : candlesticks)
    {
        if (stick.high > maxHigh)
        {
            maxHigh = stick.high;
        }
        if (minLow != 0)
        {
            if (stick.low < minLow)
            {
                minLow = stick.low;
            }
        }
        else
        {
            minLow = stick.low;
        }
    }
    range = maxHigh - minLow;
}

void CandleStickManager::drawCandleSticks()
{
    std::cout << "------CANDLESTICK INFORMATION------" << std::endl;
    for (CandleStick stick : candlesticks)
    {
        stick.computeInfo();
    }
    setStats();
    std::cout << "------CANDLESTICK GRAPH------" << std::endl;
    std::cout << std::endl;
    //iterates between -2 and 14 so that the top and bottom of the graph has space between the highest and lowest values
    for (int i = -2; i < 14; i++)
    {
        //initializes the interval variable which is the range divided by 12
        double interval = range / 12;
        //initializes the y label variable which is the current label
        double yLabel = maxHigh - (i * interval);
        if (i % 5 == 3 || i == -2)
        {
            if (yLabel > 0)
            {
                std::cout << std::fixed << std::setprecision(7) << yLabel << " | ";
            }
            else
            {
                std::cout << "0.0000000"
                          << " | ";
            }
        }
        else
        {
            // evenly spaces all the y axis since different values
            // behave differently to set precision
            if (maxHigh > 9000)
            {
                std::cout << "            "
                          << " | ";
            }
            else if (maxHigh < 1)
            {
                std::cout << "         "
                          << " | ";
            }
            else
            {
                std::cout << "           "
                          << " | ";
            }
        }

        for (CandleStick stick : candlesticks)
        {
            // if statements are different if close or open is greater
            if (stick.close > stick.open)
            {
                // if its close enough draw the close
                if (std::abs(stick.close - yLabel) < interval / 2)
                {
                    std::cout << "c -    ";
                }
                // if its between close and open draw the stick body
                else if (stick.open != 0 && stick.close > yLabel && stick.open < yLabel)
                {
                    std::cout << " | |   ";
                }
                // else just draw the open
                else if (std::abs(stick.open - yLabel) < interval && yLabel > 0 && stick.open != 0)
                {
                    std::cout << "o -    ";
                }
                // else draw a line indicating the high to the close
                else if (stick.high >= yLabel && stick.low <= yLabel)
                {
                    std::cout << "  |    ";
                }
                // and if none of the values matches, just skip by drawing a space
                else
                {
                    std::cout << "       ";
                }
            }
            else
            {
                // if open is higher, check the open as the highest value
                if (std::abs(stick.open - yLabel) < interval / 2)
                {
                    std::cout << "o -    ";
                }
                // if its between the higher open and the lower close then draw the stick body
                else if (stick.open > yLabel && stick.close < yLabel)
                {
                    std::cout << " | |   ";
                }
                // else draw the close
                else if (std::abs(stick.close - yLabel) < interval)
                {
                    std::cout << "c -    ";
                }

                // if its between the high or low then draw the stick body
                else if (stick.high >= yLabel && stick.low <= yLabel)
                {
                    std::cout << "  |    ";
                }
                // else just skip and draw a blank space
                else
                {
                    std::cout << "       ";
                }
            }
        }
        std::cout << std::endl;
    };
};
// ALL WITHOUT ASSISTANCE OTHER THAN THE GIVEN MERKLEREX CODE TO FRAMEWORK OFF OF