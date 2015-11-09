//
//  Stock.cpp
//  StockPicker
//
//  Created by Jason McAnally on 3/23/15.
//  Copyright (c) 2015 Jason McAnally. All rights reserved.
//

#include "Stock.h"
#include <iostream>

//Default constructor
Stock::Stock () {
    setSymbol("");
    setCompanyName("");
    quoteHistory.reserve(100000);
}

Stock::Stock (std::string someSymbol) {
    setSymbol(someSymbol);
    quoteHistory.reserve(100000);
}

//Constructor
Stock::Stock (std::string someSymbol, std::string someName) {
    setSymbol(someSymbol);
    setCompanyName(someName);
    quoteHistory.reserve(100000);
}

//Standard set functions
void Stock::setSymbol(std::string someSymbol) {
    symbol = someSymbol;
}
void Stock::setCompanyName(std::string someName) {
    companyName = someName;
}

void Stock::updateCurrentData(ExtQuote* someExtQuote) {
    currentData = someExtQuote;
}

//addDate function, adds a date object to the end of the quoteHistory vector
void Stock::addDate(Date* someDate) {
    quoteHistory.push_back(someDate);
}

//Standard get functions
std::string Stock::getSymbol() {
    return symbol;
}
std::string Stock::getCompanyName() {
    return companyName;
}
bool Stock::dataIsCurrent() {
  
    time_t now, zeroAM_today, zeroAm_yesterday; //time type
    struct tm t1, t2, t3; //calandar date and time, broken down into components
    time(&now); //get current time
    localtime_r(&now, &t1); //convert now to struct tm
    
    t3 = t2 = t1;
    
    //set to 00:00 local today
    t2.tm_hour = 0;
    t2.tm_min = 0;
    t2.tm_sec = 0;
    
    zeroAM_today = mktime(&t2);
    zeroAm_yesterday = mktime(&t2-(24*60*60));
    
    localtime_r(&now, &t1);
    localtime_r(&zeroAM_today, &t2);
    localtime_r(&zeroAm_yesterday, &t3);
    
    Date yesterdaysDate(t3.tm_year + 1900, t3.tm_mon, t3.tm_mday);
    Date todaysDate(t2.tm_year + 1900, t2.tm_mon, t2.tm_mday);
    Date latestQuote = *getDateLatestQuote();
    
    std::cout
    << std::endl
    << std::endl
    << t1.tm_hour << ":" << t1.tm_min
    << std::endl
    << "Today's date: " << todaysDate.getDateString()
    << std::endl
    << "Yesterday's date: " << yesterdaysDate.getDateString()
    << std::endl
    << "Latest quote's date: " << latestQuote.getDateString()
    << std::endl
    << std::endl;
    
    
    if (t1.tm_hour > 15) {
        if (latestQuote == todaysDate) {
            return true;
        } else {
            return false;
        }
    } else {
        if (latestQuote == yesterdaysDate) {
            return true;
        } else {
            return false;
        }
    }

}


//Checks if provided date object is in quoteHistory vector
bool Stock::dateInQuoteHistory(Date* someDate) {
    for (int i = 0; i < quoteHistory.size(); i++) {
        if (quoteHistory[i] == someDate) {
            return true;
        }
    }
    return false;
}

//Returns vector position of provided date object. If
int Stock::getDatePosition(Date* someDate) {
    
    
    if (dateInQuoteHistory(someDate)) {
        int position = 0;
        for (int i = 0; i < quoteHistory.size(); i++) {
            if (quoteHistory[i] == someDate) {
                
                
                position = i;
                break;
            }
        }
        return position;
        
    } else {
        std::cout << std::endl << "Date doesn't exist in quote history!\n";
        return -1;
    }
}

double Stock::getTargetDivYield(bool useAdjusted) {
    double lowestPrice = 0.0;
    
    lowestPrice = getDateWorstQuote(useAdjusted)->getQuote().getLow(useAdjusted);
    
    double lowestPriceDividend = getDateWorstQuote(useAdjusted)->getQuote().getDividend();
    
    return (lowestPriceDividend * 4)/lowestPrice;
}

double Stock::getTargetPrice(bool useAdjusted) {
    return (getDateLatestQuote()->getQuote().getDividend()*4)/getTargetDivYield(useAdjusted);
}

//Returns top value of Green Zone for a given range of dates (value is attributed to endDate)
double Stock::getGreenZoneTop(Date beginDate, Date endDate, bool useAdjusted) {
    double mostRecentDividend = quoteHistory.front()->getQuote().getDividend();
    
    double greenZoneTop = (mostRecentDividend * 4)/(.9 * (getTargetDivYield(useAdjusted)));
    return greenZoneTop;
}

//Returns top value of Yellow Zone for a given range of dates (value is attributed to endDate)
double Stock::getYellowZoneTop(Date beginDate, Date endDate, bool useAdjusted) {
    double mostRecentDividend = quoteHistory.front()->getQuote().getDividend();
    
    double yellowZoneTop = (mostRecentDividend * 4)/(.8 * (getTargetDivYield(useAdjusted)));
    return yellowZoneTop;
}

//Returns Zone value for given date object
priceZone Stock::getZone(Date* someDate, bool useAdjusted) {
    //std::cout
    //<< std::endl
    //<< "Close: " << quoteHistory[getDatePosition(someDate)].getQuote().getClose()
    //<< std::endl
    //<< "Green zone top: " << getGreenZoneTop(lastMarketTop, someDate) << std::endl;
    
    if (quoteHistory[getDatePosition(someDate)]->getQuote().getClose(useAdjusted)
                        < getGreenZoneTop(lastMarketTop, *someDate, useAdjusted)) {
        return GREEN;
    } else if (quoteHistory[getDatePosition(someDate)]->getQuote().getClose(useAdjusted)
                        < getYellowZoneTop(lastMarketTop, *someDate, useAdjusted)) {
        return YELLOW;
    } else {
        return RED;
    }
}


long Stock::getQuoteHistorySize() {
    return quoteHistory.size();
}

Date* Stock::getDateLatestQuote() {
    return quoteHistory.front();
}

Date* Stock::getDateWorstQuote(bool useAdjusted) {
    double worstPrice = 1000000000.0;
    double tempLow = 0.0;
    Date * d = getDateLatestQuote();
    for (int i = 0; i < quoteHistory.size(); i++) {
        
        tempLow = quoteHistory.at(i)->getQuote().getLow(useAdjusted);
        
        if (tempLow < worstPrice) {
            worstPrice = tempLow;
            d = quoteHistory.at(i);
        }
    }
    return d;
}

Date* Stock::getDate(Date* someDate) {
    if (dateInQuoteHistory(someDate)) {
        return quoteHistory.at(getDatePosition(someDate));
    } else {
        return NULL;
    }
}

ExtQuote* Stock::getCurrentData() {
    return currentData;
}

