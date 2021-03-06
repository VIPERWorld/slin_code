#ifndef __CLASS_ACK_LOGIN_H__
#define __CLASS_ACK_LOGIN_H__

#include <QtCore/QObject>
#include <Qtcore/QByteArray>

#include "TcpComProtocol.h"


class CAckLogin
{
public:
    CAckLogin(void);
	~CAckLogin(void);
private:
	void _Clear();
public:
	static bool checkMsgDataType(qint32 nMessageType, qint32 nDataType);
	void setValue(const QByteArray* pMessage );
	QByteArray* getMessage();
	void logInfo( const QString& fileName, qint32 lineNumber );
public:
	CTcpComProtocol::EMsgType m_nMessageType;//CTcpComProtocol::EMsgType
	CTcpComProtocol::EDataType m_nDataType;//CTcpComProtocol::EDataType
	QString m_strReqUUID;//37
	QString m_strACKUUID;//37

	QString m_strUserID;//65
	QString m_strUserName;//65
	QString m_strPassword;//65
	QString m_strLastLoginTime;
	qint32 m_nLoginCount;
	qint32 m_nState;

	CTcpComProtocol::EDataTypeLoginResult m_nLoginResult;
};

#endif//__CLASS_ACK_LOGIN_H__
