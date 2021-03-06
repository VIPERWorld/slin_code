#ifndef __CLASS_CLIENT_DB_MAMAGER__HH__
#define __CLASS_CLIENT_DB_MAMAGER__HH__

#include <QtCore/QObject>
#include <QtCore/QMap>
#include <QtCore/QList>
#include <QtCore/QVariant>
#include <QtCore/QString>

#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>

class CQtTimeHelper;
class CUserInfo;
class CClientDbOper;
class CHistoryData;
class QSqlDatabase;
class CStockMinTimeMaxTime;
class CUserTradeInfo;
class CUserAccount;
class CUserHoldAccount;
class CStockInfo;

class CClientDBManager
{
public:
	static CClientDBManager& getInstance();
	static void removeInstance();

private:
	static CClientDBManager* m_pInstance;
	static QMutex m_mutexInstance;
private:
	CClientDBManager(void);
	~CClientDBManager(void);
public:
	void resetDataHistory(const QString& strSymbolUse, const QList<CHistoryData*>& lstData);

public:
	qint32 insertSymbolMinMaxTime(const CStockMinTimeMaxTime* pData);
	qint32 updateSymbolMinMaxTime(const CStockMinTimeMaxTime* pData);
	qint32 selectSymbolMinMaxTime(const QString& strSymbolUse, CStockMinTimeMaxTime** ppData);
public:
	qint32 insertUserTradeInfo(const CUserTradeInfo* pData);
	qint32 resetUserAccount( const CUserAccount* pData );
	qint32 insertUserAccount(const CUserAccount* pData );
public:
	qint32 resetUserHoldAccount( const QList<CUserHoldAccount*>& lstData );
	qint32 resetAllStockInfo(const QList<CStockInfo*>& lstData);

public:	
	QSqlDatabase* getDB();
private:
	CUserInfo* m_pUserInfo;
	QMutex m_mutex_ClientDbOper;
	CClientDbOper* m_pClientDbOper;

private:
	CQtTimeHelper* m_pQtTimeHelper;
};

//QT_END_NAMESPACE

#endif //__CLASS_CLIENT_DB_MAMAGER__HH__


