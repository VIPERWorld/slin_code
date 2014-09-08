//qt app
//#include "vld.h"
#include <QtGui/QApplication>
#include <QtGui/QSplashScreen>
#include <QtGui/QPixmap>
#include <QtCore/QTextCodec>
#include <QtCore/QTranslator>
#include <QtCore/QSharedMemory>
#include <QtCore/QFile>

#include "QTProjectEnvironment.h"
#include "ClientManager.h"

#include "CreateNewOrderDialog.h"
//
//

void setUpSplashScreen()
{
	QSplashScreen* splash = NULL;
	QString strSplashPictureFileName;
	Qt::Alignment topRight;
	qint64 nMilliseconds = 1000;

// 	QTextCodec::setCodecForTr(QTextCodec::codecForName(QTextCodec::codecForLocale()->name()));
// 	QTextCodec::setCodecForLocale(QTextCodec::codecForName(QTextCodec::codecForLocale()->name()));
// 	QTextCodec::setCodecForCStrings(QTextCodec::codecForName(QTextCodec::codecForLocale()->name()));

	strSplashPictureFileName = QObject::tr(":/images/splash");
	topRight = Qt::AlignRight | Qt::AlignTop;

	splash = new QSplashScreen();
	splash->setPixmap(QPixmap(strSplashPictureFileName));
	splash->move(0, 0);	
	splash->show();

	CQTProjectEnviroment::qtWaitTime(nMilliseconds);	
	//splash->finish(&clientMainWindow);

	if (NULL != splash)
	{
		delete splash;
		splash = NULL;
	}

	return;
}



int main(int argc, char *argv[])
{
	int nFunRes = 0;

	CQTProjectEnviroment::getInstance();


	//����QApplication���󣬹�������Ӧ�ó������Դ��ͨ��argc��argv����ȡ���Լ��������в�����
	QApplication app(argc, argv);


	//���ñ��룬һ����Window�����������GBK���룬��Linux�����������utf-8����
	//��ȡϵͳ���룬������ֲ���������
	QTextCodec *codec = QTextCodec::codecForName("System"); 

	//���úͶԱ����ļ�ϵͳ��дʱ���Ĭ�ϱ����ʽ
	QTextCodec::setCodecForLocale(codec); 

	//���ô���tr����ʱ��Ĭ���ַ�������
	//QTextCodec::setCodecForTr(codec);
	//�����ַ���������QByteArray����QString����ʱʹ�õ�һ�ֱ��뷽ʽ
	//QTextCodec::setCodecForCStrings(codec);  

	//����Qt�е���Դ�ļ���ʹQt��ʾ���ģ�����QMessageBox���ı����Ҽ��˵��ȣ�
	QTranslator translator;  
	translator.load(QString(":/language/qt_zh_CN"));  
	app.installTranslator(&translator);  


	//����QSS��ʽ��
	QFile qss(":/qss/SmartTraderQTMVC");
	qss.open(QFile::ReadOnly);
	//qApp->setStyleSheet(qss.readAll());//QCoreApplication::instance()
	qss.close();



	//CClientManager objClientWindow;

	//CCreateNewOrderDialog* pCCreateNewOrderDialog = new CCreateNewOrderDialog(NULL);
	//pCCreateNewOrderDialog->show();

	nFunRes = app.exec(); 

	CQTProjectEnviroment::removeInstance();

	return 0;
}


