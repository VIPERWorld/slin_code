#ifndef  __CLASS__HISTORY_DATA_REQUEST_H__
#define  __CLASS__HISTORY_DATA_REQUEST_H__


#include "MyBar.h"


class CHistoryDataRequest
{
public:
	CHistoryDataRequest();
	~CHistoryDataRequest();
public:
	CHistoryDataRequest& operator=(const CHistoryDataRequest& objectCopy);

public:
	enum enCHistoryRequestType
	{
		HistoryRequestType_Time,
	};
public:
	enCHistoryRequestType m_nRequestType;
	enum BarType m_nBarType;
	bool m_bSubscribe;
	unsigned short m_nBarCount;
	unsigned int m_nTimeFrom;
	unsigned int m_nTimeTo;
public:
	unsigned int m_nRequestID;
	std::string m_strInstrumentCode;
	int m_nInstruemntID;

public:
	void logInfo(const std::string& file, int line);
	std::string _GetRequestStrValue();
};

#endif// __CLASS__HISTORY_DATA_REQUEST_H__



