#include "UserTradeWindow.h"

#include "UserOrderTableView.h"


static const int DEFVALUE_INT_Window_Width = 700;
static const int DEFVALUE_INT_Window_Height = 300;

static const std::string   DEFVALUE_String_Window_Title = "UserTrade:";


CUserTradeWindow::CUserTradeWindow( QWidget* parent /*= 0*/ )
{
	m_pUserOrderTableView = NULL;
	_SetupUi();
	_TranslateLanguage();
}

CUserTradeWindow::~CUserTradeWindow()
{


}

void CUserTradeWindow::_SetupUi()
{
	this->setTabPosition(QTabWidget::South);	//enum TabPosition { North, South, West, East
	//���ô�����������ز�����λ�ڶ���
	this->setWindowFlags(Qt::FramelessWindowHint);
	//�ɻ�ȡ������Ч��
	this->setMouseTracking(true);

	m_pUserOrderTableView = new CUserOrderTableView(this);
}

void CUserTradeWindow::_TranslateLanguage()
{
	this->setWindowTitle(QObject::tr(DEFVALUE_String_Window_Title.c_str()));
	this->addTab(m_pUserOrderTableView, QObject::tr("trade history"));

}

