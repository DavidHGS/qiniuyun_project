#include "graphicsscene.h"
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>
#include <QDebug>

GraphicsScene::GraphicsScene()
{
}

void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        _mouseStartPos = event->scenePos();
        qDebug() << "GraphicsScene INFO: mouse start pos " <<_mouseStartPos;
        switch(_curGraphicsType)
        {
            case _Hand:
                QGraphicsScene::mousePressEvent(event);
                break;
            case _Rect:
            {
                _curGraphicsItem = new QGraphicsRectItem();
                _curGraphicsItem->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
                this->addItem(_curGraphicsItem);
                _graphicsItems.push_back(_curGraphicsItem);
                _curGraphicsItem->setPos(_mouseStartPos);
                break;
            }
            case _Circle:
            {
                _curGraphicsItem = new QGraphicsEllipseItem();
                _curGraphicsItem->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
                this->addItem(_curGraphicsItem);
                _graphicsItems.push_back(_curGraphicsItem);
                _curGraphicsItem->setPos(_mouseStartPos);
                break;
            }
            default:
                break;
        }
    }
}

void GraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton)
    {
        QPointF mouseCurPos = event->scenePos();
        qDebug() << "GraphicsScene INFO: mouse current pos " <<mouseCurPos;
        switch (_curGraphicsType)
        {
            case _Hand:
                QGraphicsScene::mouseMoveEvent(event);
                break;
            case _Rect:
            {
                QGraphicsRectItem *rectItem = dynamic_cast<QGraphicsRectItem *>(_curGraphicsItem);
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
                break;
            }
            case _Circle:
            {
                QGraphicsEllipseItem *circleItem = dynamic_cast<QGraphicsEllipseItem *>(_curGraphicsItem);
                circleItem->setRect(circleItem->rect().x(), circleItem->rect().y(),
                                    mouseCurPos.x() -  _mouseStartPos.x(), mouseCurPos.x() -  _mouseStartPos.x());
                break;
            }
            default:
                break;
            }
    }
}

void GraphicsScene::setCurGraphicsType(GraphicsType type)
{
    _curGraphicsType = type;
}
