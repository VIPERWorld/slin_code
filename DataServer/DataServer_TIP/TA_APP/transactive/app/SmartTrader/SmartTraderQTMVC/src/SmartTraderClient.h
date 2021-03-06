#ifndef __CLASS_SMART_TRADER_CLIENT_HH__
#define __CLASS_SMART_TRADER_CLIENT_HH__

#include <QtCore/QObject>

#include "TradeClient.h"
#include "ClientLoginParam.h"


//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE

class IProcessRecvData;

class CSmartTraderClient : public QObject, public TradeClient
{ 
	Q_OBJECT



public:
	CSmartTraderClient(const CClientLoginParam& clientLoginParam);
	virtual ~CSmartTraderClient();
public:
	int loginToServer();
	void setProcessRecvDataHandle(IProcessRecvData* pHandle);
public:
	/// Hook method when receiving instrument information 
	virtual void onInstrumentDownloaded(const Instrument &instrument);

	//MYCODE ERROR HERE
	/// Hook method when receive market data
	//virtual void onMarketDataUpdate(const MarketData &marketData);

	virtual void onMarketDataUpdate(const Instrument &instrument);
	/// Hook method when account downloaded
	virtual void onAccountDownloaded(Account& account);
public:
	/// Hook method when the order is accepted by exchange.
	virtual void onOrderAccepted(const Order &order);

	/// Hook method when order is canceled.
	virtual void onOrderCanceled(const Order &order);

	/// Hook method when order is rejected.
	virtual void onOrderRejected(const Order &order);

	/// Hook method when order filled
	virtual void onOrderFilled(const Order &order);

	/// Hook method when cancel request get rejected
	virtual void onCancelReject(const Order &order);
public:
	/// Hook method when receive bar summary update
	virtual void onBarDataUpdate(const BarSummary &barData);
	/// Hook method when history data is downloaded
	virtual void onHistoryDataDownloaded(unsigned int requestID, BarsPtr bars);

private:
	CClientLoginParam* m_pClientLoginParam;
	IProcessRecvData* m_pProcessRecvDataHandle;
}; 

//QT_END_NAMESPACE




#endif//__CLASS_SMART_TRADER_CLIENT_HH__



