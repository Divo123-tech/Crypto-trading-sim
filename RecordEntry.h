// ALL WITHOUT ASSISTANCE OTHER THAN THE GIVEN MERKLEREX CODE TO FRAMEWORK OFF OF
#pragma once

#include <string>

class RecordEntry{
    public:
        RecordEntry(std::string _time,
                    std::string _product,
                    double _volume,
                    double _marketCap);
        std::string time;
        std::string product;
        double volume;
        double marketCap;
};
// ALL WITHOUT ASSISTANCE OTHER THAN THE GIVEN MERKLEREX CODE TO FRAMEWORK OFF OF