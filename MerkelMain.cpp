#include "MerkelMain.h"
#include <iostream>
#include <vector>
#include "OrderBookEntry.h"
#include <iomanip>
#include <cstdlib>
#include <cmath>
#include "CSVReader.h"
#include "CandleStick.h"
#include "CandleStickManager.h"
#include "HistoricalRecord.h"

MerkelMain::MerkelMain()
{
}

void MerkelMain::init()
{
    int input;
    currentTime = orderBook.getEarliestTime();
    wallet.insertCurrency("BTC", 10);
    timeElapsed.push_back(currentTime);
    while (true)
    {
        printMenu();
        input = getUserOption();
        processUserOption(input);
    }
}

void MerkelMain::printMenu()
{
    // 1 print help
    std::cout << "1: Print help " << std::endl;
    // 2 print exchange stats
    std::cout << "2: Print exchange stats" << std::endl;
    // 3 make an offer
    std::cout << "3: Make an offer " << std::endl;
    // 4 make a bid
    std::cout << "4: Make a bid " << std::endl;
    // 5 print wallet
    std::cout << "5: Print wallet " << std::endl;
    // 6 candlestick
    std::cout << "6: Candlestick " << std::endl;
    // 7 Historical records
    std::cout << "7: Check Crypto Historical Records " << std::endl;
    // 8 continue
    std::cout << "8: Continue " << std::endl;

    std::cout << "============== " << std::endl;

    std::cout << "Current time is: " << currentTime << std::endl;
}

void MerkelMain::printHelp()
{
    std::cout << "Help - your aim is to make money. Analyse the market and make bids and offers. " << std::endl;
}

void MerkelMain::printMarketStats()
{
    for (std::string const &p : orderBook.getKnownProducts())
    {
        std::cout << "Product: " << p << std::endl;
        std::vector<OrderBookEntry> entries = orderBook.getOrders(OrderBookType::ask,
                                                                  p, currentTime);
        std::cout << "Asks seen: " << entries.size() << std::endl;
        std::cout << "Max ask: " << OrderBook::getHighPrice(entries) << std::endl;
        std::cout << "Min ask: " << OrderBook::getLowPrice(entries) << std::endl;
    }
    // std::cout << "OrderBook contains :  " << orders.size() << " entries" << std::endl;
    // unsigned int bids = 0;
    // unsigned int asks = 0;
    // for (OrderBookEntry& e : orders)
    // {
    //     if (e.orderType == OrderBookType::ask)
    //     {
    //         asks ++;
    //     }
    //     if (e.orderType == OrderBookType::bid)
    //     {
    //         bids ++;
    //     }
    // }
    // std::cout << "OrderBook asks:  " << asks << " bids:" << bids << std::endl;
}

void MerkelMain::enterAsk()
{
    std::cout << "Make an ask - enter the amount: product,price, amount, eg  ETH/BTC,200,0.5" << std::endl;
    std::string input;
    std::getline(std::cin, input);

    std::vector<std::string> tokens = CSVReader::tokenise(input, ',');
    if (tokens.size() != 3)
    {
        std::cout << "MerkelMain::enterAsk Bad input! " << input << std::endl;
    }
    else
    {
        try
        {
            OrderBookEntry obe = CSVReader::stringsToOBE(
                tokens[1],
                tokens[2],
                currentTime,
                tokens[0],
                OrderBookType::ask);
            obe.username = "simuser";
            if (wallet.canFulfillOrder(obe))
            {
                std::cout << "Wallet looks good. " << std::endl;
                orderBook.insertOrder(obe);
            }
            else
            {
                std::cout << "Wallet has insufficient funds . " << std::endl;
            }
        }
        catch (const std::exception &e)
        {
            std::cout << " MerkelMain::enterAsk Bad input " << std::endl;
        }
    }
}

void MerkelMain::enterBid()
{
    std::cout << "Make an bid - enter the amount: product,price, amount, eg  ETH/BTC,200,0.5" << std::endl;
    std::string input;
    std::getline(std::cin, input);

    std::vector<std::string> tokens = CSVReader::tokenise(input, ',');
    if (tokens.size() != 3)
    {
        std::cout << "MerkelMain::enterBid Bad input! " << input << std::endl;
    }
    else
    {
        try
        {
            OrderBookEntry obe = CSVReader::stringsToOBE(
                tokens[1],
                tokens[2],
                currentTime,
                tokens[0],
                OrderBookType::bid);
            obe.username = "simuser";

            if (wallet.canFulfillOrder(obe))
            {
                std::cout << "Wallet looks good. " << std::endl;
                orderBook.insertOrder(obe);
            }
            else
            {
                std::cout << "Wallet has insufficient funds . " << std::endl;
            }
        }
        catch (const std::exception &e)
        {
            std::cout << " MerkelMain::enterBid Bad input " << std::endl;
        }
    }
}

void MerkelMain::printWallet()
{
    std::cout << wallet.toString() << std::endl;
}

void MerkelMain::gotoNextTimeframe()
{
    std::cout << "Going to next time frame. " << std::endl;
    for (std::string p : orderBook.getKnownProducts())
    {
        std::cout << "matching " << p << std::endl;
        std::vector<OrderBookEntry> sales = orderBook.matchAsksToBids(p, currentTime);
        std::cout << "Sales: " << sales.size() << std::endl;
        for (OrderBookEntry &sale : sales)
        {
            std::cout << "Sale price: " << sale.price << " amount " << sale.amount << std::endl;
            if (sale.username == "simuser")
            {
                // update the wallet
                wallet.processSale(sale);
            }
        }
    }
    currentTime = orderBook.getNextTime(currentTime);
    timeElapsed.push_back(currentTime);
}

int MerkelMain::getUserOption()
{
    int userOption = 0;
    std::string line;
    std::cout << "Type in 1-8" << std::endl;
    std::getline(std::cin, line);
    try
    {
        userOption = std::stoi(line);
    }
    catch (const std::exception &e)
    {
        //
    }
    std::cout << "You chose: " << userOption << std::endl;
    return userOption;
}

// ALL WITHOUT ASSISTANCE OTHER THAN THE GIVEN MERKLEREX CODE TO FRAMEWORK OFF OF
std::vector<CandleStick> MerkelMain::getCandleSticks(OrderBookType type, std::string product)
{
    // define the candlestick type vectors
    std::vector<CandleStick> sticks;
    // nextopen starts at 0 as there is no "previous time" for the first timestamp
    double nextOpen = 0;
    for (std::string time : timeElapsed)
    {
        // entries for the candlestick
        std::vector<OrderBookEntry> timeEntries = orderBook.getOrders(type,
                                                                      product, time);
        CandleStick candlestick{time,
                                nextOpen,
                                OrderBook::getHighPrice(timeEntries),
                                OrderBook::getLowPrice(timeEntries),
                                OrderBook::getAveragePrice(timeEntries)};
        // pushes the candlestick object to sticks vector
        sticks.push_back(candlestick);
        // makes open of the next candlestick the average of the previous time
        nextOpen = OrderBook::getAveragePrice(timeEntries);
    };
    // return a std::vector<CandleStick>
    return sticks;
}

void MerkelMain::displayCandleStick()
{
    std::cout << "Display CandleStick - enter the product and type (NO SPACES):  eg. ETH/BTC,ask" << std::endl;
    std::string input;
    std::getline(std::cin, input);
    std::vector<std::string> tokens = CSVReader::tokenise(input, ',');
    // input validation to make sure input is 2 things
    if (tokens.size() != 2)
    {
        std::cout << "MerkelMain::displayCandleStick Bad input! " << input << std::endl;
    }
    else
    {
        // makes sure the order type is either bid or ask
        if (OrderBookEntry::stringToOrderBookType(tokens[1]) == OrderBookType::unknown)
        {

            std::cout << "MerkelMain::whatever Bad input! " << input << std::endl;
        }

        else
        {
            // instantiates a CandleStickManager class while passing in the getCandleStick() function
            CandleStickManager csm{getCandleSticks(OrderBookEntry::stringToOrderBookType(tokens[1]), tokens[0])};
            // draws the CandleSticks
            csm.drawCandleSticks();
        }
    }
}


void MerkelMain::showHistory()
{
    std::cout << "Here you can look at the historical records of certain crypto currencies' volume and market cap" << std::endl;
    std::cout << "Available Products:" << std::endl;
    std::cout << "BTC, ETH, DOGE" << std::endl;
    std::cout << "Available TimeFrame:" << std::endl;
    std::cout << "2015-09 until 2020-04" << std::endl;
    std::cout << "Available Metrics:" << std::endl;
    std::cout << "Market Cap: mcap | Volume : vol" << std::endl;
    std::cout << "Type the crypto currency, year-month, metric. ie. BTC,2018-08,mcap or ETH,2016-11,vol" << std::endl;
    // receives input from user
    std::string input;
    std::getline(std::cin, input);
    std::vector<std::string> tokens = CSVReader::tokenise(input, ',');
    // input validation to make sure the input is 3 things
    if (tokens.size() != 3)
    {
        std::cout << "MerkelMain::showHistory Bad input! " << input << std::endl;
    }
    else
    {
        // make sure that they only specify a specifc month and year
        if (tokens[1].size() != 7)
        {
            std::cout << "Please use the year-month format!" << std::endl;
        }
        else
        {
            // instantiates a Historical Record object that uses the HistoricalRecords.csv file
            HistoricalRecord HR{"HistoricalRecords.csv"};
            // draws the History using the products, time, and metric taken from the user input
            HR.drawHistory(tokens[0], tokens[1], tokens[2]);
        }
    }
}
// ALL WITHOUT ASSISTANCE OTHER THAN THE GIVEN MERKLEREX CODE TO FRAMEWORK OFF OF


void MerkelMain::processUserOption(int userOption)
{
    if (userOption == 0) // bad input
    {
        std::cout << "Invalid choice. Choose 1-8" << std::endl;
    }
    if (userOption == 1)
    {
        printHelp();
    }
    if (userOption == 2)
    {
        printMarketStats();
    }
    if (userOption == 3)
    {
        enterAsk();
    }
    if (userOption == 4)
    {
        enterBid();
    }
    if (userOption == 5)
    {
        printWallet();
    }
    if (userOption == 6)
    {
        displayCandleStick();
    }
    if (userOption == 7)
    {
        showHistory();
    }
    if (userOption == 8)
    {
        gotoNextTimeframe();
    }
}
