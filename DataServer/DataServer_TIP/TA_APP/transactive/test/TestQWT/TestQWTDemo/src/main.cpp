//#include "vld.h"

//#include <qapplication.h>
#include <QtGui/QApplication>
#include <QtGui/QSplashScreen>
#include <QtGui/QPixmap>
#include <QtCore/QTextCodec>
#include <QtCore/QTranslator>
#include <QtCore/QSharedMemory>
#include <QtCore/QFile>

//////////////////////////////////////////////////////////////////////////

#include <QtGui/QApplication>
#include <Qt/qmath.h>
//#include <QVector>
#include <QtCore/QVector>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_plot_magnifier.h>
#include <qwt_plot_panner.h>
#include <qwt_legend.h>
#include <qwt_point_data.h>

//////////////////////////////////////////////////////////////////////////


#include <iostream>
#include "Log4cppLogger.h"
//QWT_DLL

#pragma comment(lib, "Ws2_32.lib")//winsock2
//Ws2_32.lib

int main( int argc, char* argv[] )
{
	CLog4cppLogger::getInstance();
	CLog4cppLogger::getInstance().initLog();
	CLog4cppLogger::getInstance().testLog();
	CLog4cppLogger::removeInstance();



	QApplication a(argc, argv);
	QwtPlot plot(QwtText("CppQwtExample1"));
	plot.resize(640,400);
	//���������������
	plot.setAxisTitle(QwtPlot::xBottom, "x->");
	plot.setAxisTitle(QwtPlot::yLeft, "y->");
	//����������ķ�Χ//����X��Y���귶Χ  
	plot.setAxisScale(QwtPlot::xBottom, 0.0, 2.0 * M_PI);
	plot.setAxisScale(QwtPlot::yLeft, -1.0, 1.0);
	//�����ұ߱�ע
	plot.insertLegend(new QwtLegend(), QwtPlot::RightLegend);
	//ʹ�ù��ַŴ�/��С
	(void) new QwtPlotMagnifier( plot.canvas() );
	//ʹ��������ƽ��
	(void) new QwtPlotPanner( plot.canvas() );
	//������������
	QVector<double> xs;
	QVector<double> ys;
	for (double x = 0; x < 2.0 * M_PI; x+=(M_PI / 10.0))
	{
		xs.append(x);
		ys.append(qSin(x));
	}
	//������������
	QwtPointArrayData * const data = new QwtPointArrayData(xs, ys);
	
	//�½�һ�����߶���
	QwtPlotCurve curve("Sine");//curve1
	curve.setData(data);//��������
	curve.setStyle(QwtPlotCurve::Lines);//ֱ����ʽ
	curve.setCurveAttribute(QwtPlotCurve::Fitted, true);//�����߸��⻬
	curve.setRenderHint(QwtPlotItem::RenderAntialiased,true);//����� 
	curve.setPen(QPen(Qt::blue));//���û���
	curve.attach(&plot);//�����߸��ӵ�plot��
	plot.show();

	a.exec();
	
	return 0;
}










