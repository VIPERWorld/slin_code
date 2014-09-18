#include "MidSubWidget.h"



#include "ProjectQTInclude.h"

#include "ClientDataManagerWorker.h"
#include "qcustomplot.h"
#include "HistoryDataManager.h"


#include "BoostLogger.h"
USING_BOOST_LOG;


//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE

//////////////////////////////////////////////////////////////////////////
static int DEFVALUE_INT_Window_Width = 100;
static int DEFVALUE_INT_Window_Height = 100;
static const std::string   DEFVALUE_String_Window_Title = "MidSubWidget";

CMidSubWidget::CMidSubWidget(QWidget* parent)
    : QWidget(parent)
{

	m_pCustomPlot = NULL;

    setupUi();
	translateLanguage();


	_CreateAction();
	_CreateConnect();

	//doTest(customPlot);


}


CMidSubWidget::~CMidSubWidget()
{
	
}


QSize CMidSubWidget::sizeHint() const
{
	//for QDockWidget
	return QSize(DEFVALUE_INT_Window_Width, DEFVALUE_INT_Window_Height); /* �����ﶨ��dock�ĳ�ʼ��С */
}

void CMidSubWidget::_CreateAction()
{

}

void CMidSubWidget::_CreateConnect()
{

}

void CMidSubWidget::setupUi()
{
	//this->resize(DEFVALUE_INT_Window_Width, DEFVALUE_INT_Window_Height);
	//this->setWindowFlags(Qt::Dialog);
	m_pCustomPlot = new QCustomPlot(this);

	verticalLayout = new QVBoxLayout(this);
	verticalLayout->setSpacing(6);
	verticalLayout->setContentsMargins(11, 11, 11, 11);
	verticalLayout->addWidget(m_pCustomPlot);

	//setGeometry(400, 250, 542, 390);
	
	QMetaObject::connectSlotsByName(this);
} 
void CMidSubWidget::translateLanguage()
{
	this->setWindowTitle(QObject::tr(DEFVALUE_String_Window_Title.c_str()));

}



void CMidSubWidget::doTest()
{



}

void CMidSubWidget::slotHistoryDataChanged( CHistoryDataManager* pMyBarSumary )
{
	//emit
	{
		LOG_DEBUG<<" "<<"slot"
			<<" "<<"class:"<<"CMidSubWidget"
			<<" "<<"fun:"<<"slotHistoryDataChanged()"
			<<" "<<"param:"
			<<" "<<"pMyBarSumary=0x"<<pMyBarSumary;
	}


	QBrush redBrush(QColor(255, 0, 0, 255));//red
	QPen redPen(QColor(255, 0, 0, 255));//red
	QBrush greenBrush(QColor(0, 255, 0, 255));//green
	QPen greenPen(QColor(0, 255, 0, 255));//green

	int nBarWith = pMyBarSumary->m_pHistoryRequest->m_nBarTypeSeconds; //FIVE_MINUTES

	QBrush* pBoxBrushRef = NULL;
	QPen* pBoxPenRef = NULL;
	QCPStatisticalBox *pStatisticalBoxRef = NULL;

	double fMinimum = 0;
	double fMaximum = 0;
	double fLowerQuartile = 0;
	double fUpperQuartile = 0;

	QMap<unsigned int, Bar>::iterator iterMap;
	int nIndex = 0;
	QVector<double> xData;
	QVector<double> yData;

	// prepare axes:
	m_pCustomPlot->clearGraphs();	
	m_pCustomPlot->xAxis->setLabel(QObject::tr("X-time"));
	m_pCustomPlot->yAxis->setLabel(QObject::tr("Y-value"));

	// configure bottom axis to show date and time instead of number:
	m_pCustomPlot->xAxis->setTickLabelType(QCPAxis::ltDateTime);
	m_pCustomPlot->xAxis->setDateTimeFormat("yyyy-MM-dd\nhh-mm-ss");

	// make key axis range scroll with the data (at a constant range size of 8):
	m_pCustomPlot->xAxis->setRange(pMyBarSumary->m_pHistoryRequest->m_nFromTime_Type0, pMyBarSumary->m_pHistoryRequest->m_nToTime_Type0);
	//customPlot->yAxis->setRange(0, 200);
	// show legend:
	m_pCustomPlot->legend->setVisible(false);

	nIndex = 0;
	iterMap = pMyBarSumary->m_pHistoryACK->m_MapBarData.begin();
	while (iterMap != pMyBarSumary->m_pHistoryACK->m_MapBarData.end())
	{
		//iterMap->second;
		// create empty statistical box plottables:
		pStatisticalBoxRef = NULL;
		pStatisticalBoxRef = new QCPStatisticalBox(m_pCustomPlot->xAxis, m_pCustomPlot->yAxis);
		m_pCustomPlot->addPlottable(pStatisticalBoxRef);


		fMinimum = iterMap->low;
		fMaximum= iterMap->high;
		//iterMap->second.timestamp = nTimeNow + nIndex * nBarTypeSeconds;//5 minutes
		xData[nIndex] = iterMap->timestamp;
		yData[nIndex] = iterMap->volume;

		if (iterMap->open > iterMap->close)
		{
			//high->low
			fLowerQuartile = iterMap->close;
			fUpperQuartile = iterMap->open;

			pBoxBrushRef = &redBrush;
			pBoxPenRef = &redPen;

		}
		else
		{
			fLowerQuartile = iterMap->open;
			fUpperQuartile = iterMap->close;

			pBoxBrushRef = &greenBrush;
			pBoxPenRef = &greenPen;
		}

		//boxBrush.setStyle(Qt::SolidPattern); // make it look oldschool Qt::SolidPattern  Qt::Dense6Pattern
		pStatisticalBoxRef->setBrush(*pBoxBrushRef);
		pStatisticalBoxRef->setPen(*pBoxPenRef);
		pStatisticalBoxRef->setWhiskerPen(*pBoxPenRef);
		pStatisticalBoxRef->setWhiskerBarPen(*pBoxPenRef);
		pStatisticalBoxRef->setMedianPen(*pBoxPenRef);

		// set data:
		//pStatisticalBoxTmp->setKey(nIndex);
		pStatisticalBoxRef->setKey(iterMap->timestamp);
		pStatisticalBoxRef->setMinimum(fMinimum);
		pStatisticalBoxRef->setLowerQuartile(fLowerQuartile);
		pStatisticalBoxRef->setMedian(fLowerQuartile);
		pStatisticalBoxRef->setUpperQuartile(fUpperQuartile);
		pStatisticalBoxRef->setMaximum(fMaximum);

		//pStatisticalBoxTmp->setWidth(1);//���ο��
		pStatisticalBoxRef->setWidth(nBarWith);//���ο��

		pStatisticalBoxRef->setWhiskerWidth(0);//�϶����µ� ֱ�߿��

		nIndex++;
		iterMap++;
	}//while


	QCPGraph *pGrapLineVolume = m_pCustomPlot->addGraph(m_pCustomPlot->xAxis, m_pCustomPlot->yAxis);
	pGrapLineVolume->setData(xData, yData);


	m_pCustomPlot->rescaleAxes();
	m_pCustomPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);
	m_pCustomPlot->replot();//draw again
}

//QT_END_NAMESPACE

