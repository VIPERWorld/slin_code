#ifndef __CLASS_DATA_REAL_TIME_WORKER__HH__
#define __CLASS_DATA_REAL_TIME_WORKER__HH__

#include "MyQtThread.h"
#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>
#include <QtCore/QList>

class CMyTradeClient;
class CReqData;


class CDataRealTimeWorker : public CMyQtThread
{
	Q_OBJECT
private:
	enum EDataWorkerState
	{
		DataWorkerState_Begin,
		
		DataWorkerState_UpdateStockRealTimeInfo,

		DataWorkerState_End,
	};

public:
	CDataRealTimeWorker(void);
	~CDataRealTimeWorker(void);

public:
	virtual void run();	
	virtual void terminate();
	bool  isFinishWork();
private:
	void _ThreadJob();
	int	 _ProcessUserTerminate();  
private:
	bool	m_toTerminate;
	EDataWorkerState m_nDataWorkerState;
public:
	void setDataProcessHandle(CMyTradeClient* pHandle);
private:
	void _DoJob_UpdateStockRealTimeInfo();
private:
	CMyTradeClient* m_pMyTradeClientRef;
};


#endif //__CLASS_DATA_WORKER__HH__

