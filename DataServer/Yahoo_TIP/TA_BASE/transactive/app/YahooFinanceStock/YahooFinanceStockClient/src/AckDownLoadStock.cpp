#include "AckDownLoadStock.h"
#include <QtCore/QDataStream>
#include "Log4cppLogger.h"

CAckDownLoadStock::CAckDownLoadStock( void )
{
	_Clear();
}

CAckDownLoadStock::~CAckDownLoadStock( void )
{
	_Clear();
}

void CAckDownLoadStock::_Clear()
{
	m_nMessageType = CTcpComProtocol::MsgType_Ack;
	m_nDataType = CTcpComProtocol::DataType_DownLoadStock;
	m_strReqUUID.clear();
	m_strACKUUID.clear();
	m_nStockCount = 0;
	m_LstStock.clear();	
}

void CAckDownLoadStock::logInfo( const QString& fileName, qint32 lineNumber )
{
	MYLOG4CPP_DEBUG_Base<<" "<<"["<<fileName<<":"<<lineNumber<<"]"
		<<" "<<"CAckDownLoadStock:"
		<<" "<<"nMessageType="<<CTcpComProtocol::getStringValue(m_nMessageType)
		<<" "<<"m_nDataType="<<CTcpComProtocol::getStringValue(m_nDataType)
		<<" "<<"m_strReqUUID="<<m_strReqUUID
		<<" "<<"m_strACKUUID="<<m_strACKUUID
		<<" "<<"m_nStockCount="<<m_nStockCount;
}
//static
bool CAckDownLoadStock::checkMsgDataType( qint32 nMessageType, qint32 nDataType )
{
	bool bFunRes = false;

	CTcpComProtocol::EMsgType nMsgTypeTmp = (CTcpComProtocol::EMsgType)(nMessageType);
	CTcpComProtocol::EDataType nDataTypeTmp = (CTcpComProtocol::EDataType)(nDataType);

	if (CTcpComProtocol::MsgType_Ack == nMsgTypeTmp
		&& CTcpComProtocol::DataType_DownLoadStock == nDataTypeTmp)
	{
		bFunRes = true;
	}
	return bFunRes;
}

QByteArray* CAckDownLoadStock::getMessage()
{
	QByteArray* pMessage = NULL;
	//QByteArray &append(const char *s, int len);
	pMessage = new QByteArray();

	m_nStockCount = m_LstStock.size();

	QDataStream writeToByteArray(pMessage, QIODevice::WriteOnly);
	writeToByteArray.setVersion(QDataStream::Qt_4_0);

	writeToByteArray<<(quint32)(m_nMessageType);
	writeToByteArray<<(quint32)(m_nDataType);
	writeToByteArray<<(m_strReqUUID);
	writeToByteArray<<(m_strACKUUID);
	writeToByteArray<<(quint32)(m_nStockCount);

	foreach (const QString& strValue, m_LstStock)
	{
		writeToByteArray<<strValue;
	}

	return pMessage;	
}

void CAckDownLoadStock::setValue(const QByteArray* pMessage )
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
	readMessageBuffer>>m_nStockCount;
	m_LstStock.clear();

	for (qint32 nIndex = 0; nIndex < m_nStockCount; nIndex++)
	{
		QString strValue;
		readMessageBuffer>>strValue;
		m_LstStock.push_back(strValue);
	}

	m_nMessageType = (CTcpComProtocol::EMsgType)(nMessageType);
	m_nDataType = (CTcpComProtocol::EDataType)(nDataType);
}


