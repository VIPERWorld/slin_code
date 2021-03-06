#include "UserAccountWidget.h"

#include <QtSql/QSqlTableModel>
#include "ProjectDBStruct.h"
#include "ProjectQTInclude.h"
#include "ProjectCommonData.h"
#include "ClientDBManager.h"
#include "SignalSlotManager.h"

#include "Log4cppLogger.h"

static int DEFVALUE_INT_Window_Width = 600;
static int DEFVALUE_INT_Window_Height = 200;
static char* DEFVALUE_WINDOW_TITLE = "UserAccount";
//this->setWindowTitle(QObject::tr(DEFVALUE_WINDOW_TITLE));



CUserAccountWidget::CUserAccountWidget( QWidget* parent)
{
	QModelIndex inValidIndex;
	//this->resize(DEFVALUE_INT_Window_Width, DEFVALUE_INT_Window_Height);//mdi not work

	//this->setWindowFlags(Qt::FramelessWindowHint);
	this->setWindowFlags(Qt::WindowMinMaxButtonsHint);
	this->setWindowFlags(Qt::WindowTitleHint);
	this->setWindowTitle(QObject::tr(DEFVALUE_WINDOW_TITLE));

	QGridLayout* pGridLayout = NULL;

	m_pUserAccountTableView = NULL;
	m_pUserAccountModel = NULL;

	m_pUserAccountTableView = new QTableView(this);
	m_pUserAccountTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	m_pUserAccountTableView->setAlternatingRowColors(true);
	m_pUserAccountTableView->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
	m_pUserAccountTableView->resizeColumnsToContents();

	m_pUserAccountModel = new QSqlTableModel(this, *(CClientDBManager::getInstance().getDB()));
	m_pUserAccountModel->setTable(str_TABLE_USER_ACCOUNT);
	m_pUserAccountModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
	m_pUserAccountModel->select();

	m_pUserAccountTableView->setModel(m_pUserAccountModel);
	m_pUserAccountTableView->setCurrentIndex(inValidIndex);
	CSignalSlotManager::getInstance().set_Slot_DataChange_UserAccount(this);


	pGridLayout = new QGridLayout(this);
	pGridLayout->addWidget(m_pUserAccountTableView, 0, 0, 1, 1);

	_CreateAction();
	_CreateConnect();

}

CUserAccountWidget::~CUserAccountWidget()
{
	CSignalSlotManager::getInstance().set_Slot_DataChange_UserAccount(NULL);
}
void CUserAccountWidget::_CreateAction()
{
	//action
}
void CUserAccountWidget::_CreateConnect()
{
}

void CUserAccountWidget::slot_DataChange_UserAccount()
{
	MYLOG4CPP_DEBUG<<"CUserAccountWidget process slot_DataChange_UserAccount";
	if (NULL != m_pUserAccountModel)
	{
		m_pUserAccountModel->select();
	}
	QModelIndex inValidIndex;
	m_pUserAccountTableView->setCurrentIndex(inValidIndex);
	m_pUserAccountTableView->resizeColumnsToContents();
}


