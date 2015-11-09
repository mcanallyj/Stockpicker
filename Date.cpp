//
//  Date.cpp
//  StockPicker
//
//  Created by Jason McAnally on 3/25/15.
//  Copyright (c) 2015 Jason McAnally. All rights reserved.
//

#include "Date.h"
#include <ctime>
#include <iostream>

//Default constructor
Date::Date() {
    year = 1900;
    month = 0;
    day = 1;
}

Date::Date(std::string s) {
    int* temp = parseDate(s);
    year = temp[0];
    month = temp[1];
    day = temp[2];
    delete temp;
}

Date::Date(int someYear, int someMonth, int someDay) {
    //creating time object "now", ltm is a pointer to a tm object initialized to current local time
    time_t now = time(0);
    struct tm ltm;
    localtime_r(&now, &ltm);
    int yr = 1900 + ltm.tm_year;

    
    //if parameter year is after 1900 and is not in the future...
    if (someYear > 1900 && someYear <= yr) {
        
        year = someYear; //set parameter year as year
        
        //if parameter day is positive...
        if (someDay > 0) {
            
            switch (someMonth) {
                case 0: { //parameter Month is January
                    month = someMonth;
                    if (someDay <= 31) { //31 days in January
                        day = someDay;
                        break;
                    } else {
                        std::cout << std::endl << "Day is invalid\n";
                        return;
                    }
                }
                case 1: { //parameter Month is February
                    month = someMonth;
                    if (someYear % 4 == 0 && someDay <= 29) { //leap year has 29 days in February
                        day = someDay;
                        break;
                    } else if (someYear % 4 != 0 && someDay <= 28) { //non-leap year has 28 days in February
                        day = someDay;
                        break;
                    } else {
                        std::cout << std::endl << "Day is invalid\n";
                        return;
                    }
                }
                case 2: { //parameter Month is March
                    month = someMonth;
                    if (someDay <= 31) { //31 days in March
                        day = someDay;
                        break;
                    } else {
                        std::cout << std::endl << "Day is invalid\n";
                        return;
                    }
                }
                case 3: { //parameter Month is April
                    month = someMonth;
                    if (someDay <= 30) { //30 days in April
                        day = someDay;
                        break;
                    } else {
                        std::cout << std::endl << "Day is invalid\n";
                        return;
                    }
                }
                case 4: { //parameter Month is May
                    month = someMonth;
                    if (someDay <= 31) { //31 days in May
                        day = someDay;
                        break;
                    } else {
                        std::cout << std::endl << "Day is invalid\n";
                        return;
                    }
                }
                case 5: { //parameter Month is June
                    month = someMonth;
                    if (someDay <= 30) { //30 days in June
                        day = someDay;
                        break;
                    } else {
                        std::cout << std::endl << "Day is invalid\n";
                        return;
                    }
                }
                case 6: { //parameter Month is July
                    month = someMonth;
                    if (someDay <= 31) { //31 days in July
                        day = someDay;
                        break;
                    } else {
                        std::cout << std::endl << "Day is invalid\n";
                        return;
                    }
                }
                case 7: { //parameter Month is August
                    month = someMonth;
                    if (someDay <= 31) { //31 days in August
                        day = someDay;
                        break;
                    } else {
                        std::cout << std::endl << "Day is invalid\n";
                        return;
                    }
                }
                case 8: { //parameter Month is September
                    month = someMonth;
                    if (someDay <= 30) { //30 days in September
                        day = someDay;
                        break;
                    } else {
                        std::cout << std::endl << "Day is invalid\n";
                        return;
                    }
                }
                case 9: { //parameter Month is October
                    month = someMonth;
                    if (someDay <= 31) { //31 days in October
                        day = someDay;
                        break;
                    } else {
                        std::cout << std::endl << "Day is invalid\n";
                        return;
                    }
                }
                case 10: { //parameter Month is November
                    month = someMonth;
                    if (someDay <= 30) { //30 days in November
                        day = someDay;
                        break;
                    } else {
                        std::cout << std::endl << "Day is invalid\n";
                        return;
                    }
                }
                case 11: { //parameter Month is December
                    month = someMonth;
                    if (someDay <= 31) { //31 days in December
                        day = someDay;
                        break;
                    } else {
                        std::cout << std::endl << "Day is invalid\n";
                        return;
                    }
                }
                default: { //parameter month is not 0-11
                    std::cout << std::endl << "Month is invalid\n";
                    return;
                }
            }
        } else { //parameter day is not positive
            std::cout << std::endl << "Day is invalid\n";
            return;
        }
        
    } else { //parameter year is before 1900 or in the future
        std::cout << std::endl << "Year is invalid\n";
        return;
    }
}



//Constructor
Date::Date(Date* someDate, Quote someQuote) {
    year = someDate->getYear();
    month = someDate->getMonth();
    day = someDate->getDay();
    dayQuote = someQuote;
}

int Date::Compare(const Date &d) const {
    if (year > d.year) {
        return 1;
    } else if (year < d.year) {
        return -1;
    } else {
        if (month > d.month) {
            return 1;
        } else if (month < d.month) {
            return -1;
        } else {
            if (day > d.day) {
                return 1;
            } else if (day < d.day) {
                return -1;
            } else {
                return 0;
            }
        }
    }
}

bool Date::operator==(const Date &d) const {
    return (Compare(d)==0);
}

bool Date::operator<(const Date &d) const {
    return (Compare(d)==-1);
}

bool Date::operator>(const Date &d) const {
    return (Compare(d)==1);
}

//standard get function
Quote Date::getQuote() {
    return dayQuote;
}

int Date::getYear() const{
    return year;
}

int Date::getMonth() const{
    return month;
}

int Date::getDay() const{
    return day;
}

void Date::setQuote(Quote someQuote) {
    dayQuote = someQuote;
}

std::string Date::getDateString() const {
    std::string dateString = std::to_string(year)
                            + " " + std::to_string(month)
                            + " " + std::to_string(day);
    return dateString;
}

/*********************************************************************
 ** Function: parseDate
 ** Description: Takes a string object that should correspond to a date, parses
 **     it such that it returns an integer array which gives the year, month and
 **     day as elements 0, 1 and 2
 ** Parameters: a string object
 ** Pre-Conditions: string object is formatted as xxxx-xx-xx
 ** Post-Conditions: N/A
 *********************************************************************/
int* Date::parseDate (std::string someString) {
    std::string bufferInt = "";
    int* d = new int[3];
    int counter = 0;
    bool bufferRemaining = false;
    
    for (int i = 0; i < someString.size(); i++) {
        //good stuff for buffer
        if (someString[i] != '-') {
            bufferInt+=someString[i];
            bufferRemaining = true;
        } else
            //just hit a '-', flush buffer to date[counter]
        {
            d[counter] = atoi(bufferInt.c_str());
            bufferInt = "";
            bufferRemaining = false;
            counter++;
        }
        
    }
    
    if (bufferRemaining) {
        d[counter] = atoi(bufferInt.c_str());
    }
    
    return d;
}

