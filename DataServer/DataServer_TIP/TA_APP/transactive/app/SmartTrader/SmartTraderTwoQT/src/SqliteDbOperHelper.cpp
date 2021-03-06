#include "SqliteDbOperHelper.h"

#include "BaseException.h"

#include "HistoryData.h"
#include "SqliteDbOper.h"
#include "Log4cppLogger.h"





CSqliteDbOperHelper::CSqliteDbOperHelper( const std::string& strSymbolUse )
{
	m_strSymbolUse = strSymbolUse;

	QMutexLocker lock(&m_mutex_SqliteDbOper);
	m_pSqliteDbOper = NULL;
	m_pSqliteDbOper = new CSqliteDbOper();
	m_pSqliteDbOper->setDataBaseValue(strSymbolUse.c_str());

}

CSqliteDbOperHelper::~CSqliteDbOperHelper()
{	

	QMutexLocker lock(&m_mutex_SqliteDbOper);	
	if (NULL != m_pSqliteDbOper)
	{
		delete m_pSqliteDbOper;
		m_pSqliteDbOper = NULL;
	}

}

void CSqliteDbOperHelper::_AnalysisData(QStringList& strLstLines, LstHistoryDataT& lstData)
{
	CHistoryData* pHistoryData = NULL;

	foreach (const QString& strLine, strLstLines)
	{
		if (false == strLine.isEmpty())
		{
			pHistoryData = new CHistoryData();
			pHistoryData->resetValue(strLine);

			lstData.push_back(pHistoryData);
		}

		pHistoryData = NULL;
	}//foreach

	if (NULL != pHistoryData)
	{
		delete pHistoryData;
		pHistoryData = NULL;
	}
}

void CSqliteDbOperHelper::_FreeData(LstHistoryDataT* pLstData)
{
	LstHistoryDataIterT iterLst;
	CHistoryData* pDataTmp = NULL;

	if (pLstData->empty())
	{
		return;
	}

	iterLst = pLstData->begin();
	while (iterLst != pLstData->end())
	{
		pDataTmp = (*iterLst);

		delete pDataTmp;
		pDataTmp = NULL;

		iterLst++;
	}//while

	pLstData->clear();
	return;
}

void CSqliteDbOperHelper::saveData(const std::string& strSymbolUse, const std::string& strHistoryData)
{
	QMutexLocker lock(&m_mutex_SqliteDbOper);	

	QString strHistoryDataTmp;
	QStringList strListHistoryDataTmp;
	LstHistoryDataT lstHistoryData;

	strHistoryDataTmp = strHistoryData.c_str();

	strListHistoryDataTmp.clear();
	strListHistoryDataTmp = strHistoryDataTmp.split("\n");

	if (strListHistoryDataTmp.size() >= 1)
	{
		strListHistoryDataTmp[0] = "";
		strListHistoryDataTmp[0].clear();// = "";//column name set null
	}
	_AnalysisData(strListHistoryDataTmp, lstHistoryData);

	if (m_strSymbolUse != strSymbolUse)
	{
		m_strSymbolUse = strSymbolUse;
		m_pSqliteDbOper->resetDataBaseValue(m_strSymbolUse.c_str());
	}

	m_pSqliteDbOper->saveData(&lstHistoryData);

	strListHistoryDataTmp.clear();
	_FreeData(&lstHistoryData);
	lstHistoryData.clear();
}

int CSqliteDbOperHelper::selectData(
	const std::string& strSymbolUse,
	const std::string& strFrom, 
	const std::string& strTo, 
	LstHistoryDataT& lstData )
{
	QMutexLocker lock(&m_mutex_SqliteDbOper);	
	if (m_strSymbolUse != strSymbolUse)
	{
		m_strSymbolUse = strSymbolUse;
		m_pSqliteDbOper->resetDataBaseValue(m_strSymbolUse.c_str());
	}
	m_pSqliteDbOper->selectData(strFrom, strTo, lstData);

	return 0;
}

std::string CSqliteDbOperHelper::getSymbolUse()
{
	return m_strSymbolUse;
}



