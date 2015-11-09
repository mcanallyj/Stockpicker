//
//  Quote.h
//  StockPicker
//
//  Created by Jason McAnally on 3/26/15.
//  Copyright (c) 2015 Jason McAnally. All rights reserved.
//

#ifndef __StockPicker__Quote__
#define __StockPicker__Quote__


class Date;

class Quote {
private:
    double open,
            close,
            high,
            low,
            dividend;
    
    double aOpen,
            aHigh,
            aLow,
            aClose;
    
    
    int volume;
    
public:
    Quote();
    Quote(double o, double c, double h, double l,
          int vol, double div, double adjClose);
    double getOpen(bool useAdjusted);
    double getClose(bool useAdjusted);
    double getHigh(bool useAdjusted);
    double getLow(bool useAdjusted);
    double getDividend();
    double getDividendYield(bool useAdjusted);
    int getVolume();
};


#endif /* defined(__StockPicker__Quote__) */
