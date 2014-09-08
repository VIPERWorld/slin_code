#ifndef __CLASS_QUOTES_INFO_HH__
#define __CLASS_QUOTES_INFO_HH__



//qt sys
#include <QtCore/QChar>
#include <QtCore/QString>
#include <QtCore/QVariant>

#include "Instrument.h"
#include "IconDelegate.h"


//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE

class CProjectUtilityFun;

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

class CQuotesInfo 
{ 
public: 
	CQuotesInfo();

	virtual ~CQuotesInfo(); 
	CQuotesInfo& operator=(const CQuotesInfo& exchangeParam);

public:
	void setValue( const Instrument &instrument);

	unsigned int getInstrumentID() const;
	QString getInstrumentCode() const;

	void logInfo(const QString& strLogInfo) const;
public:
	void setDefaultValue();
	QVariant getValueByName(const QString& strName);
private:
	void _ClearData();
public:
	IconDelegate::enInstrumentPriceChange m_nInstrumentPriceChange;
public:
	QString m_strExchangeName;//Exchange Name//ExchangeName//������
	QString m_strInstrumentCode;//Contract Name//InstrumentCode//��Լ����

	int m_nBidVolume;//Bid Volume//BidVolume//����
	float m_fBidPrice;//Bid//BidPrice//���

	float m_fAskPrice;//Offer//AskPrice//����
	int m_nAskVolume;//Offer Volume//AskVolume//����

	float m_fLastPrice;//Last//LastPrice//�ɽ���
	int m_nLastVolume;//Last Volume//LastVolume//�ɽ���

	QString m_strChangeTmp;//Change//�䶯
	QString m_strYDSPTmp;//YDSP//������

	int m_nMarketStatus;//Status//MarketStatus//�г�״̬
	float m_fOpeningPrice;//Opening//OpeningPrice//���м�

	QString m_strBidTotalTmp;//Bid Total//���ۼ�
	QString m_strOfferTotalTmp;//Offer Total//���ۼ�

	float m_fLowPrice;//Low//LowPrice//��ͼ�
	float m_fHighPrice;//High//HighPrice//��߼�

	QString m_strCloseingTmp;//Closeing//���̼�
	QString m_strRefPriceTmp;//Ref Price//�ο���

	unsigned int m_timeUpdateTime;//����ʱ��
	std::string m_strGetupdateTime;

public:
	unsigned int m_nInstrumentID;
	QString m_strUnderlyingCode;

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
private:
	CProjectUtilityFun* m_pUtilityFun;
}; 


//QT_END_NAMESPACE


#endif//__CLASS_CONTRACT_INFO_HH__



