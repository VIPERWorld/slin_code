#include "ClientLoginWindow.h"


#include <QtCore/QtCore>
#include <QtGui/QtGui>

#include "share/UiStyleManager.h"
#include "share/UiPathResolve.h"

#include "share/UiImageBorderWidget.h"
#include "share/UiCanResizeMoveWidget.h"

#include "UiTitleWidget.h"


CClientLoginWindow::CClientLoginWindow( QWidget* parent /*= 0*/ )
: IUiCanResizeMoveWidget(parent)
{	
	//Ui level 0, nothing
	//��͸���ı���
	this->setAttribute(Qt::WA_TranslucentBackground); 
	//�ޱ߿�
	this->setWindowFlags(Qt::FramelessWindowHint);
	this->setContentsMargins(0, 0, 0, 0);

	m_pUiMouseEventWidget = NULL;
	m_pUiImageBorderWidget = NULL;
	m_pUiTitleWidget = NULL;
	//Ui level 1
	m_pUiImageBorderWidget = new CUiImageBorderWidget(this);

	m_pUiMouseEventWidget = new CUiMouseEventWidget(this, m_pUiImageBorderWidget);
	m_pUiMouseEventWidget->setContentsMargins(0, 0, 0, 0);
	m_pUiMouseEventWidget->setAutoFillBackground(true);// ���̳и�����ı���ɫ must set
	m_pUiMouseEventWidget->setClientAreaCursorShape(Qt::ArrowCursor);
	m_pUiTitleWidget = new CUiTitleWidget(this, m_pUiMouseEventWidget);
	m_pUiTitleWidget->setTitle("LoginWindow");

	QBoxLayout* pLayout_MouseEventWidget = NULL;
	pLayout_MouseEventWidget = new QBoxLayout(QBoxLayout::TopToBottom);
	pLayout_MouseEventWidget->setContentsMargins(0, 0, 0, 0);
	pLayout_MouseEventWidget->setSpacing(0);
	pLayout_MouseEventWidget->addWidget(m_pUiTitleWidget);
	m_pUiMouseEventWidget->setLayout(pLayout_MouseEventWidget);


	//��һ��QBoxLayout������m_pUiWallWidget�Ĵ�С��m_pUiRect9GirdWidgetһ����
	QBoxLayout* pBoxLayout = NULL;
	pBoxLayout = new QBoxLayout(QBoxLayout::TopToBottom);
	pBoxLayout->setContentsMargins(0, 0, 0, 0);
	pBoxLayout->setSpacing(0);
	pBoxLayout->addWidget(m_pUiMouseEventWidget);//m_pUiWallWidget's rect = m_pUiRect9GirdWidget's rect
	m_pUiImageBorderWidget->setLayout(pBoxLayout);

	//��һ��QBoxLayout������m_pShadowWidget�Ĵ�С��CUiShadowWindowһ����
	QBoxLayout* windowLayout = NULL;
	windowLayout = new QBoxLayout(QBoxLayout::TopToBottom);
	windowLayout->setContentsMargins(0, 0, 0, 0);
	windowLayout->setSpacing(0);
	windowLayout->addWidget(m_pUiImageBorderWidget);//m_pShadowWidget's rect = CUiShadowWindow's rect
	//
	this->setLayout(windowLayout);
}


//posCurrent_InWidget
CUiCommon::ESplitRectType CClientLoginWindow::posType( const QPoint& posValue )
{
	CUiCommon::ESplitRectType  nType = CUiCommon::SplitRectType_NULL;

	if (NULL != m_pUiImageBorderWidget)
	{
		nType = m_pUiImageBorderWidget->posType(posValue);
	}

	return nType;
}

void CClientLoginWindow::setCanResize( bool bValue )
{
	m_pUiMouseEventWidget->setCanResize(bValue);
}

bool CClientLoginWindow::canResize() const
{
	return m_pUiMouseEventWidget->canResize();
}

void CClientLoginWindow::setCanMove( bool bValue )
{
	m_pUiMouseEventWidget->setCanMove(bValue);
}

bool CClientLoginWindow::canMove() const
{
	return m_pUiMouseEventWidget->canMove();
}




