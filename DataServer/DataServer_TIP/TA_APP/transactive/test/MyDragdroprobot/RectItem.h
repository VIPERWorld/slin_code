#ifndef __CLASS_CRECT_ITEM__HH__
#define __CLASS_CRECT_ITEM__HH__

#include <QtGui/QtGui>
#include <QtGui/QGraphicsItem>
#include <QtGui/QGraphicsScene>

//! [0]
class CRectItem : public QGraphicsItem
{
public:
    CRectItem(QGraphicsItem *parent = 0, QGraphicsScene *scene = 0);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
protected:
	// dragEnterEvent ����ק����������ק�Ŀؼ�ʱ����
	//void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
	// dragLeaveEvent ����ק(û���ͷ����ʱ)�뿪������ק�Ŀؼ�ʱ����
	//void dragLeaveEvent(QGraphicsSceneDragDropEvent *event);
	// dragMoveEvent ��ק״̬���ڽ�����ק�Ŀؼ����ƶ����ʱ����

	//dropEvent ��ק״̬���ͷ����ʱ����
	//void dropEvent(QGraphicsSceneDragDropEvent *event);
public:
	void setColor(QColor nColorValue);
	void setItemPos( QPointF pointValue );
private:
	qreal  m_nBoundingRectWidthHalf;
	qreal  m_nBoundingRectHeightHalf;
	qreal  m_nBoundingRectWidth;
	qreal  m_nBoundingRectHeight;
	QRectF m_rectDrawInScenePos;
	QRectF m_rectOutSideBoundingInScenePos;

private:
    QColor m_nColor;
	QColor m_nDragColor;
	bool m_bDragOver;
	QGraphicsScene* m_pSceneRef;
};
//! [0]

#endif
