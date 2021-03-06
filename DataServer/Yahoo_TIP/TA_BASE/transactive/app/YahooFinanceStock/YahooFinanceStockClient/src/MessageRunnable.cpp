#include "MessageRunnable.h"

#include <QtCore/QDataStream>
#include <QtCore/QList>

#include "MessageProcesser.h"
#include "WorkTime.h"
#include "Log4cppLogger.h"

#include "TcpComProtocol.h"
#include "ReqLogin.h"
#include "ReqLogout.h"
#include "ReqSynYahoo.h"
#include "ReqDownLoadStock.h"
#include "ReqStockMinTimeMaxTime.h"
#include "ReqStockHistoryData.h"
#include "ReqCreateUser.h"
#include "ReqTrade.h"
#include "ReqHistoryTrade.h"
#include "ReqAccount.h"
#include "ReqHoldAccount.h"

#include "AckLogin.h"
#include "AckLogout.h"
#include "AckSynYahoo.h"
#include "AckDownLoadStock.h"
#include "AckStockMinTimeMaxTime.h"
#include "AckStockHistoryData.h"
#include "AckCreateUser.h"
#include "AckTrade.h"
#include "AckHistoryTrade.h"
#include "AckAccount.h"
#include "AckHoldAccount.h"


CMessageRunnable::CMessageRunnable(qint32 nHanle, QByteArray* pMessage)
{
	m_nHanle = 0;
	m_pMessage = NULL;
	m_pMessageProcesser = NULL;

	m_nHanle = nHanle;
	m_pMessage = pMessage;
	m_pMessageProcesser = new CMessageProcesser(m_nHanle);
}

CMessageRunnable::~CMessageRunnable()
{
	if (NULL != m_pMessage)
	{
		delete m_pMessage;
		m_pMessage = NULL;
	}

	if (NULL != m_pMessageProcesser)
	{
		delete m_pMessageProcesser;
		m_pMessageProcesser = NULL;
	}
}



void CMessageRunnable::run()
{
	CWorkTimeNoLock workTime(0);
	workTime.workBegin();
	MYLOG4CPP_DEBUG<<"CMessageRunnable::run() begin";

	_ProcessMessage();

	workTime.workEnd();
	MYLOG4CPP_DEBUG<<"CMessageRunnable::run() end getWorkTime="<<workTime.getWorkTime()<<" "<<"ms";

}

void CMessageRunnable::_ProcessMessage()
{
	MYLOG4CPP_DEBUG<<" "
		<<" "<<"class:"<<" "<<"CMessageRunnable"
		<<" "<<"fun:"<<" "<<"_ProcessMessage"
		<<" "<<"param:"<<" "<<"m_nHanle="<<m_nHanle
		<<" "<<"param:"<<" "<<"m_pMessage=0x"<<m_pMessage;

	QDataStream readMessageBuffer(*m_pMessage);
	readMessageBuffer.setVersion(QDataStream::Qt_4_0);

	qint32 nMessageType = 0;//CTcpComProtocol::MsgType_Req
	qint32 nDataType = 0;//CTcpComProtocol::EDataType

	readMessageBuffer>>nMessageType;
	readMessageBuffer>>nDataType;

	if (CTcpComProtocol::MsgType_Req == nMessageType)
	{
		_ProcessMessage_Req(nMessageType, nDataType);
	}
	else if (CTcpComProtocol::MsgType_Ack == nMessageType)
	{
		_ProcessMessage_Ack(nMessageType, nDataType);
	}


}


void CMessageRunnable::_ProcessMessage_Req(qint32 nMessageType, qint32 nDataType )
{
	if (CReqCreateUser::checkMsgDataType(nMessageType, nDataType))
	{
		_ProcessMessage_ReqCreateUser();		
	}
	else if (CReqLogin::checkMsgDataType(nMessageType, nDataType))
	{
		_ProcessMessage_ReqLogin();
	}	
	else if (CReqLogout::checkMsgDataType(nMessageType, nDataType))
	{
		_ProcessMessage_ReqLogout();		
	}
	else if (CReqSynYahoo::checkMsgDataType(nMessageType, nDataType))
	{
		_ProcessMessage_ReqSynYahoo();		
	}
	else if (CReqDownLoadStock::checkMsgDataType(nMessageType, nDataType))
	{
		_ProcessMessage_ReqDownLoadStock();		
	}
	else if (CReqStockMinTimeMaxTime::checkMsgDataType(nMessageType, nDataType))
	{
		_ProcessMessage_ReqStockMinTimeMaxTime();		
	}
	else if (CReqStockHistoryData::checkMsgDataType(nMessageType, nDataType))
	{
		_ProcessMessage_ReqStockHistoryData();		
	}
	else if (CReqTrade::checkMsgDataType(nMessageType, nDataType))
	{
		_ProcessMessage_ReqTrade();		
	}
	else if (CReqHistoryTrade::checkMsgDataType(nMessageType, nDataType))
	{
		_ProcessMessage_ReqHistoryTrade();
	}
	else if (CReqAccount::checkMsgDataType(nMessageType, nDataType))
	{
		_ProcessMessage_ReqAccount();
	}
	else if (CReqHoldAccount::checkMsgDataType(nMessageType, nDataType))
	{
		_ProcessMessage_ReqHoldAccount();
	}
	else
	{
		MYLOG4CPP_ERROR<<"not find processer for REQ"
			<<" "<<"nMessageType="<<nMessageType
			<<" "<<"nDataType="<<nDataType;
	}
}

void CMessageRunnable::_ProcessMessage_ReqLogin()
{
	CReqLogin* pReq = NULL;
	pReq = new CReqLogin();
	pReq->setValue(m_pMessage);
	pReq->logInfo(__FILE__, __LINE__);

	m_pMessageProcesser->processReq(pReq);

	if (NULL != pReq)
	{
		delete pReq;
		pReq = NULL;
	}
}
void CMessageRunnable::_ProcessMessage_ReqLogout()
{
	CReqLogout* pReq = NULL;
	pReq = new CReqLogout();
	pReq->setValue(m_pMessage);
	pReq->logInfo(__FILE__, __LINE__);

	m_pMessageProcesser->processReq(pReq);

	if (NULL != pReq)
	{
		delete pReq;
		pReq = NULL;
	}

}
void CMessageRunnable::_ProcessMessage_ReqSynYahoo()
{
	CReqSynYahoo* pReq = NULL;
	pReq = new CReqSynYahoo();
	pReq->setValue(m_pMessage);
	pReq->logInfo(__FILE__, __LINE__);

	m_pMessageProcesser->processReq(pReq);

	if (NULL != pReq)
	{
		delete pReq;
		pReq = NULL;
	}
}
void CMessageRunnable::_ProcessMessage_ReqDownLoadStock()
{
	CReqDownLoadStock* pReq = NULL;
	pReq = new CReqDownLoadStock();
	pReq->setValue(m_pMessage);
	pReq->logInfo(__FILE__, __LINE__);

	m_pMessageProcesser->processReq(pReq);

	if (NULL != pReq)
	{
		delete pReq;
		pReq = NULL;
	}
}
void CMessageRunnable::_ProcessMessage_ReqStockMinTimeMaxTime()
{
	CReqStockMinTimeMaxTime* pReq = NULL;
	pReq = new CReqStockMinTimeMaxTime();
	pReq->setValue(m_pMessage);
	pReq->logInfo(__FILE__, __LINE__);

	m_pMessageProcesser->processReq(pReq);

	if (NULL != pReq)
	{
		delete pReq;
		pReq = NULL;
	}
}

void CMessageRunnable::_ProcessMessage_ReqStockHistoryData()
{
	CReqStockHistoryData* pReq = NULL;
	pReq = new CReqStockHistoryData();
	pReq->setValue(m_pMessage);
	pReq->logInfo(__FILE__, __LINE__);

	m_pMessageProcesser->processReq(pReq);

	if (NULL != pReq)
	{
		delete pReq;
		pReq = NULL;
	}
}

void CMessageRunnable::_ProcessMessage_ReqCreateUser()
{
	CReqCreateUser* pReq = NULL;
	pReq = new CReqCreateUser();
	pReq->setValue(m_pMessage);
	pReq->logInfo(__FILE__, __LINE__);

	m_pMessageProcesser->processReq(pReq);

	if (NULL != pReq)
	{
		delete pReq;
		pReq = NULL;
	}
}


void CMessageRunnable::_ProcessMessage_ReqTrade()
{
	CReqTrade* pReq = NULL;
	pReq = new CReqTrade();
	pReq->setValue(m_pMessage);
	pReq->logInfo(__FILE__, __LINE__);

	m_pMessageProcesser->processReq(pReq);

	if (NULL != pReq)
	{
		delete pReq;
		pReq = NULL;
	}
}

void CMessageRunnable::_ProcessMessage_ReqHistoryTrade()
{
	CReqHistoryTrade* pReq = NULL;
	pReq = new CReqHistoryTrade();
	pReq->setValue(m_pMessage);
	pReq->logInfo(__FILE__, __LINE__);

	m_pMessageProcesser->processReq(pReq);

	if (NULL != pReq)
	{
		delete pReq;
		pReq = NULL;
	}
}

void CMessageRunnable::_ProcessMessage_ReqAccount()
{

}
void CMessageRunnable::_ProcessMessage_ReqHoldAccount()
{

}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
void CMessageRunnable::_ProcessMessage_Ack(qint32 nMessageType, qint32 nDataType )
{
	if (CAckCreateUser::checkMsgDataType(nMessageType, nDataType))
	{
		_ProcessMessage_AckCreateUser();		
	}
	else if (CAckLogin::checkMsgDataType(nMessageType, nDataType))
	{
		_ProcessMessage_AckLogin();
	}	
	else if (CAckLogout::checkMsgDataType(nMessageType, nDataType))
	{
		_ProcessMessage_AckLogout();
	}
	else if (CAckSynYahoo::checkMsgDataType(nMessageType, nDataType))
	{
		_ProcessMessage_AckSynYahoo();
	}
	else if (CAckDownLoadStock::checkMsgDataType(nMessageType, nDataType))
	{
		_ProcessMessage_AckDownLoadStock();		
	}
	else if (CAckStockMinTimeMaxTime::checkMsgDataType(nMessageType, nDataType))
	{
		_ProcessMessage_AckStockMinTimeMaxTime();		
	}
	else if (CAckStockHistoryData::checkMsgDataType(nMessageType, nDataType))
	{
		_ProcessMessage_AckStockHistoryData();		
	}
	else if (CAckTrade::checkMsgDataType(nMessageType, nDataType))
	{
		_ProcessMessage_AckTrade();
	}
	else if (CAckHistoryTrade::checkMsgDataType(nMessageType, nDataType))
	{
		_ProcessMessage_AckHistoryTrade();
	}
	else if (CAckAccount::checkMsgDataType(nMessageType, nDataType))
	{
		_ProcessMessage_AckAccount();
	}
	else if (CAckHoldAccount::checkMsgDataType(nMessageType, nDataType))
	{
		_ProcessMessage_AckHoldAccount();
	}
	else
	{
		MYLOG4CPP_ERROR<<"not find processer for ACK"
			<<" "<<"nMessageType="<<nMessageType
			<<" "<<"nDataType="<<nDataType;
	}
}

void CMessageRunnable::_ProcessMessage_AckLogin()
{
	CAckLogin* pAck = NULL;
	pAck = new CAckLogin();
	pAck->setValue(m_pMessage);
	pAck->logInfo(__FILE__, __LINE__);

	m_pMessageProcesser->processAck(pAck);

	if (NULL != pAck)
	{
		delete pAck;
		pAck = NULL;
	}
}

void CMessageRunnable::_ProcessMessage_AckLogout()
{
	CAckLogout* pAck = NULL;
	pAck = new CAckLogout();
	pAck->setValue(m_pMessage);
	pAck->logInfo(__FILE__, __LINE__);

	m_pMessageProcesser->processAck(pAck);

	if (NULL != pAck)
	{
		delete pAck;
		pAck = NULL;
	}
}
void CMessageRunnable::_ProcessMessage_AckSynYahoo()
{
	CAckSynYahoo* pAck = NULL;
	pAck = new CAckSynYahoo();
	pAck->setValue(m_pMessage);
	pAck->logInfo(__FILE__, __LINE__);

	m_pMessageProcesser->processAck(pAck);

	if (NULL != pAck)
	{
		delete pAck;
		pAck = NULL;
	}
}


void CMessageRunnable::_ProcessMessage_AckDownLoadStock()
{
	CAckDownLoadStock* pAck = NULL;
	pAck = new CAckDownLoadStock();
	pAck->setValue(m_pMessage);
	pAck->logInfo(__FILE__, __LINE__);

	m_pMessageProcesser->processAck(pAck);

	if (NULL != pAck)
	{
		delete pAck;
		pAck = NULL;
	}
}

void CMessageRunnable::_ProcessMessage_AckStockMinTimeMaxTime()
{
	CAckStockMinTimeMaxTime* pAck = NULL;
	pAck = new CAckStockMinTimeMaxTime();
	pAck->setValue(m_pMessage);
	pAck->logInfo(__FILE__, __LINE__);

	m_pMessageProcesser->processAck(pAck);

	if (NULL != pAck)
	{
		delete pAck;
		pAck = NULL;
	}
}


void CMessageRunnable::_ProcessMessage_AckStockHistoryData()
{
	CAckStockHistoryData* pAck = NULL;
	pAck = new CAckStockHistoryData();
	pAck->setValue(m_pMessage);
	pAck->logInfo(__FILE__, __LINE__);

	m_pMessageProcesser->processAck(pAck);

	if (NULL != pAck)
	{
		delete pAck;
		pAck = NULL;
	}
}

void CMessageRunnable::_ProcessMessage_AckCreateUser()
{
	CAckCreateUser* pAck = NULL;
	pAck = new CAckCreateUser();
	pAck->setValue(m_pMessage);
	pAck->logInfo(__FILE__, __LINE__);

	m_pMessageProcesser->processAck(pAck);

	if (NULL != pAck)
	{
		delete pAck;
		pAck = NULL;
	}
}

void CMessageRunnable::_ProcessMessage_AckTrade()
{
	CAckTrade* pAck = NULL;
	pAck = new CAckTrade();
	pAck->setValue(m_pMessage);
	pAck->logInfo(__FILE__, __LINE__);

	m_pMessageProcesser->processAck(pAck);

	if (NULL != pAck)
	{
		delete pAck;
		pAck = NULL;
	}
}

void CMessageRunnable::_ProcessMessage_AckHistoryTrade()
{
	CAckHistoryTrade* pAck = NULL;
	pAck = new CAckHistoryTrade();
	pAck->setValue(m_pMessage);
	pAck->logInfo(__FILE__, __LINE__);

	m_pMessageProcesser->processAck(pAck);

	if (NULL != pAck)
	{
		delete pAck;
		pAck = NULL;
	}
}

void CMessageRunnable::_ProcessMessage_AckAccount()
{
	CAckAccount* pAck = NULL;
	pAck = new CAckAccount();
	pAck->setValue(m_pMessage);
	pAck->logInfo(__FILE__, __LINE__);

	m_pMessageProcesser->processAck(pAck);

	if (NULL != pAck)
	{
		delete pAck;
		pAck = NULL;
	}
}

void CMessageRunnable::_ProcessMessage_AckHoldAccount()
{
	CAckHoldAccount* pAck = NULL;
	pAck = new CAckHoldAccount();
	pAck->setValue(m_pMessage);
	pAck->logInfo(__FILE__, __LINE__);

	m_pMessageProcesser->processAck(pAck);

	if (NULL != pAck)
	{
		delete pAck;
		pAck = NULL;
	}
}
