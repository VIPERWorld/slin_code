#ifndef __CLASS__SIGNALE_SLOT_MANAGER_H__
#define __CLASS__SIGNALE_SLOT_MANAGER_H__


#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>

class CClientDataManager;
class CClientMainWindow;
class CStockMinTimeMaxTimeTableView;
class CStockHistoryDataTableView;
class CUserTradeTableView;
class CUserAccountWidget;
class CHistoryData;
class CUserHoldAccountWidget;
class CStockInfoWidget;

class CSignalSlotManager : public QObject
{
	Q_OBJECT
public:
	static CSignalSlotManager& getInstance();
	static void removeInstance();

private:
	static CSignalSlotManager* m_pInstance;
	static QMutex m_mutexInstance;
private:
	CSignalSlotManager(void);
	~CSignalSlotManager(void);

//////////////////////////////////////////////////////
private:
	CClientDataManager* m_pRefSignal_ShownMessage;
	CClientMainWindow* m_pRefSlot_ShownMessage;
public:
	void set_Signal_ShownMessage( CClientDataManager* pRefSignal);
	void set_Slot_ShownMessage(CClientMainWindow* pRefSlot);
signals:
	void signal_ShownMessage(QString strMessage);
private slots:
	void slot_ShownMessage(QString strMessage);
public:
	void emit_ShownMessage(QString strMessage);
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
private:
	CClientDataManager* m_pRefSignal_DataChange_StockMinTimeMaxTime;
	CStockMinTimeMaxTimeTableView* m_pRefSlot_DataChange_StockMinTimeMaxTime;
public:
	void set_Signal_DataChange_StockMinTimeMaxTime( CClientDataManager* pRefSignal);
	void set_Slot_DataChange_StockMinTimeMaxTime(CStockMinTimeMaxTimeTableView* pRefSlot);
	void set_Slot_DataChange_NewOrderData(CStockMinTimeMaxTimeTableView* pRefSlot);
signals:
	void signal_DataChange_StockMinTimeMaxTime();
	void signal_DataChange_NewOrderData(CHistoryData* pData);
private slots:
	void slot_DataChange_StockMinTimeMaxTime();
	void slot_DataChange_NewOrderData(CHistoryData* pData);
public:
	void emit_DataChange_StockMinTimeMaxTime();
	void emit_DataChange_NewOrderData(CHistoryData* pData);
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
private:
	CClientDataManager* m_pRefSignal_DataChange_StockHistoryData;
	CStockHistoryDataTableView* m_pRefSlot_DataChange_StockHistoryData;
public:
	void set_Signal_DataChange_StockHistoryData( CClientDataManager* pRefSignal);
	void set_Slot_DataChange_StockHistoryData(CStockHistoryDataTableView* pRefSlot);
signals:
	void signal_DataChange_StockHistoryData();
private slots:
	void slot_DataChange_StockHistoryData();
public:
	void emit_DataChange_StockHistoryData();
//////////////////////////////////////////////////////
//////////////////////////////////////////////////////
private:
	CClientDataManager* m_pRefSignal_DataChange_UserTrade;
	CUserTradeTableView* m_pRefSlot_DataChange_UserTrade;
public:
	void set_Signal_DataChange_UserTrade( CClientDataManager* pRefSignal);
	void set_Slot_DataChange_UserTrade(CUserTradeTableView* pRefSlot);
signals:
	void signal_DataChange_UserTrade();
private slots:
	void slot_DataChange_UserTrade();
public:
	void emit_DataChange_UserTrade();
//////////////////////////////////////////////////////
private:
	CClientDataManager* m_pRefSignal_DataChange_UserAccount;
	CUserAccountWidget* m_pRefSlot_DataChange_UserAccount;
public:
	void set_Signal_DataChange_UserAccount( CClientDataManager* pRefSignal);
	void set_Slot_DataChange_UserAccount(CUserAccountWidget* pRefSlot);
signals:
	void signal_DataChange_UserAccount();
private slots:
	void slot_DataChange_UserAccount();
public:
	void emit_DataChange_UserAccount();
//////////////////////////////////////////////////////
private:
	CClientDataManager* m_pRefSignal_DataChange_UserHoldAccount;
	CUserHoldAccountWidget* m_pRefSlot_DataChange_UserHoldAccount;
public:
	void set_Signal_DataChange_UserHoldAccount( CClientDataManager* pRefSignal);
	void set_Slot_DataChange_UserHoldAccount(CUserHoldAccountWidget* pRefSlot);
signals:
	void signal_DataChange_UserHoldAccount();
private slots:
	void slot_DataChange_UserHoldAccount();
public:
	void emit_DataChange_UserHoldAccount();
//////////////////////////////////////////////////////

private:
	CClientDataManager* m_pRefSignal_DataChange_StockInfo;
	CStockInfoWidget* m_pRefSlot_DataChange_StockInfo;
public:
	void set_Signal_DataChange_StockInfo( CClientDataManager* pRefSignal);
	void set_Slot_DataChange_StockInfo(CStockInfoWidget* pRefSlot);
signals:
	void signal_DataChange_StockInfo();
private slots:
	void slot_DataChange_StockInfo();
public:
	void emit_DataChange_StockInfo();
//////////////////////////////////////////////////////

};

//QT_END_NAMESPACE

#endif//__CLASS__SIGNALE_SLOT_MANAGER_H__
