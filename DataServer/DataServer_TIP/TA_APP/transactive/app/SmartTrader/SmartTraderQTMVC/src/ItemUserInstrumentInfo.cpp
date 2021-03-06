#include "ItemUserInstrumentInfo.h"


//qt sys
#include <QtCore/QChar>
#include <QtCore/QString>
#include <QtCore/QDir>
#include <QtCore/QVariant>
#include <QtCore/QMap>
#include <QtCore/QObject>
#include <QtCore/QStringList>

#include "UserInstrumentInfoHelper.h"
#include "ConfigInfo.h"

#include "Log4cppLogger.h"


//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE

/*
Exchange Name//ExchangeName//交易所
Contract Name//InstrumentCode//合约名称

Bid Volume//BidVolume//买量
Bid//BidPrice//买价

Offer//AskPrice//卖价
Offer Volume//AskVolume//卖量

Last//LastPrice//成交价
Last Volume//LastVolume//成交量

Change//变动
YDSP//昨收盘

Status//MarketStatus//市场状态
Opening//OpeningPrice//开市价

Bid Total//买累计
Offer Total//卖累计

High//HighPrice//最高价
Low//LowPrice//最低价

Closeing//收盘价
Ref Price//参考价

*/

static const std::string DEFVALUE_String_ColumnName_SmartQuotes_InstrumentPriceChange = "Change";//Change//变动//价格变化颜色

static const std::string DEFVALUE_String_ColumnName_SmartQuotes_ExchangeName = "Exchange Name";//ExchangeName//交易所
static const std::string DEFVALUE_String_ColumnName_SmartQuotes_InstrumentCode = "Contract Name";//InstrumentCode//合约名称

static const std::string DEFVALUE_String_ColumnName_SmartQuotes_BidVolume = "Bid Volume";//BidVolume//买量
static const std::string DEFVALUE_String_ColumnName_SmartQuotes_BidPrice = "Bid";//BidPrice//买价

static const std::string DEFVALUE_String_ColumnName_SmartQuotes_AskVolume = "Offer Volume";//AskVolume//卖量
static const std::string DEFVALUE_String_ColumnName_SmartQuotes_AskPrice = "Offer";//AskPrice//卖价

static const std::string DEFVALUE_String_ColumnName_SmartQuotes_LastVolume = "Last Volume";//LastVolume//成交量
static const std::string DEFVALUE_String_ColumnName_SmartQuotes_LastPrice = "Last";//LastPrice//成交价

static const std::string DEFVALUE_String_ColumnName_SmartQuotes_YDSP = "YDSP";//YDSP//昨收盘

static const std::string DEFVALUE_String_ColumnName_SmartQuotes_MarketStatus = "Status";//MarketStatus//市场状态
static const std::string DEFVALUE_String_ColumnName_SmartQuotes_OpeningPrice = "Opening";//OpeningPrice//开市价

static const std::string DEFVALUE_String_ColumnName_SmartQuotes_BidTotal = "Bid Total";//Bid Total//买累计
static const std::string DEFVALUE_String_ColumnName_SmartQuotes_OfferTotal = "Offer Total";//Offer Total//卖累计

static const std::string DEFVALUE_String_ColumnName_SmartQuotes_LowPrice = "Low";//LowPrice//最低价
static const std::string DEFVALUE_String_ColumnName_SmartQuotes_HighPrice = "High";//HighPrice//最高价


static const std::string DEFVALUE_String_ColumnName_SmartQuotes_Closeing = "Closeing";//Closeing//收盘价
static const std::string DEFVALUE_String_ColumnName_SmartQuotes_RefPrice = "Ref Price";//Ref Price//参考价

static const std::string DEFVALUE_String_ColumnName_SmartQuotes_strUpdateTime = "UpdateTime";//更新时间


//======================================================
static const std::string DEFVALUE_String_ColumnName_SmartQuotes_InstrumentID = "InstrumentID";
static const std::string DEFVALUE_String_ColumnName_SmartQuotes_UnderlyingCode = "UnderlyingCode";

static const std::string DEFVALUE_String_ColumnName_SmartQuotes_DecimalPlace = "DecimalPlace";
static const std::string DEFVALUE_String_ColumnName_SmartQuotes_TickSize = "TickSize";

static const std::string DEFVALUE_String_ColumnName_SmartQuotes_TickValue = "TickValue";
static const std::string DEFVALUE_String_ColumnName_SmartQuotes_TotalVolume = "TotalVolume";

static const std::string DEFVALUE_String_ColumnName_SmartQuotes_SettlementPrice = "SettlementPrice";
static const std::string DEFVALUE_String_ColumnName_SmartQuotes_timeUpdateTime = "timeUpdateTime";

static const std::string DEFVALUE_String_ColumnName_SmartQuotes_ValuePerPoint = "ValuePerPoint";
static const std::string DEFVALUE_String_ColumnName_SmartQuotes_LegSize = "LegSize";

static const std::string DEFVALUE_String_ColumnName_SmartQuotes_LegSecurityID = "LegSecurityID";
static const std::string DEFVALUE_String_ColumnName_SmartQuotes_SecurityType = "SecurityType";
static const std::string DEFVALUE_String_ColumnName_SmartQuotes_OrderTypes = "OrderTypes";
//======================================================




//NS_BEGIN(TA_App_App)

CItemUserInstrumentInfo::CItemUserInstrumentInfo(const QList<QVariant> &data, CItemUserInstrumentInfo *parent /*= 0*/ )
{
	m_pParentItem = NULL;
	m_ItemData.clear();
	m_ItemDataNum = 0;
	m_LstChildItems.clear();

	m_pParentItem = parent;
	m_ItemData = data;
	m_ItemDataNum = m_ItemData.count();
	m_nDataType = ItemDataType_ITEM;
	m_nInstrumentPriceChange = IconDelegate::InstrumentPriceChange_NoQuotes;
	m_nInstrumentID = 0;
	m_strInstrumentCode = "0";
	m_fLastPrice = 0;
}

CItemUserInstrumentInfo::CItemUserInstrumentInfo()
{
	QList<QVariant> dataTreeItem;
	getLstClumnName(dataTreeItem);
	
	m_pParentItem = NULL;
	m_ItemData.clear();
	m_LstChildItems.clear();

	m_pParentItem = NULL;
	m_ItemData = dataTreeItem;
	m_ItemDataNum = m_ItemData.count();
	m_nDataType = CItemUserInstrumentInfo::ItemDataType_ROOT;

}


CItemUserInstrumentInfo::~CItemUserInstrumentInfo()
{
	CItemUserInstrumentInfo* pTreeItem = NULL;
	QList<CItemUserInstrumentInfo*>::iterator iterLst;

	iterLst = m_LstChildItems.begin();
	while (iterLst != m_LstChildItems.end())
	{
		pTreeItem = (*iterLst);

		if (NULL != pTreeItem)
		{
			delete pTreeItem;
			pTreeItem = NULL;
		}

		iterLst++;
	}
	m_LstChildItems.clear();


	m_pParentItem = NULL;
	m_ItemData.clear();


}

void CItemUserInstrumentInfo::appendChild(CItemUserInstrumentInfo** ppItem)
{
	CItemUserInstrumentInfo* pItem = NULL;
	if (NULL == ppItem || NULL == *ppItem)
	{
		return;
	}
	pItem = *ppItem;

	m_LstChildItems.push_back(pItem);


}

CItemUserInstrumentInfo* CItemUserInstrumentInfo::child(int row)
{
	return m_LstChildItems.value(row);
}

int CItemUserInstrumentInfo::childCount() const
{
    return m_LstChildItems.count();
}

int CItemUserInstrumentInfo::columnCount() const
{
    return m_ItemData.count();
}

QVariant CItemUserInstrumentInfo::data(int column) const
{
    return m_ItemData.value(column);
}

CItemUserInstrumentInfo* CItemUserInstrumentInfo::parent()
{
    return m_pParentItem;
}

int CItemUserInstrumentInfo::childNumber() const
{
	int nIndex = 0;

    if (NULL != m_pParentItem)
	{
		//nIndex = m_pParentItem->m_LstChildItems.indexOf(const_cast<TreeItem*>(this));
		nIndex = m_pParentItem->indexOfChildren(const_cast<CItemUserInstrumentInfo*>(this));
        return nIndex;
	}

    return nIndex;
}

int CItemUserInstrumentInfo::indexOfChildren(CItemUserInstrumentInfo* pChildrenItem) const
{
	int nIndex = 0;
	nIndex = m_LstChildItems.indexOf(pChildrenItem);
	return nIndex;
}

void CItemUserInstrumentInfo::appendChildByData(CUserInstrumentInfoHelper* pExchangeInfo)
{
	QList<QVariant> dataTreeItem;
	CItemUserInstrumentInfo* pTreeItemInstrumentCode = NULL;

	pTreeItemInstrumentCode = new CItemUserInstrumentInfo(dataTreeItem, this);
	pTreeItemInstrumentCode->resetCurrentNodeData(pExchangeInfo);
	pTreeItemInstrumentCode->setDataType(ItemDataType_ITEM);

	this->appendChild(&pTreeItemInstrumentCode);
	pTreeItemInstrumentCode = NULL;
}



void CItemUserInstrumentInfo::_GetItemDataFromClass(CUserInstrumentInfoHelper* pData, QList<QVariant>& itemDataTmp)
{

	QVariant varValueGet;
	QStringList strlstClumnNameShow;
	CItemUserInstrumentInfo::getLstClumnName(strlstClumnNameShow);

	//default data
	varValueGet = pData->getValueByName(QObject::tr(DEFVALUE_String_ColumnName_SmartQuotes_InstrumentPriceChange.c_str()));
	m_nInstrumentPriceChange = (IconDelegate::enInstrumentPriceChange)varValueGet.toInt();
	varValueGet = pData->getValueByName(QObject::tr(DEFVALUE_String_ColumnName_SmartQuotes_InstrumentID.c_str()));
	m_nInstrumentID = varValueGet.toUInt();
	varValueGet = pData->getValueByName(QObject::tr(DEFVALUE_String_ColumnName_SmartQuotes_ExchangeName.c_str()));
	m_strExchangeName = varValueGet.toString();
	varValueGet = pData->getValueByName(QObject::tr(DEFVALUE_String_ColumnName_SmartQuotes_InstrumentCode.c_str()));
	m_strInstrumentCode = varValueGet.toString();
	varValueGet = pData->getValueByName(QObject::tr(DEFVALUE_String_ColumnName_SmartQuotes_LastPrice.c_str()));
	m_fLastPrice = varValueGet.toFloat();


	itemDataTmp.clear();


	foreach (const QString& strColumnName, strlstClumnNameShow)
	{
		varValueGet = pData->getValueByName(strColumnName);
		itemDataTmp.push_back(varValueGet);
	}

	return;
}


void CItemUserInstrumentInfo::resetCurrentNodeData(CUserInstrumentInfoHelper* pExchangeInfo )
{
	m_ItemData.clear();
	m_ItemDataNum = 0;

	_GetItemDataFromClass(pExchangeInfo, m_ItemData);
	m_ItemDataNum = m_ItemData.count();
}

void CItemUserInstrumentInfo::resetCurrentNodeDataDefultValue()
{
	QList<QVariant> dataTreeItem;

	for (int nIndex = 0; nIndex < m_ItemDataNum; nIndex++)
	{
		dataTreeItem.push_back("");
	}
	m_ItemData.clear();
	m_ItemData = dataTreeItem;
	m_ItemDataNum = m_ItemData.count();
}


unsigned int CItemUserInstrumentInfo::getHotInstrumentIDByCode(const QString& strInstrumentCode)
{
	CItemUserInstrumentInfo* pTreeItemFind = NULL;
	QList<CItemUserInstrumentInfo*>::iterator iterLst;
	unsigned int nInstrumentID = -1;

	iterLst = m_LstChildItems.begin();
	while (iterLst != m_LstChildItems.end())
	{
		pTreeItemFind = (*iterLst);

		if (pTreeItemFind->getInstrumentCode() == strInstrumentCode)
		{
			nInstrumentID = pTreeItemFind->getInstrumentID();
			return nInstrumentID;
		}

		iterLst++;
	}
	return nInstrumentID;

}

void CItemUserInstrumentInfo::resetChildrenData(CUserInstrumentInfoHelper* pExchangeInfo )
{
	CItemUserInstrumentInfo* pTreeItemFind = NULL;
	QList<CItemUserInstrumentInfo*>::iterator iterLst;
	unsigned int nInstrumentID = 0;
	nInstrumentID = pExchangeInfo->getInstrumentID();

	iterLst = m_LstChildItems.begin();
	while (iterLst != m_LstChildItems.end())
	{
		pTreeItemFind = (*iterLst);

		if (pTreeItemFind->getInstrumentID() == nInstrumentID)
		{
			pTreeItemFind->resetCurrentNodeData(pExchangeInfo);
			break;
		}

		iterLst++;
	}
	
}


bool CItemUserInstrumentInfo::removeChildren( int position, int count )
{
	CItemUserInstrumentInfo* pTreeItem = NULL;

	if (position < 0 || position + count > m_LstChildItems.size())
	{
		MYLOG4CPP_ERROR<<"removeChildren() error!"
			<<" "<<"position="<<position
			<<" "<<"count="<<count
			<<" "<<"m_LstChildItems.count()="<<m_LstChildItems.count();

		return false;
	}

	for (int row = 0; row < count; ++row)
	{
		//get and remove 
		pTreeItem = m_LstChildItems.takeAt(position);

		if (NULL != pTreeItem)
		{
			delete pTreeItem;
			pTreeItem = NULL;
		}
	}

	return true;
}

void CItemUserInstrumentInfo::setDataType( enItemDataType nDataTypeExchange )
{
	m_nDataType = nDataTypeExchange;
}

CItemUserInstrumentInfo::enItemDataType CItemUserInstrumentInfo::getDataType()
{
	return m_nDataType;
}


unsigned int CItemUserInstrumentInfo::getInstrumentID()
{
	return m_nInstrumentID;
}
QString CItemUserInstrumentInfo::getExchangeName()
{
	return m_strExchangeName;
}

IconDelegate::enInstrumentPriceChange CItemUserInstrumentInfo::getInstrumentPriceChange()
{
	return m_nInstrumentPriceChange;
}

void CItemUserInstrumentInfo::getLstClumnName(QStringList& strlstClumnName )
{
	strlstClumnName.clear();
	strlstClumnName = CConfigInfo::getInstance().getLstSelectedColumns();
	return;
}

void CItemUserInstrumentInfo::getLstClumnName(QList<QVariant>& lstClumnName )
{
	QStringList strlstClumnName;
	QVariant varColumnName;

	lstClumnName.clear();

	CItemUserInstrumentInfo::getLstClumnName(strlstClumnName);

	foreach (const QString& strColumnName, strlstClumnName)
	{
		varColumnName = QVariant(strColumnName);
		lstClumnName.push_back(varColumnName);
	}

	return;
}

#if 0

void CTreeItemQuotes::getLstClumnName(QStringList& strlstClumnName )
{
	QString strColumnName;

	strlstClumnName.clear();

	//static const std::string DEFVALUE_String_ColumnName_SmartQuotes_InstrumentPriceChange = "Change";//Change//变动//价格变化颜色
	strColumnName = QObject::tr(DEFVALUE_String_ColumnName_SmartQuotes_InstrumentPriceChange.c_str());
	strlstClumnName.push_back(strColumnName);

	//static const std::string DEFVALUE_String_ColumnName_SmartQuotes_ExchangeName = "Exchange Name";//ExchangeName//交易所
	strColumnName = QObject::tr(DEFVALUE_String_ColumnName_SmartQuotes_ExchangeName.c_str());
	strlstClumnName.push_back(strColumnName);

	//static const std::string DEFVALUE_String_ColumnName_SmartQuotes_InstrumentCode = "Contract Name";//InstrumentCode//合约名称
	strColumnName = QObject::tr(DEFVALUE_String_ColumnName_SmartQuotes_InstrumentCode.c_str());
	strlstClumnName.push_back(strColumnName);

	//static const std::string DEFVALUE_String_ColumnName_SmartQuotes_BidVolume = "Bid Volume";//BidVolume//买量
	strColumnName = QObject::tr(DEFVALUE_String_ColumnName_SmartQuotes_BidVolume.c_str());
	strlstClumnName.push_back(strColumnName);

	//static const std::string DEFVALUE_String_ColumnName_SmartQuotes_BidPrice = "Bid";//BidPrice//买价
	strColumnName = QObject::tr(DEFVALUE_String_ColumnName_SmartQuotes_BidPrice.c_str());
	strlstClumnName.push_back(strColumnName);

	//static const std::string DEFVALUE_String_ColumnName_SmartQuotes_AskVolume = "Offer Volume";//AskVolume//卖量
	strColumnName = QObject::tr(DEFVALUE_String_ColumnName_SmartQuotes_AskVolume.c_str());
	strlstClumnName.push_back(strColumnName);

	//static const std::string DEFVALUE_String_ColumnName_SmartQuotes_AskPrice = "Offer";//AskPrice//卖价
	strColumnName = QObject::tr(DEFVALUE_String_ColumnName_SmartQuotes_AskPrice.c_str());
	strlstClumnName.push_back(strColumnName);

	//static const std::string DEFVALUE_String_ColumnName_SmartQuotes_LastVolume = "Last Volume";//LastVolume//成交量
	strColumnName = QObject::tr(DEFVALUE_String_ColumnName_SmartQuotes_LastVolume.c_str());
	strlstClumnName.push_back(strColumnName);

	//static const std::string DEFVALUE_String_ColumnName_SmartQuotes_LastPrice = "Last";//LastPrice//成交价
	strColumnName = QObject::tr(DEFVALUE_String_ColumnName_SmartQuotes_LastPrice.c_str());
	strlstClumnName.push_back(strColumnName);


	//static const std::string DEFVALUE_String_ColumnName_SmartQuotes_YDSP = "YDSP";//YDSP//昨收盘
	strColumnName = QObject::tr(DEFVALUE_String_ColumnName_SmartQuotes_YDSP.c_str());
	strlstClumnName.push_back(strColumnName);

	//static const std::string DEFVALUE_String_ColumnName_SmartQuotes_MarketStatus = "Status";//MarketStatus//市场状态
	strColumnName = QObject::tr(DEFVALUE_String_ColumnName_SmartQuotes_MarketStatus.c_str());
	strlstClumnName.push_back(strColumnName);

	//static const std::string DEFVALUE_String_ColumnName_SmartQuotes_OpeningPrice = "Opening";//OpeningPrice//开市价
	strColumnName = QObject::tr(DEFVALUE_String_ColumnName_SmartQuotes_OpeningPrice.c_str());
	strlstClumnName.push_back(strColumnName);


	//static const std::string DEFVALUE_String_ColumnName_SmartQuotes_BidTotal = "Bid Total";//Bid Total//买累计
	strColumnName = QObject::tr(DEFVALUE_String_ColumnName_SmartQuotes_BidTotal.c_str());
	strlstClumnName.push_back(strColumnName);

	//static const std::string DEFVALUE_String_ColumnName_SmartQuotes_OfferTotal = "Offer Total";//Offer Total//卖累计
	strColumnName = QObject::tr(DEFVALUE_String_ColumnName_SmartQuotes_OfferTotal.c_str());
	strlstClumnName.push_back(strColumnName);


	//static const std::string DEFVALUE_String_ColumnName_SmartQuotes_LowPrice = "Low";//LowPrice//最低价
	strColumnName = QObject::tr(DEFVALUE_String_ColumnName_SmartQuotes_LowPrice.c_str());
	strlstClumnName.push_back(strColumnName);

	//static const std::string DEFVALUE_String_ColumnName_SmartQuotes_HighPrice = "High";//HighPrice//最高价
	strColumnName = QObject::tr(DEFVALUE_String_ColumnName_SmartQuotes_HighPrice.c_str());
	strlstClumnName.push_back(strColumnName);


	//static const std::string DEFVALUE_String_ColumnName_SmartQuotes_Closeing = "Closeing";//Closeing//收盘价
	strColumnName = QObject::tr(DEFVALUE_String_ColumnName_SmartQuotes_Closeing.c_str());
	strlstClumnName.push_back(strColumnName);

	//static const std::string DEFVALUE_String_ColumnName_SmartQuotes_RefPrice = "Ref Price";//Ref Price//参考价
	strColumnName = QObject::tr(DEFVALUE_String_ColumnName_SmartQuotes_RefPrice.c_str());
	strlstClumnName.push_back(strColumnName);

	//static const std::string DEFVALUE_String_ColumnName_SmartQuotes_strUpdateTime = "UpdateTime";//更新时间
	strColumnName = QObject::tr(DEFVALUE_String_ColumnName_SmartQuotes_strUpdateTime.c_str());
	strlstClumnName.push_back(strColumnName);


}
#endif


#if 0

void CTreeItemQuotes::getLstClumnName(QList<QVariant>& lstClumnName )
{
	QList<QVariant> dataTreeItem;
	QVariant strColumnName;
	dataTreeItem.clear();

	//static const std::string DEFVALUE_String_ColumnName_SmartQuotes_InstrumentPriceChange = "Change";//Change//变动//价格变化颜色
	strColumnName = QVariant(DEFVALUE_String_ColumnName_SmartQuotes_InstrumentPriceChange.c_str());
	dataTreeItem.push_back(strColumnName);


	//static const std::string DEFVALUE_String_ColumnName_SmartQuotes_ExchangeName = "Exchange Name";//ExchangeName//交易所
	strColumnName = QVariant(DEFVALUE_String_ColumnName_SmartQuotes_ExchangeName.c_str());
	dataTreeItem.push_back(strColumnName);

	//static const std::string DEFVALUE_String_ColumnName_SmartQuotes_InstrumentCode = "Contract Name";//InstrumentCode//合约名称
	strColumnName = QVariant(DEFVALUE_String_ColumnName_SmartQuotes_InstrumentCode.c_str());
	dataTreeItem.push_back(strColumnName);

	//static const std::string DEFVALUE_String_ColumnName_SmartQuotes_BidVolume = "Bid Volume";//BidVolume//买量
	strColumnName = QVariant(DEFVALUE_String_ColumnName_SmartQuotes_BidVolume.c_str());
	dataTreeItem.push_back(strColumnName);

	//static const std::string DEFVALUE_String_ColumnName_SmartQuotes_BidPrice = "Bid";//BidPrice//买价
	strColumnName = QVariant(DEFVALUE_String_ColumnName_SmartQuotes_BidPrice.c_str());
	dataTreeItem.push_back(strColumnName);

	//static const std::string DEFVALUE_String_ColumnName_SmartQuotes_AskVolume = "Offer Volume";//AskVolume//卖量
	strColumnName = QVariant(DEFVALUE_String_ColumnName_SmartQuotes_AskVolume.c_str());
	dataTreeItem.push_back(strColumnName);

	//static const std::string DEFVALUE_String_ColumnName_SmartQuotes_AskPrice = "Offer";//AskPrice//卖价
	strColumnName = QVariant(DEFVALUE_String_ColumnName_SmartQuotes_AskPrice.c_str());
	dataTreeItem.push_back(strColumnName);

	//static const std::string DEFVALUE_String_ColumnName_SmartQuotes_LastVolume = "Last Volume";//LastVolume//成交量
	strColumnName = QVariant(DEFVALUE_String_ColumnName_SmartQuotes_LastVolume.c_str());
	dataTreeItem.push_back(strColumnName);

	//static const std::string DEFVALUE_String_ColumnName_SmartQuotes_LastPrice = "Last";//LastPrice//成交价
	strColumnName = QVariant(DEFVALUE_String_ColumnName_SmartQuotes_LastPrice.c_str());
	dataTreeItem.push_back(strColumnName);


	//static const std::string DEFVALUE_String_ColumnName_SmartQuotes_YDSP = "YDSP";//YDSP//昨收盘
	strColumnName = QVariant(DEFVALUE_String_ColumnName_SmartQuotes_YDSP.c_str());
	dataTreeItem.push_back(strColumnName);

	//static const std::string DEFVALUE_String_ColumnName_SmartQuotes_MarketStatus = "Status";//MarketStatus//市场状态
	strColumnName = QVariant(DEFVALUE_String_ColumnName_SmartQuotes_MarketStatus.c_str());
	dataTreeItem.push_back(strColumnName);

	//static const std::string DEFVALUE_String_ColumnName_SmartQuotes_OpeningPrice = "Opening";//OpeningPrice//开市价
	strColumnName = QVariant(DEFVALUE_String_ColumnName_SmartQuotes_OpeningPrice.c_str());
	dataTreeItem.push_back(strColumnName);


	//static const std::string DEFVALUE_String_ColumnName_SmartQuotes_BidTotal = "Bid Total";//Bid Total//买累计
	strColumnName = QVariant(DEFVALUE_String_ColumnName_SmartQuotes_BidTotal.c_str());
	dataTreeItem.push_back(strColumnName);

	//static const std::string DEFVALUE_String_ColumnName_SmartQuotes_OfferTotal = "Offer Total";//Offer Total//卖累计
	strColumnName = QVariant(DEFVALUE_String_ColumnName_SmartQuotes_OfferTotal.c_str());
	dataTreeItem.push_back(strColumnName);


	//static const std::string DEFVALUE_String_ColumnName_SmartQuotes_LowPrice = "Low";//LowPrice//最低价
	strColumnName = QVariant(DEFVALUE_String_ColumnName_SmartQuotes_LowPrice.c_str());
	dataTreeItem.push_back(strColumnName);

	//static const std::string DEFVALUE_String_ColumnName_SmartQuotes_HighPrice = "High";//HighPrice//最高价
	strColumnName = QVariant(DEFVALUE_String_ColumnName_SmartQuotes_HighPrice.c_str());
	dataTreeItem.push_back(strColumnName);


	//static const std::string DEFVALUE_String_ColumnName_SmartQuotes_Closeing = "Closeing";//Closeing//收盘价
	strColumnName = QVariant(DEFVALUE_String_ColumnName_SmartQuotes_Closeing.c_str());
	dataTreeItem.push_back(strColumnName);

	//static const std::string DEFVALUE_String_ColumnName_SmartQuotes_RefPrice = "Ref Price";//Ref Price//参考价
	strColumnName = QVariant(DEFVALUE_String_ColumnName_SmartQuotes_RefPrice.c_str());
	dataTreeItem.push_back(strColumnName);

	//static const std::string DEFVALUE_String_ColumnName_SmartQuotes_strUpdateTime = "UpdateTime";//更新时间
	strColumnName = QVariant(DEFVALUE_String_ColumnName_SmartQuotes_strUpdateTime.c_str());
	dataTreeItem.push_back(strColumnName);


	lstClumnName.clear();
	lstClumnName = dataTreeItem;
}
#endif


bool CItemUserInstrumentInfo::insertChildren( int position, int count, int columns )
{
	if (position < 0 || position > m_LstChildItems.size())
	{
		return false;
	}

	for (int row = 0; row < count; ++row) 
	{
		QList<QVariant> dataTreeItem;
// 		for (int nColumn = 0; nColumn < columns; nColumn++)
// 		{
// 			dataTreeItem.push_back("");
// 		}
		CItemUserInstrumentInfo* pTreeItemInstrumentCode = NULL;
		pTreeItemInstrumentCode = new CItemUserInstrumentInfo(dataTreeItem, this);
		pTreeItemInstrumentCode->resetCurrentNodeDataDefultValue();
		pTreeItemInstrumentCode->setDataType(ItemDataType_ITEM);
		m_LstChildItems.insert(position, pTreeItemInstrumentCode);
		pTreeItemInstrumentCode = NULL;

	}

	return true;
}

bool CItemUserInstrumentInfo::insertColumns( int position, int columns )
{
	if (position < 0 || position > m_ItemData.size())
	{
		return false;
	}

	for (int column = 0; column < columns; ++column)
	{
		m_ItemData.insert(position, QVariant());
	}

	foreach (CItemUserInstrumentInfo *children, m_LstChildItems)
	{
		children->insertColumns(position, columns);
	}

	return true;
}

bool CItemUserInstrumentInfo::removeColumns( int position, int columns )
{
	QList<QVariant>::Iterator iterList;

	if (position < 0 || position + columns > m_ItemData.size())
	{
		return false;
	}

	for (int column = 0; column < columns; ++column)
	{
		//m_ItemData.remove(position);

		iterList = m_ItemData.begin();
		iterList += position;
		m_ItemData.erase(iterList);
	}

	foreach (CItemUserInstrumentInfo *child, m_LstChildItems)
	{
		child->removeColumns(position, columns);
	}

	return true;
}

bool CItemUserInstrumentInfo::setData( int column, const QVariant &dataValue )
{
	if (column < 0 || column >= m_ItemData.size())
	{
		return false;
	}

	m_ItemData[column] = dataValue;

	return true;
}

QString CItemUserInstrumentInfo::getInstrumentCode()
{
	return m_strInstrumentCode;
}

float CItemUserInstrumentInfo::getLastPrice()
{
	return m_fLastPrice;
}

void CItemUserInstrumentInfo::rootNodeRetColumnsName()
{
	if (CItemUserInstrumentInfo::ItemDataType_ROOT != m_nDataType)
	{
		return;
	}
	m_ItemData.clear();
	m_ItemDataNum = 0;

	CItemUserInstrumentInfo::getLstClumnName(m_ItemData);

	m_ItemDataNum = m_ItemData.count();
	this->setDataType(CItemUserInstrumentInfo::ItemDataType_ROOT);
}

void CItemUserInstrumentInfo::removeChildByData( CUserInstrumentInfoHelper* pExchangeInfo )
{
	CItemUserInstrumentInfo* pTreeItemFind = NULL;
	QList<CItemUserInstrumentInfo*>::iterator iterLst;
	unsigned int nInstrumentID = 0;
	nInstrumentID = pExchangeInfo->getInstrumentID();

	iterLst = m_LstChildItems.begin();
	while (iterLst != m_LstChildItems.end())
	{
		pTreeItemFind = (*iterLst);

		if (pTreeItemFind->getInstrumentID() == nInstrumentID)
		{
			delete pTreeItemFind;
			pTreeItemFind = NULL;

			m_LstChildItems.erase(iterLst);// removeAt()
			break;
		}

		iterLst++;
	}
}


//QT_END_NAMESPACE

