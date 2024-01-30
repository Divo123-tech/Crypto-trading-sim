// ALL WITHOUT ASSISTANCE OTHER THAN THE GIVEN MERKLEREX CODE TO FRAMEWORK OFF OF
#include "HistoricalRecord.h"
#include "CSVReader.h"
#include <vector>
#include <iostream>
#include <iomanip>
#include <cstring>
#include <cstdlib>

HistoricalRecord::HistoricalRecord(std::string filename)
{
    //initialize both values as 0
    min = 0;
    max = 0;
    //initialize values by the vector passed to constructor
    records = CSVReader::readHistory(filename);

};

//gets specific records based on the product and time passed to the function
std::vector<RecordEntry> HistoricalRecord::getRecords(std::string product, std::string time)
{
    std::vector<RecordEntry> cryptoRecords;
    int num = 0;
    for (RecordEntry &rec : records)
    {
        if (rec.product == product && rec.time.find(time) != std::string::npos)
        {
            cryptoRecords.push_back(rec);
        }
    }
    //returns a vector of a specific product's record and a specific time
    return cryptoRecords;
}
void HistoricalRecord::drawXaxis(std::vector<RecordEntry> product_records)
{
    // goes through the row two times, one for the line and the other for the label
    for (int i = 0; i < 2; i++)
    {
        // gives the 10 spaces for both the line and the label
        std::cout << "            ";
        // iterates through the number of records
        for (int j = 1; j <= product_records.size(); j++)
        {
            // if its the first draw just the line, else draw the label, while adding 0 in the front
            // if the label is less than 10 so its evenly spaced.
            (i == 0 ? (std::cout << "---") : std::cout << (j < 10 ? "0" : "") << j << " ");
        }
        std::cout << std::endl;
    }
}

void HistoricalRecord::drawHistory(std::string product, std::string time, std::string metric)
{
    std::vector<RecordEntry> product_records = getRecords(product, time);
    // sets the max min and range to use later for drawing purposes
    for (RecordEntry &rec : product_records)
    {
        //initializes the currentMetric variable which will either by volume or marketCap
        //dependent on what drawHistory is passed
        double currentMetric = (metric == "vol" ? rec.volume : rec.marketCap);
        if (currentMetric > max)
        {
            max = currentMetric;
        }
        if (currentMetric < min || min == 0)
        {
            min = currentMetric;
        }
    }
    range = max - min;
    std::cout << "------HISTORICAL GRAPH -------" << std::endl;
    std::cout << product << " " << (metric == "vol" ? "VOLUME " : "MARKET CAP ") << "IN THE MONTH " << time << std::endl;
    //iterates between -2 and 14 so that the top and bottom of the graph has space between the highest and lowest values
    for (int i = -2; i < 14; i++)
    {
        //initializes the interval variable which is the range divided by 12
        double interval = range / 12;
        //initializes the y label variable which is the current label
        double yLabel = max - (i * interval);
        std::string axis = std::to_string(yLabel);
        // evenly spaces the labels by 5 spots
        if (i % 5 == 3 || i == -2)
        {
            // limits it to a constant 10 characters
            for (int x = 0; x < 10; x++)
            {
                std::cout << axis[x];
            }
            std::cout << " |";
        }
        else
        {
            // else leave it blank by 10 spaces so its a constant y axis.
            std::cout << "          "
                      << " |";
        }
        // for every row iterate through every record in product records
        for (RecordEntry &rec : product_records)
        {
            // changes the current metric that will be expressed depending on what metric is passed
            double currentMetric = (metric == "vol" ? rec.volume : rec.marketCap);
            // if the value of the current metric is close enough to a yLabel then place a marker
            if (std::abs(currentMetric - yLabel) < interval / 2)
            {
                std::cout << " X ";
            }
            // else leave it blank and move on to the next record in the product_records vector
            else
            {
                std::cout << "   ";
            }
        }
        std::cout << std::endl;
    }
    // draws the X axis and its labels
    drawXaxis(product_records);

    std::cout << std::endl;
}
// ALL WITHOUT ASSISTANCE OTHER THAN THE GIVEN MERKLEREX CODE TO FRAMEWORK OFF OF