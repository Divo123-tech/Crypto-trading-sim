// ALL WITHOUT ASSISTANCE OTHER THAN THE GIVEN MERKLEREX CODE TO FRAMEWORK OFF OF
#pragma once
#include <vector>
#include <string>
#include "OrderBookEntry.h"

class CandleStick{
    public:
        CandleStick(std::string _time,  double _open, double _high,  double _low, double _close);
        std::string time;
        double high;
        double open;
        double close;
        double low;
        void computeInfo();

};
// ALL WITHOUT ASSISTANCE OTHER THAN THE GIVEN MERKLEREX CODE TO FRAMEWORK OFF OF