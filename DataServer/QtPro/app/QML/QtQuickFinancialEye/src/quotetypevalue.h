#ifndef QUOTETYPEVALUE_H
#define QUOTETYPEVALUE_H

#include <QObject>

#if QT_VERSION < 0x050000
    // Qt 4.x.x
    #include <QtDeclarative>
#else
    // Qt 5.x.x
    #include <QtQml/QtQml>
#endif

class QuoteTypeValue : public QObject
{
    Q_OBJECT
public:
    explicit QuoteTypeValue(QObject *parent = 0);

signals:

public slots:
public:
    //! \brief Quote types
       enum EnStyleQuoteType
       {
           ask, // a
           averageDailyVolume, // a2
           askSize, // a5
           bid, // b
           askRealTime, // b2
           bidRealTime, // b3
           bookValue, // b4
           bidSize, // b6
           changeAndPercentChange, // c
           change, // c1
           commission, // c3
           changeRealTime, // c6
           afterHoursChangeRealTime, // c8
           dividendShare, // d
           lastTradeDate, // d1
           tradeDate, // d2
           earningsShare, // e
           errorIndication, // e1 (returned for symbol changed / invalid)
           epsEstimateCurrentYear, // e7
           epsEstimateNextYear, // e8
           epsEstimateNextQuarter, // e9
           floatShares, // f6
           dayLow, // g
           dayHigh, // h
           _52WeekLow, // j
           _52WeekHigh, // k
           holdingsGainPercent, // g1
           annualizedGain, // g3
           holdingsGain, // g4
           holdingsGainPercentRealTime, // g5
           holdingsGainRealTime, // g6
           moreInfo, // i
           orderBookRealTime, // i5
           marketCapitalization, // j1
           marketCapRealTime, // j3
           ebitda, // j4
           changeFrom52WeekLow, // j5
           percentChangeFrom52WeekLow, // j6
           lastTradeRealTimeWithTime, // k1
           changePercentRealTime, // k2
           lastTradeSize, // k3
           changeFrom52WeekHigh, // k4
           percebtChangeFrom52WeekHigh, // k5
           lastTradeWithTime, // l
           lastTradePriceOnly, // l1
           highLimit, // l2
           lowLimit, // l3
           dayRange, // m
           dayRangeRealTime, // m2
           _50DayMovingAverage, // m3
           _200DayMovingAverage, // m4
           changeFrom200DayMovingAverage, // m5
           percentChangeFrom200DayMovingAverage, // m6
           changeFrom50DayMovingAverage, // m7
           percentChangeFrom50DayMovingAverage, // m8
           name, // n
           notes, // n4
           open, // o
           previousClose, // p
           pricePaid, // p1
           changeinPercent, // p2
           priceSales, // p5
           priceBook, // p6
           exDividendDate, // q
           peRatio, // r
           dividendPayDate, // r1
           peRatioRealTime, // r2
           pegRatio, // r5
           priceEpsEstimateCurrentYear, // r6
           priceEpsEstimateNextYear, // r7
           symbol, // s
           sharesOwned, // s1
           shortRatio, // s7
           lastTradeTime, // t1
           tradeLinks, // t6
           tickerTrend, // t7
           _1yrTargetPrice, // t8
           volume, // v
           holdingsValue, // v1
           holdingsValueRealTime, // v7
           _52WeekRange, // w
           dayValueChange, // w1
           dayValueChangeRealTime, // w4
           stockExchange, // x
           dividendYield  // y
       };
       Q_ENUMS(EnStyleQuoteType)



       // Do not forget to declare your class to the QML system.
       static void declareQML();


};

#endif // QUOTETYPEVALUE_H
