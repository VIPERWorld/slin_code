#include "TestCaseLog4qt.h"

#include <QtCore/QFileInfo>

#include <QtCore/QDateTime>
#include <QtCore/QString>
#include <QtCore/QDir>

#include "log4qt/logger.h"
#include "log4qt/fileappender.h"
#include "log4qt/ttcclayout.h"
#include "log4qt/patternlayout.h"
#include "log4qt/logmanager.h"


using namespace std;
using namespace Log4Qt;

//////////////////////////////////////////////////////////////////////////
CTestCaseLog4qt::CTestCaseLog4qt(void)
{	
	_Test_CFG_1();
}

CTestCaseLog4qt::~CTestCaseLog4qt(void)
{


}

void CTestCaseLog4qt::_Test_CFG_1()
{
	//������־�������沢���ٶ�����־��Ϣ�����ʵ��
	Logger* logger = Log4Qt::Logger::rootLogger();
	logger->removeAllAppenders();
	//������־�ļ�
	Log4Qt::FileAppender *fileappender=new Log4Qt::FileAppender();
	fileappender->setName("MyLogger");
	//������־��
	QFileInfo fileinfo(QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss") + ".log");
	fileappender->setFile(fileinfo.filePath());
	//������־��ʽ
	//Log4Qt::TTCCLayout *filelayout = new Log4Qt::TTCCLayout(Log4Qt::TTCCLayout::ISO8601);
	Log4Qt::PatternLayout *filelayout= new Log4Qt::PatternLayout("%d %p-%m %n");
	fileappender->setLayout(filelayout);
	fileappender->activateOptions();
	logger->addAppender(fileappender);

	// Request a logger and output "Hello World!"
	Log4Qt::Logger::logger(QLatin1String("MyLogger"))->info("Hello World!");
}

void CTestCaseLog4qt::_Test_CFG_2()
{
	
}

/*
layout���������ͣ������ǣ�
PatternLayout����������ָ������ģʽ���� 
SimpleLayout��������־��Ϣ�ļ������Ϣ�ַ������� 
TTCCLayout��������־������ʱ�䡢�̡߳����ȵ���Ϣ�� 
���彲��ɲ��յ������ֶ��������ļ��е�Layout�� 
���ʹ��pattern���־�Ҫָ���Ĵ�ӡ��Ϣ�ľ����ʽConversionPattern����ӡ�������£� 
����%m ���������ָ������Ϣ 
  ��%p ������ȼ�����DEBUG��INFO��WARN��ERROR��FATAL 
	%r �����Ӧ�������������log��Ϣ�ķѵĺ����� 
	%c �����������Ŀ��ͨ�������������ȫ�� 
	%t �����������־�¼����߳��� 
	%n ���һ���س����з���Windowsƽ̨Ϊ��n����Unixƽ̨Ϊ��rn����ȷ������ 
	%d �����־ʱ�������ڻ�ʱ�䣬Ĭ�ϸ�ʽΪISO8601��Ҳ���������ָ����ʽ�����磺%d{yyyy MMM dd HH:mm:ss,SSS}��������ƣ�2002��10��18�� 22��10��28��921 
	%l �����־�¼��ķ���λ�ã�������Ŀ�����������̣߳��Լ��ڴ����е������� 
*/



