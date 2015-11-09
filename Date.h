//
//  Date.h
//  StockPicker
//
//  Created by Jason McAnally on 3/25/15.
//  Copyright (c) 2015 Jason McAnally. All rights reserved.
//

#ifndef __StockPicker__Date__
#define __StockPicker__Date__

#include <stdio.h>
#include <string>
#include <cstdlib>
#include "Quote.h"


class Quote;
class ExtQuote;
class Stock;

class Date {
private:
    int year;
    int month;
    int day;
    Quote dayQuote;
    
    
public:
    Date();
    Date(std::string s);
    Date(int someYear, int someMonth, int someDay);
    Date(Date* someDate, Quote someQuote);
    int Compare(const Date &d) const;
    bool operator==(const Date &d) const;
    bool operator<(const Date &d) const;
    bool operator>(const Date &d) const;
    Quote getQuote();
    void setQuote(Quote someQuote);
    int getYear() const;
    int getMonth() const;
    int getDay() const;
    std::string getDateString() const;
    int* parseDate (std::string someString);
};


#endif /* defined(__StockPicker__Date__) */
