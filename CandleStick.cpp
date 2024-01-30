// ALL WITHOUT ASSISTANCE OTHER THAN THE GIVEN MERKLEREX CODE TO FRAMEWORK OFF OF
#include "OrderBook.h"
#include "CandleStick.h"
#include <iostream>

CandleStick::CandleStick(std::string _time, double _open, double _high, double _low, double _close) : time(_time),
                                                                                                      open(_open),
                                                                                                      high(_high),
                                                                                                      low(_low),
                                                                                                      close(_close){

                                                                                                      };

void CandleStick::computeInfo()
{
        std::cout << "DATE: " << time << std::endl;
        std::cout << "OPEN"
                  << "-----"
                  << "HIGH"
                  << "-----"
                  << "LOW"
                  << "-----"
                  << "CLOSE" << std::endl;
        std::cout << open << "-----";
        std::cout << high << "-----";
        std::cout << low << "-----";
        std::cout << close << std::endl;
        std::cout << std::endl;
};
// ALL WITHOUT ASSISTANCE OTHER THAN THE GIVEN MERKLEREX CODE TO FRAMEWORK OFF OF