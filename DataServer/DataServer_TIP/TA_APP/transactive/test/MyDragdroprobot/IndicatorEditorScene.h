#ifndef __CLASS__INDICATOR_EDITOR_SECNE_H__
#define __CLASS__INDICATOR_EDITOR_SECNE_H__


#include <QtGui/QtGui>
#include <QtGui/QGraphicsScene>


class CIndicatorEditorScene : public QGraphicsScene
{
    Q_OBJECT

public:
    CIndicatorEditorScene(QObject *parent = 0);
	virtual ~CIndicatorEditorScene();

public slots:
	

signals:


protected:
	// dragEnterEvent ����ק����������ק�Ŀؼ�ʱ����
	//void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
	// dragLeaveEvent ����ק(û���ͷ����ʱ)�뿪������ק�Ŀؼ�ʱ����
	void dragLeaveEvent(QGraphicsSceneDragDropEvent *event);
	
	//dragMoveEvent ��ק״̬���ڽ�����ק�Ŀؼ����ƶ����ʱ����
	//void dragMoveEvent(QGraphicsSceneDragDropEvent *event);
	//dropEvent ��ק״̬���ͷ����ʱ����
	//void dropEvent(QGraphicsSceneDragDropEvent *event);

private:
	QColor m_nColor;

	QColor m_nDragColor;
	bool m_bDragOver;
};


#endif//__CLASS__INDICATOR_EDITOR_SECNE_H__
