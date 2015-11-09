//
//  Quote.cpp
//  StockPicker
//
//  Created by Jason McAnally on 3/26/15.
//  Copyright (c) 2015 Jason McAnally. All rights reserved.
//

#include "Quote.h"

//Default constructor
Quote::Quote() {
    open = 0.0;
    close = 0.0;
    high = 0.0;
    low = 0.0;
    dividend = 0.0;
    volume = 0;
    aOpen = 0.0;
    aClose = 0.0;
    aHigh = 0.0;
    aLow = 0.0;
}

//Constructor
Quote::Quote(double o, double c, double h, double l,
             int vol, double div, double adjClose) {
    open = o;
    close = c;
    high = h;
    low = l;
    volume = vol;
    dividend = div;
    aClose = adjClose;
    aOpen = open * (aClose/close);
    aHigh = high * (aClose/close);
    aLow = low * (aClose/close);
}

//Standard get functions
double Quote::getOpen(bool useAdjusted) {
    if (useAdjusted)
        return open * (aClose/close);
    else
        return open;
}
double Quote::getClose(bool useAdjusted) {
    if (useAdjusted)
        return aClose;
    else
        return close;
}
double Quote::getHigh(bool useAdjusted) {
    if (useAdjusted)
        return high * (aClose/close);
    else
        return high;
}
double Quote::getLow(bool useAdjusted) {
    if (useAdjusted)
        return low * (aClose/close);
    else
        return low;
}

double Quote::getDividend() {
    return dividend;
}
double Quote::getDividendYield(bool useAdjusted) {
    return (dividend * 4) / getClose(useAdjusted);
}
int Quote::getVolume() {
    return volume;
}
