#include "BottomDockWidget.h"



#include "ProjectQTInclude.h"

#include "ClientDataManagerWorker.h"
#include "TreeItemOrder.h"
#include "TreeModelOrder.h"

#include "BoostLogger.h"
USING_BOOST_LOG;


//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE

//////////////////////////////////////////////////////////////////////////
static int DEFVALUE_INT_Window_Width = 600;
static int DEFVALUE_INT_Window_Height = 100;
static const std::string   DEFVALUE_String_Window_Title = "OrderInfo";

CBottomDockWidget::CBottomDockWidget(QWidget* parent)
    : QWidget(parent)
{

	m_pVBoxLayout = NULL;
	m_pTreeModel_Order = NULL;
	m_pTableView_Order = NULL;//

    setupUi();
	translateLanguage();

	_CreateAction();
	_CreateConnect();
}


CBottomDockWidget::~CBottomDockWidget()
{
	
}


QSize CBottomDockWidget::sizeHint() const
{
	//for QDockWidget
	return QSize(DEFVALUE_INT_Window_Width, DEFVALUE_INT_Window_Height); /* �����ﶨ��dock�ĳ�ʼ��С */
}

void CBottomDockWidget::_CreateAction()
{

}

void CBottomDockWidget::_CreateConnect()
{

}

void CBottomDockWidget::setupUi()
{
	this->resize(DEFVALUE_INT_Window_Width, DEFVALUE_INT_Window_Height);
	//this->setWindowFlags(Qt::Dialog);

	m_pTabWidget = new QTabWidget(this);
	m_pTabWidget->setTabPosition(QTabWidget::South);	//enum TabPosition { North, South, West, East


	m_pTableView_Order = new QTableView(m_pTabWidget);
	m_pTableView_Order->setFrameShape(QFrame::NoFrame); //�����ޱ߿�
	
 	m_pVBoxLayout = new QVBoxLayout(this);
 	m_pVBoxLayout->addWidget(m_pTabWidget);
 	m_pVBoxLayout->setSpacing(0);
 	m_pVBoxLayout->setContentsMargins(0, 0, 0, 0);
	//

	this->setLayout(m_pVBoxLayout);
	//���ô�����������ز�����λ�ڶ���
	this->setWindowFlags(Qt::FramelessWindowHint);
	//�ɻ�ȡ������Ч��
	this->setMouseTracking(true);


	QMetaObject::connectSlotsByName(this);
} 
void CBottomDockWidget::translateLanguage()
{
	this->setWindowTitle(QObject::tr(DEFVALUE_String_Window_Title.c_str()));
	m_pTabWidget->addTab(m_pTableView_Order, QObject::tr("OrderInfo"));

}

void CBottomDockWidget::slotOrderInfoChanged( CTreeItemOrder* pTreeItem )
{
	LOG_DEBUG<<"CBottomDockWidget process slotOrderInfoChanged"
		<<" "<<"pTreeItem=0x"<<pTreeItem;

	QModelIndex inValidIndex;

	if (NULL == m_pTreeModel_Order)
	{
		//
		m_pTreeModel_Order = new CTreeModelOrder(this);
		m_pTreeModel_Order->setRootItem(pTreeItem);

		//mvc
		m_pTableView_Order->setModel(m_pTreeModel_Order);
		//m_pTreeView_Quotes->setColumnWidth(0, 200);
		m_pTableView_Order->setCurrentIndex(inValidIndex);
		m_pTableView_Order->resizeColumnsToContents();

	}
	else
	{
		m_pTreeModel_Order->setRootItem(pTreeItem);
		m_pTableView_Order->setCurrentIndex(inValidIndex);
		m_pTableView_Order->resizeColumnsToContents();
	}
}



//QT_END_NAMESPACE

