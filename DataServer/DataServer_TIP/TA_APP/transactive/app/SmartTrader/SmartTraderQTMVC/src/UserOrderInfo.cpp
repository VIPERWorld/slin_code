#include "UserOrderInfo.h"

#include <QtCore/QStringList>
#include "Order.h"
#include "Instrument.h"
#include "Account.h"
#include "OrderInfoHelper.h"
#include "ItemUserInstrumentInfo.h"

#include "Log4cppLogger.h"


//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE

//////////////////////////////////////////////////////////////////////////

CUserOrderInfo::CUserOrderInfo()
{
	m_pOrderInfo = NULL;
	m_pOrderInfo = new COrderInfo();
	_ClearData();

	

}

CUserOrderInfo::~CUserOrderInfo()
{
	if (NULL != m_pOrderInfo)
	{
		delete m_pOrderInfo;
		m_pOrderInfo = NULL;
	}
}


CUserOrderInfo& CUserOrderInfo::operator=( const CUserOrderInfo& cParam )
{
	m_nInstrumentID = cParam.m_nInstrumentID;
	m_strExchangeName = cParam.m_strExchangeName;
	m_strInstrumentCode = cParam.m_strInstrumentCode;
	m_fLastPrice = cParam.m_fLastPrice;
	m_nQuantity = cParam.m_nQuantity;
	m_nSide = cParam.m_nSide;
	m_nOrderType = cParam.m_nOrderType;



	return *this;
}

void CUserOrderInfo::_ClearData()
{
	

}

void CUserOrderInfo::setDataByItem( CItemUserInstrumentInfo* pData )
{
	_ClearData();
	m_nInstrumentID = pData->getInstrumentID();
	m_strExchangeName = pData->getExchangeName();
	m_strInstrumentCode = pData->getInstrumentCode();
	m_fLastPrice = pData->getLastPrice();
	m_nQuantity = 1;

}






