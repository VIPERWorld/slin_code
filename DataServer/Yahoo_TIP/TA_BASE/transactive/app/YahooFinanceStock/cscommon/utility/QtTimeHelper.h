#ifndef __CLASS_QT_TIME_HELPER_H__
#define __CLASS_QT_TIME_HELPER_H__

#include <time.h>
#include <QtCore/QString>
#include <QtCore/QDateTime>

class CQtTimeHelper 
{
public:
	CQtTimeHelper();
	virtual ~CQtTimeHelper();
public:
	time_t   getCurrentTime();
	QString   getCurrentTimeStr();

	QString  getStringValue(const QDate& nData);

	QString  getStringValue(const QDateTime& nDataTime);

	QString  getStringValue(time_t secsSince1Jan1970UTC);
	time_t   getTimeValue(const QString & strTimeValue);
	QDateTime getDateTimeValue(const QString & strTimeValue);
public:
	void getTimeYearMonthDay(time_t secsSince1Jan1970UTC,unsigned int& nYear, unsigned int& nMonth, unsigned int& nDay);




};


#endif //__CLASS_QT_TIME_HELPER_H__
