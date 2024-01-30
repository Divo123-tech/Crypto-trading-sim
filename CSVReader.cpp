#include "CSVReader.h"
#include "RecordEntry.h"
#include <iostream>
#include <fstream>
#include <cmath>

CSVReader::CSVReader()
{
}

std::vector<OrderBookEntry> CSVReader::readCSV(std::string csvFilename)
{
    std::vector<OrderBookEntry> entries;

    std::ifstream csvFile{csvFilename};
    std::string line;
    if (csvFile.is_open())
    {
        while (std::getline(csvFile, line))
        {
            try
            {
                OrderBookEntry obe = stringsToOBE(tokenise(line, ','));
                entries.push_back(obe);
            }
            catch (const std::exception &e)
            {
                std::cout << "CSVReader::readCSV bad data" << std::endl;
            }
        } // end of while
    }

    std::cout << "CSVReader::readCSV read " << entries.size() << " entries" << std::endl;
    return entries;
}

// ALL WITHOUT ASSISTANCE OTHER THAN THE GIVEN MERKLEREX CODE TO FRAMEWORK OFF OF
std::vector<RecordEntry> CSVReader::readHistory(std::string csvFilename)
{
    std::vector<RecordEntry> records;
    std::ifstream csvFile{csvFilename};
    std::string line;
    if (csvFile.is_open())
    {
        while (std::getline(csvFile, line))
        {
            try
            {
                RecordEntry rec = stringToRE(tokenise(line, ','));
                records.push_back(rec);
            }
            catch (const std::exception &e)
            {
                std::cout << "CSVReader::readHistory bad data" << std::endl;
            }
        } // end of while
    }
    std::cout << "CSVReader::readCSV read " << records.size() << " records" << std::endl;
    return records;
}
// ALL WITHOUT ASSISTANCE OTHER THAN THE GIVEN MERKLEREX CODE TO FRAMEWORK OFF OF


std::vector<std::string> CSVReader::tokenise(std::string csvLine, char separator)
{
    std::vector<std::string> tokens;
    signed int start, end;
    std::string token;
    start = csvLine.find_first_not_of(separator, 0);
    do
    {
        end = csvLine.find_first_of(separator, start);
        if (start == csvLine.length() || start == end)
            break;
        if (end >= 0)
            token = csvLine.substr(start, end - start);
        else
            token = csvLine.substr(start, csvLine.length() - start);
        tokens.push_back(token);
        start = end + 1;
    } while (end > 0);

    return tokens;
}

OrderBookEntry CSVReader::stringsToOBE(std::vector<std::string> tokens)
{
    double price, amount;

    if (tokens.size() != 5) // bad
    {
        std::cout << "Bad line " << std::endl;
        throw std::exception{};
    }
    // we have 5 tokens
    try
    {
        price = std::stod(tokens[3]);
        amount = std::stod(tokens[4]);
    }
    catch (const std::exception &e)
    {
        std::cout << "CSVReader::stringsToOBE Bad float! " << tokens[3] << std::endl;
        std::cout << "CSVReader::stringsToOBE Bad float! " << tokens[4] << std::endl;
        throw;
    }

    OrderBookEntry obe{price,
                       amount,
                       tokens[0],
                       tokens[1],
                       OrderBookEntry::stringToOrderBookType(tokens[2])};

    return obe;
}

OrderBookEntry CSVReader::stringsToOBE(std::string priceString,
                                       std::string amountString,
                                       std::string timestamp,
                                       std::string product,
                                       OrderBookType orderType)
{
    double price, amount;
    try
    {
        price = std::stod(priceString);
        amount = std::stod(amountString);
    }
    catch (const std::exception &e)
    {
        std::cout << "CSVReader::stringsToOBE Bad float! " << priceString << std::endl;
        std::cout << "CSVReader::stringsToOBE Bad float! " << amountString << std::endl;
        throw;
    }
    OrderBookEntry obe{price,
                       amount,
                       timestamp,
                       product,
                       orderType};

    return obe;
};

// ALL WITHOUT ASSISTANCE OTHER THAN THE GIVEN MERKLEREX CODE TO FRAMEWORK OFF OF
//converts string to a record entry object
RecordEntry CSVReader::stringToRE(std::vector<std::string> tokens)
{
    double volume;
    double marketCap;
    try
    {
        //tries to turn the string of volume and marketcap into a double
        volume = std::stod(tokens[2]);
        marketCap = std::stod(tokens[3]);
    }
    //if theres a bad line or input make the user aware of it
    catch (const std::exception &e)
    {
        std::cout << "CSVReader::stringsToRE Bad float! " << tokens[2] << std::endl;
        std::cout << "CSVReader::stringsToRE Bad float! " << tokens[3] << std::endl;
        throw;
    }
    RecordEntry re{
        tokens[1],
        tokens[0],
        volume,
        marketCap};
    //return a record entry pbject from teh information taken by the csv file line
    return re;
};
// ALL WITHOUT ASSISTANCE OTHER THAN THE GIVEN MERKLEREX CODE TO FRAMEWORK OFF OF