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

//QT_END_NAMESPACE

















