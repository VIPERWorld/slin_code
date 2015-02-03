#include "YahuoHistoryReqAck.h"

#include <QtCore/QByteArray>
#include <QtCore/QDataStream>
#include <sstream>

#include "BaseException.h"
#include "Log4cppLogger.h"

CYahuoHistoryReqAck::CYahuoHistoryReqAck()
{

}

CYahuoHistoryReqAck::~CYahuoHistoryReqAck()
{

}

/*
2014-01-01 - 2014-02-01    month value - 1
http://ichart.yahoo.com/table.csv?s=000008.SZ&a=0&b=1&c=2014&d=1&e=1&f=2014&g=d&ignore=.csv
*/
QString CYahuoHistoryReqAck::getRequestUrl(
	const QString &strSymbolUse, 
	qint32 startYear, qint32 startMonth, qint32 startDay,
	qint32 endYear, qint32 endMonth, qint32 endDay, 
	const QString &rangeType) 
{
	QString strUrl;
	std::stringstream byteUrl;
	int nRequestStartMonth = 0;
	int nRequestEndMonth = 0;

	nRequestStartMonth = startMonth - 1;
	nRequestEndMonth = endMonth - 1;

	MYLOG4CPP_DEBUG<<"startMonth="<<startMonth
		<<" "<<"nRequestStartMonth="<<nRequestStartMonth
		<<" "<<"endMonth="<<endMonth
		<<" "<<"nRequestEndMonth="<<nRequestEndMonth;

	byteUrl << "http://ichart.yahoo.com/table.csv?s="
		<< strSymbolUse.toStdString()
		<< "&a="
		<< nRequestStartMonth
		<< "&b="
		<< startDay
		<< "&c="
		<< startYear
		<< "&d="
		<< nRequestEndMonth
		<< "&e="
		<< endDay
		<< "&f="
		<< endYear
		<< "&g="
		<< rangeType.toStdString()
		<< "&ignore=.csv";

	strUrl = byteUrl.str().c_str();
	return strUrl;

	
	//"http://ichart.finance.yahoo.com/table.csv?s=600155.SS&a=00&b=1&c=2014&d=02&e=1&f=2014";
}//

QString CYahuoHistoryReqAck::getRequestUrl( const QString &strSymbolUse, 
qint32 startYear, qint32 startMonth, unsigned startDay, 
qint32 endYear, qint32 endMonth, qint32 endDay, const YahuoReqAck::RangeType &rangeType )
{
	QString strRangeTyep = YahuoReqAck::getString(rangeType);
	return getRequestUrl(strSymbolUse, startYear, startMonth, startDay, endYear, endMonth, endDay, strRangeTyep);
}






void CYahuoHistoryReqAck::test_CYahuoHistoryReqAck()
{

	CYahuoHistoryReqAck classCYahuoHistoryReqAck;
	QString strResGet;
	strResGet= classCYahuoHistoryReqAck.getRequestUrl("600667.SS", 2010, 4, 1, 2014, 10, 13, YahuoReqAck::dividendsOnly);
	// if data can not be retrieved by any of the functions, an exception is thrown

	QString petr4HistoricalPrices = classCYahuoHistoryReqAck.getRequestUrl("600667.SS",
		2014, 4, 2,
		2014, 10, 7,
		YahuoReqAck::daily);
}


////////////////
#if 0

void YahooHistoryObject::getUrl (QDateTime sd, QDateTime ed, QString symbol, QString &url)
{
	//http://ichart.finance.yahoo.com/table.csv?s=AAPL&d=1&e=22&f=2011&g=d&a=8&b=7&c=1984&ignore=.csv
	url = "http://ichart.finance.yahoo.com/table.csv?s=";
	url.append(symbol);
	url.append("&d=" + QString::number(ed.date().month() - 1));
	url.append("&e=" + ed.date().toString("d"));
	url.append("&f=" + ed.date().toString("yyyy"));
	url.append("&a=" + QString::number(sd.date().month() - 1));
	url.append("&b=" + sd.date().toString("d"));
	url.append("&c=" + sd.date().toString("yyyy"));
	url.append("&ignore=.csv");
}
int YahooHistoryObject::downloadName (QString symbol, QString &name)
{
	QString url = "http://download.finance.yahoo.com/d/quotes.csv?s=";
	url.append(symbol);
	url.append("&f=n");
	url.append("&e=.csv");

	QNetworkAccessManager manager;
	QNetworkReply *reply = manager.get(QNetworkRequest(QUrl(url)));
	QEventLoop e;
	QObject::connect(&manager, SIGNAL(finished(QNetworkReply *)), &e, SLOT(quit()));
	e.exec();

	// parse the data and save quotes
	QByteArray ba = reply->readAll();
	QString s(ba);
	s = s.remove('"');
	s = s.remove(',');
	s = s.trimmed();
	if (s.isEmpty())
		return 0;

	name = s;

	return 1;
}
#endif
////////////////
#if 0
���ʹ�� Yahoo! Finance stock API ��ȡ��Ʊ���� 
http://blog.sina.com.cn/s/blog_7ed3ed3d010147pk.html
1��ͨ��API��ȡʵʱ����
�����ַ
http://finance.yahoo.com/d/quotes.csv?s=<��Ʊ����>&f=<������ѡ��>
����
s �C ��ʾ��Ʊ���ƣ������Ʊ֮��ʹ��Ӣ�ļӺŷָ����硱XOM+BBDb.TO+JNJ+MSFT�����������ĸ���˾�Ĺ�Ʊ��XOM, BBDb.TO, JNJ, MSFT��
f �C ��ʾ���������У��硱snd1l1yr��������ϸ�Ĳμ��Ż���Ʊ API f �������ձ�
2��ͨ��API��ȡ��ʷ����
�����ַ
http://ichart.yahoo.com/table.csv?s=<string>&a=<int>&b=<int>&c=<int>&d=<int>&e=<int>&f=<int>&g=d&ignore=.csv
����
s �C ��Ʊ����
a �C ��ʼʱ�䣬��
b �C ��ʼʱ�䣬��
c �C ��ʼʱ�䣬��
d �C ����ʱ�䣬��
e �C ����ʱ�䣬��
f �C ����ʱ�䣬��
g �C ʱ�����ڡ�Example: g=w, ��ʾ�����ǡ��ܡ���d->���ա�(day), w->���ܡ�(week)��m->���¡�(mouth)��v->��dividends only��
һ��ע���·ݲ�������ֵ����ʵ����-1������Ҫ9�����ݣ���дΪ08��
3��ͨ��API��ȡ���Ʊ����
�Ż���API�ǹ����Եģ�֧�ֲ�ѯ���ڻ�����е����ݣ���������΢�䶯һ�£����ַ����еĴ����ǣ�600000.SS�������ǣ��Ϻ��г�ĩβ��.ss�������г�ĩβ��.sz��

�������������Ƹ����һ��Ʊ��վ����Ʊ�����ݴ�����������һ�������⣬��Ʊ���һ�㶼�Ǽ��ܴ���ģ�����һЩweb servicesҲ��Ҫ�ʺŵģ���ѵķ���ֻ��һ���ˣ�ץ������վ�����ݡ����ھ����о�������yahoo�ṩ���ں͹������ÿ��Ľ����������ϣ����νһ �����°���
http://table.finance.yahoo.com/table.csv?s=ibm&d=6&e=22&f=2006&g=d&a=11&b=16&c=1991&ignore=.csv
��������ӿ���ץȡIBM��Ʊ��1991��11��16����2006��6��22�����ݡ���ibm�ĳ�sohu���Ϳ���ץ��sohu�Ĺ�Ʊ�����ˡ�
http://table.finance.yahoo.com/table.csv?s=sohu&d=6&e=22&f=2008&g=d&a=11&b=16&c=2008&ignore=.csv
�������ӿ���ץ�Ѻ���Ʊ�����ݡ�

������ô�й����е�������û���أ����ǿ϶��ģ�����Ҫ��������Ĳ�����Щ�����������ṩȫ��֤ȯ�����������ϡ�
  ��֤��Ʊ�ǹ�Ʊ����������.ss����֤��Ʊ�ǹ�Ʊ����������.sz
  ���磺000001 = 000001.sz
�����������ӣ�http://table.finance.yahoo.com/table.csv?s=000001.sz
�����������ӣ�http://table.finance.yahoo.com/table.csv?s=600000.ss
��֤��ָ���룺000001.ss����֤��ָ���룺399001.SZ������300���룺000300.ss

������������Ʊ����������ַ����д��Ҫ�����ĸ���Ʊ�����������ݣ��Ͱ�������ĸ�ʽ�Դ����ơ�
�Ϻ�������=cn.finance.yahoo.com,.SS,Chinese,sl1d1t1c1ohgv
���ڽ�����=cn.finance.yahoo.com,.SZ,Chinese,sl1d1t1c1ohgv
����������=finance.yahoo.com,,United States,sl1d1t1c1ohgv
���ô�=ca.finance.yahoo.com,.TO,Toronto,sl1d1t1c1ohgv
������=au.finance.yahoo.com,.NZ,sl1d1t1c1ohgv
�¼���=sg.finance.yahoo.com,.SI,Singapore,sl1d1t1c1ohgv
���=hk.finance.yahoo.com,.HK,Hong Kong,sl1d1t1c1ohgv
̨��=tw.finance.yahoo.com,.TW,Taiwan,sl1d1t1c1ohgv
ӡ��=in.finance.yahoo.com,.BO,Bombay,sl1d1t1c1ohgv
�׶�=uk.finance.yahoo.com,.L,London,sl1d1t1c1ohgv
����=au.finance.yahoo.com,.AX,Sydney,sl1d1t1c1ohgv
����=br.finance.yahoo.com,.SA,Sao Paulo,sl1d1t1c1ohgv
���=se.finance.yahoo.com,.ST,Stockholm,sl1d1t1c1ohgv
#endif