#include "ClientMainWindowMdiArea.h"

#include "StockMinTimeMaxTimeTableView.h"
#include "StockHistoryDataTableView.h"
#include "UserTradeTableView.h"
#include "UserAccountWidget.h"
#include "UserHoldAccountWidget.h"
#include "StockInfoWidget.h"

#include "Log4cppLogger.h"

static const int DEFVALUE_INT_Window_Width_StockMinTimeMaxTimeTableView = 400;
static const int DEFVALUE_INT_Window_Height_StockMinTimeMaxTimeTableView = 300;

static const int DEFVALUE_INT_Window_Width_StockHistoryDataTableView = 400;
static const int DEFVALUE_INT_Window_Height_StockHistoryDataTableView = 300;

static const int DEFVALUE_INT_Window_Width_UserTradeTableView = 800;
static const int DEFVALUE_INT_Window_Height_UserTradeTableView = 200;

static const int DEFVALUE_INT_Window_Width_CUserAccountWidget = 800;
static const int DEFVALUE_INT_Window_Height_CUserAccountWidget = 200;

CClientMainWindowMdiArea::CClientMainWindowMdiArea(QWidget *parent)
    : QMdiArea(parent)
{
    //this->resize(200, 300);
	m_pStockMinTimeMaxTimeTableView = NULL;
	m_pStockHistoryDataTableView = NULL;
	m_pUserTradeTableView = NULL;
	m_pUserAccountWidget = NULL;

	_SetupUi();
	_TranslateLanguage();
}

CClientMainWindowMdiArea::~CClientMainWindowMdiArea()
{
	
}



void CClientMainWindowMdiArea::_SetupUi()
{
	int nIndex = 0;
	QMdiSubWindow* pSubWindowRef = NULL;
	this->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
	this->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

	m_pStockMinTimeMaxTimeTableView = new CStockMinTimeMaxTimeTableView(this);
	m_pStockHistoryDataTableView = new CStockHistoryDataTableView(this);
	m_pUserTradeTableView = new CUserTradeTableView(this);
	m_pUserAccountWidget = new CUserAccountWidget(this);
	m_pUserHoldAccountWidget = new CUserHoldAccountWidget(this);
	m_pStockInfoWidget = new CStockInfoWidget(this);

	pSubWindowRef = NULL;
	pSubWindowRef = this->addSubWindow(m_pUserAccountWidget);
	pSubWindowRef = NULL;
	pSubWindowRef = this->addSubWindow(m_pStockHistoryDataTableView);
	pSubWindowRef = NULL;
	pSubWindowRef = this->addSubWindow(m_pUserTradeTableView);
	pSubWindowRef = NULL;
	pSubWindowRef = this->addSubWindow(m_pStockMinTimeMaxTimeTableView);
	pSubWindowRef = NULL;
	pSubWindowRef = this->addSubWindow(m_pUserHoldAccountWidget);
	pSubWindowRef = NULL;
	pSubWindowRef = this->addSubWindow(m_pStockInfoWidget);

	this->tileSubWindows();
	//this->cascadeSubWindows();

	/*
	nIndex = 0;
	foreach (QMdiSubWindow *pSubWindow, this->subWindowList()) 
	{
		if (0 == nIndex)
		{
			//TestChildWindow *mdiChild = qobject_cast<TestChildWindow *>(window->widget());
			this->setActiveSubWindow(pSubWindow);
			this->activeSubWindow()->move(0, 0);
			this->activeSubWindow()->resize(DEFVALUE_INT_Window_Width_StockMinTimeMaxTimeTableView, 
				DEFVALUE_INT_Window_Height_StockMinTimeMaxTimeTableView);
		}
		else if (1 == nIndex)
		{
			this->setActiveSubWindow(pSubWindow);
			this->activeSubWindow()->move(DEFVALUE_INT_Window_Width_StockMinTimeMaxTimeTableView, 0);
			this->activeSubWindow()->resize(DEFVALUE_INT_Window_Width_StockHistoryDataTableView, 
				DEFVALUE_INT_Window_Height_StockHistoryDataTableView);
		}
		else if (2 == nIndex)
		{
			this->setActiveSubWindow(pSubWindow);
			this->activeSubWindow()->move(0, DEFVALUE_INT_Window_Height_StockMinTimeMaxTimeTableView + 10);
			this->activeSubWindow()->resize(DEFVALUE_INT_Window_Width_UserTradeTableView, 
				DEFVALUE_INT_Window_Height_UserTradeTableView);
		}
		else if (3 == nIndex)
		{
			this->setActiveSubWindow(pSubWindow);
			this->activeSubWindow()->move(0, DEFVALUE_INT_Window_Height_StockMinTimeMaxTimeTableView + DEFVALUE_INT_Window_Height_UserTradeTableView + 10);
			this->activeSubWindow()->resize(DEFVALUE_INT_Window_Width_CUserAccountWidget, 
				DEFVALUE_INT_Window_Height_CUserAccountWidget);
		}
		nIndex++;
	}//foreach

	*/
}

void CClientMainWindowMdiArea::_TranslateLanguage()
{

}


