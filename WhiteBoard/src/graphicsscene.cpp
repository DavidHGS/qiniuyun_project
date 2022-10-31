#include "graphicsscene.h"
#include "rectitem.h"
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>
#include <QCursor>
#include <QDebug>

GraphicsScene::GraphicsScene()
{
}

void GraphicsScene::createItem(GraphicsType type, QPointF itemPos)
{
    if(_Hand == type)
    {
        return;
    }
    if(_Rect == type)
    {
        _curGraphicsItem = new RectItem();
        this->addItem(_curGraphicsItem);
        _graphicsItems.push_back(_curGraphicsItem);
        _curGraphicsItem->setPos(itemPos);
    }
    if(_Circle == type)
    {
        _curGraphicsItem = new QGraphicsEllipseItem();
        _curGraphicsItem->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
        this->addItem(_curGraphicsItem);
        _graphicsItems.push_back(_curGraphicsItem);
        _curGraphicsItem->setPos(itemPos);
    }
}

void GraphicsScene::drawItem(QGraphicsItem *item, GraphicsType type, QPointF mouseCurPos)
{

        if(_Hand == type)
        {
            return;
        }
        if(_Rect == type)
        {
            RectItem *rectItem = dynamic_cast<RectItem *>(item);
            QPointF topLeft(0, 0);
            QPointF bottomRight(0, 0);
            if(mouseCurPos.x() < _mouseStartPos.x() && mouseCurPos.y() < _mouseStartPos.y())
            {
                topLeft = mouseCurPos - _mouseStartPos;
            }
            else if(mouseCurPos.x() < _mouseStartPos.x() && mouseCurPos.y() > _mouseStartPos.y())
            {
                topLeft = QPointF(mouseCurPos.x() - _mouseStartPos.x(), 0);
                bottomRight = QPointF(0, mouseCurPos.y() - _mouseStartPos.y());
            }
            else if(mouseCurPos.x() > _mouseStartPos.x() && mouseCurPos.y() < _mouseStartPos.y())
            {
                topLeft = QPointF(0, mouseCurPos.y() - _mouseStartPos.y());
                bottomRight = QPointF(mouseCurPos.x() - _mouseStartPos.x(), 0);
            }
            else if(mouseCurPos.x() > _mouseStartPos.x() && mouseCurPos.y() > _mouseStartPos.y())
            {
                bottomRight = mouseCurPos - _mouseStartPos;
            }
            rectItem->setRect(QRectF(topLeft, bottomRight));
        }
        if(_Circle == type)
        {
            QGraphicsEllipseItem *circleItem = dynamic_cast<QGraphicsEllipseItem *>(item);
            circleItem->setRect(circleItem->rect().x(), circleItem->rect().y(),
                                mouseCurPos.x() -  _mouseStartPos.x(), mouseCurPos.x() -  _mouseStartPos.x());
        }
}

void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        _mouseStartPos = event->scenePos();
//        qDebug() << "GraphicsScene INFO: mouse start pos " <<_mouseStartPos;
        if(_mouseAction == _Draw)
        {
            createItem(_curGraphicsType, _mouseStartPos);
        }
        else
        {
            QGraphicsScene::mousePressEvent(event);
        }
    }
//    QGraphicsScene::mousePressEvent(event);
}

void GraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton)
    {
        QPointF mouseCurPos = event->scenePos();
//        qDebug() << "GraphicsScene INFO: mouse current pos " <<mouseCurPos;
        if(_mouseAction == _Draw)
        {
            drawItem(_curGraphicsItem, _curGraphicsType, mouseCurPos);
        }
        else
        {
            QGraphicsScene::mouseMoveEvent(event);
        }
    }
    QGraphicsScene::mouseMoveEvent(event);
}


void GraphicsScene::setCurGraphicsType(GraphicsType type)
{
    _curGraphicsType = type;
}

void GraphicsScene::setMouseAction(MouseAction mouseAction)
{
    _mouseAction = mouseAction;
}
