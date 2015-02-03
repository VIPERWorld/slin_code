#include <iostream>
//#include <QtGui/QApplication>
#include <QtCore/QCoreApplication>

////////////////
//_WINDOWS;UNICODE;WIN32;QT_DLL;QT_HAVE_MMX;QT_HAVE_3DNOW;QT_HAVE_SSE;QT_HAVE_MMXEXT;QT_HAVE_SSE2;QT_GUI_LIB;QT_CORE_LIB;QT_THREAD_SUPPORT

////////////////
//sys
#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"wldap32.lib")
#pragma comment(lib,"ws2_32.lib")//winsock2

//qt
#pragma comment(lib,"qtmaind.lib")
#pragma comment(lib,"QtCored4.lib")
#pragma comment(lib,"QtGuid4.lib")
#pragma comment(lib,"QtSqld4.lib")
#pragma comment(lib,"QtNetworkd4.lib")

//user
#pragma comment(lib,"log4cppD.lib")
////////////////



#include "ProjectEnvironment.h"
#include "ClientActorManager.h"

int main(int argc, char *argv[])
{
	qint32 nFunRes = 0;
	QCoreApplication coreapp(argc, argv);
	CProjectEnvironment::getInstance();

	CClientActorManager::getInstance();
	QString strServerIP = "127.0.0.1";
	quint16 nServerPort = 5000;
	QString strUserName = "usernamelsl";
	QString strPassWord = "passwordlsl";
	CClientActorManager::getInstance().createClient(strServerIP, nServerPort, strUserName, strPassWord);


    nFunRes = coreapp.exec();
	CClientActorManager::removeInstance();
	CProjectEnvironment::removeInstance();

	return 0;
}




