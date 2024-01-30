#pragma once

#include "OrderBookEntry.h"
#include "RecordEntry.h"
#include <vector>
#include <string>

class CSVReader
{
public:
    CSVReader();

    static std::vector<OrderBookEntry> readCSV(std::string csvFile);
    static std::vector<std::string> tokenise(std::string csvLine, char separator);

    static OrderBookEntry stringsToOBE(std::string price,
                                       std::string amount,
                                       std::string timestamp,
                                       std::string product,
                                       OrderBookType OrderBookType);
    // ALL WITHOUT ASSISTANCE OTHER THAN THE GIVEN MERKLEREX CODE TO FRAMEWORK OFF OF
    static std::vector<RecordEntry> readHistory(std::string csvFile);
    static RecordEntry stringToRE(std::vector<std::string> strings);
    // ALL WITHOUT ASSISTANCE OTHER THAN THE GIVEN MERKLEREX CODE TO FRAMEWORK OFF OF
private:
    static OrderBookEntry stringsToOBE(std::vector<std::string> strings);
};