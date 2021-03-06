#include "ProjectLogHelper.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <list> 
#include <time.h>
#include <math.h>       /* isnan, sqrt */
#include <limits>

#include <QtCore/QCoreApplication>
#include <QtCore/QElapsedTimer>
#include <QtCore/QDateTime>

#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>

#include "Log4cppLogger.h"



CProjectLogHelper::CProjectLogHelper( void )
{
}

CProjectLogHelper::~CProjectLogHelper( void )
{

}


time_t CProjectLogHelper::getTimeNow_Qt()
{
	QDateTime time_local;
	time_t timeGetTimeValue;

	time_local = QDateTime::currentDateTime();

	timeGetTimeValue = time_local.toTime_t();

	return timeGetTimeValue;
}
std::string CProjectLogHelper::dateTimeToStr_Qt(time_t secsSince1Jan1970UTC)
{
	//QDateTime	fromTime_t ( uint seconds )
	QDateTime time_utc;
	QDateTime time_local;
	QString   strTime_utc;
	QString   strTime_local;
	std::string strTime_local_Res;


	//time_utc.setTimeSpec(Qt::UTC);
	//time_utc.setTime_t(0);
	//QString strUTC = time_utc.toString("yyyy-MM-dd hh:mm:ss"); //strUTC = "1970-01-01 00:00:00"

	//time_local.setTimeSpec(Qt::LocalTime);
	//time_local.setTime_t(0);
	//QString strTime_local = time_local.toString("yyyy-MM-dd hh:mm:ss"); //strUTC = "1970-01-01 08:00:00"

	time_utc.setTimeSpec(Qt::UTC);
	time_utc.setTime_t(secsSince1Jan1970UTC);//(uint secsSince1Jan1970UTC
	strTime_utc = time_utc.toString("yyyy-MM-dd hh:mm:ss");

	time_local.setTimeSpec(Qt::LocalTime);
	time_local.setTime_t(secsSince1Jan1970UTC);//(uint secsSince1Jan1970UTC
	strTime_local = time_local.toString("yyyy-MM-dd hh:mm:ss");

	strTime_local_Res = strTime_local.toStdString();

	return strTime_local_Res;
}



void CProjectLogHelper::log_Instrument_info(
	const std::string& file, int line, 
	const std::string& strLogInfo, const Instrument &instrument )
{
	unsigned int nGetInstrumentID = 0;
	std::string  strGetInstrumentCode;
	std::string  strGetUnderlyingCode;
	std::string  strGetExchangeName;
	char chGetDecimalPlace = 0;
	float fGetTickSize = 0;
	float fGetTickValue = 0;
	int nGetBidVolume = 0;
	int nGetAskVolume = 0;
	int nGetLastVolume = 0;
	int nGetTotalVolume = 0;
	float fGetBidPrice = 0;
	float fGetAskPrice = 0;
	float fGetLowPrice = 0;
	float fGetHighPrice = 0;
	float fGetLastPrice = 0;
	float fGetOpeningPrice = 0;
	float fGetSettlementPrice = 0;
	unsigned int timeGetUpdateTime = 0;//time
	std::string strGetupdateTime;
	double fGetValuePerPoint = 0;
	int nGetLegSize = 0;
	unsigned int nGetLegSecurityID = 0;
	int nGetMarketStatus = 0;
	int nGetSecurityType = 0;
	unsigned int nGetOrderTypes = 0;

	nGetInstrumentID = instrument.getInstrumentID();
	strGetInstrumentCode = instrument.getInstrumentCode();
	strGetUnderlyingCode = instrument.getUnderlyingCode();
	strGetExchangeName = instrument.getExchangeName();
	chGetDecimalPlace = instrument.getDecimalPlace();
	fGetTickSize = instrument.getTickSize();
	fGetTickValue = instrument.getTickValue();
	nGetBidVolume = instrument.getBidVolume();
	nGetAskVolume = instrument.getAskVolume();
	nGetLastVolume = instrument.getLastVolume();
	nGetTotalVolume = instrument.getTotalVolume();
	fGetBidPrice = instrument.getBidPrice();
	fGetAskPrice = instrument.getAskPrice();
	fGetLowPrice = instrument.getLowPrice();
	fGetHighPrice = instrument.getHighPrice();
	fGetLastPrice = instrument.getLastPrice();
	fGetOpeningPrice = instrument.getOpeningPrice();
	fGetSettlementPrice = instrument.getSettlementPrice();
	timeGetUpdateTime = instrument.getUpdateTime();
	strGetupdateTime = dateTimeToStr_Qt(timeGetUpdateTime);
	fGetValuePerPoint = instrument.getValuePerPoint();
	nGetLegSize = instrument.getLegSize();
	//nGetLegSecurityID = instrument.getLegSecurityID();
	nGetMarketStatus = instrument.getMarketStatus();
	nGetSecurityType = instrument.getSecurityType();
	nGetOrderTypes = instrument.getOrderTypes();


	MYLOG4CPP_DEBUG_Base<<" "<<"["<<file<<":"<<line<<"]"<<strLogInfo
		<<" "<<"nGetInstrumentID="<<nGetInstrumentID
		<<" "<<"strGetInstrumentCode="<<strGetInstrumentCode
		<<" "<<"strGetUnderlyingCode="<<strGetUnderlyingCode
		<<" "<<"strGetExchangeName="<<strGetExchangeName
		<<" "<<"chGetDecimalPlace="<<chGetDecimalPlace
		<<" "<<"fGetTickSize="<<fGetTickSize
		<<" "<<"fGetTickValue="<<fGetTickValue
		<<" "<<"nGetBidVolume="<<nGetBidVolume
		<<" "<<"nGetAskVolume="<<nGetAskVolume
		<<" "<<"nGetLastVolume="<<nGetLastVolume
		<<" "<<"nGetTotalVolume="<<nGetTotalVolume
		<<" "<<"fGetBidPrice="<<fGetBidPrice
		<<" "<<"fGetAskPrice="<<fGetAskPrice
		<<" "<<"fGetLowPrice="<<fGetLowPrice
		<<" "<<"fGetHighPrice="<<fGetHighPrice
		<<" "<<"fGetLastPrice="<<fGetLastPrice
		<<" "<<"fGetOpeningPrice="<<fGetOpeningPrice
		<<" "<<"fGetSettlementPrice="<<fGetSettlementPrice
		<<" "<<"fGetBidPrice="<<fGetBidPrice
		<<" "<<"timeGetUpdateTime="<<timeGetUpdateTime
		<<" "<<"strGetupdateTime="<<strGetupdateTime		
		<<" "<<"fGetValuePerPoint="<<fGetValuePerPoint
		<<" "<<"nGetLegSize="<<nGetLegSize
		//<<" "<<"nGetLegSecurityID="<<nGetLegSecurityID
		<<" "<<"nGetMarketStatus="<<nGetMarketStatus
		<<" "<<"nGetSecurityType="<<nGetSecurityType
		<<" "<<"nGetOrderTypes="<<nGetOrderTypes;
}

std::string CProjectLogHelper::getString_BarType( enum BarType nBarType )
{
	std::string strRes;

	switch (nBarType)
	{
	case FIVE_SECOND:
		strRes = "FIVE_SECOND";
		break;
	case TEN_SECOND:
		strRes = "TEN_SECOND";
		break;
	case FIFTEEN_SECEOND:
		strRes = "FIFTEEN_SECEOND";
		break;
	case THIRTY_SECOND:
		strRes = "THIRTY_SECOND";
		break;
	case MINUTE:
		strRes = "MINUTE";
		break;
	case FIVE_MINUTE:
		strRes = "FIVE_MINUTE";
		break;
	case FIFTEEN_MINUTE:
		strRes = "FIFTEEN_MINUTE";
		break;
	case THIRTY_MINUTE:
		strRes = "THIRTY_MINUTE";
		break;
	case ONE_HOUR:
		strRes = "ONE_HOUR";
		break;
	case DAY:
		strRes = "DAY";
		break;
	case WEEK:
		strRes = "WEEK";
		break;
	case MONTH:
		strRes = "MONTH";
		break;
	case YEAR:
		strRes = "YEAR";
		break;
	default:
		strRes = "UNKNOWN";
		break;
	}//switch

	return strRes;
}

enum BarType CProjectLogHelper::getBarTypeByString(const std::string& strBarType )
{
	std::string strTemp;
	enum BarType nBarType = FIVE_SECOND;

	strTemp = "FIVE_SECOND";
	if (strBarType == strTemp)
	{
		nBarType = FIVE_SECOND;
		return nBarType;
	}

	strTemp = "TEN_SECOND";
	if (strBarType == strTemp)
	{
		nBarType = TEN_SECOND;
		return nBarType;
	}

	strTemp = "FIFTEEN_SECEOND";
	if (strBarType == strTemp)
	{
		nBarType = FIFTEEN_SECEOND;
		return nBarType;
	}



	strTemp = "THIRTY_SECOND";
	if (strBarType == strTemp)
	{
		nBarType = THIRTY_SECOND;
		return nBarType;
	}

	strTemp = "MINUTE";
	if (strBarType == strTemp)
	{
		nBarType = MINUTE;
		return nBarType;
	}


	strTemp = "FIVE_MINUTE";
	if (strBarType == strTemp)
	{
		nBarType = FIVE_MINUTE;
		return nBarType;
	}

	strTemp = "FIFTEEN_MINUTE";
	if (strBarType == strTemp)
	{
		nBarType = FIFTEEN_MINUTE;
		return nBarType;
	}


	strTemp = "THIRTY_MINUTE";
	if (strBarType == strTemp)
	{
		nBarType = THIRTY_MINUTE;
		return nBarType;
	}

	strTemp = "ONE_HOUR";
	if (strBarType == strTemp)
	{
		nBarType = ONE_HOUR;
		return nBarType;
	}


	strTemp = "DAY";
	if (strBarType == strTemp)
	{
		nBarType = DAY;
		return nBarType;
	}

	strTemp = "WEEK";
	if (strBarType == strTemp)
	{
		nBarType = WEEK;
		return nBarType;
	}

	strTemp = "MONTH";
	if (strBarType == strTemp)
	{
		nBarType = MONTH;
		return nBarType;
	}

	strTemp = "YEAR";
	if (strBarType == strTemp)
	{
		nBarType = YEAR;
		return nBarType;
	}


	return nBarType;
}

//QT_END_NAMESPACE

















