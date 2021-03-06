#ifndef __CLASS_STOCK_TCP_CLIENT_ACTOR_H__
#define __CLASS_STOCK_TCP_CLIENT_ACTOR_H__

#include "MyQtThread.h"


class CMessageManager;
class CClientComWorker;

class CDistributeTaskWorker : public CMyQtThread
{
    Q_OBJECT
public:
	CDistributeTaskWorker(
		const QString& strServerIP, 
		quint16 nServerPort, 
		QObject* parent=0);

	~CDistributeTaskWorker();
signals:
	void signalConnectToServer();
private slots:
	void slotDisconnected();
	void slotConnected();
public:
	virtual void run();	
	virtual void terminate();
//////////////////////////////////////////////////////////////////////////
signals:
	void signalDeleteConnection(CDistributeTaskWorker* pActor);
private:
	QString m_strServerIP;// = "127.0.0.1";
	quint16 m_nServerPort;// = 5000;

	CClientComWorker* m_pComWorker;
	CMessageManager* m_pMessageManager;
};

#endif//__CLASS_STOCK_TCP_CLIENT_ACTOR_H__
