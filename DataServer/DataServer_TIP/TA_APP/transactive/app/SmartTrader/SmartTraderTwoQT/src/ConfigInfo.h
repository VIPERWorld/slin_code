#ifndef __CLASS_CONFIGINFO__HH__
#define __CLASS_CONFIGINFO__HH__

#include <QtCore/QString>
#include <QtCore/QStringList>

#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>

//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE

class CConfigFileHelper;

class CConfigInfo
{
public:
	static CConfigInfo& getInstance();
	static void removeInstance();

private:
	static CConfigInfo* m_pInstance;
	static QMutex m_mutexInstance;

public:
	CConfigInfo();
	virtual ~CConfigInfo();
public:
	void setSQLiteDBPath(const QString& strSQLiteDBPath);
	QString getSQLiteDBPath();
	void setFileDBPath(const QString& strFileDBPath);
	QString getFileDBPath();
	void setLastUpdateTime(const QString& strLastUpdateTime);
	QString getLastUpdateTime();
public:
	QStringList getLstUserInstrument();
	void setLstUserInstrument(QStringList& lstStringValue);
	void removeInstrument(const QString& strInstrumentID);
	void removeInstrument(unsigned int nInstrumentID);
	void addInstrument(const QString& strInstrumentID);
	void addInstrument(unsigned int nInstrumentID);
	bool checkUserInstrument(const QString& strInstrumentID);
	bool checkUserInstrument(unsigned int nInstrumentID);

private:
	void _LoadDataFromCfgFile();
	void _WriteDataToCfgFile();

private:
	QString m_strFileDBPath;
	QString m_strSQLiteDBPath;
	QString m_strLastUpdateTime;
	QStringList m_LstUserInstrument;

private:
	CConfigFileHelper* m_pConfigFileHelper;
};
//QT_END_NAMESPACE
#endif  // __CLASS_CONFIGINFO__HH__



