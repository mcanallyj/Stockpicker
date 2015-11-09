//
//  Stock.h
//  StockPicker
//
//  Created by Jason McAnally on 3/23/15.
//  Copyright (c) 2015 Jason McAnally. All rights reserved.
//

#ifndef __StockPicker__Stock__
#define __StockPicker__Stock__

#include <stdio.h>
#include <vector>
#include <string>
#include "Date.h"
#include "ExtQuote.h"

class Date;
class File;

enum priceZone {GREEN, YELLOW, RED};

const Date lastMarketTop(2007, 0, 3);

class Stock {
private:
    std::string symbol;
    std::string companyName;
    std::vector<Date*> quoteHistory;
    ExtQuote* currentData;
    
public:
    Stock();
    Stock(std::string someSymbol, std::string someName);
    Stock(std::string someSymbol);
     
    //setters
    void setSymbol(std::string someSymbol);
    void setCompanyName(std::string someName);
    void updateCurrentData(ExtQuote* someExtQuote);
    
    //getters
    std::string getSymbol();
    std::string getCompanyName();
    Date* getDateLatestQuote();
    Date* getDateWorstQuote(bool useAdjusted);
    Date* getDate(Date* someDate);
    bool dataIsCurrent();
    void addDate(Date* someDate);
    double getTargetDivYield(bool useAdjusted);
    double getTargetPrice(bool useAdjusted);
    bool dateInQuoteHistory(Date* someDate);
    int getDatePosition(Date* someDate);
    double getGreenZoneTop(Date beginDate, Date endDate, bool useAdjusted);
    double getYellowZoneTop(Date beginDate, Date endDate, bool useAdjusted);
    priceZone getZone(Date* someDate, bool useAdjusted);
    double getSMA(Date* beginDate, Date* endDate);
    long getQuoteHistorySize();
    ExtQuote* getCurrentData();
};

#endif /* defined(__StockPicker__Stock__) */
