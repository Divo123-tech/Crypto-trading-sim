#pragma once

#include <vector>
#include "OrderBookEntry.h"
#include "OrderBook.h"
#include "Wallet.h"
#include "CandleStick.h"

class MerkelMain
{
public:
    MerkelMain();
    /** Call this to start the sim */
    void init();

private:
    void printMenu();
    void printHelp();
    void printMarketStats();
    void enterAsk();
    void enterBid();
    void printWallet();
    void gotoNextTimeframe();
    int getUserOption();
    void processUserOption(int userOption);
    // ALL WITHOUT ASSISTANCE OTHER THAN THE GIVEN MERKLEREX CODE TO FRAMEWORK OFF OF
    std::vector<CandleStick> getCandleSticks(OrderBookType type, std::string product);
    void drawCandleStickGraph(std::vector<CandleStick> candlesticks);
    void displayCandleStick();
    void showHistory();
    std::vector<std::string> timeElapsed;
    // ALL WITHOUT ASSISTANCE OTHER THAN THE GIVEN MERKLEREX CODE TO FRAMEWORK OFF OF
    std::string currentTime;
    //        OrderBook orderBook{"20200317.csv"};
    OrderBook orderBook{"20200601.csv"};
    Wallet wallet;
    ;
};
