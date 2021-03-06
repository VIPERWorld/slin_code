#include "CheckTotalStocks.h"

#include <boost/chrono.hpp>
#include <boost/thread.hpp>


#include "BaseException.h"
#include "StockData.h"
#include "TotalStocksData.h"
#include "YahuoHistoryReqAck.h"

#include "Log4cppLogger.h"

static const std::string DEF_STRING_VALUE_filename_good = "yahuo_have_data.csv";
static const std::string DEF_STRING_VALUE_filename_bad = "yahuo_not_have_data.csv";


CCheckTotalStocks::CCheckTotalStocks()
{
	m_nWorkState = WorkState_Begin;

	m_strFileName_Good = DEF_STRING_VALUE_filename_good;
	m_strFileName_Bad = DEF_STRING_VALUE_filename_bad;
	remove(m_strFileName_Good.c_str());
	remove(m_strFileName_Bad.c_str());

	// Open the file for appending (retain existing entries) 
	m_streamFile_Good.open(m_strFileName_Good.c_str(), std::ios::out | std::ios::app);
	if (m_streamFile_Good.is_open())
	{
		m_streamFile_Good.flush();
	}
	else
	{
		m_streamFile_Good.close();
	}

	// Open the file for appending (retain existing entries) 
	m_streamFile_Bad.open(m_strFileName_Bad.c_str(), std::ios::out | std::ios::app);
	if (m_streamFile_Bad.is_open())
	{
		m_streamFile_Bad.flush();
	}
	else
	{
		m_streamFile_Bad.close();
	}


	_FreeData_MapStockDataItemT_Total();
	_FreeData_MapStockDataItemT_Good();
	_FreeData_MapStockDataItemT_Bad();
}

CCheckTotalStocks::~CCheckTotalStocks()
{
	if (m_streamFile_Good.is_open())
	{
		m_streamFile_Good.clear();
		m_streamFile_Good.close();
	}
	if (m_streamFile_Bad.is_open())
	{
		m_streamFile_Bad.clear();
		m_streamFile_Bad.close();
	}


	_FreeData_MapStockDataItemT_Total();
	_FreeData_MapStockDataItemT_Good();
	_FreeData_MapStockDataItemT_Bad();
}

void CCheckTotalStocks::do_check()
{
	m_nWorkState = WorkState_Begin;
	_LoadData_MapStockDataItemT_Total();
	_CheckTotalData();
	_SaveDataToFile_Good();
	_SaveDataToFile_Bad();
	
	m_nWorkState = WorkState_End;
}

void CCheckTotalStocks::_LoadData_MapStockDataItemT_Total()
{
	int nArrSize = 0;
	CStockData* pCStockData = NULL;
	int nIndex = 0;
	std::string strSymbol;
	std::string strName;
	std::string strNamePinYin;
	std::string strSymbolExtern;
	std::string strSymbolUse;


	nArrSize = sizeof(s_SSSZ_Stocks) / sizeof (*s_SSSZ_Stocks);
	MYLOG4CPP_INFO<<"s_SSSZ_Stocks ArrSize="<<nArrSize;

	{
		boost::mutex::scoped_lock lock(m_mutexMapStockDataItemT_Total);
		for (nIndex = 0; nIndex < nArrSize; nIndex++)
		{
			pCStockData = new CStockData();

			strSymbol = s_SSSZ_Stocks[nIndex].m_psz_Symbol;
			//strName = s_SSSZ_Stocks[nIndex].m_psz_Name;
			strNamePinYin = s_SSSZ_Stocks[nIndex].m_psz_NamePinYin;
			strSymbolExtern = s_SSSZ_Stocks[nIndex].m_psz_SymbolExtern;
			strSymbolUse = strSymbol + strSymbolExtern;

			
			pCStockData->m_strSymbol = strSymbol;
			pCStockData->m_strNamePinYin = strNamePinYin;
			pCStockData->m_strSymbolExtern = strSymbolExtern;
			pCStockData->m_nIndex = nIndex;
			pCStockData->m_strSymbolUse = strSymbolUse;
			pCStockData->m_strName = strNamePinYin;

			m_MapStockDataItemT_Total.insert(
				MapStockDataItemValueTypeT(strSymbolUse, pCStockData));

			pCStockData = NULL;
		}//for
	}


	if (NULL != pCStockData)
	{
		delete pCStockData;
		pCStockData = NULL;
	}

}


void CCheckTotalStocks::_FreeData_MapStockDataItemT_Total()
{
	{
		boost::mutex::scoped_lock lock(m_mutexMapStockDataItemT_Total);
		_FreeData_MapStockDataItemT(m_MapStockDataItemT_Total);
	}

}

void CCheckTotalStocks::_FreeData_MapStockDataItemT_Good()
{
	{
		boost::mutex::scoped_lock lock(m_mutexMapStockDataItemT_Good);
		_FreeData_MapStockDataItemT(m_MapStockDataItemT_Good);
	}
}

void CCheckTotalStocks::_FreeData_MapStockDataItemT_Bad()
{
	{
		boost::mutex::scoped_lock lock(m_mutexMapStockDataItemT_Bad);
		_FreeData_MapStockDataItemT(m_MapStockDataItemT_Bad);
	}
}

void CCheckTotalStocks::_FreeData_MapStockDataItemT(MapStockDataItemT& mapStockData)
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

void CCheckTotalStocks::_CheckTotalData()
{

	boost::mutex::scoped_lock lockTotal(m_mutexMapStockDataItemT_Total);
	boost::mutex::scoped_lock lockGood(m_mutexMapStockDataItemT_Good);
	boost::mutex::scoped_lock lockBad(m_mutexMapStockDataItemT_Bad);

	MapStockDataItemIterT iterMap;
	CStockData* pData = NULL;
	int nFunCheckRes = 0;

	iterMap = m_MapStockDataItemT_Total.begin();
	while (iterMap != m_MapStockDataItemT_Total.end())
	{
		sleep(1000);


		pData = (iterMap->second);

		nFunCheckRes = 0;
		nFunCheckRes = _Test_YahuoHistoryReqAck(pData->m_strSymbolUse);
		if (0 == nFunCheckRes)
		{
			m_MapStockDataItemT_Good.insert(
				MapStockDataItemValueTypeT(pData->m_strSymbolUse, pData));	
			std::string strMessage = "have data";
			pData->logInfo(__FILE__, __LINE__, strMessage);

		}
		else
		{
			m_MapStockDataItemT_Bad.insert(
				MapStockDataItemValueTypeT(pData->m_strSymbolUse, pData));	

			std::string errorMessage = "_Test_YahuoHistoryReqAck error!!";
			pData->logInfo(__FILE__, __LINE__, errorMessage);

		}

		pData = NULL;
		iterMap++;
	}

	m_MapStockDataItemT_Total.clear();
}


int CCheckTotalStocks::_Test_YahuoHistoryReqAck(const std::string& strSymbolUse)
{
	int nFunRes = 0;

	CYahuoHistoryReqAck classCYahuoHistoryReqAck;
	std::string petr4HistoricalPrices;

	try
	{
		petr4HistoricalPrices = classCYahuoHistoryReqAck.getHistoricalQuotesCsv(
			strSymbolUse, 2014, 11, 10, 2014, 11, 13, YahuoReqAck::daily);
	}
	catch(CBaseException& e)
	{
		nFunRes = -1;
	}
	catch(...)
	{
		nFunRes = -1;
	}


	return nFunRes;
};

void CCheckTotalStocks::_SaveDataToFile_Bad()
{
	boost::mutex::scoped_lock lockBad(m_mutexMapStockDataItemT_Bad);

	MapStockDataItemIterT iterMap;
	CStockData* pData = NULL;

	iterMap = m_MapStockDataItemT_Bad.begin();
	while (iterMap != m_MapStockDataItemT_Bad.end())
	{
		pData = (iterMap->second);
		
		m_streamFile_Bad<<pData->getStringInfo()<<std::endl;
		pData = NULL;
		iterMap++;
	}

	
}

void CCheckTotalStocks::_SaveDataToFile_Good()
{
	boost::mutex::scoped_lock lockBad(m_mutexMapStockDataItemT_Good);

	MapStockDataItemIterT iterMap;
	CStockData* pData = NULL;

	iterMap = m_MapStockDataItemT_Good.begin();
	while (iterMap != m_MapStockDataItemT_Good.end())
	{
		pData = (iterMap->second);

		m_streamFile_Good<<pData->getStringInfo()<<std::endl;
		pData = NULL;
		iterMap++;
	}


}

void CCheckTotalStocks::sleep(unsigned int milliSeconds)
{  

	boost::xtime timeTmp;
	boost::xtime_get(&timeTmp, boost::TIME_UTC_);
	timeTmp.nsec += milliSeconds%1000*1000*1000;
	timeTmp.sec += milliSeconds/1000;
	boost::thread::sleep(timeTmp);
	//boost::this_thread::sleep(boost::posix_time::milliseconds(500));
}


