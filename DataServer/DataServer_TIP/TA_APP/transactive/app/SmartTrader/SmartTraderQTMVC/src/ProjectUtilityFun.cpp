#include "ProjectUtilityFun.h"
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


//"%04d-%02d-%02d %02d:%02d:%02d"
//"%d-%d-%d %d:%d:%d"
//YYYY-MM-DD HH:MM:SS
//"yyyy-MM-dd hh:mm:ss"


CProjectUtilityFun::CProjectUtilityFun( void )
{
}

CProjectUtilityFun::~CProjectUtilityFun( void )
{

}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

template<typename T>
bool CProjectUtilityFun::uti_isnan(T value)
{
	return value != value;
}

// requires #include <limits>
template<typename T>
bool CProjectUtilityFun::uti_isinf(T value)
{
	return std::numeric_limits<T>::has_infinity() &&
		value == std::numeric_limits<T>::infinity();
}

float CProjectUtilityFun::checkFloatNanValue(const float& fValueTmp)
{
	/*
	According to the IEEE standard, 
	NaN values have the odd property that comparisons involving them are always false. 
	That is, for a float f, f != f will be true only if f is NaN
	*/

	/*
	#include <boost/algorithm/string.hpp>
	#include <boost/math/special_functions/fpclassify.hpp> 
	if ((boost::math::isnan)(fValueTmp))
	{
	//x is NaN
	return 0;
	} 
	*/
	if (uti_isnan(fValueTmp))
	{
		//x is NaN
		return 0;
	}

	return fValueTmp;
}



time_t CProjectUtilityFun::getTimeNow_Qt()
{
	QDateTime time_local;
	time_t timeGetTimeValue;

	time_local = QDateTime::currentDateTime();

	timeGetTimeValue = time_local.toTime_t();

	return timeGetTimeValue;
}
time_t CProjectUtilityFun::strToDateTime_Qt(const std::string& strTimeValue)
{
	QString   strTime_local;
	time_t    nTime_local;
	QDateTime time_local;
	/*
	QDateTime dateTime = QDateTime::fromString("1970-01-01 08:00:00","yyyy-MM-dd hh:mm:ss");
	dateTime.setTimeSpec(Qt::LocalTime);
	uint secondsLocal= dateTime.toTime_t();  //secondsLocal =0;
	dateTime.setTimeSpec(Qt::UTC);
	uint secondsUTC = dateTime.toTime_t();   //secondsUTC = 28800;8小时
	*/


	strTime_local = strTimeValue.c_str();
	time_local = QDateTime::fromString(strTime_local, "yyyy-MM-dd hh:mm:ss");
	time_local.setTimeSpec(Qt::LocalTime);
	nTime_local = time_local.toTime_t();
	return nTime_local;
}


std::string CProjectUtilityFun::dateTimeToStr_Qt(time_t secsSince1Jan1970UTC)
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

















