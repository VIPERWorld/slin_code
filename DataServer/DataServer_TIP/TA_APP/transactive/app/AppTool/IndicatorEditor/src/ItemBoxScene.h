#ifndef __CLASS__ITEM_BOX_SECNE_H__
#define __CLASS__ITEM_BOX_SECNE_H__

#include "CommonDef.h"

#include <QtGui/QtGui>
#include <QtGui/QGraphicsScene>

//QT_BEGIN_NAMESPACE


class CItemBoxScene : public QGraphicsScene
{
    Q_OBJECT



public:
    CItemBoxScene(QObject *parent = 0);
	virtual ~CItemBoxScene();

protected:
	// dragEnterEvent ����ק����������ק�Ŀؼ�ʱ����
	//void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
	// dragLeaveEvent ����ק(û���ͷ����ʱ)�뿪������ק�Ŀؼ�ʱ����
	//void dragLeaveEvent(QGraphicsSceneDragDropEvent *event);
	// dragMoveEvent ��ק״̬���ڽ�����ק�Ŀؼ����ƶ����ʱ����

	//dropEvent ��ק״̬���ͷ����ʱ����
	//void dropEvent(QGraphicsSceneDragDropEvent *event);
};

//QT_END_NAMESPACE

#endif//__CLASS__INDICATOR_EDITOR_SECNE_H__
