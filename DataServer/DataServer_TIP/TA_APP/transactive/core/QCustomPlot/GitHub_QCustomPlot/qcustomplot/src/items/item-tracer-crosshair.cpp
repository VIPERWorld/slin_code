#include "item-tracer-crosshair.h"

#include "../painter.h"
#include "../core.h"
#include "../plottables/plottable-graph.h"
#include "../layoutelements/layoutelement-axisrect.h"


#include "../plottables/plottable-statisticalbox.h"



//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////


QCPItemTracerCrossHair::QCPItemTracerCrossHair(QCustomPlot *parentPlot) :
QCPAbstractItem(parentPlot),
m_pItemPosition(this->createPosition("position"))/*QCPItemPosition* const m_pItemPosition*/
{
	//Qt::Horizontal 水平
	m_linef_Horizontal = QLineF(0, 0, 0, 0);
	m_bShow_Linef_Horizontal = false;
	m_str_Horizontal_left.clear();
	m_str_Horizontal_right.clear();
	m_pointf_Horizontal_left = QPointF(0, 0);
	m_pointf_Horizontal_right = QPointF(0, 0);
	m_bShow_Horizontal_left = true;
	m_nShowType_Horizontal_left = QCPAxis::ltNumber;

	//Qt::Vertical 垂直
	m_linef_Vertical = QLineF(0, 0, 0, 0);
	m_bShow_Linef_Vertical = false;
	m_str_Vertical_bottom.clear();
	m_str_Vertical_top.clear();
	m_pointf_Vertical_bottom = QPointF(0, 0);
	m_pointf_Vertical_top = QPointF(0, 0);
	m_bShow_Vertical_bottom = true;
	m_nShowType_Vertical_bottom = QCPAxis::ltNumber;

	//m_pItemPosition = NULL;
	//m_pItemPosition = this->createPosition("position");//QCPAbstractItem::createPosition(const QString &name)
	m_pItemPosition->setType(QCPItemPosition::ptPlotCoords);
	m_pItemPosition->setAxes(mParentPlot->xAxis, mParentPlot->yAxis);//default
	if (mParentPlot->axisRect())
	{
		m_pItemPosition->setAxisRect(mParentPlot->axisRect());//default
	}
	m_pItemPosition->setCoords(0, 0);//default
	m_pItemPosition->setPixelPoint(QPointF(0,0));//default


	m_pQCPGraphTracerCrossData = NULL;
	m_pQCPGraphTracerCrossData = new QCPGraphTracerCrossData();

	m_pQCPStatisticalBoxTracerCrossData = NULL; 	
	m_pQCPStatisticalBoxTracerCrossData = new QCPStatisticalBoxTracerCrossData();

	setBrush(Qt::NoBrush);
	setSelectedBrush(Qt::NoBrush);
	setPen(QPen(Qt::black));
	//setSelectedPen(QPen(Qt::blue, 2));
	setSelectedPen(QPen(Qt::black));
	setStyle(tsCrosshair);
	setCenterPos(QPointF(0, 0));
}

QCPItemTracerCrossHair::~QCPItemTracerCrossHair()
{
	if (NULL != m_pQCPGraphTracerCrossData)
	{
		delete m_pQCPGraphTracerCrossData;
		m_pQCPGraphTracerCrossData = NULL;
	}

	if (NULL != m_pQCPStatisticalBoxTracerCrossData)
	{
		delete m_pQCPStatisticalBoxTracerCrossData;
		m_pQCPStatisticalBoxTracerCrossData = NULL;
	}

	
}

/*!
Sets the pen that will be used to draw the line of the tracer

\see setSelectedPen, setBrush
*/
void QCPItemTracerCrossHair::setPen(const QPen &pen)
{
	mPen = pen;
}

/*!
Sets the pen that will be used to draw the line of the tracer when selected

\see setPen, setSelected
*/
void QCPItemTracerCrossHair::setSelectedPen(const QPen &pen)
{
	mSelectedPen = pen;
}

/*!
Sets the brush that will be used to draw any fills of the tracer

\see setSelectedBrush, setPen
*/
void QCPItemTracerCrossHair::setBrush(const QBrush &brush)
{
	mBrush = brush;
}

/*!
Sets the brush that will be used to draw any fills of the tracer, when selected.

\see setBrush, setSelected
*/
void QCPItemTracerCrossHair::setSelectedBrush(const QBrush &brush)
{
	mSelectedBrush = brush;
}



/*!
Sets the style/visual appearance of the tracer.

If you only want to use the tracer \a position as an anchor for other items, set \a style to
\ref tsNone.
*/
void QCPItemTracerCrossHair::setStyle(QCPItemTracerCrossHair::TracerStyle style)
{
	mStyle = style;
}




/* inherits documentation from base class */
double QCPItemTracerCrossHair::selectTest(const QPointF &pos, bool onlySelectable, QVariant *details) const
{
	Q_UNUSED(details)
		if (onlySelectable && !mSelectable)
			return -1;

	//QPointF center(m_pointf_center);
	QPointF center(m_pItemPosition->pixelPoint());

	QRect clip = clipRect();
	switch (mStyle)
	{
	case tsNone: 
		return -1;
	case tsCrosshair:
		{
			return qSqrt(qMin(distSqrToLine(QPointF(clip.left(), center.y()), QPointF(clip.right(), center.y()), pos),
				distSqrToLine(QPointF(center.x(), clip.top()), QPointF(center.x(), clip.bottom()), pos)));
		}
	}
	return -1;
}

/* inherits documentation from base class */
void QCPItemTracerCrossHair::draw(QCPPainter *painter)
{
	if (mStyle == tsNone)
	{
		return;
	}
	painter->setPen(mainPen());
	painter->setBrush(mainBrush());

	switch (mStyle)
	{
	case tsCrosshair:
		{
			if (m_bShow_Linef_Vertical)
			{
				painter->drawLine(m_linef_Vertical);
			}
			if (m_bShow_Linef_Horizontal)
			{
				painter->drawLine(m_linef_Horizontal);
			}

 			painter->drawText(m_pointf_Horizontal_right, m_str_Horizontal_right);
 			painter->drawText(m_pointf_Horizontal_left, m_str_Horizontal_left);
 			painter->drawText(m_pointf_Vertical_bottom, m_str_Vertical_bottom);
 			painter->drawText(m_pointf_Vertical_top, m_str_Vertical_top);

			if (m_pQCPGraphTracerCrossData->isSetData())
			{
				QString strInfo;
				strInfo = QString("%1, %2").arg(m_pQCPGraphTracerCrossData->m_nGraphKey).arg(m_pQCPGraphTracerCrossData->m_nGraphValue);
				painter->drawText(m_pointf_Horizontal_left.x() + 50, m_pointf_Horizontal_left.y() + 10, strInfo);
			}
			
			break;
		}
	default:
		return;
	}
}

/*! \internal

Returns the pen that should be used for drawing lines. Returns mPen when the item is not selected
and mSelectedPen when it is.
*/
QPen QCPItemTracerCrossHair::mainPen() const
{
	return mSelected ? mSelectedPen : mPen;
}

/*! \internal

Returns the brush that should be used for drawing fills of the item. Returns mBrush when the item
is not selected and mSelectedBrush when it is.
*/
QBrush QCPItemTracerCrossHair::mainBrush() const
{
	return mSelected ? mSelectedBrush : mBrush;
}

void QCPItemTracerCrossHair::setCenterPos( const QPointF& posf )
{
	//m_pointf_center = posf;

	m_pItemPosition->setPixelPoint(posf);//default

	_UpdateAllInfo();
}

void QCPItemTracerCrossHair::_UpdateLinesInfo()
{
	QPointF center(m_pItemPosition->pixelPoint());
	QRect clip = clipRect();
	
	//Qt::Vertical 垂直
	if (center.x() > clip.left() && center.x() < clip.right())
	{
		m_bShow_Linef_Vertical = true;
		m_linef_Vertical = QLineF(center.x(), clip.bottom(), center.x(), clip.top());
		m_pointf_Vertical_bottom = m_linef_Vertical.p1();
		m_pointf_Vertical_top = m_linef_Vertical.p2();

	}
	else
	{
		m_bShow_Linef_Vertical = false;
		m_linef_Vertical = QLineF(clip.topLeft(), clip.bottomLeft());
		m_pointf_Vertical_bottom = QPointF(0, 0);
		m_pointf_Vertical_top = QPointF(0, 0);

	}



	//Qt::Horizontal 水平
	if (center.y() > clip.top() && center.y() < clip.bottom())
	{
		m_bShow_Linef_Horizontal = true;
		m_linef_Horizontal = QLineF(clip.left(), center.y(), clip.right(), center.y());
		m_pointf_Horizontal_left = m_linef_Horizontal.p1();
		m_pointf_Horizontal_right = m_linef_Horizontal.p2();

	}
	else
	{
		m_bShow_Linef_Horizontal = false;
		m_linef_Horizontal = QLineF(clip.topLeft(), clip.topRight());
		m_pointf_Horizontal_left = QPointF(0, 0);
		m_pointf_Horizontal_right = QPointF(0, 0);
	}


}

void QCPItemTracerCrossHair::_UpdateTextInfo()
{
	double fKey = 0; 
	double fValue = 0;

	fKey = m_pItemPosition->key();
	fValue = m_pItemPosition->value();

	if (m_bShow_Vertical_bottom)
	{
		if (QCPAxis::ltDateTime == m_nShowType_Vertical_bottom)
		{
			QString strTimeValue;
			strTimeValue = mParentPlot->locale().toString(QDateTime::fromTime_t(fKey).toLocalTime(), m_strFormat_Vertical_bottom);
			m_str_Vertical_bottom =  QString("%1 fKey=%2 strTimekey=%3").arg("Vertical_bottom").arg(fKey).arg(strTimeValue);
		}
		else
		{
			m_str_Vertical_bottom =  QString("%1 fKey=%2").arg("Vertical_bottom").arg(fKey);
		}		
	}
	else
	{
		m_str_Vertical_bottom =  QString("");
	}


	if (m_bShow_Horizontal_left)
	{
		if (QCPAxis::ltDateTime == m_nShowType_Horizontal_left)
		{
			QString strTimeValue;
			strTimeValue = mParentPlot->locale().toString(QDateTime::fromTime_t(fKey).toLocalTime(), m_strFormat_Horizontal_left);
			m_str_Horizontal_left =  QString("%1 fValue=%2 strTimekey=%3").arg("Horizontal_left").arg(fValue).arg(strTimeValue);
		}
		else
		{
			m_str_Horizontal_left =  QString("%1 fValue=%2").arg("Horizontal_left").arg(fValue);
		}		
	}
	else
	{
		m_str_Horizontal_left =  QString("");
	}
	
	m_str_Horizontal_right =  QString("%1").arg("Horizontal_right");
	m_str_Vertical_top = QString("%1").arg("Vertical_top");

	//坐标系 topleft(0, 0) x轴 y轴
	m_pointf_Horizontal_left.setX(m_pointf_Horizontal_left.x() + 5);
	m_pointf_Horizontal_left.setY(m_pointf_Horizontal_left.y() - 10);
	m_pointf_Horizontal_right.setX(m_pointf_Horizontal_right.x() - 100);
	m_pointf_Horizontal_right.setY(m_pointf_Horizontal_right.y() - 10);
	m_pointf_Vertical_bottom.setX(m_pointf_Vertical_bottom.x() + 5);
	m_pointf_Vertical_bottom.setY(m_pointf_Vertical_bottom.y() - 20);
	m_pointf_Vertical_top.setX(m_pointf_Vertical_top.x() + 5);
	m_pointf_Vertical_top.setY(m_pointf_Vertical_top.y() + 20);


}

void QCPItemTracerCrossHair::_UpdateAllInfo()
{
	_UpdateLinesInfo();
	_UpdateVerticalCrossValue();
	_UpdateTextInfo();
}

void QCPItemTracerCrossHair::setTracerAxisRect( QCPAxisRect* pAxisRect )
{
	if (NULL == pAxisRect)
	{
		return;
	}
	
	QCPAxis* pAxisKey = NULL; 
	QCPAxis* pAxisValue = NULL;

	this->setClipToAxisRect(true);
	this->setClipAxisRect(pAxisRect);


	pAxisKey = pAxisRect->axis(QCPAxis::atBottom);
	pAxisValue = pAxisRect->axis(QCPAxis::atLeft);

	m_pItemPosition->setType(QCPItemPosition::ptPlotCoords);
	m_pItemPosition->setAxes(pAxisKey, pAxisValue);//default
	m_pItemPosition->setAxisRect(pAxisRect);//default
	m_pItemPosition->setCoords(0, 0);//default
	m_pItemPosition->setPixelPoint(QPointF(0,0));//default
}

void QCPItemTracerCrossHair::setShowBottom(QCPAxis::LabelType nShowType, bool bShow, const QString& strFormat )
{
	m_bShow_Vertical_bottom = bShow;
	m_nShowType_Vertical_bottom = nShowType;
	m_strFormat_Vertical_bottom = strFormat;
}

void QCPItemTracerCrossHair::setShowLeft(QCPAxis::LabelType nShowType, bool bShow, const QString& strFormat )
{
	m_bShow_Horizontal_left = bShow;
	m_nShowType_Horizontal_left = nShowType;
	m_strFormat_Horizontal_left = strFormat;
}

void QCPItemTracerCrossHair::_ClearCrossData()
{

	if (NULL != m_pQCPGraphTracerCrossData)
	{
		m_pQCPGraphTracerCrossData->clear();
	}

	if (NULL != m_pQCPStatisticalBoxTracerCrossData)
	{
		m_pQCPStatisticalBoxTracerCrossData->clear();
	}
	
}


void QCPItemTracerCrossHair::_GetValue_QCPGraph(QCPGraph* pPlottableRef)
{
	if (NULL == pPlottableRef)
	{
		return;
	}

	double nGraphKey = 0;
	//QPointF center(m_pItemPosition->pixelPoint());

	//nGraphKey = center.x();
	nGraphKey = m_pItemPosition->key();

	if (NULL != m_pQCPGraphTracerCrossData)
	{
		m_pQCPGraphTracerCrossData->clear();
		m_pQCPGraphTracerCrossData->setGraphKey(nGraphKey);
		m_pQCPGraphTracerCrossData->setGraphValue(pPlottableRef);
	}
	


}
void QCPItemTracerCrossHair::_GetValue_QCPStatisticalBox(QCPStatisticalBox* pPlottableRef)
{
	if (NULL == pPlottableRef)
	{
		return;
	}
	

}
void QCPItemTracerCrossHair::_UpdateVerticalCrossValue()
{
	QCPAbstractPlottable* pPlottableRef = NULL;
	int nPlottableCount = 0;
	int nPlottableIndex = 0;
	QCPAbstractPlottable::PLayerableType  nPType;
	QCPGraph* pQCPGraphTmp = NULL;
	QCPStatisticalBox* pQCPStatisticalBoxTmp = NULL;
	
	_ClearCrossData();

	nPlottableCount = mParentPlot->plottableCount();
	for (nPlottableIndex = 0; nPlottableIndex < nPlottableCount; nPlottableIndex++)
	{	
		pPlottableRef = mParentPlot->plottable(nPlottableIndex);
		nPType = pPlottableRef->getPTType();

		switch (nPType)
		{
		case QCPAbstractPlottable::ptNone:
			break;
		case QCPAbstractPlottable::ptQCPAbstractPlottable:
			///< QCPAbstractPlottable
			break;
		case QCPAbstractPlottable::ptQCPBars:
			///< QCPBars
			break;
		case QCPAbstractPlottable::ptQCPColorMap:
			///< QCPColorMap
			break;
		case QCPAbstractPlottable::ptQCPCurve:
			///< QCPCurve
			break;
		case QCPAbstractPlottable::ptQCPGraph:
			///< QCPGraph
			pQCPGraphTmp = dynamic_cast<QCPGraph*>(pPlottableRef);//child parent
			_GetValue_QCPGraph(pQCPGraphTmp);
			break;
		case QCPAbstractPlottable::ptQCPStatisticalBox:
			 ///< QCPStatisticalBox
			pQCPStatisticalBoxTmp = dynamic_cast<QCPStatisticalBox*>(pPlottableRef); 
			_GetValue_QCPStatisticalBox(pQCPStatisticalBoxTmp);
			break;
		default:
			break;
		}//switch
		
	}//for
	

}





//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////
QCPStatisticalBoxTracerCrossData::QCPStatisticalBoxTracerCrossData()
{
	m_bSetData = false;
	m_nGraphKey = 0;
	m_nGraphValue = 0;
}

QCPStatisticalBoxTracerCrossData::~QCPStatisticalBoxTracerCrossData()
{
	m_bSetData = false;
	m_nGraphKey = 0;
	m_nGraphValue = 0;
}

void QCPStatisticalBoxTracerCrossData::clear()
{
	m_bSetData = false;
	m_nGraphKey = 0;
	m_nGraphValue = 0;
}

//////////////////////////////////////////////////////////////////////////
QCPGraphTracerCrossData::QCPGraphTracerCrossData()
{
	m_bSetData = false;
	m_nGraphKey = 0;
	m_nGraphValue = 0;
}

QCPGraphTracerCrossData::~QCPGraphTracerCrossData()
{
	m_bSetData = false;
	m_nGraphKey = 0;
	m_nGraphValue = 0;
}

void QCPGraphTracerCrossData::clear()
{
	m_bSetData = false;
	m_nGraphKey = 0;
	m_nGraphValue = 0;
}

void QCPGraphTracerCrossData::setGraphKey(double fGraphKey)
{
	clear();
	m_bSetData = true;
	m_nGraphKey = fGraphKey;
}
void QCPGraphTracerCrossData::setGraphValue(QCPGraph* pPlottableRef)
{
	if (NULL == pPlottableRef)
	{
		m_bSetData = false;
		return;
	}

	if (false == m_bSetData)
	{
		return;
	}
	bool mInterpolating = false;

	if (pPlottableRef->data()->size() > 1)
	{
		QCPDataMap::const_iterator first = pPlottableRef->data()->constBegin();
		QCPDataMap::const_iterator last = pPlottableRef->data()->constEnd()-1;
		if (m_nGraphKey < first.key())
		{
			m_nGraphValue = first.value().value;
			m_bSetData = false;
		}
		else if (m_nGraphKey > last.key())
		{
			m_nGraphValue = last.value().value;
			m_bSetData = false;
		}
		else
		{
			QCPDataMap::const_iterator it = pPlottableRef->data()->lowerBound(m_nGraphKey);
			if (it != first) // mGraphKey is somewhere between iterators
			{
				QCPDataMap::const_iterator prevIt = it-1;
				if (mInterpolating)
				{
					// interpolate between iterators around mGraphKey:
					double slope = 0;
					if (!qFuzzyCompare((double)it.key(), (double)prevIt.key()))
					{
						slope = (it.value().value-prevIt.value().value)/(it.key()-prevIt.key());
					}
					m_nGraphValue = (m_nGraphKey-prevIt.key()) * slope + prevIt.value().value;
				} 
				else
				{
					// find iterator with key closest to mGraphKey:
					if (m_nGraphKey < (prevIt.key()+it.key())*0.5)
					{
						it = prevIt;
					}
					m_nGraphValue =  it.value().value;
				}
			} 
			else // mGraphKey is exactly on first iterator
			{
				m_nGraphValue =  it.value().value;
			}
		}
	} 
	else if (pPlottableRef->data()->size() == 1)
	{
		QCPDataMap::const_iterator it = pPlottableRef->data()->constBegin();
		if (m_nGraphKey < it.key())
		{
			m_nGraphValue = it.value().value;
			m_bSetData = false;
		}
		else if (m_nGraphKey > it.key())
		{
			m_nGraphValue = it.value().value;
			m_bSetData = false;
		}
		else
		{
			m_nGraphValue =  it.value().value;
			m_bSetData = true;
		}
	} 
	else
	{
		qDebug() << Q_FUNC_INFO << "graph has no data";
	}


}

bool QCPGraphTracerCrossData::isSetData()
{
	return m_bSetData;
}


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////


