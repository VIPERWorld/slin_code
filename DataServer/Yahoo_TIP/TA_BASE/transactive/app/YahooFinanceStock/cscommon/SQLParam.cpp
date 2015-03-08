#include "SQLParam.h"
#include <sstream>
//#include <limits>
#include <string.h>
#include "Log4cppLogger.h"

CSQLParam::CSQLParam()
{
	strParam.clear();
}
CSQLParam::~CSQLParam()
{
	strParam.clear();
}
CSQLParam& CSQLParam::operator=( const CSQLParam& objCopy )
{
	strParam = objCopy.strParam;
	return *this;
}

CSQLParam::CSQLParam( const CSQLParam& objCopy )
{
	strParam = objCopy.strParam;
}


CSQLParam::CSQLParam( const QString& tmpValue )
{
	strParam = QString("%1").arg(tmpValue);
}

CSQLParam::CSQLParam( const char* tmpValue )
{
	strParam = QString("%1").arg(tmpValue);
}

CSQLParam::CSQLParam( const char& tmpValue )
{
	strParam = QString("%1").arg(tmpValue);
}

CSQLParam::CSQLParam( const qint32& tmpValue )
{
	//strParam = QString("%1").arg(tmpValue);
	strParam = QString::number(tmpValue);
}

CSQLParam::CSQLParam( const qint64& tmpValue )
{
	strParam = QString("%1").arg(tmpValue);
}
CSQLParam::CSQLParam( const float& tmpValue )
{
	strParam =  do_fraction(tmpValue, 6);
}
CSQLParam::CSQLParam( const double& tmpValue )
{
	//error!  1222.445  "1222.4"
	//strParam = QString("%1").arg(tmpValue);
	//strParam.setNum();
	//strParam = QString::number(tmpValue);
	//strParam = QString::number(tmpValue, 'g', 6);
	strParam =  do_fraction(tmpValue, 6);
}

QString CSQLParam::getParam() const
{
	return strParam;
}
//void CSQLParam::do_fraction(long double value, int decplaces=6)
QString CSQLParam::do_fraction(long double value, int decplaces)
{
	QString strGetValue;
	std::ostringstream out;
	qint32 prec = 18; // 18
	std::string str;
	char DECIMAL_POINT='.';
	size_t nFind = 0;

	//prec = numeric_limits::digits10; // 18
	out.precision(prec);//����Ĭ�Ͼ���
	out<<value;
	str = out.str(); //������ȡ���ַ���
	nFind = str.find(DECIMAL_POINT);//DECIMAL_POINT//char DECIMAL_POINT='.'; // ŷ���÷�Ϊ','

	//��С������
	//�������ٻ���decplacesλ��
	if ((nFind != std::string::npos) && (str.size()> nFind + decplaces))
	{
		//���ǵ�һ���������
		str[nFind + decplaces] = '\0';
	}
	//ɾ��nul֮��Ķ����ַ�
	str.swap(std::string(str.c_str()));
	strGetValue = str.c_str();
	return strGetValue;
}



