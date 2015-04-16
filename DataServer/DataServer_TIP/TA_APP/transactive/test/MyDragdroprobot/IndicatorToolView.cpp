#include "IndicatorToolView.h"


//////////////////////////////////////////////////////////////////////////
static int DEFVALUE_Int_Wide_CIndicatorEditorView= 600;
static int DEFVALUE_Int_Hight_CIndicatorEditorView = 600;

static const std::string DEFVALUE_String_CIndicatorEditorView_Title = "Indicator Editor Window";

CIndicatorToolView::CIndicatorToolView(QWidget* parent)
:QGraphicsView(parent)
{
	// ʹ�ÿ������Ⱦ
	setRenderHint(QPainter::Antialiasing);

	// ���û��汳�����������Լӿ���Ⱦ�ٶ�
	setCacheMode(QGraphicsView::CacheBackground);
	setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
	
	setDragMode(QGraphicsView::ScrollHandDrag);
}

CIndicatorToolView::~CIndicatorToolView()
{

}





