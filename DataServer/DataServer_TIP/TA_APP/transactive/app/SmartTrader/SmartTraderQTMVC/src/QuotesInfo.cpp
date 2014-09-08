#include "QuotesInfo.h"

#include "ProjectUtilityFun.h"

#include "BoostLogger.h"
USING_BOOST_LOG;

//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE





static const std::string DEFVALUE_String_ColumnName_SmartQuotes_InstrumentPriceChange = "Change";//Change//�䶯//�۸�仯��ɫ

static const std::string DEFVALUE_String_ColumnName_SmartQuotes_ExchangeName = "Exchange Name";//ExchangeName//������
static const std::string DEFVALUE_String_ColumnName_SmartQuotes_InstrumentCode = "Contract Name";//InstrumentCode//��Լ����

static const std::string DEFVALUE_String_ColumnName_SmartQuotes_BidVolume = "Bid Volume";//BidVolume//����
static const std::string DEFVALUE_String_ColumnName_SmartQuotes_BidPrice = "Bid";//BidPrice//���

static const std::string DEFVALUE_String_ColumnName_SmartQuotes_AskVolume = "Offer Volume";//AskVolume//����
static const std::string DEFVALUE_String_ColumnName_SmartQuotes_AskPrice = "Offer";//AskPrice//����

static const std::string DEFVALUE_String_ColumnName_SmartQuotes_LastVolume = "Last Volume";//LastVolume//�ɽ���
static const std::string DEFVALUE_String_ColumnName_SmartQuotes_LastPrice = "Last";//LastPrice//�ɽ���

static const std::string DEFVALUE_String_ColumnName_SmartQuotes_YDSP = "YDSP";//YDSP//������

static const std::string DEFVALUE_String_ColumnName_SmartQuotes_MarketStatus = "Status";//MarketStatus//�г�״̬
static const std::string DEFVALUE_String_ColumnName_SmartQuotes_OpeningPrice = "Opening";//OpeningPrice//���м�

static const std::string DEFVALUE_String_ColumnName_SmartQuotes_BidTotal = "Bid Total";//Bid Total//���ۼ�
static const std::string DEFVALUE_String_ColumnName_SmartQuotes_OfferTotal = "Offer Total";//Offer Total//���ۼ�

static const std::string DEFVALUE_String_ColumnName_SmartQuotes_LowPrice = "Low";//LowPrice//��ͼ�
static const std::string DEFVALUE_String_ColumnName_SmartQuotes_HighPrice = "High";//HighPrice//��߼�


static const std::string DEFVALUE_String_ColumnName_SmartQuotes_Closeing = "Closeing";//Closeing//���̼�
static const std::string DEFVALUE_String_ColumnName_SmartQuotes_RefPrice = "Ref Price";//Ref Price//�ο���

static const std::string DEFVALUE_String_ColumnName_SmartQuotes_strUpdateTime = "UpdateTime";//����ʱ��


//////////////////////////////////////////////////////////////////////////
//ex
static const std::string DEFVALUE_String_ColumnName_SmartQuotes_InstrumentID = "InstrumentID";



//////////////////////////////////////////////////////////////////////////

CQuotesInfo::CQuotesInfo()
{
	m_nInstrumentPriceChange = IconDelegate::InstrumentPriceChange_NoQuotes;

	_ClearData();

	m_nInstrumentID = 0;
	m_strInstrumentCode.clear();
	m_strUnderlyingCode.clear();
	m_strExchangeName.clear();

	m_chDecimalPlace = 0;
	m_fTickSize = 0;
	m_fTickValue = 0;
	m_nBidVolume = 0;

	m_nAskVolume = 0;
	m_nLastVolume = 0;
	m_nTotalVolume = 0;

	m_fBidPrice = 0;
	m_fAskPrice = 0;
	m_fLowPrice = 0;
	m_fHighPrice = 0;

	m_fLastPrice = 0;
	m_fOpeningPrice = 0;
	m_fSettlementPrice = 0;
	m_timeUpdateTime = 0;
	m_strGetupdateTime.clear();

	m_fValuePerPoint = 0;
	m_nLegSize = 0;
	m_nLegSecurityID = 0;
	m_nMarketStatus = 0;
	m_nSecurityType = 0;
	m_nOrderTypes = 0;

	m_pUtilityFun = NULL;
	m_pUtilityFun = new CProjectUtilityFun();

}

CQuotesInfo::~CQuotesInfo()
{
	if (NULL != m_pUtilityFun)
	{
		delete m_pUtilityFun;
		m_pUtilityFun = NULL;
	}

}


CQuotesInfo& CQuotesInfo::operator=( const CQuotesInfo& exchangeParam )
{
	m_nInstrumentPriceChange = exchangeParam.m_nInstrumentPriceChange;

	m_nInstrumentID = exchangeParam.m_nInstrumentID;
	m_strInstrumentCode = exchangeParam.m_strInstrumentCode;
	m_strUnderlyingCode = exchangeParam.m_strUnderlyingCode;
	m_strExchangeName = exchangeParam.m_strExchangeName;

	m_chDecimalPlace = exchangeParam.m_chDecimalPlace;
	m_fTickSize = exchangeParam.m_fTickSize;
	m_fTickValue = exchangeParam.m_fTickValue;
	m_nBidVolume = exchangeParam.m_nBidVolume;

	m_nAskVolume = exchangeParam.m_nAskVolume;
	m_nLastVolume = exchangeParam.m_nLastVolume;
	m_nTotalVolume = exchangeParam.m_nTotalVolume;

	m_fBidPrice = exchangeParam.m_fBidPrice;
	m_fAskPrice = exchangeParam.m_fAskPrice;
	m_fLowPrice = exchangeParam.m_fLowPrice;
	m_fHighPrice = exchangeParam.m_fHighPrice;

	m_fLastPrice = exchangeParam.m_fLastPrice;
	m_fOpeningPrice = exchangeParam.m_fOpeningPrice;
	m_fSettlementPrice = exchangeParam.m_fSettlementPrice;
	m_timeUpdateTime = exchangeParam.m_timeUpdateTime;
	m_strGetupdateTime = exchangeParam.m_strGetupdateTime;

	m_fValuePerPoint = exchangeParam.m_fValuePerPoint;
	m_nLegSize = exchangeParam.m_nLegSize;
	m_nLegSecurityID = exchangeParam.m_nLegSecurityID;
	m_nMarketStatus = exchangeParam.m_nMarketStatus;
	m_nSecurityType = exchangeParam.m_nSecurityType;
	m_nOrderTypes = exchangeParam.m_nOrderTypes;



	m_strExchangeName = exchangeParam.m_strExchangeName;//Exchange Name//ExchangeName//������
	m_strInstrumentCode = exchangeParam.m_strInstrumentCode;//Contract Name//InstrumentCode//��Լ����
	m_nBidVolume = exchangeParam.m_nBidVolume;//Bid Volume//BidVolume//����
	m_fBidPrice = exchangeParam.m_fBidPrice;//Bid//BidPrice//���
	m_fAskPrice = exchangeParam.m_fAskPrice;//Offer//AskPrice//����
	m_nAskVolume = exchangeParam.m_nAskVolume;//Offer Volume//AskVolume//����
	m_fLastPrice = exchangeParam.m_fLastPrice;//Last//LastPrice//�ɽ���
	m_nLastVolume = exchangeParam.m_nLastVolume;//Last Volume//LastVolume//�ɽ���
	m_strChangeTmp = exchangeParam.m_strChangeTmp;//Change//�䶯
	m_strYDSPTmp = exchangeParam.m_strYDSPTmp;//YDSP//������
	m_nMarketStatus = exchangeParam.m_nMarketStatus;//Status//MarketStatus//�г�״̬
	m_fOpeningPrice = exchangeParam.m_fOpeningPrice;//Opening//OpeningPrice//���м�
	m_strBidTotalTmp = exchangeParam.m_strBidTotalTmp;//Bid Total//���ۼ�
	m_strOfferTotalTmp = exchangeParam.m_strOfferTotalTmp;//Offer Total//���ۼ�
	m_fLowPrice = exchangeParam.m_fLowPrice;//Low//LowPrice//��ͼ�
	m_fHighPrice = exchangeParam.m_fHighPrice;//High//HighPrice//��߼�
	m_strCloseingTmp = exchangeParam.m_strCloseingTmp;//Closeing//���̼�
	m_strRefPriceTmp = exchangeParam.m_strRefPriceTmp;//Ref Price//�ο���

	return *this;
}

void CQuotesInfo::_ClearData()
{
	m_strExchangeName.clear();//Exchange Name//ExchangeName//������
	m_strInstrumentCode.clear();//Contract Name//InstrumentCode//��Լ����
	m_nBidVolume = 0;//Bid Volume//BidVolume//����
	m_fBidPrice = 0;//Bid//BidPrice//���
	m_fAskPrice = 0;//Offer//AskPrice//����
	m_nAskVolume = 0;//Offer Volume//AskVolume//����
	m_fLastPrice = 0;//Last//LastPrice//�ɽ���
	m_nLastVolume = 0;//Last Volume//LastVolume//�ɽ���
	m_strChangeTmp.clear();//Change//�䶯
	m_strYDSPTmp.clear();//YDSP//������
	m_nMarketStatus = 0;//Status//MarketStatus//�г�״̬
	m_fOpeningPrice = 0;//Opening//OpeningPrice//���м�
	m_strBidTotalTmp.clear();//Bid Total//���ۼ�
	m_strOfferTotalTmp.clear();//Offer Total//���ۼ�
	m_fLowPrice = 0;//Low//LowPrice//��ͼ�
	m_fHighPrice = 0;//High//HighPrice//��߼�
	m_strCloseingTmp.clear();//Closeing//���̼�
	m_strRefPriceTmp.clear();//Ref Price//�ο���
	m_timeUpdateTime = 0;
	m_strGetupdateTime.clear();

}


void CQuotesInfo::setValue( const Instrument &instrument)
{
	_ClearData();

	m_fOpeningPrice  = instrument.getOpeningPrice();
	m_fOpeningPrice = m_pUtilityFun->checkFloatNanValue(m_fOpeningPrice);

	m_fLastPrice = instrument.getLastPrice();
	m_fLastPrice = m_pUtilityFun->checkFloatNanValue(m_fLastPrice);

	if (m_fLastPrice > m_fOpeningPrice)
	{
		m_nInstrumentPriceChange = IconDelegate::InstrumentPriceChange_Increase;
	}
	else if (m_fLastPrice < m_fOpeningPrice)
	{
		m_nInstrumentPriceChange = IconDelegate::InstrumentPriceChange_Reduction;
	}
	//else if (fabs(m_fLastPrice - m_fOpeningPrice) <= EPSILON)//�жϸ������Ƿ����
	else
	{
		m_nInstrumentPriceChange = IconDelegate::InstrumentPriceChange_NoQuotes;
	}


	m_nInstrumentID = instrument.getInstrumentID();
	m_strInstrumentCode = instrument.getInstrumentCode().c_str();
	m_strUnderlyingCode = instrument.getUnderlyingCode().c_str();
	m_strExchangeName = instrument.getExchangeName().c_str();

	m_chDecimalPlace = instrument.getDecimalPlace();
	m_fTickSize = instrument.getTickSize();
	m_fTickSize = m_pUtilityFun->checkFloatNanValue(m_fTickSize);

	m_fTickValue  = instrument.getTickValue();
	m_fTickValue = m_pUtilityFun->checkFloatNanValue(m_fTickValue);

	m_nBidVolume  = instrument.getBidVolume();

	m_nAskVolume  = instrument.getAskVolume();
	m_nLastVolume  = instrument.getLastVolume();
	m_nTotalVolume  = instrument.getTotalVolume();

	m_fBidPrice  = instrument.getBidPrice();
	m_fBidPrice = m_pUtilityFun->checkFloatNanValue(m_fBidPrice);

	m_fAskPrice = instrument.getAskPrice();
	m_fAskPrice = m_pUtilityFun->checkFloatNanValue(m_fAskPrice);

	m_fLowPrice = instrument.getLowPrice();
	m_fLowPrice = m_pUtilityFun->checkFloatNanValue(m_fLowPrice);

	m_fHighPrice  = instrument.getHighPrice();
	m_fHighPrice = m_pUtilityFun->checkFloatNanValue(m_fHighPrice);

	m_fLastPrice = instrument.getLastPrice();
	m_fLastPrice = m_pUtilityFun->checkFloatNanValue(m_fLastPrice);

	m_fOpeningPrice  = instrument.getOpeningPrice();
	m_fOpeningPrice = m_pUtilityFun->checkFloatNanValue(m_fOpeningPrice);

	m_fSettlementPrice  = instrument.getSettlementPrice();
	m_fSettlementPrice = m_pUtilityFun->checkFloatNanValue(m_fSettlementPrice);

	m_timeUpdateTime  = instrument.getUpdateTime();
	m_strGetupdateTime = m_pUtilityFun->dataTimeToStr(m_timeUpdateTime);
	//strGetupdateTime  = instrument.getInstrumentID();

	m_fValuePerPoint  = instrument.getValuePerPoint();
	m_nLegSize = instrument.getLegSize();
	//m_nLegSecurityID  = instrument.getLegSecurityID();
	m_nMarketStatus = instrument.getMarketStatus();
	m_nSecurityType = instrument.getSecurityType();
	m_nOrderTypes  = instrument.getOrderTypes();

}






unsigned int CQuotesInfo::getInstrumentID() const
{
	return m_nInstrumentID;
}
void CQuotesInfo::logInfo( const QString& strLogInfo ) const
{
	LOG_DEBUG<<strLogInfo.toStdString()
		<<" "<<"m_nInstrumentID="<<m_nInstrumentID
		<<" "<<"m_strExchangeName="<<m_strExchangeName.toStdString()
		<<" "<<"m_strUnderlyingCode="<<m_strUnderlyingCode.toStdString()
		<<" "<<"m_strInstrumentCode="<<m_strInstrumentCode.toStdString();
}

QString CQuotesInfo::getInstrumentCode() const
{
	return m_strInstrumentCode;
}

void CQuotesInfo::setDefaultValue()
{
	m_nInstrumentID = 1;
	m_strExchangeName = "AAAA";
	m_strUnderlyingCode = "BB";
	m_strInstrumentCode = "AAAA_BB_CC";
}

QVariant CQuotesInfo::getValueByName( const QString& strName )
{
	QVariant varValueRes;
	QStringList strlstClumnNameShow;

	strlstClumnNameShow.push_back(strName);




	//
	//static const std::string DEFVALUE_String_ColumnName_SmartQuotes_InstrumentID = "InstrumentID";
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_SmartQuotes_InstrumentID.c_str())))
	{
		varValueRes = QVariant(this->m_nInstrumentID);
		return varValueRes;
	}
	

	//
	//static const std::string DEFVALUE_String_ColumnName_SmartQuotes_InstrumentPriceChange = "Change";//Change//�䶯//�۸�仯��ɫ
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_SmartQuotes_InstrumentPriceChange.c_str())))
	{
		varValueRes = QVariant(this->m_nInstrumentPriceChange);
		return varValueRes;
	}


	//
	//static const std::string DEFVALUE_String_ColumnName_SmartQuotes_ExchangeName = "Exchange Name";//ExchangeName//������
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_SmartQuotes_ExchangeName.c_str())))
	{
		varValueRes = QVariant(this->m_strExchangeName);
		return varValueRes;
	}


	//
	//static const std::string DEFVALUE_String_ColumnName_SmartQuotes_InstrumentCode = "Contract Name";//InstrumentCode//��Լ����
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_SmartQuotes_InstrumentCode.c_str())))
	{
		varValueRes = QVariant(this->m_strInstrumentCode);
		return varValueRes;
	}


	//
	//static const std::string DEFVALUE_String_ColumnName_SmartQuotes_BidVolume = "Bid Volume";//BidVolume//����
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_SmartQuotes_BidVolume.c_str())))
	{
		varValueRes = QVariant(this->m_nBidVolume);
		return varValueRes;
	}



	//
	//static const std::string DEFVALUE_String_ColumnName_SmartQuotes_BidPrice = "Bid";//BidPrice//���
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_SmartQuotes_BidPrice.c_str())))
	{
		varValueRes = QVariant(this->m_fBidPrice);
		return varValueRes;
	}


	//
	//static const std::string DEFVALUE_String_ColumnName_SmartQuotes_AskVolume = "Offer Volume";//AskVolume//����
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_SmartQuotes_AskVolume.c_str())))
	{
		varValueRes = QVariant(this->m_nAskVolume);
		return varValueRes;
	}

	//
	//static const std::string DEFVALUE_String_ColumnName_SmartQuotes_AskPrice = "Offer";//AskPrice//����
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_SmartQuotes_AskPrice.c_str())))
	{
		varValueRes = QVariant(this->m_fAskPrice);
		return varValueRes;
	}

	//
	//static const std::string DEFVALUE_String_ColumnName_SmartQuotes_LastVolume = "Last Volume";//LastVolume//�ɽ���
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_SmartQuotes_LastVolume.c_str())))
	{
		varValueRes = QVariant(this->m_nLastVolume);
		return varValueRes;
	}

	//
	//static const std::string DEFVALUE_String_ColumnName_SmartQuotes_LastPrice = "Last";//LastPrice//�ɽ���
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_SmartQuotes_LastPrice.c_str())))
	{
		varValueRes = QVariant(this->m_fLastPrice);
		return varValueRes;
	}


	//
	//static const std::string DEFVALUE_String_ColumnName_SmartQuotes_YDSP = "YDSP";//YDSP//������
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_SmartQuotes_YDSP.c_str())))
	{
		varValueRes = QVariant(this->m_strYDSPTmp);
		return varValueRes;
	}



	//
	//static const std::string DEFVALUE_String_ColumnName_SmartQuotes_MarketStatus = "Status";//MarketStatus//�г�״̬
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_SmartQuotes_MarketStatus.c_str())))
	{
		varValueRes = QVariant(this->m_nMarketStatus);
		return varValueRes;
	}



	//
	//static const std::string DEFVALUE_String_ColumnName_SmartQuotes_OpeningPrice = "Opening";//OpeningPrice//���м�
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_SmartQuotes_OpeningPrice.c_str())))
	{
		varValueRes = QVariant(this->m_fOpeningPrice);
		return varValueRes;
	}



	//
	//static const std::string DEFVALUE_String_ColumnName_SmartQuotes_BidTotal = "Bid Total";//Bid Total//���ۼ�
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_SmartQuotes_BidTotal.c_str())))
	{
		varValueRes = QVariant(this->m_strBidTotalTmp);
		return varValueRes;
	}


	//
	//static const std::string DEFVALUE_String_ColumnName_SmartQuotes_OfferTotal = "Offer Total";//Offer Total//���ۼ�
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_SmartQuotes_OfferTotal.c_str())))
	{
		varValueRes = QVariant(this->m_strOfferTotalTmp);
		return varValueRes;
	}

	//
	//static const std::string DEFVALUE_String_ColumnName_SmartQuotes_LowPrice = "Low";//LowPrice//��ͼ�
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_SmartQuotes_LowPrice.c_str())))
	{
		varValueRes = QVariant(this->m_fLowPrice);
		return varValueRes;
	}

	//
	//static const std::string DEFVALUE_String_ColumnName_SmartQuotes_HighPrice = "High";//HighPrice//��߼�
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_SmartQuotes_HighPrice.c_str())))
	{
		varValueRes = QVariant(this->m_fHighPrice);
		return varValueRes;
	}

	//
	//static const std::string DEFVALUE_String_ColumnName_SmartQuotes_Closeing = "Closeing";//Closeing//���̼�
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_SmartQuotes_Closeing.c_str())))
	{
		varValueRes = QVariant(this->m_strCloseingTmp);
		return varValueRes;
	}

	//
	//static const std::string DEFVALUE_String_ColumnName_SmartQuotes_RefPrice = "Ref Price";//Ref Price//�ο���
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_SmartQuotes_RefPrice.c_str())))
	{
		varValueRes = QVariant(this->m_strRefPriceTmp);
		return varValueRes;
	}


	//
	//static const std::string DEFVALUE_String_ColumnName_SmartQuotes_strUpdateTime = "UpdateTime";//����ʱ��
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_SmartQuotes_strUpdateTime.c_str())))
	{
		varValueRes = QVariant(this->m_strGetupdateTime.c_str());
		return varValueRes;
	}

	return varValueRes;
}


//QT_END_NAMESPACE





