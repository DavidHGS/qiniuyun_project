#include "graphicsscene.h"
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>
#include <QCursor>
#include <QMetaObject>
#include <QDebug>

GraphicsScene::GraphicsScene()
{
    init();
}

void GraphicsScene::init()
{
}

void GraphicsScene::createItem(Board::GraphicsType type, QPointF itemPos)
{
    if(Board::GraphicsType::_NoneType == type)
    {
        return;
    }
    if(Board::GraphicsType::_Rect == type)
    {
        RectItem *temp = new RectItem;
        _curGraphicsItem = temp;
        this->addItem(_curGraphicsItem);
        _graphicsItems[_curGraphicsItem] = Board::GraphicsType::_Rect;
        _curGraphicsItem->setPos(itemPos);
        connect(temp, SIGNAL(selected()), this, SLOT(itemSelected()));
    }
    if(Board::GraphicsType::_Circle == type)
    {
        CircleItem *temp = new CircleItem;
        _curGraphicsItem = temp;
        _curGraphicsItem->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
        this->addItem(_curGraphicsItem);
        _graphicsItems[_curGraphicsItem] = Board::GraphicsType::_Circle;
        _curGraphicsItem->setPos(itemPos);
        connect(temp, SIGNAL(selected()), this, SLOT(itemSelected()));
    }
}

void GraphicsScene::drawItem(QGraphicsItem *item, Board::GraphicsType type, QPointF mouseCurPos)
{

        if(Board::GraphicsType::_NoneType == type)
        {
            return;
        }
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
        if(Board::GraphicsType::_Rect == type)
        {
            RectItem *rectItem = dynamic_cast<RectItem *>(item);           
            rectItem->setRect(QRectF(topLeft, bottomRight));
            emit rectItem->selected();
        }
        if(Board::GraphicsType::_Circle == type)
        {
            CircleItem *circleItem = dynamic_cast<CircleItem *>(item);
            QRectF itemRect(topLeft, bottomRight);
            itemRect.setHeight(itemRect.width());
            circleItem->setRect(itemRect);
            emit circleItem->selected();
        }
}

void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        _mouseStartPos = event->scenePos();
//        qDebug() << "GraphicsScene INFO: mouse start pos " <<_mouseStartPos;
        if(_mouseAction == Board::MouseAction::_Draw)
        {
            createItem(_curGraphicsType, _mouseStartPos);
        }
        else
        {

            QGraphicsScene::mousePressEvent(event);
        }
    }
}

void GraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{

    if(event->buttons() & Qt::LeftButton)
    {
        QPointF mouseCurPos = event->scenePos();
//        qDebug() << "GraphicsScene INFO: mouse current pos " <<mouseCurPos;
        if(_mouseAction == Board::_Draw)
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

void GraphicsScene::setCurGraphicsType(Board::GraphicsType type)
{
    _curGraphicsType = type;
}

void GraphicsScene::setMouseAction(Board::MouseAction mouseAction)
{
    _mouseAction = mouseAction;  
}

void GraphicsScene::itemSelected()
{
    _curGraphicsItem = dynamic_cast<QGraphicsItem*>(sender());
    _curGraphicsType = _graphicsItems[_curGraphicsItem];
//     qDebug() << "GraphicsScene INFO: itemSelected " << _curGraphicsItem;
    for(auto it : _graphicsItems)
    {
        if(it.first == _curGraphicsItem)
        {
            it.first->setZValue(1);
        }
        else
        {
            it.first->setZValue(0);
            it.first->setSelected(false);
        }
    }
    emit itemSelected(_curGraphicsItem, _curGraphicsType);
//    qDebug() << "GraphicsScene INFO: current ZValue: " << _curGraphicsItem->zValue();
}
