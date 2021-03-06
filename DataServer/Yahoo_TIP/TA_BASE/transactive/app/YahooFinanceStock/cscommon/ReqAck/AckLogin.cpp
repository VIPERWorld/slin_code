#include "AckLogin.h"
#include <QtCore/QDataStream>
#include "Log4cppLogger.h"

CAckLogin::CAckLogin( void )
{
	_Clear();
}

CAckLogin::~CAckLogin( void )
{
	_Clear();
}

void CAckLogin::_Clear()
{
	m_nMessageType = CTcpComProtocol::MsgType_Ack;
	m_nDataType = CTcpComProtocol::DataType_Login;
	m_strReqUUID.clear();
	m_strACKUUID.clear();
	m_strUserID.clear();
	m_strUserName.clear();
	m_strPassword.clear();
	m_strLastLoginTime.clear();
	m_nLoginCount = 0;
	m_nState = 0;
	m_nLoginResult = CTcpComProtocol::DataType_LoginResult_OK;
}

void CAckLogin::logInfo( const QString& fileName, qint32 lineNumber )
{
	MYLOG4CPP_DEBUG_Base<<" "<<"["<<fileName<<":"<<lineNumber<<"]"
		<<" "<<"CAckLogin:"
		<<" "<<"nMessageType="<<CTcpComProtocol::getStringValue(m_nMessageType)
		<<" "<<"m_nDataType="<<CTcpComProtocol::getStringValue(m_nDataType)
		<<" "<<"m_strReqUUID="<<m_strReqUUID
		<<" "<<"m_strACKUUID="<<m_strACKUUID		
		<<" "<<"m_strUserID="<<m_strUserID
		<<" "<<"m_strUserName="<<m_strUserName
		<<" "<<"m_strPassword="<<m_strPassword
		<<" "<<"m_strLastLoginTime="<<m_strLastLoginTime
		<<" "<<"m_nLoginCount="<<m_nLoginCount
		<<" "<<"m_nState="<<m_nState		
		<<" "<<"m_nLoginResult="<<CTcpComProtocol::getStringValue(m_nLoginResult);
}
//static
bool CAckLogin::checkMsgDataType( qint32 nMessageType, qint32 nDataType )
{
	bool bFunRes = false;

	CTcpComProtocol::EMsgType nMsgTypeTmp = (CTcpComProtocol::EMsgType)(nMessageType);
	CTcpComProtocol::EDataType nDataTypeTmp = (CTcpComProtocol::EDataType)(nDataType);

	if (CTcpComProtocol::MsgType_Ack == nMsgTypeTmp
		&& CTcpComProtocol::DataType_Login == nDataTypeTmp)
	{
		bFunRes = true;
	}
	return bFunRes;
}

QByteArray* CAckLogin::getMessage()
{
	QByteArray* pMessage = NULL;
	//QByteArray &append(const char *s, int len);
	pMessage = new QByteArray();

	QDataStream writeToByteArray(pMessage, QIODevice::WriteOnly);
	writeToByteArray.setVersion(QDataStream::Qt_4_0);

	writeToByteArray<<(qint32)(m_nMessageType);
	writeToByteArray<<(qint32)(m_nDataType);
	writeToByteArray<<(m_strReqUUID);
	writeToByteArray<<(m_strACKUUID);
	writeToByteArray<<(m_strUserID);
	writeToByteArray<<(m_strUserName);
	writeToByteArray<<(m_strPassword);
	writeToByteArray<<(m_strLastLoginTime);
	writeToByteArray<<(m_nLoginCount);
	writeToByteArray<<(m_nState);
	writeToByteArray<<(qint32)(m_nLoginResult);

	return pMessage;	
}

void CAckLogin::setValue(const QByteArray* pMessage )
{
	MYLOG4CPP_DEBUG<<"setValue"
		<<" "<<"param:"<<" "<<"QByteArray* pMessage=0x"<<pMessage;
	qint32 nMessageType = 0;//CTcpComProtocol::MsgType_Req
	qint32 nDataType = 0;//CTcpComProtocol::EDataType
	qint32 nLoginResult = 0;
	QDataStream readMessageBuffer(*pMessage);
	readMessageBuffer.setVersion(QDataStream::Qt_4_0);

	readMessageBuffer>>nMessageType;
	readMessageBuffer>>nDataType;
	readMessageBuffer>>m_strReqUUID;
	readMessageBuffer>>m_strACKUUID;
	readMessageBuffer>>m_strUserID;
	readMessageBuffer>>m_strUserName;
	readMessageBuffer>>m_strPassword;
	readMessageBuffer>>m_strLastLoginTime;
	readMessageBuffer>>m_nLoginCount;
	readMessageBuffer>>m_nState;	

	readMessageBuffer>>nLoginResult;

	m_nMessageType = (CTcpComProtocol::EMsgType)(nMessageType);
	m_nDataType = (CTcpComProtocol::EDataType)(nDataType);
	m_nLoginResult = (CTcpComProtocol::EDataTypeLoginResult)nLoginResult;
	
}