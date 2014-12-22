#ifndef __CLASS_ITEM_WAITING_INSTRUMENT_HELPER_HH__
#define __CLASS_ITEM_WAITING_INSTRUMENT_HELPER_HH__



//qt sys
#include <QtCore/QChar>
#include <QtCore/QString>
#include <QtCore/QVariant>
#include <QtCore/QStringList>

#include "MyInstrument.h"
#include "ItemWaitingInstrument.h"


class CItemWaitingInstrumentHelper 
{ 
public: 
	CItemWaitingInstrumentHelper();

	virtual ~CItemWaitingInstrumentHelper(); 
	CItemWaitingInstrumentHelper& operator=(const CItemWaitingInstrumentHelper& objCopy);

public:
	void setValue( const CMyInstrument &instrument);
public:
	void logInfo(const std::string& file, int line, const QString& strLogInfo);
	void getItemNodeData(QList<QVariant>& itemDataTmp, CItemWaitingInstrument::EItemType nDataType);
	QVariant getColumnValueByName( const QString& strtColumnName );
	void getLstClumnName( QStringList& lstClumnName );
	void getLstClumnName( QList<QVariant>& lstClumnName );
private:
	void _ClearData();

public:
	unsigned int m_nInstrumentID;
	QString m_strExchangeName;//Exchange Name//ExchangeName//������
	QString m_strUnderlyingCode;
	QString m_strInstrumentCode;//Contract Name//InstrumentCode//��Լ����
}; 


//QT_END_NAMESPACE


#endif//__CLASS_ITEM_WAITING_INSTRUMENT_HELPER_HH__



