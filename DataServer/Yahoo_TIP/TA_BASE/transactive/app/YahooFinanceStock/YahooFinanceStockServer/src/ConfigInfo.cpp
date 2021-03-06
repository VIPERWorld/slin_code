#include "ConfigInfo.h"

#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>

#include "CfgFileUtil.h"

#include "Log4cppLogger.h"

static const char* DEFAULT_STRING_VALUE_STRING_SPLIT = ",";


static const char*  DEF_VALUE_CONFIG_FILE = "./config.ini";
static const char*  DEF_VALUE_CONFIG_GROUP_config = "config";
static const char*  DEF_VALUE_CONFIG_GROUP_config_KEY_filedbpath = "filedbpath";
static const char*  DEF_VALUE_CONFIG_GROUP_config_KEY_filedbpath_defValue = "C:/LSL/LSL_DATA/SaveDataFile/";
static const char*  DEF_VALUE_CONFIG_GROUP_config_KEY_sqlitedbpath = "sqlitedbpath";
static const char*  DEF_VALUE_CONFIG_GROUP_config_KEY_sqlitedbpath_defValue = "C:/LSL/LSL_DATA/SaveDataSqliteDB/";

static const char*  DEF_VALUE_CONFIG_GROUP_config_KEY_serverdbpath = "serverdbpath";
static const char*  DEF_VALUE_CONFIG_GROUP_config_KEY_serverdbpath_defValue = "C:/LSL/LSL_DATA/ServerDB/";

//static const char* DEF_VALUE_STRING_UTC_START_DATE_TIME = "1970-01-01 08:00:00";
static const char*  DEF_VALUE_CONFIG_GROUP_config_KEY_userinstrument = "userinstrument";
static const char*  DEF_VALUE_CONFIG_GROUP_config_KEY_userinstrument_defValue = "";//5614,5378

static const char*  DEF_VALUE_CONFIG_GROUP_config_KEY_minstockindex = "minstockindex";
static const qint32  DEF_VALUE_CONFIG_GROUP_config_KEY_minstockindex_defValue = 0;
static const char*  DEF_VALUE_CONFIG_GROUP_config_KEY_maxstockindex = "maxstockindex";
static const qint32  DEF_VALUE_CONFIG_GROUP_config_KEY_maxstockindex_defValue = 2296;
static const char*  DEF_VALUE_CONFIG_GROUP_config_KEY_serverport = "serverport";
static const quint16  DEF_VALUE_CONFIG_GROUP_config_KEY_serverport_defValue = 5000;

CConfigInfo* CConfigInfo::m_pInstance = 0;
QMutex CConfigInfo::m_mutexInstance;

CConfigInfo& CConfigInfo::getInstance()
{	
	QMutexLocker lock(&m_mutexInstance);	
	if (NULL == m_pInstance)
	{
		m_pInstance = new CConfigInfo();
	}
	return (*m_pInstance);
}

void CConfigInfo::removeInstance()
{
	QMutexLocker lock(&m_mutexInstance);	
	if (NULL != m_pInstance)
	{
		delete m_pInstance;
		m_pInstance = NULL;
	}
}


CConfigInfo::CConfigInfo()
{
	m_strConfigFileName.clear();
	m_strFileDBPath.clear();
	m_strSQLiteDBPath.clear();
	m_strServerDBPath.clear();
	m_LstUserInstrument.clear();
	m_nMinStockIndex = -1;
	m_nMaxStockIndex = -1;
	m_nServerPort = 0;

	CCfgFileUtil::getInstance();

	m_strConfigFileName = DEF_VALUE_CONFIG_FILE;
	_LoadDataFromCfgFile();
}

CConfigInfo::~CConfigInfo()
{
	_WriteDataToCfgFile();
	CCfgFileUtil::removeInstance();
}

QString CConfigInfo::getFileDBPath()
{
	int nFunRes = 0;
	QString strGroup;
	QString strKey;
	QString strValue;

	if (m_strFileDBPath.isEmpty())
	{
		strGroup = DEF_VALUE_CONFIG_GROUP_config;
		strKey = DEF_VALUE_CONFIG_GROUP_config_KEY_filedbpath;
		strValue = DEF_VALUE_CONFIG_GROUP_config_KEY_filedbpath_defValue;
		nFunRes = CCfgFileUtil::getInstance().read(m_strConfigFileName, strGroup, strKey, strValue);
		if (0 != nFunRes)
		{
			strValue = DEF_VALUE_CONFIG_GROUP_config_KEY_filedbpath_defValue;
		}
		m_strFileDBPath = strValue;
	}

	return m_strFileDBPath;
}
void CConfigInfo::setFileDBPath(const QString& strFileDBPath)
{
	QMutexLocker lock(&m_mutexConfigFileHandle);
	QString strGroup;
	QString strKey;

	//if (strFileDBPath != m_strFileDBPath)
	{
		strGroup = DEF_VALUE_CONFIG_GROUP_config;
		strKey = DEF_VALUE_CONFIG_GROUP_config_KEY_filedbpath;
		CCfgFileUtil::getInstance().write(m_strConfigFileName, strGroup, strKey, strFileDBPath);
	}

	m_strFileDBPath = strFileDBPath;

}
QString CConfigInfo::getSQLiteDBPath()
{
	int nFunRes = 0;
	QString strGroup;
	QString strKey;
	QString strValue;

	if (m_strSQLiteDBPath.isEmpty())
	{
		strGroup = DEF_VALUE_CONFIG_GROUP_config;
		strKey = DEF_VALUE_CONFIG_GROUP_config_KEY_sqlitedbpath;
		strValue = DEF_VALUE_CONFIG_GROUP_config_KEY_sqlitedbpath_defValue;
		nFunRes = CCfgFileUtil::getInstance().read(m_strConfigFileName, strGroup, strKey, strValue);
		if (0 != nFunRes)
		{
			strValue = DEF_VALUE_CONFIG_GROUP_config_KEY_sqlitedbpath_defValue;
		}
		m_strSQLiteDBPath = strValue;
	}

	return m_strSQLiteDBPath;
}
void CConfigInfo::setSQLiteDBPath(const QString& strSQLiteDBPath)
{
	QMutexLocker lock(&m_mutexConfigFileHandle);
	QString strGroup;
	QString strKey;

	//if (strSQLiteDBPath != m_strSQLiteDBPath)
	{
		strGroup = DEF_VALUE_CONFIG_GROUP_config;
		strKey = DEF_VALUE_CONFIG_GROUP_config_KEY_sqlitedbpath;
		CCfgFileUtil::getInstance().write(m_strConfigFileName, strGroup, strKey, strSQLiteDBPath);
	}

	m_strSQLiteDBPath = strSQLiteDBPath;
}


void CConfigInfo::_LoadDataFromCfgFile()
{
	getFileDBPath();
	getSQLiteDBPath();
	getLstUserInstrument();
	getMinStockIndex();
	getMaxStockIndex();
	getServerPort();
	getServerDBPath();
}

void CConfigInfo::_WriteDataToCfgFile()
{
	QString strValue;
	QStringList strLstValue;
	strValue = m_strFileDBPath;
	setFileDBPath(strValue);
	strValue = m_strSQLiteDBPath;
	setSQLiteDBPath(strValue);
	strLstValue = m_LstUserInstrument;
	setLstUserInstrument(strLstValue);

}


QStringList CConfigInfo::getLstUserInstrument()
{
	int nFunRes = 0;
	QString strGroup;
	QString strKey;
	QString strValue;

	if (m_LstUserInstrument.isEmpty())
	{
		strGroup = DEF_VALUE_CONFIG_GROUP_config;
		strKey = DEF_VALUE_CONFIG_GROUP_config_KEY_userinstrument;
		strValue = DEF_VALUE_CONFIG_GROUP_config_KEY_userinstrument_defValue;
		nFunRes = CCfgFileUtil::getInstance().read(m_strConfigFileName, strGroup, strKey, strValue);
		if (0 != nFunRes)
		{
			strValue = DEF_VALUE_CONFIG_GROUP_config_KEY_userinstrument_defValue;
		}
		m_LstUserInstrument = strValue.split(DEFAULT_STRING_VALUE_STRING_SPLIT);
	}

	return m_LstUserInstrument;
}

void CConfigInfo::removeInstrument(const QString& strInstrumentID)
{
	QStringList lstStringValue;
	QStringList lstStringValueNew;
	QString  strValue;

	lstStringValue = getLstUserInstrument();

	foreach (const QString& strValue, lstStringValue)
	{
		if (strInstrumentID != strValue)
		{
			lstStringValueNew.push_back(strValue);
		}
	}

	setLstUserInstrument(lstStringValueNew);


}

void CConfigInfo::removeInstrument( unsigned int nInstrumentID )
{
	QString strUserInstruemt;
	strUserInstruemt = QString("%1").arg(nInstrumentID);

	removeInstrument(strUserInstruemt);

}

void CConfigInfo::addInstrument(const QString& strInstrumentID)
{
	QStringList lstStringValue;
	lstStringValue = getLstUserInstrument();

	if (!lstStringValue.contains(strInstrumentID))
	{
		lstStringValue.push_back(strInstrumentID);
		setLstUserInstrument(lstStringValue);
	}
}

void CConfigInfo::addInstrument( unsigned int nInstrumentID )
{
	QString strUserInstruemt;
	strUserInstruemt = QString("%1").arg(nInstrumentID);

	addInstrument(strUserInstruemt);
}

void CConfigInfo::setLstUserInstrument(const QStringList& lstStringValue )
{
	QMutexLocker lock(&m_mutexConfigFileHandle);
	QString strGroup;
	QString strKey;
	QString strValue;

	m_LstUserInstrument.clear();
	m_LstUserInstrument = lstStringValue;

	strValue = m_LstUserInstrument.join(DEFAULT_STRING_VALUE_STRING_SPLIT);//","

	{
		strGroup = DEF_VALUE_CONFIG_GROUP_config;
		strKey = DEF_VALUE_CONFIG_GROUP_config_KEY_userinstrument;
		CCfgFileUtil::getInstance().write(m_strConfigFileName, strGroup, strKey, strValue);
	}


}
bool CConfigInfo::checkUserInstrument( const QString& strInstrumentID )
{
	bool bFunRes = false;
	//subscribeMarketData user hot Instrument
	QStringList LstUserInstrument;
	LstUserInstrument = CConfigInfo::getInstance().getLstUserInstrument();
	if (LstUserInstrument.contains(strInstrumentID))
	{
		bFunRes = true;
	}

	return bFunRes;
}

bool CConfigInfo::checkUserInstrument( unsigned int nInstrumentID )
{
	QString strUserInstruemt;
	strUserInstruemt = QString("%1").arg(nInstrumentID);
	return checkUserInstrument(strUserInstruemt);
}

qint32 CConfigInfo::getMinStockIndex()
{
	int nFunRes = 0;
	QString strGroup;
	QString strKey;
	QString strValue;

	if (-1 == m_nMinStockIndex)
	{
		strGroup = DEF_VALUE_CONFIG_GROUP_config;
		strKey = DEF_VALUE_CONFIG_GROUP_config_KEY_minstockindex;
		strValue = QString("%1").arg(DEF_VALUE_CONFIG_GROUP_config_KEY_minstockindex_defValue);
		nFunRes = CCfgFileUtil::getInstance().read(m_strConfigFileName, strGroup, strKey, strValue);
		if (0 != nFunRes)
		{
			strValue = QString("%1").arg(DEF_VALUE_CONFIG_GROUP_config_KEY_minstockindex_defValue);
		}
		m_nMinStockIndex = strValue.toInt();
	}

	return m_nMinStockIndex;
}

qint32 CConfigInfo::getMaxStockIndex()
{
	int nFunRes = 0;
	QString strGroup;
	QString strKey;
	QString strValue;

	if (-1 == m_nMaxStockIndex)
	{
		strGroup = DEF_VALUE_CONFIG_GROUP_config;
		strKey = DEF_VALUE_CONFIG_GROUP_config_KEY_maxstockindex;
		strValue = QString("%1").arg(DEF_VALUE_CONFIG_GROUP_config_KEY_maxstockindex_defValue);
		nFunRes = CCfgFileUtil::getInstance().read(m_strConfigFileName, strGroup, strKey, strValue);
		if (0 != nFunRes)
		{
			strValue = QString("%1").arg(DEF_VALUE_CONFIG_GROUP_config_KEY_maxstockindex_defValue);
		}
		m_nMaxStockIndex = strValue.toInt();
	}

	return m_nMaxStockIndex;
}

quint16 CConfigInfo::getServerPort()
{
	int nFunRes = 0;
	QString strGroup;
	QString strKey;
	QString strValue;

	if (0 == m_nServerPort)
	{
		strGroup = DEF_VALUE_CONFIG_GROUP_config;
		strKey = DEF_VALUE_CONFIG_GROUP_config_KEY_serverport;
		strValue = QString("%1").arg(DEF_VALUE_CONFIG_GROUP_config_KEY_serverport_defValue);
		nFunRes = CCfgFileUtil::getInstance().read(m_strConfigFileName, strGroup, strKey, strValue);
		if (0 != nFunRes)
		{
			strValue = QString("%1").arg(DEF_VALUE_CONFIG_GROUP_config_KEY_serverport_defValue);
		}
		m_nServerPort = strValue.toUShort();
	}

	return m_nServerPort;
}

QString CConfigInfo::getServerDBPath()
{
	int nFunRes = 0;
	QString strGroup;
	QString strKey;
	QString strValue;

	if (m_strServerDBPath.isEmpty())
	{
		strGroup = DEF_VALUE_CONFIG_GROUP_config;
		strKey = DEF_VALUE_CONFIG_GROUP_config_KEY_serverdbpath;
		strValue = QString("%1").arg(DEF_VALUE_CONFIG_GROUP_config_KEY_serverdbpath_defValue);
		nFunRes = CCfgFileUtil::getInstance().read(m_strConfigFileName, strGroup, strKey, strValue);
		if (0 != nFunRes)
		{
			strValue = QString("%1").arg(DEF_VALUE_CONFIG_GROUP_config_KEY_serverdbpath_defValue);
		}
		m_strServerDBPath = strValue;
	}

	return m_strServerDBPath;
}
