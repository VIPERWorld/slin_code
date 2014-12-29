#ifndef __CLASS_MY_INSTRUMENT_HH__
#define __CLASS_MY_INSTRUMENT_HH__

//qt sys
#include <QtCore/QChar>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>



class CStockData;
class CMyMarketData;
class CHistoryData;

class CMyInstrument
{ 
public: 
	CMyInstrument();
	virtual ~CMyInstrument(); 
public: 
	CMyInstrument& operator=(const CMyInstrument& objCopy);

public: 
	/// Get the unique ID of the instrument
	virtual unsigned int getInstrumentID() const;

	/// Get the unique name of the instrument
	virtual const std::string & getInstrumentCode() const;

	/// Get the unique name of the underlying of the instrument
	virtual const std::string & getUnderlyingCode() const;

	/// Get the unique name of the exchange of the instrument
	virtual const std::string & getExchangeName() const;

	/// Get the decimal place of the instrument
	virtual char getDecimalPlace() const;

	/// Get the tick size of the instrument
	virtual float getTickSize() const;

	/// Get the tick value of the instrument
	virtual float getTickValue() const;

	/// Get current best bid volume 
	virtual int getBidVolume() const;

	/// Get the current best ask volume
	virtual int getAskVolume() const;

	/// Get the last traded volume
	virtual int getLastVolume() const;

	/// Get the total traded volume intra day
	virtual int getTotalVolume() const;

	/// Get current best bid price
	virtual float getBidPrice() const;

	/// Get current best ask price
	virtual float getAskPrice() const;

	/// Get the lowest price intro day
	virtual float getLowPrice() const;

	/// Get the highest price intro day
	virtual float getHighPrice() const;

	/// Get the price of latest deal
	virtual float getLastPrice() const;

	/// Get latest opening price 
	virtual float getOpeningPrice() const;

	/// Get the latest settlement price
	virtual float getSettlementPrice() const;

	/// Get the bid price with depth level
	virtual float getBidPrice(int level) const;

	/// Get the ask price with depth level
	virtual float getAskPrice(int level) const;

	/// Get bid volume with depth level
	virtual int getBidVolume(int level) const;

	/// Get ask volume with depth level
	virtual int getAskVolume(int level) const;

	/// Get Update Timestamp
	virtual unsigned int getUpdateTime() const;

	/// Get Value Per Point
	virtual double getValuePerPoint() const;

	/// Get Number of Legs
	virtual int getLegSize() const;

	/// Get Leg Ratio
	virtual int getLegRatio(int index) const;

	/// Get Leg Security ID
	virtual unsigned int getLegSecurityID(int index) const;


	/// Get Market Status
	virtual int getMarketStatus() const;

	/// Get Security Type
	virtual int getSecurityType() const;

	/// Get Order Types
	virtual unsigned int getOrderTypes() const;
public:
	void logInfo(const std::string& file, int line);
	float checkFloatNanValue(const float& fValueTmp);
	template<typename T> bool uti_isinf(T value);
	template<typename T> bool uti_isnan(T value);

public:
	void setDefaultValue();
	void setValue(const CStockData* pStockData);
	void setValue(const CMyMarketData* pMyMarketData);
	void setValue(const CHistoryData* pHistoryData);

private:
	void _ClearData();
public:
	std::string m_strExchangeName;//Exchange Name//ExchangeName//������
	std::string m_strInstrumentCode;//Contract Name//InstrumentCode//��Լ����

	int m_nBidVolume;//Bid Volume//BidVolume//����
	float m_fBidPrice;//Bid//BidPrice//���

	float m_fAskPrice;//Offer//AskPrice//����
	int m_nAskVolume;//Offer Volume//AskVolume//����

	float m_fLastPrice;//Last//LastPrice//�ɽ���
	int m_nLastVolume;//Last Volume//LastVolume//�ɽ���

	std::string m_strChangeTmp;//Change//�䶯
	std::string m_strYDSPTmp;//YDSP//������

	int m_nMarketStatus;//Status//MarketStatus//�г�״̬
	float m_fOpeningPrice;//Opening//OpeningPrice//���м�

	std::string m_strBidTotalTmp;//Bid Total//���ۼ�
	std::string m_strOfferTotalTmp;//Offer Total//���ۼ�

	float m_fLowPrice;//Low//LowPrice//��ͼ�
	float m_fHighPrice;//High//HighPrice//��߼�

	std::string m_strCloseingTmp;//Closeing//���̼�
	std::string m_strRefPriceTmp;//Ref Price//�ο���

	unsigned int m_timeUpdateTime;//����ʱ��
	std::string m_strGetupdateTime;

public:
	unsigned int m_nInstrumentID;
	std::string m_strUnderlyingCode;

	char m_chDecimalPlace;
	float m_fTickSize;
	float m_fTickValue;

	int m_nTotalVolume;
	
	float m_fSettlementPrice;

	double m_fValuePerPoint;
	int m_nLegSize;
	unsigned int m_nLegSecurityID;
	int m_nSecurityType;
	unsigned int m_nOrderTypes;
	int m_nLegRatio;
}; 


//QT_END_NAMESPACE


#endif//__CLASS_MY_INSTRUMENT_HH__


/*
Exchange Name//ExchangeName//������
Contract Name//InstrumentCode//��Լ����

Bid Volume//BidVolume//����
Bid//BidPrice//���

Offer//AskPrice//����
Offer Volume//AskVolume//����

Last//LastPrice//�ɽ���
Last Volume//LastVolume//�ɽ���

Change//�䶯
YDSP//������

Status//MarketStatus//�г�״̬
Opening//OpeningPrice//���м�

Bid Total//���ۼ�
Offer Total//���ۼ�

High//HighPrice//��߼�
Low//LowPrice//��ͼ�

Closeing//���̼�
Ref Price//�ο���

*/

