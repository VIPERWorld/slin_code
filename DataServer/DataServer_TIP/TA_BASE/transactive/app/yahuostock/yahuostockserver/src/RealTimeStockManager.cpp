#include "RealTimeStockManager.h"

#include "BaseException.h"
#include "StockData.h"
#include "StockManager.h"
#include "Log4cppLogger.h"
#include "YahuoRealTimeReqAck.h"


CRealTimeStockManager* CRealTimeStockManager::m_pInstance = 0;
QMutex CRealTimeStockManager::m_mutexInstance;

CRealTimeStockManager& CRealTimeStockManager::getInstance()
{	
	QMutexLocker lock(&m_mutexInstance);	
	if (NULL == m_pInstance)
	{
		m_pInstance = new CRealTimeStockManager();
	}
	return (*m_pInstance);
}

void CRealTimeStockManager::removeInstance()
{
	QMutexLocker lock(&m_mutexInstance);	
	delete m_pInstance;
	m_pInstance = NULL;
}

CRealTimeStockManager::CRealTimeStockManager()
{
	_FreeData_MapStockDataItemT_RealTime();
}

CRealTimeStockManager::~CRealTimeStockManager()
{	
	_FreeData_MapStockDataItemT_RealTime();	
}




void CRealTimeStockManager::_FreeData_MapStockDataItemT_RealTime()
{
	QMutexLocker lock(&m_mutexMapStockDataItemT_RealTime);	
	_FreeData_MapStockDataItemT(m_MapStockDataItemT_RealTime);
}


void CRealTimeStockManager::_FreeData_MapStockDataItemT(MapStockDataItemT& mapStockData)
{
	MapStockDataItemIterT iterMap;
	CStockData* pData = NULL;

	iterMap = mapStockData.begin();
	while (iterMap != mapStockData.end())
	{
		pData = (iterMap->second);

		delete pData;
		pData = NULL;

		iterMap++;
	}
	mapStockData.clear();
	return;
}

void CRealTimeStockManager::addRealTimeReq( const CStockData* pStockData )
{
	CStockData* pData = NULL;
	pData = new CStockData();

	*pData = *pStockData;
	QMutexLocker lock(&m_mutexMapStockDataItemT_RealTime);	
	m_MapStockDataItemT_RealTime.insert(
		MapStockDataItemValueTypeT(pData->m_strSymbolUse, pData));

	pData = NULL;
}

void CRealTimeStockManager::addRealTimeReq( const std::string& strSymbolUse )
{
	const CStockData* pDataFind = NULL;

	pDataFind = NULL;
	pDataFind = CStockManager::getInstance().find_StockData_BySymbolUse(strSymbolUse);
	if (NULL == pDataFind)
	{
		MYLOG4CPP_ERROR<<"not find strSymbolUse="<<strSymbolUse;
		return;
	}
	addRealTimeReq(pDataFind);
}


void CRealTimeStockManager::subscribeMarketData(const std::string& strSymbolUse)
{
	int nFunRes = 0;
	std::list<YahuoReqAck::QuoteType> lstQuoteTypes;
	lstQuoteTypes.push_back(YahuoReqAck::stockExchange);
	lstQuoteTypes.push_back(YahuoReqAck::symbol);
	lstQuoteTypes.push_back(YahuoReqAck::changeRealTime);
	lstQuoteTypes.push_back(YahuoReqAck::changeinPercent);
	lstQuoteTypes.push_back(YahuoReqAck::lastTradeDate);
	lstQuoteTypes.push_back(YahuoReqAck::lastTradeTime);
	lstQuoteTypes.push_back(YahuoReqAck::open);
	lstQuoteTypes.push_back(YahuoReqAck::bid);
	lstQuoteTypes.push_back(YahuoReqAck::ask);
	lstQuoteTypes.push_back(YahuoReqAck::dayLow);
	lstQuoteTypes.push_back(YahuoReqAck::dayHigh);
	lstQuoteTypes.push_back(YahuoReqAck::dayRange);
	lstQuoteTypes.push_back(YahuoReqAck::lastTradePriceOnly);
	lstQuoteTypes.push_back(YahuoReqAck::_1yrTargetPrice);
	lstQuoteTypes.push_back(YahuoReqAck::volume);
	lstQuoteTypes.push_back(YahuoReqAck::averageDailyVolume);
	lstQuoteTypes.push_back(YahuoReqAck::name);

	CYahuoRealTimeReqAck  classCYahuoRealTimeReqAck;
	std::string petr4Quotes;

	try
	{
		petr4Quotes = classCYahuoRealTimeReqAck.getLatestQuotesCsv(strSymbolUse, lstQuoteTypes);
		std::cout << petr4Quotes << std::endl;
	}
	catch(CBaseException& e)
	{
		nFunRes = -1;
	}
	catch(...)
	{
		nFunRes = -1;
	}

}
