#ifndef __CLASS_USER_TRADE_INFO_H__
#define __CLASS_USER_TRADE_INFO_H__

#include <QtCore/QString>
#include <QtCore/QStringList>
#include "TcpComProtocol.h"

class CReqTrade;
class CAckTrade;

class CUserTradeInfo
{
public:
	CUserTradeInfo();
	virtual ~CUserTradeInfo();
public:
	CUserTradeInfo& operator=(const CUserTradeInfo& objectCopy);
public:
	void clear();
public:
	void setValue(const QString& strUserID, const CReqTrade* pReq );

public:
	void setValue(const CAckTrade* pAck);
public:
	QString m_strUserID;
	QString m_strTradeUUID;
	QString m_strTradeTime;

	CTcpComProtocol::ETradeType m_nTradeType;
	QString m_strSymbolUse;
	double m_fTradePrice;

	qint32 m_nTradeVolume;
	double m_fTradeAmount;
	double m_fTradeFees;

	double m_fTotalTradeFee;
	double m_fTotalTradeAmount;

};


#endif //__CLASS_USER_TRADE_INFO_H__