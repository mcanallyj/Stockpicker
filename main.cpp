//
//  main.cpp
//  StockPicker
//
//  Created by Jason McAnally on 3/23/15.
//  Copyright (c) 2015 Jason McAnally. All rights reserved.
//

#include <iomanip>
#include <iostream>
#include <fstream>
#include "Stock.h"
#include "File.h"
#include "Quote.h"
#include "ExtQuote.h"
#include "Date.h"

#include <cstring>
#include <ctime>
#include <sys/stat.h>
#include <string>
#include <queue>



void downloadYahooHistoricalPriceData(std::vector<Stock>* stockVector,
                                      std::string workingDirectory);
void downloadYahooDividendData(std::vector<Stock>* stockVector,
                               std::string workingDirectory);
void downloadYahooExtendedQuoteData(std::vector<Stock>* stockVector,
                                    std::string workingDirectory);

void assignPriceData(std::vector<Stock>* stockVector,
                     std::string workingDirectory);

void assignExtQuoteData(std::vector<Stock>* stockVector,
                        std::string workingDirectory);

void mainMenu(std::vector<Stock>* stockVector);
void lookUpMenu(std::vector<Stock> * stockVector);
void zoneMenu(std::vector<Stock>* stockVector, priceZone z, bool useAdjusted);
void printStockInfo(Stock* s, bool useAdjusted);

std::vector<std::string> parseCSVLine (std::string someString);
double getDividendData(std::ifstream &fileStream, Date * datePTR);
std::vector<Stock>* getStocksInZone(std::vector<Stock>* stockVector, priceZone z, bool useAdjusted);


std::string wDirectory = "/Users/Jason/Desktop/StockData/";

std::string paddedInteger (int someInt, int digitsWide);

int main(int argc, const char * argv[]) {
    
    std::string filename = wDirectory + "divChamps.txt";

    std::vector<Stock> * stockList = new std::vector<Stock>;
    
    std::ifstream divChamps(filename);
    
    if (divChamps.is_open()) {
        std::string textline;
        while (getline(divChamps, textline)) {
            Stock newStock(textline);
            stockList->push_back(newStock);
        }
        
        divChamps.close();
    } else {
        std::cout << "divChamps.txt did not open";
    }
    
        
    
        
    downloadYahooHistoricalPriceData(stockList,
                                     wDirectory+ "HistoricalData/");
     
    downloadYahooDividendData(stockList,
                              wDirectory + "DividendData/");
    
    downloadYahooExtendedQuoteData(stockList,
                                   wDirectory + "ExtendedQuotes/");
    
        
    std::cout << std::endl << "Assigning price/dividend data...";
    
    assignPriceData(stockList, wDirectory);
    
    assignExtQuoteData(stockList, wDirectory);
        
    std::cout << std::endl << "Price/Dividend data assigned...";

    mainMenu(stockList);
    
    return 0;
}


void mainMenu(std::vector<Stock>* stockVector) {
    
    int choice = 0;
    do {
        
        std::cout
        << std::endl
        << std::endl
        << "Main Menu: \n"
        << "    1. Look up specific stock via symbol\n"
        << "    2. Display stocks in green zone (adjusted)\n"
        << "    3. Display stocks in yellow zone (adjusted)\n"
        << "    4. Display stocks in green zone (unadjusted)\n"
        << "    5. Display stocks in yellow zone (unadjusted)\n"
        << "    6. Quit program\n"
        << "\n"
        << "Enter number of your choice: ";
        
        std::cin >> choice;
        
        switch (choice) {
            case 1: {
                lookUpMenu(stockVector);
                break;
            
            } case 2: {
                std::cout << std::endl << "Stocks in Green Zone: \n";
                zoneMenu(getStocksInZone(stockVector, GREEN, true), GREEN, true);
                break;
                
            } case 3: {
                zoneMenu(getStocksInZone(stockVector, YELLOW, true), YELLOW, true);
                break;
                
            } case 4: {
                zoneMenu(getStocksInZone(stockVector, GREEN, false), GREEN, false);
                break;
            } case 5: {
                zoneMenu(getStocksInZone(stockVector, YELLOW, false), YELLOW, false);
                break;
            } case 6: {
                std::cout
                << std::endl
                << std::endl
                << "Have a nice day...\n";
                break;
            } default: {
                std::cout
                << std::endl
                << "Invalid entry, entry must be # of valid available choice\n";
                break;
            }
        }
    } while (choice != 4);
}


void lookUpMenu(std::vector<Stock> *stockVector) {
    std::string userSymbol = "";
    int z = -1;
    char input = 'x';
    
    Stock* s;
    Date* l;
    std::cout
    << std::endl
    << std::endl
    << "Enter the symbol of the stock you want to look up: ";
    
    std::cin >> userSymbol;
    
    
    for (int i = 0; i < stockVector->size(); i++) {
        if (stockVector->at(i).getSymbol() == userSymbol) {
            z = i;
            break;
        }
    }
    
    if (z >= 0) {
        s = &stockVector->at(z);
        l = s->getDateLatestQuote();
        std::cout << std::string(100, '\n');
        
        std::cout
        << std::endl
        << std::endl
        << userSymbol << ": \n"
        << std::endl
        << std::endl
        << "Latest quote date: " << l->getDateString()
        << std::endl
        << std::endl
        << std::setw(20) << "Open: $" << l->getQuote().getOpen(false)
        << std::endl
        << std::setw(20) << "Close: $" << l->getQuote().getClose(false)
        << std::endl
        << std::setw(20) << "High: $" << l->getQuote().getHigh(false)
        << std::endl
        << std::setw(20) << "Low: $" << l->getQuote().getLow(false)
        << std::endl
        << std::setw(20) << "Yearly Dividend: $" << l->getQuote().getDividend() * 4
        << std::endl
        << std::setw(20) << "Dividend Yield:  "
        << std::setprecision(3)
        << l->getQuote().getDividendYield(false) * 100 << "%\n"
        
        << std::setw(20) << "Payout Ratio:  "
        << ((l->getQuote().getDividend() * 4) /
            s->getCurrentData()->ePSEstimateCurrentYear) * 100 << "%\n";
        
        std::cout
        << std::endl << "Unadjusted numbers: " << std::endl;
        printStockInfo(s, false);
        
        std::cout
        << std::endl << "Adjusted numbers: " << std::endl;
        printStockInfo(s, true);
        
        std::cout << "Enter 0 to return to main menu: ";
        std::cin >> input;
    }
}


void printStockInfo(Stock* s, bool useAdjusted) {
    Date* l;
    Date* w;
    
    l = s->getDateLatestQuote();
    w = s->getDateWorstQuote(useAdjusted);
    
    
    
    std::cout << std::endl
    << "Worst performance since " << lastMarketTop.getDateString()
    << " was on: " << w->getDateString()
    << std::endl
    << std::endl;
    
    std::resetiosflags(ALLPERMS);
    std::cout
    << std::setw(20) << "Price: $" << w->getQuote().getLow(useAdjusted) << std::endl
    << std::setw(20) << "Yearly dividend: $" << std::setprecision(3) << w->getQuote().getDividend() * 4 << std::endl
    << std::setw(20) << "Dividend yield:  "
    << ((w->getQuote().getDividend() * 4) / w->getQuote().getLow(useAdjusted)) * 100 << "%\n"
    << std::setw(20) << "Desired Price: $" << std::setprecision(4)
    << (l->getQuote().getDividend() * 4)/((w->getQuote().getDividend() *4)/ w->getQuote().getLow(useAdjusted));
    
    
    std::cout
    << std::endl
    << std::endl
    << std::setw(20) << "Green zone top: " << s->getGreenZoneTop(*w, *l, useAdjusted)
    << std::endl
    << std::setw(20) << "Yellow zone top: " << s->getYellowZoneTop(*w, *l, useAdjusted)
    << std::endl
    << std::endl;

    
    
    
}


/*********************************************************************
 ** Function: downloadYahooPriceData
 ** Description: downloads stock price history from Yahoo using csv API. Files
 **     are downloaded for each stock ticker that is in stockVector argument.
 ** Parameters: vector of stocks, string listing the download directory
 ** Pre-Conditions: N/A
 ** Post-Conditions: N/A
 *********************************************************************/
void downloadYahooHistoricalPriceData(std::vector<Stock>* stockVector,
                                      std::string workingDirectory) {
    time_t now = time(0);
    struct tm current_tm;
    localtime_r(&now, &current_tm);
     
    std::string yahooURL = "http://real-chart.finance.yahoo.com/table.csv?s=";
     
    for (int i = 0; i < stockVector->size(); i++) {
        std::string symbol = stockVector->at(i).getSymbol();
        
        File csvFile((symbol + ".csv"), workingDirectory);
        
        if (csvFile.exists()) {
            struct tm fileLastModified;
            time_t t = csvFile.timeLastModified();
            localtime_r(&t, &fileLastModified);
            
            if (fileLastModified.tm_year != current_tm.tm_year
                || fileLastModified.tm_mon != current_tm.tm_mon
                || fileLastModified.tm_mday != current_tm.tm_mday) {
                    
                std::cout
                << std::endl
                << "Price Data expired, commencing refresh of price data for "
                << symbol << "...";
                std::cout.flush();
                    
                std::string codedRemainder = symbol +
                "'&'a=" + paddedInteger(lastMarketTop.getMonth(), 2) +
                "'&'b=" + paddedInteger(lastMarketTop.getDay(), 2) +
                "'&'c=" + std::to_string(lastMarketTop.getYear()) +
                "'&'d=" + paddedInteger(current_tm.tm_mon, 2) +
                "'&'e=" + paddedInteger(current_tm.tm_mday, 2) +
                "'&'f=" + std::to_string(current_tm.tm_year+1900) +
                "'&'g=d" +
                "'&'ignore=.csv";
                std::string command = "curl -s -L -o "
                                        + workingDirectory
                                        + symbol
                                        + ".csv "
                                        + yahooURL
                                        + codedRemainder;
            
                std::system(command.c_str());
                
                std::cout << "Download complete!";
                std::cout.flush();
            } else {
                /*std::cout << std::endl << "Price data already current as of "
                    + std::to_string(fileLastModified.tm_hour)
                    + ":"
                    + std::to_string(fileLastModified.tm_min) + " today...";*/
            }
        } else {
            std::cout
            << std::endl
            << "Downloading price data for "
            << symbol << "...";
            
            std::cout.flush();
            
            std::string codedRemainder = symbol +
            "'&'a=" + paddedInteger(lastMarketTop.getMonth(), 2) +
            "'&'b=" + paddedInteger(lastMarketTop.getDay(), 2) +
            "'&'c=" + std::to_string(lastMarketTop.getYear()) +
            "'&'d=" + paddedInteger(current_tm.tm_mon, 2) +
            "'&'e=" + paddedInteger(current_tm.tm_mday, 2) +
            "'&'f=" + std::to_string(current_tm.tm_year+1900) +
            "'&'g=d" +
            "'&'ignore=.csv";
            std::string command = "curl -s -L -o "
                                    + workingDirectory
                                    + symbol
                                    + ".csv "
                                    + yahooURL
                                    + codedRemainder;
            
            std::system(command.c_str());
            
            std::cout << "Download complete!";
            std::cout.flush();
        }
    }
}


/*********************************************************************
 ** Function: downloadYahooDividendData
 ** Description: downloads stock dividend history from Yahoo using csv API.
 **     Files are downloaded for each stocker that is in stockVector argument.
 ** Parameters: vector of stocks, string listing the download directory
 ** Pre-Conditions: N/A
 ** Post-Conditions: N/A
 *********************************************************************/
void downloadYahooDividendData(std::vector<Stock> * stockVector,
                               std::string workingDirectory) {
    time_t now = time(0);
    struct tm current_tm;
    localtime_r(&now, &current_tm);
    
    std::string yahooURL = "http://real-chart.finance.yahoo.com/table.csv?s=";
    for (int i = 0; i < stockVector->size(); i++) {
        
        std::string symbol = stockVector->at(i).getSymbol();
        
        File csvFile((symbol + "_dividend.csv"), workingDirectory);
        
        if (csvFile.exists()) {
            struct tm fileLastModified;
            time_t t = csvFile.timeLastModified();
            localtime_r(&t, &fileLastModified);
            if (fileLastModified.tm_year != current_tm.tm_year
                || fileLastModified.tm_mon != current_tm.tm_mon
                || fileLastModified.tm_mday != current_tm.tm_mday) {

                std::cout
                << std::endl
                << "Dividend data expired, commencing refresh for "
                << symbol << "...";
                std::cout.flush();
              
                std::string codedRemainder = symbol +
                "'&'a=" + paddedInteger(lastMarketTop.getMonth(), 2) +
                "'&'b=" + paddedInteger(lastMarketTop.getDay(), 2) +
                "'&'c=" + std::to_string(lastMarketTop.getYear()-1) +
                "'&'d=" + paddedInteger(current_tm.tm_mon, 2) +
                "'&'e=" + paddedInteger(current_tm.tm_mday, 2) +
                "'&'f=" + std::to_string(current_tm.tm_year+1900) +
                "'&'g=v" +
                "'&'ignore=.csv";
                
                
                std::string command =
                "curl -s -L -o "
                    + workingDirectory
                    + symbol
                    + "_dividend.csv "
                    + yahooURL
                    + codedRemainder;
                
                
                std::system(command.c_str());
                   
                std::cout << "Complete!";
                std::cout.flush();
                std::cout << std::endl << "Dividend data refreshed...";
              
            } else {
                /*std::cout << std::endl << "Dividend data already current as of "
                    + std::to_string(fileLastModified.tm_hour)
                    + ":" + std::to_string(fileLastModified.tm_min)
                    + " today..."; */
            }
        } else {
            std::cout << std::endl << "Downloading dividend data for "
            << symbol << "...";
            std::cout.flush();
            
            std::string codedRemainder = symbol +
            "'&'a=" + paddedInteger(lastMarketTop.getMonth(), 2) +
            "'&'b=" + paddedInteger(lastMarketTop.getDay(), 2) +
            "'&'c=" + std::to_string(lastMarketTop.getYear()-1) +
            "'&'d=" + paddedInteger(current_tm.tm_mon, 2) +
            "'&'e=" + paddedInteger(current_tm.tm_mday, 2) +
            "'&'f=" + std::to_string(current_tm.tm_year+1900) +
            "'&'g=v" +
            "'&'ignore=.csv";
            std::string command =
            "curl -s -L -o "
            + workingDirectory
            + symbol
            + "_dividend.csv "
            + yahooURL
            + codedRemainder;
          
            
            std::system(command.c_str());
            
            std::cout << "Complete!";
            std::cout.flush();
            std::cout << std::endl << "Dividend data downloaded...";
        }
    }
}
/*********************************************************************
 ** Function: downloadYahooExtendedQuoteData
 ** Description: downloads stock price history from Yahoo using csv API. Files
 **     are downloaded for each stock ticker that is in stockVector argument.
 ** Parameters: vector of stocks, string listing the download directory
 ** Pre-Conditions: N/A
 ** Post-Conditions: N/A
 *********************************************************************/
void downloadYahooExtendedQuoteData(std::vector<Stock>* stockVector,
                                      std::string workingDirectory) {
    time_t now = time(0);
    struct tm current_tm;
    localtime_r(&now, &current_tm);
    
    std::string yahooURL
        = "http://download.finance.yahoo.com/d/quotes.csv?s=";
    
    for (int i = 0; i < stockVector->size(); i++) {
        std::string symbol = stockVector->at(i).getSymbol();
        
        File csvFile((symbol + "_ext.csv"), workingDirectory);
        
        //http://download.finance.yahoo.com/d/quotes.csv?s=%40%5EDJI,GOOG&f=nsl1op&e=.csv
        
        
        
        std::string codedRemainder = symbol + "'&'f="
        + _AfterHoursChangeRealtime
        + _AnnualizedGain
        + _Ask
        + _AskRealtime
        + _AskSize
        + _AverageDailyVolume
        + _Bid
        + _BidRealtime
        + _BidSize
        + _BookValuePerShare
        + _Change
        + _Change_ChangeInPercent
        + _ChangeFromFiftydayMovingAverage
        + _ChangeFromTwoHundreddayMovingAverage
        + _ChangeFromYearHigh
        + _ChangeFromYearLow
        + _ChangeInPercent
        + _ChangeInPercentRealtime
        + _ChangeRealtime
        + _Commission
        + _DaysHigh
        + _DaysLow
        + _DaysRange
        + _DaysRangeRealtime
        + _TrailingAnnualDividendYield
        + _TrailingAnnualDividendYieldInPercent
        + _DilutedEPS
        + _EBITDA
        + _EPSEstimateCurrentYear
        + _EPSEstimateNextQuarter
        + _EPSEstimateNextYear
        + _FiftydayMovingAverage
        + _HighLimit
        + _HoldingsGain
        + _HoldingsGainPercent
        + _HoldingsGainPercentRealtime
        + _HoldingsGainRealtime
        + _HoldingsValue
        + _HoldingsValueRealtime
        + _LastTradePriceOnly
        + _LastTradeSize
        + _LastTradeTime
        + _LowLimit
        + _MarketCapitalization
        + _MarketCapRealtime
        + _OneyrTargetPrice
        + _Open
        + _OrderBookRealtime
        + _PEGRatio
        + _PERatio
        + _PERatioRealtime
        + _PercentChangeFromFiftydayMovingAverage
        + _PercentChangeFromTwoHundreddayMovingAverage
        + _ChangeInPercentFromYearHigh
        + _PercentChangeFromYearLow
        + _PreviousClose
        + _PriceBook
        + _PriceEPSEstimateCurrentYear
        + _PriceEPSEstimateNextYear
        + _PricePaid
        + _PriceSales
        + _Revenue
        + _ShortRatio
        + _TwoHundreddayMovingAverage
        + _YearHigh
        + _YearLow
        + _YearRange
        + _Currency
        + _Name
        + _Notes
        + _StockExchange
        + _Symbol
        + _TickerTrend
        + _TradeData
        + _TradeLinks
        + _TradeLinksAdditional
        + _DividendPayDate
        + _ExDividendDate
        + _LastTradeDate
        + _SharesOwned
        + _SharesOutstanding
        + _Volume
        + "'&'e=.csv";
        
        std::string command = "curl -s -L -o "
        + workingDirectory
        + symbol
        + "_ext.csv "
        + yahooURL
        + codedRemainder;
        
        if (csvFile.exists()) {
            struct tm fileLastModified;
            time_t t = csvFile.timeLastModified();
            localtime_r(&t, &fileLastModified);
            
            if (fileLastModified.tm_year != current_tm.tm_year
                || fileLastModified.tm_mon != current_tm.tm_mon
                || fileLastModified.tm_mday != current_tm.tm_mday) {
                
                std::cout
                << std::endl
                << "Extended Quote data expired, commencing refresh for "
                << symbol << "...";
                std::cout.flush();
                
                std::system(command.c_str());
                
                std::cout << "Download complete!";
                std::cout.flush();
            } else {
                /*std::cout << std::endl << "Extended data already current as of "
                + std::to_string(fileLastModified.tm_hour)
                + ":"
                + std::to_string(fileLastModified.tm_min) + " today...";*/
            }
        } else {
            std::cout
            << std::endl
            << "Downloading Extended Quote data for "
            << symbol << "...";
            
            std::cout.flush();
            
            std::system(command.c_str());
            
            std::cout << "Download complete!";
            std::cout.flush();
        }
    }
}


/*********************************************************************
 ** Function: assignPriceData
 ** Description: pulls data from each line of the csv file (stock and dividend
 **     files, both), and assigns it as a daily quote for the stock involved.
 **     This is done for all stocks that are in the stock vector passed as
 **     argument.
 ** Parameters: vector of stocks, workingDirectory string giving path for files
 ** Pre-Conditions: N/A
 ** Post-Conditions: Stock objects have price history
 *********************************************************************/
void assignPriceData(std::vector<Stock>* stockVector,
                     std::string workingDirectory) {
    
    for (int i = 0; i < stockVector->size(); i++) {
        std::string symbol = stockVector->at(i).getSymbol();
        
        std::ifstream stockFile(workingDirectory
                              + "HistoricalData/" + symbol + ".csv");
        
        std::ifstream divFile(workingDirectory
                              + "DividendData/" + symbol + "_dividend.csv");
        
        std::string bufferDate = "";
        
        if (stockFile && divFile) {
            
            
            std::string input = "";
            getline(stockFile, input); //junk line gives column titles
            input = "";
            
            
            getline(stockFile, input);
            do {
                
                
                std::vector<std::string> stringVector = parseCSVLine(input);
                
                Date* d = new Date(stringVector[0]);

                double open = stod(stringVector[1]);
                double high = stod(stringVector[2]);
                double low = stod(stringVector[3]);
                double close = stod(stringVector[4]);
                int volume = stoi(stringVector[5]);
                double adjClose = stod(stringVector[6]);
                
                double dividend = getDividendData(divFile, d);
                
                if (dividend == 0) {
                    std::cout << std::endl << "Something went wrong...\n";
                }
                
                Quote newQuote(open, close, high, low, volume, dividend, adjClose);

                stockVector->at(i).addDate(new Date(d, newQuote));
                delete d;
                
            } while (getline(stockFile, input));
        } else {
            std::cout
            << std::endl
            << "Error opening either stock or dividend file!";
        }
        stockFile.close();
    }
}

void assignExtQuoteData(std::vector<Stock>* stockVector,
                        std::string workingDirectory) {
    
    for (int i = 0; i < stockVector->size(); i++) {
        
        std::string symbol = stockVector->at(i).getSymbol();
    
        std::ifstream extFile(workingDirectory
                          + "ExtendedQuotes/" + symbol + "_ext.csv");
    
        if (extFile) {
            std::string input = "";
            getline(extFile, input);
            
            std::vector<std::string> stringVector = parseCSVLine(input);
            
            stockVector->at(i).
                updateCurrentData(new ExtQuote(&stockVector->at(i),
                                               stringVector));
            
        } else {
            std::cout
            << std::endl
            << "Could not open " << symbol << "_ext.csv!\n";
        }
    }
}



/********************************************************************* 
 ** Function: parseCSVLine
 ** Description: Takes a CSV line and separates the values, returning them as
 **     a vector of string objects.
 ** Parameters: a CSV string object
 ** Pre-Conditions: string is separated by commas
 ** Post-Conditions: N/A
 *********************************************************************/
std::vector<std::string> parseCSVLine (std::string someString) {
    std::vector<std::string> stringVector;
    std::string bufferString;
    for (int i=0; i < someString.size(); i++) {
        if (someString[i] != ',') {
            bufferString+=someString[i];
        } else {
            stringVector.push_back(bufferString);
            bufferString = "";
        }
    }
    if (bufferString != "") {
        stringVector.push_back(bufferString);
    }
    return stringVector;
}




/*********************************************************************
 ** Function: getDividendData
 ** Description: Searches a dividend file for the first line that corresponds
 **     to a date that is equal or before the year, month, day that is passed
 **     via int array pointer. The dividend that is parsed from that line is
 **     returned as a double.
 ** Parameters: address of filestream object, pointer to an int array
 ** Pre-Conditions: fileStream object is open, datePTR points to a valid date
 ** Post-Conditions: N/A
 *********************************************************************/
double getDividendData (std::ifstream &fileStream, Date * datePTR) {
    std::string line = "";
    std::string bufferedString = "";
    Date divDate;
    double dividend = 0.0;
    
    fileStream.seekg(std::ios::beg);
    //junk line
    getline(fileStream, line);
    
    line = "";
    
    while (getline(fileStream, line)) {
        
        //Grab first comma separated value, it should be the date of the line
        for (int i=0; line[i] != ','; i++) {
            bufferedString += line[i];
        }
        
        //pointer to an int[3] containing year, month, day
        Date divDate(bufferedString);
        
        
        bufferedString = "";
        
        //Since dates start from most recent going backwards, once you hit a
        //  date that was either the same day or before datePTR, you hit the
        //  appropriate dividend line
        if (divDate.operator<(*datePTR)) {
            //starting at where we left off (xxxx/xx/xx, plus ','
            for (int i=11; i < line.size(); i++) {
                bufferedString+=line[i];
            }
            dividend = stod(bufferedString);
            
            //datePTR->printDate();
            //std::cout << " ";
            //divDate->printDate();
            //std::cout << std::endl;
            
            if (dividend != 0) {
                break;
            }
            bufferedString = "";
        }
    }

    return dividend;
}


/*********************************************************************
 ** Function: paddedInteger
 ** Description: Takes an integer and makes it "wider" by adding zero's
 **     to the front via a string.
 ** Parameters: someInt, digitsWide
 ** Pre-Conditions: N/A
 ** Post-Conditions: integer becomes a string...
 *********************************************************************/
std::string paddedInteger (int someInt, int digitsWide) {
    std::string paddedString = std::to_string(someInt);
    while (paddedString.size() < digitsWide) {
        paddedString.insert(0, "0");
    }
    return paddedString;
}

void zoneMenu(std::vector<Stock>* stockVector, priceZone z, bool useAdjusted) {

    int order = 0;
    std::queue<Stock> q;
    
    std::string zone = "";
    if (z == 0) {zone = "green";}
    if (z == 1) {zone = "yellow";}
    
    std::cout << std::string(100, '\n');
    
    std::cout
    << std::endl
    << std::endl
    << stockVector->size() << " stocks in " << zone << " zone...\n"
    << "1. Sort by lowest price to desired price ratio\n"
    << "2. Sort by highest current dividend yield\n"
    << "3. Sort by worst price performance since last market bottom\n"
    << std::endl
    << "Enter # of order in which to display stocks: ";
    
    std::cin >> order;
    
    switch (order) {
        case 1: {
            std::vector<Stock> stocks;
            stocks.reserve(stockVector->size());
            copy(stockVector->begin(), stockVector->end(), back_inserter(stocks));
            int location = 0;
            double v1, v2;
            double ratio = 0.0;
            double lowestRatio = 1000000000;
            Stock * ptr = NULL;
            Stock * keeper = NULL;
            int k = (int)stocks.size();
            for (int i = 0; i < k; i++) {
                for (int j = 0; j < stocks.size(); j++) {
                    ptr = &(stocks.at(j));
                    v1 = ptr->getDateLatestQuote()->getQuote().getClose(useAdjusted);
                    v2 = ptr->getTargetPrice(useAdjusted);
                    ratio = v1/v2;
                    if (ratio < lowestRatio) {
                        lowestRatio = ratio;
                        keeper = ptr;
                        location = j;
                    }
                }
                q.push(*keeper);
                stocks.erase(stocks.begin() + location);
                lowestRatio = 1000000000;
            }
            
            while (!q.empty()) {
                std::cout << q.front().getSymbol() << std::endl;
                q.pop();
            }
            
        }
            
    }
}



std::vector<Stock>* getStocksInZone(std::vector<Stock>* stockVector, priceZone z, bool useAdjusted) {
    
    std::vector<Stock>* stocksInZone = new std::vector<Stock>;
    
    for (int i = 0; i < stockVector->size(); i++) {
        
        Stock s = stockVector->at(i);
        
        double divYield = s.getDateLatestQuote()->getQuote().getDividendYield(false);
        
        double payoutRatio = (s.getDateLatestQuote()->getQuote().getDividend() * 4) /
                                s.getCurrentData()->ePSEstimateCurrentYear;
        
        if (divYield > .02) {
            if (payoutRatio <= .6) {
                priceZone zone = s.getZone(s.getDateLatestQuote(), useAdjusted);
                
                if (zone == z) {
                    stocksInZone->push_back(s);
                }

            } else {
                /*std::cout
                << std::endl
                << s.getSymbol() << "'s payout ratio is "
                << payoutRatio << ", which is > .6"
                << std::endl;*/
            }
        } else {
            /*std::cout
            << std::endl
            << s.getSymbol() << "'s dividend yield is "
            << divYield << ", which is < .02"
            << std::endl;*/
        }
        
    }
    return stocksInZone;
}

