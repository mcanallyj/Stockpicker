//
//  ExtQuote.cpp
//  StockPicker
//
//  Created by Jason McAnally on 7/12/15.
//  Copyright (c) 2015 Jason McAnally. All rights reserved.
//

#include "ExtQuote.h"
#include <cstdlib>
#include "Stock.h"
#include "Date.h"

ExtQuote::ExtQuote() {
    
}

ExtQuote::ExtQuote(Stock* stock, std::vector<std::string>& s) {
    if (s[0] == "N/A") {
        afterHoursChangeRealtime = 0;
    } else {
        afterHoursChangeRealtime = atof(s[0].c_str());
    }
    
    
    if (s[1] == "N/A") {
        annualizedGain = 0;
    } else {
        annualizedGain = atof(s[1].c_str());
    }
    
    if (s[2] == "N/A") {
        ask = 0;
    } else {
        ask = atof(s[2].c_str());
    }
    
    if (s[3] == "N/A") {
        askRealtime = 0;
    } else {
        askRealtime = atof(s[3].c_str());
    }
    
    
    if (s[4] == "N/A") {
        askSize = 0;
    } else {
        askSize = atof(s[4].c_str());
    }
    
    if (s[5] == "N/A") {
        averageDailyVolume = 0;
    } else {
        averageDailyVolume = atof(s[5].c_str());
    }
    
    if (s[6] == "N/A") {
        bid = 0;
    } else {
        bid = atof(s[6].c_str());
    }
    
    if (s[7] == "N/A") {
        bidRealtime = 0;
    } else {
        bidRealtime = atof(s[7].c_str());
    }
    
    if (s[8] == "N/A") {
        bidSize = 0;
    } else {
        bidSize = atof(s[8].c_str());
    }
    
    if (s[9] == "N/A") {
        bookValuePerShare = 0;
    } else {
        bookValuePerShare = atof(s[9].c_str());
    }
    
    if (s[10] == "N/A") {
        change = 0;
    } else {
        change = atof(s[10].c_str());
    }
    
    if (s[11] == "N/A") {
        change_ChangeInPercent = 0;
    } else {
        change_ChangeInPercent = atof(s[11].c_str());
    }
    
    if (s[12] == "N/A") {
        changeFromFiftydayMovingAverage = 0;
    } else {
        changeFromFiftydayMovingAverage = atof(s[12].c_str());
    }
    
    if (s[13] == "N/A") {
        changeFromTwoHundreddayMovingAverage = 0;
    } else {
        changeFromTwoHundreddayMovingAverage = atof(s[13].c_str());
    }
    
    if (s[14] == "N/A") {
        changeFromYearHigh = 0;
    } else {
        changeFromYearHigh = atof(s[14].c_str());
    }
    
    if (s[15] == "N/A") {
        changeFromYearLow = 0;
    } else {
        changeFromYearLow = atof(s[15].c_str());
    }
    
    if (s[16] == "N/A") {
        changeInPercent = 0;
    } else {
        changeInPercent = atof(s[16].c_str());
    }
    
    if (s[17] == "N/A") {
        changeInPercentRealtime = 0;
    } else {
        changeInPercentRealtime = atof(s[17].c_str());
    }
    
    if (s[18] == "N/A") {
        changeRealtime = 0;
    } else {
        changeRealtime = atof(s[18].c_str());
    }
    
    
    if (s[19] == "N/A") {
        commission = 0;
    } else {
        commission = atof(s[19].c_str());
    }
    
    
    if (s[20] == "N/A") {
        daysHigh = 0;
    } else {
        daysHigh = atof(s[20].c_str());
    }
    
    
    if (s[21] == "N/A") {
        daysLow = 0;
    } else {
        daysLow = atof(s[21].c_str());
    }
    
    
    if (s[22] == "N/A") {
        daysRange = 0;
    } else {
        daysRange = atof(s[22].c_str());
    }
    
    if (s[23] == "N/A") {
        daysRangeRealtime = 0;
    } else {
        daysRangeRealtime = atof(s[23].c_str());
    }
    
    
    if (s[24] == "N/A") {
        trailingAnnualDividendYield = 0;
    } else {
        trailingAnnualDividendYield = atof(s[24].c_str());
    }
    
    
    if (s[25] == "N/A") {
        trailingAnnualDividendYieldInPercent = 0;
    } else {
        trailingAnnualDividendYieldInPercent = atof(s[25].c_str());
    }
    
    
    if (s[26] == "N/A") {
        dilutedEPS = 0;
    } else {
        dilutedEPS = atof(s[26].c_str());
    }
    
    
    if (s[27] == "N/A") {
        eBITDA = 0;
    } else {
        eBITDA = atof(s[27].c_str());
    }
    
    
    if (s[28] == "N/A") {
        ePSEstimateCurrentYear = 0;
    } else {
        ePSEstimateCurrentYear = atof(s[28].c_str());
    }
    
    
    if (s[29] == "N/A") {
        ePSEstimateNextQuarter = 0;
    } else {
        ePSEstimateNextQuarter = atof(s[29].c_str());
    }
    
    if (s[30] == "N/A") {
        ePSEstimateNextYear = 0;
    } else {
        ePSEstimateNextYear = atof(s[30].c_str());
    }
    
    if (s[31] == "N/A") {
        fiftydayMovingAverage = 0;
    } else {
        fiftydayMovingAverage = atof(s[31].c_str());
    }
    
    if (s[32] == "N/A") {
        highLimit = 0;
    } else {
        highLimit = atof(s[32].c_str());
    }
    
    if (s[33] == "N/A") {
        holdingsGain = 0;
    } else {
        holdingsGain = atof(s[33].c_str());
    }
    
    if (s[34] == "N/A") {
        holdingsGainPercent = 0;
    } else {
        holdingsGainPercent = atof(s[34].c_str());
    }
    
    if (s[35] == "N/A") {
        holdingsGainPercentRealtime = 0;
    } else {
        holdingsGainPercentRealtime = atof(s[35].c_str());
    }
    
    if (s[36] == "N/A") {
        holdingsGainRealtime = 0;
    } else {
        holdingsGainRealtime = atof(s[36].c_str());
    }
    
    if (s[37] == "N/A") {
        holdingsValue = 0;
    } else {
        holdingsValue = atof(s[37].c_str());
    }
    
    if (s[38] == "N/A") {
        holdingsValueRealtime = 0;
    } else {
        holdingsValueRealtime = atof(s[38].c_str());
    }
    
    if (s[39] == "N/A") {
        lastTradePriceOnly = 0;
    } else {
        lastTradePriceOnly = atof(s[39].c_str());
    }
    
    if (s[40] == "N/A") {
        lastTradeSize = 0;
    } else {
        lastTradeSize = atof(s[40].c_str());
    }
    
    
    if (s[41] == "N/A") {
        lastTradeTime = 0;
    } else {
        lastTradeTime = atof(s[41].c_str());
    }
    
    
    if (s[42] == "N/A") {
        lowLimit = 0;
    } else {
        lowLimit = atof(s[42].c_str());
    }
    
    
    if (s[43] == "N/A") {
        marketCapitalization = 0;
    } else {
        marketCapitalization = atof(s[43].c_str());
    }
    
    
    if (s[44] == "N/A") {
        marketCapRealtime = 0;
    } else {
        marketCapRealtime = atof(s[44].c_str());
    }
    
    
    if (s[45] == "N/A") {
        oneyrTargetPrice = 0;
    } else {
        oneyrTargetPrice = atof(s[45].c_str());
    }
    
    
    if (s[46] == "N/A") {
        open = 0;
    } else {
        open = atof(s[46].c_str());
    }
    
    
    if (s[47] == "N/A") {
        orderBookRealtime = 0;
    } else {
        orderBookRealtime = atof(s[47].c_str());
    }
    
    
    if (s[48] == "N/A") {
        pEGRatio = 0;
    } else {
        pEGRatio = atof(s[48].c_str());
    }
    
    
    if (s[49] == "N/A") {
        pERatio = 0;
    } else {
        pERatio = atof(s[49].c_str());
    }
    
    
    if (s[50] == "N/A") {
        pERatioRealtime = 0;
    } else {
        pERatioRealtime = atof(s[50].c_str());
    }
    
    
    if (s[51] == "N/A") {
        percentChangeFromFiftydayMovingAverage = 0;
    } else {
        percentChangeFromFiftydayMovingAverage = atof(s[51].c_str());
    }
    
    if (s[52] == "N/A") {
        percentChangeFromTwoHundreddayMovingAverage = 0;
    } else {
        percentChangeFromTwoHundreddayMovingAverage = atof(s[52].c_str());
    }
    
    if (s[53] == "N/A") {
        changeInPercentFromYearHigh = 0;
    } else {
        changeInPercentFromYearHigh = atof(s[53].c_str());
    }
    
    if (s[54] == "N/A") {
        percentChangeFromYearLow = 0;
    } else {
        percentChangeFromYearLow = atof(s[54].c_str());
    }

    if (s[55] == "N/A") {
        previousClose = 0;
    } else {
        previousClose = atof(s[55].c_str());
    }
    
    if (s[56] == "N/A") {
        priceBook = 0;
    } else {
        priceBook = atof(s[56].c_str());
    }
    
    if (s[57] == "N/A") {
        priceEPSEstimateCurrentYear = 0;
    } else {
        priceEPSEstimateCurrentYear = atof(s[57].c_str());
    }
    
    if (s[58] == "N/A") {
        priceEPSEstimateNextYear = 0;
    } else {
        priceEPSEstimateNextYear = atof(s[58].c_str());
    }
    
    if (s[59] == "N/A") {
        pricePaid = 0;
    } else {
        pricePaid = atof(s[59].c_str());
    }
    
    if (s[60] == "N/A") {
        priceSales = 0;
    } else {
        priceSales = atof(s[60].c_str());
    }
    
    if (s[61] == "N/A") {
        revenue = 0;
    } else {
        revenue = atof(s[61].c_str());
    }
    
    if (s[62] == "N/A") {
        shortRatio = 0;
    } else {
        shortRatio = atof(s[62].c_str());
    }
    
    if (s[63] == "N/A") {
        twoHundreddayMovingAverage = 0;
    } else {
        twoHundreddayMovingAverage = atof(s[63].c_str());
    }
    
    if (s[64] == "N/A") {
        yearHigh = 0;
    } else {
        yearHigh = atof(s[64].c_str());
    }
    
    if (s[65] == "N/A") {
        yearLow = 0;
    } else {
        yearLow = atof(s[65].c_str());
    }
    
    if (s[66] == "N/A") {
        yearRange = 0;
    } else {
        yearRange = atof(s[66].c_str());
    }
    
    if (s[67] == "N/A") {
        currency = "";
    } else {
        currency = s[67];
    }
    
    if (s[68] == "N/A") {
        name = "";
    } else {
        name = s[68];
    }

    
    if (s[69] == "N/A") {
        notes = "";
    } else {
        notes = s[69];
    }
    
    if (s[70] == "N/A") {
        stockExchange = "";
    } else {
        stockExchange = s[70];
    }
    
    if (s[71] == "N/A") {
        symbol = "";
    } else {
        symbol = s[71];
    }
    
    if (s[72] == "N/A") {
        tickerTrend = "";
    } else {
        tickerTrend = s[72];
    }
    
    if (s[73] == "N/A") {
        tradeData = "";
    } else {
        tradeData = s[73];
    }
    
    if (s[74] == "N/A") {
        tradeLinks = "";
    } else {
        tradeLinks = s[74];
    }
    
    if (s[75] == "N/A") {
        tradeLinksAdditional = "";
    } else {
        tradeLinksAdditional = s[75];
    }
    
    if (s[76] == "N/A") {
        dividendPayDate = NULL;
    } else {
        dividendPayDate = stock->getDate(new Date(s[76]));
    }
    
    if (s[77] == "N/A") {
        exDividendDate = NULL;
    } else {
        exDividendDate = stock->getDate(new Date(s[77]));
    }
    
    if (s[78] == "N/A") {
        lastTradeDate = NULL;
    } else {
        lastTradeDate = stock->getDate(new Date(s[78]));
    }
    
    if (s[79] == "N/A") {
        sharesOwned = 0;
    } else {
        sharesOwned = atol(s[79].c_str());
    }
    
    if (s[80] == "N/A") {
        sharesOutstanding = 0;
    } else {
        sharesOutstanding = atol(s[80].c_str());
    }
    
    if (s[81] == "N/A") {
        volume = 0;
    } else {
        volume = atol(s[81].c_str());
    }
}


ExtQuote::ExtQuote(double pAfterHoursChangeRealtime,
         double pAnnualizedGain,
         double pAsk,
         double pAskRealtime,
         double pAskSize,
         double pAverageDailyVolume,
         double pBid,
         double pBidRealtime,
         double pBidSize,
         double pBookValuePerShare,
         double pChange,
         double pChange_ChangeInPercent,
         double pChangeFromFiftydayMovingAverage,
         double pChangeFromTwoHundreddayMovingAverage,
         double pChangeFromYearHigh,
         double pChangeFromYearLow,
         double pChangeInPercent,
         double pChangeInPercentRealtime,
         double pChangeRealtime,
         double pCommission,
         double pDaysHigh,
         double pDaysLow,
         double pDaysRange,
         double pDaysRangeRealtime,
         double pTrailingAnnualDividendYield,
         double pTrailingAnnualDividendYieldInPercent,
         double pDilutedEPS,
         double pEBITDA,
         double pEPSEstimateCurrentYear,
         double pEPSEstimateNextQuarter,
         double pEPSEstimateNextYear,
         double pFiftydayMovingAverage,
         double pHighLimit,
         double pHoldingsGain,
         double pHoldingsGainPercent,
         double pHoldingsGainPercentRealtime,
         double pHoldingsGainRealtime,
         double pHoldingsValue,
         double pHoldingsValueRealtime,
         double pLastTradePriceOnly,
         double pLastTradeSize,
         double pLastTradeTime,
         double pLowLimit,
         double pMarketCapitalization,
         double pMarketCapRealtime,
         double pOneyrTargetPrice,
         double pOpen,
         double pOrderBookRealtime,
         double pPEGRatio,
         double pPERatio,
         double pPERatioRealtime,
         double pPercentChangeFromFiftydayMovingAverage,
         double pPercentChangeFromTwoHundreddayMovingAverage,
         double pChangeInPercentFromYearHigh,
         double pPercentChangeFromYearLow,
         double pPreviousClose,
         double pPriceBook,
         double pPriceEPSEstimateCurrentYear,
         double pPriceEPSEstimateNextYear,
         double pPricePaid,
         double pPriceSales,
         double pRevenue,
         double pShortRatio,
         double pTwoHundreddayMovingAverage,
         double pYearHigh,
         double pYearLow,
         double pYearRange,
         std::string pCurrency,
         std::string pName,
         std::string pNotes,
         std::string pStockExchange,
         std::string pSymbol,
         std::string pTickerTrend,
         std::string pTradeData,
         std::string pTradeLinks,
         std::string pTradeLinksAdditional,
         Date* pDividendPayDate,
         Date* pExDividendDate,
         Date* pLastTradeDate,
         long pSharesOwned,
         long pSharesOutstanding,
         long pVolume
         ) {
    afterHoursChangeRealtime = pAfterHoursChangeRealtime;
    annualizedGain = pAnnualizedGain;
    ask = pAsk;
    askRealtime = pAskRealtime;
    askSize = pAskSize;
    averageDailyVolume = pAverageDailyVolume;
    bid = pBid;
    bidRealtime = pBidRealtime;
    bidSize = pBidSize;
    bookValuePerShare = pBookValuePerShare;
    change = pChange;
    change_ChangeInPercent = pChange_ChangeInPercent;
    changeFromFiftydayMovingAverage = pChangeFromFiftydayMovingAverage;
    changeFromTwoHundreddayMovingAverage = pChangeFromTwoHundreddayMovingAverage;
    changeFromYearHigh = pChangeFromYearHigh;
    changeFromYearLow = pChangeFromYearLow;
    changeInPercent = pChangeInPercent;
    changeInPercentRealtime = pChangeInPercentRealtime;
    changeRealtime = pChangeRealtime;
    commission = pCommission;
    daysHigh = pDaysHigh;
    daysLow = pDaysLow;
    daysRange = pDaysRange;
    daysRangeRealtime = pDaysRangeRealtime;
    trailingAnnualDividendYield = pTrailingAnnualDividendYield;
    trailingAnnualDividendYieldInPercent = pTrailingAnnualDividendYieldInPercent;
    dilutedEPS = pDilutedEPS;
    eBITDA = pEBITDA;
    ePSEstimateCurrentYear = pEPSEstimateCurrentYear;
    ePSEstimateNextQuarter = pEPSEstimateNextQuarter;
    ePSEstimateNextYear = pEPSEstimateNextYear;
    fiftydayMovingAverage = pFiftydayMovingAverage;
    highLimit = pHighLimit;
    holdingsGain = pHoldingsGain;
    holdingsGainPercent = pHoldingsGainPercent;
    holdingsGainPercentRealtime = pHoldingsGainPercentRealtime;
    holdingsGainRealtime = pHoldingsGainRealtime;
    holdingsValue = pHoldingsValue;
    holdingsValueRealtime = pHoldingsValueRealtime;
    lastTradePriceOnly = pLastTradePriceOnly;
    lastTradeSize = pLastTradeSize;
    lastTradeTime = pLastTradeTime;
    lowLimit = pLowLimit;
    marketCapitalization = pMarketCapitalization;
    marketCapRealtime = pMarketCapRealtime;
    oneyrTargetPrice = pOneyrTargetPrice;
    open = pOpen;
    orderBookRealtime = pOrderBookRealtime;
    pEGRatio = pPEGRatio;
    pERatio = pPERatio;
    pERatioRealtime = pPERatioRealtime;
    percentChangeFromFiftydayMovingAverage = pPercentChangeFromFiftydayMovingAverage;
    percentChangeFromTwoHundreddayMovingAverage = pPercentChangeFromTwoHundreddayMovingAverage;
    changeInPercentFromYearHigh = pChangeInPercentFromYearHigh;
    percentChangeFromYearLow = pPercentChangeFromYearLow;
    previousClose = pPreviousClose;
    priceBook = pPriceBook;
    priceEPSEstimateCurrentYear = pPriceEPSEstimateCurrentYear;
    priceEPSEstimateNextYear = pPriceEPSEstimateNextYear;
    pricePaid = pPricePaid;
    priceSales = pPriceSales;
    revenue = pRevenue;
    shortRatio = pShortRatio;
    twoHundreddayMovingAverage = pTwoHundreddayMovingAverage;
    yearHigh = pYearHigh;
    yearLow = pYearLow;
    yearRange = pYearRange;
    currency = pCurrency;
    name = pName;
    notes = pNotes;
    stockExchange = pStockExchange;
    symbol = pSymbol;
    tickerTrend = pTickerTrend;
    tradeData = pTradeData;
    tradeLinks = pTradeLinks;
    tradeLinksAdditional = pTradeLinksAdditional;
}

