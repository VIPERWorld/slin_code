#include "MyRect.h"
#include "CommonData.h"

#include "MyRectGraphicsItem.h"

#include <QtGui/QPainter>
#include <QtCore/QPoint>

//////////////////////////////////////////////////////////////////////////
class CMyRectData  
{
public:
	CMyRectData();
	virtual ~CMyRectData();
public:
	QPainter* m_pPainter;
};

CMyRectData::CMyRectData()
{
	m_pPainter = NULL;
	m_pPainter = new QPainter();
}

CMyRectData::~CMyRectData ()
{
	if (NULL != m_pPainter)
	{
		delete m_pPainter;
		m_pPainter = NULL;
	}
}

//////////////////////////////////////////////////////////////////////////

// constructor
CMyRect::CMyRect( QWidget* parent /*= 0*/ )
:QWidget(parent)
{
	m_pData = NULL;
	m_pGraphicsView = NULL;
	m_pGraphicsScene = NULL;
	m_pMyRectGraphicsItem = NULL;

	m_pData = new CMyRectData();

	_SetupWidgetUi();
}

// destructor
CMyRect::~CMyRect ()
{

	if (NULL != m_pMyRectGraphicsItem)
	{
		delete m_pMyRectGraphicsItem;
		m_pMyRectGraphicsItem = NULL;
	}

	if (NULL != m_pGraphicsScene)
	{
		delete m_pGraphicsScene;
		m_pGraphicsScene = NULL;
	}

	if (NULL != m_pGraphicsView)
	{
		delete m_pGraphicsView;
		m_pGraphicsView = NULL;
	}
	

	if (NULL != m_pData)
	{
		delete m_pData;
		m_pData = NULL;
	}

};

void CMyRect::_SetupWidgetUi()
{
	/*move to central*/
	this->setWindowTitle(tr("MyRect"));
	//this->setGeometry(0, 0, 800, 800);
	this->setFixedSize(800, 800);

	QDesktopWidget *desk = QApplication::desktop();   
	int wd = desk->width();   
	int ht = desk->height();   
	this->move( (wd - width())/2, (ht - height())/2 );   


	/*
	����һ������QGraphicsScene�����ǿ��԰���������һ��������
	���ǵ�QGraphicsItem������Ƶ���������ϣ�
	Ȼ���ٰ�����������ҡ���QGraphicsView��⡰ǽ����չʾ����
	*/

	m_pGraphicsView = new QGraphicsView(this);
	m_pGraphicsScene = new QGraphicsScene();
	m_pMyRectGraphicsItem = new CMyRectGraphicsItem();



	//���á������������������꣨-500��-500��Ϊ���Ͻǣ�
	//�����ζ��scene������λ��Ϊ(0,0).�������ϵ����scene������ϵ
	m_pGraphicsScene->setSceneRect(-500, -500, 1000, 1000);

	m_pGraphicsScene->addItem(m_pMyRectGraphicsItem);//�����������ϻ���MyItem 
	//m_pMyRectGraphicsItem->setPos(0,0)����MyItem�ڡ�������scene��λ�ã���ʱ�����ǰ�item������Լ�������ϵ��ԭ��ŵ�scene�ģ�0,0��λ��
	m_pMyRectGraphicsItem->setPos(0, 0);


	m_pGraphicsView->setObjectName(QString::fromUtf8("graphicsView"));
	m_pGraphicsView->setScene(m_pGraphicsScene);
	m_pGraphicsView->centerOn(0, 0);//�ѻ���scene������λ�÷ŵ�QGraphicsView������ 
	//m_pGraphicsView->setGeometry(QRect(0, 0, 600, 600));
	m_pGraphicsView->setFixedSize(600, 600);
	m_pGraphicsView->move(
		((this->width() - m_pGraphicsView->width()) / 2),
		((this->height() - m_pGraphicsView->height()) / 2)
		);



} // setupUi

void CMyRect::paintEvent( QPaintEvent *pEvent )
{
	//QPainter* painter = NULL;
	//painter = m_pData->m_pPainter;
	//painter->begin(this);
	//painter->setPen(QPen(Qt::blue, 4, Qt::DashLine)); //���û�����ʽ ��������ɫ���ߵ����ͣ�
	//painter->setBrush(QBrush(Qt::red, Qt::SolidPattern)); //���û�ˢ��ʽ
	//painter->drawRect(20,20,160,160);//�� ����
	//painter->drawEllipse(20,20,210,160);  //����Բ //   ��1��2�������ֱ��ʾԲ/��Բ�����Ͻǵ�����������3,4��������ʾԲ/��Բ�Ŀ�Ⱥ͸߶ȡ�����ȷ�еر��������Բ����Բ���ھ����У�������ε����ϽǵĶ������������е�λ��Ϊ��20��20�������Բ����Բ������Ϊ������ε����ģ����µĶ����ƣ�����
	//painter->drawRoundRect(20,20,210,160,50,50);//����Բ�Ǿ���    ����������������ǵ�Բ�ȡ�������Ϊ0��99֮�������ֵ��99������Բ����
	//painter->drawPie(20,20,210,160,0,500);//��������ͼ  ǰ�ĸ���������Բ(��drawEllipse()������ͬ������������������Բ����ʽ��0Ϊ��ʼ�Ƕȣ�ʵ�ʵ�λΪ1/16�ȣ���500Ϊ������չ���ĽǶ�(��λҲΪ1/16��)��
	//painter->drawChord(20,20,210,160,500,1000);//������
	//painter->drawArc(20, 20, 210, 160, 500, 1000);//����Բ��
	//painter->end();
	//painter = NULL;
}
