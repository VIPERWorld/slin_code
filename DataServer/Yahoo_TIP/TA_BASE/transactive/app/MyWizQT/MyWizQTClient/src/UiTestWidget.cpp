#include "UiTestWidget.h"
CUiTestWidget::CUiTestWidget( QWidget* parent/*=0*/ )
{
	//setMouseTracking ������
	//If mouse tracking is enabled, the widget receives mouse move events even if no buttons are pressed.
	//If mouse tracking is switched off, mouse move events only occur if a mouse button is pressed 
	this->setMouseTracking(true);
}

void CUiTestWidget::_SetAttribute()
{
	//
	//enable MainWindow to be transparent
	//��͸���ı���
	this->setAttribute(Qt::WA_TranslucentBackground); 
	//�ޱ߿�
	this->setWindowFlags(Qt::FramelessWindowHint);
	/*
	�հף�margin���ͼ�ࣨspacing��
	ÿ�ֲ��ֶ���������Ҫ�����ԣ��հ׺ͼ�ࡣ�հ�ָ���������������ܾ��봰���Ե�ľ��룻���ָ���ǲ��ֹ������ڲ��������ڲ���֮��ľ��롣
	Qt��Ĭ�Ϸ���£��Ӵ��岿����margin()��ֵ��9Ӣ�磬�����margin()ֵ��11Ӣ��
	*/
	this->setContentsMargins(0, 0, 0, 0);
	//setMouseTracking ������
	//If mouse tracking is enabled, the widget receives mouse move events even if no buttons are pressed.
	this->setMouseTracking(true);
	//this->setMouseTracking(false);

	// ���̳и�����ı���ɫ
	//can't set setAutoFillBackground=true, ��Ȼ�����ı߶��Ǻڵ�
	//setAutoFillBackground(true);
}


void CUiTestWidget::mousePressEvent( QMouseEvent *event )
{
	QWidget::mousePressEvent(event);
}
//If mouse tracking is switched off, mouse move events only occur if a mouse button is pressed 
//����ڶԻ������ƶ�������û�е���mouseMoveEvent��Ҫ��������ƶ�����
void CUiTestWidget::mouseMoveEvent( QMouseEvent *event )
{
	int a = 0;
}


void CUiTestWidget::mouseReleaseEvent( QMouseEvent *event )
{
	//
	QWidget::mouseReleaseEvent(event);
}
