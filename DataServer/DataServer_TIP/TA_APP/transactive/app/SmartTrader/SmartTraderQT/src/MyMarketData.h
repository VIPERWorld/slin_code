#ifndef __CLASS_MY_MARKET_DATA_H__
#define __CLASS_MY_MARKET_DATA_H__

#include <string>

class CMyMarketData
{
public:
	enum MarketStatus
	{
		PRE_OPEN = 48,
		OPENED,
		PRE_CLOSE,
		CLOSED,
		SUSPENDED,
	};

	enum PriceType
	{
		OPENNING_PRICE = 0,
		SESSION_HIGH,
		SESSION_LOW,
		REFERENCE_PRICE,
		YESTERDAY_SETTLMENT_PRICE,
		LAST_TRADED_PRICE,
		SETTLEMENT_PRICE,
	};

	enum VolumeType
	{
		OPEN_INTEREST = 0,
		OPENING_VOLUME,
		LAST_TRADED_VOLUME,
		TOTAL_TRADED_VOLUME,
	};

	CMyMarketData();
	CMyMarketData(unsigned int secID);
	~CMyMarketData();

	CMyMarketData(const CMyMarketData &);
	CMyMarketData & operator= (const CMyMarketData &);

	void setSecurityID(unsigned int secID);
	unsigned int getSecurityID() const;

	int getMarketStatus() const;
	unsigned int getTime() const;

	int getVolume(int type) const;//enum VolumeType
	int getBidVol(int level) const;
	int getAskVol(int level) const;

	float getPrice(int type) const;//enum PriceType
	float getBidPx(int level) const;
	float getAskPx(int level) const;

	unsigned int getDataBits() const;
	unsigned int getChangeBits() const;
public:
	void setValue(const std::string& strData);
private:
	unsigned int m_nSecurityID;
	int m_nMarketStatus;
	unsigned int m_nTime;
	int m_nVolume_OPEN_INTEREST;
	int m_nVolume_OPENING_VOLUME;
	int m_nVolume_LAST_TRADED_VOLUME;
	int m_nVolume_TOTAL_TRADED_VOLUME;
	int m_nBidVol;
	int m_nAskVol;
	float m_fPrice_OPENNING_PRICE;
	float m_fPrice_SESSION_HIGH;
	float m_fPrice_SESSION_LOW;
	float m_fPrice_REFERENCE_PRICE;
	float m_fPrice_YESTERDAY_SETTLMENT_PRICE;
	float m_fPrice_LAST_TRADED_PRICE;
	float m_fPrice_SETTLEMENT_PRICE;
	float m_fBidPx;
	float m_fAskPx;
	unsigned int m_nDataBits;
	unsigned int m_nChangeBits;

};


#endif //__CLASS_MY_MARKET_DATA_H__

