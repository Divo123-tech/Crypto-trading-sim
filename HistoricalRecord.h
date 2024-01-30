// ALL WITHOUT ASSISTANCE OTHER THAN THE GIVEN MERKLEREX CODE TO FRAMEWORK OFF OF
#pragma once
#include "RecordEntry.h"
#include "CSVReader.h"
#include <vector>

class HistoricalRecord
{
public:
    HistoricalRecord(std::string filename);
    std::vector<RecordEntry> records;
    std::vector<RecordEntry> getRecords(std::string product, std::string time);
    void drawHistory(std::string product, std::string time, std::string metric);

private:
    double max;
    double min;
    double range;
    void drawXaxis(std::vector<RecordEntry> product_records);
};