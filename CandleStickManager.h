// ALL WITHOUT ASSISTANCE OTHER THAN THE GIVEN MERKLEREX CODE TO FRAMEWORK OFF OF
#pragma once
#include <vector>
#include "CandleStick.h"

class CandleStickManager
{
public:
    CandleStickManager(std::vector<CandleStick> sticks);
    void drawCandleSticks();

private:
    std::vector<CandleStick> candlesticks;
    void setStats();
    double maxHigh;
    double minLow;
    double range;
};
// ALL WITHOUT ASSISTANCE OTHER THAN THE GIVEN MERKLEREX CODE TO FRAMEWORK OFF OF