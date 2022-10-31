#include "rectitem.h"
#include <QGraphicsSceneHoverEvent>
#include <QRect>
#include <QCursor>
#include <QDebug>

RectItem::RectItem()
{
    _handleAreasize = QSizeF(20.0, 20.0);
    updateHandleArea();
    this->setFlags(QGraphicsItem::ItemIsMovable |
                               QGraphicsItem::ItemIsSelectable );
    this->setAcceptHoverEvents(true);
}

void RectItem::updateHandleArea()
{
//    qDebug() << "RectItem INFO: updateHandleArea ";
    QRectF rect = this->boundingRect();
//    qDebug() << "RectItem INFO: rect size" << rect;
    _handleArea[_TopLeft] = QRectF(QPointF(rect.left() - _handleAreasize.width() / 2, rect.top() - _handleAreasize.height() / 2), _handleAreasize);
    _handleArea[_TopMiddle] = QRectF(QPointF(rect.center().x() - rect.width() / 6, rect.top() - _handleAreasize.height() / 2), QSizeF(rect.width() / 3, _handleAreasize.height()));
    _handleArea[_TopRight] = QRectF(QPointF(rect.right() - _handleAreasize.width() / 2, rect.top() - _handleAreasize.height() / 2), _handleAreasize);
    _handleArea[_LeftMiddle] = QRectF(QPointF(rect.left() - _handleAreasize.width() / 2, rect.center().y() - rect.height() / 6), QSizeF(_handleAreasize.width(), rect.height() / 3));
    _handleArea[_RightMiddle] = QRectF(QPointF(rect.right() - _handleAreasize.width() / 2, rect.center().y() - rect.height() / 6), QSizeF(_handleAreasize.width(), rect.height() / 3));
    _handleArea[_BottomLeft] = QRectF(QPointF(rect.left() - _handleAreasize.width() / 2, rect.bottom() - _handleAreasize.height() / 2), _handleAreasize);
    _handleArea[_BottomMiddle] = QRectF(QPointF(rect.center().x() - rect.width() / 6, rect.bottom() - _handleAreasize.height() / 2), QSizeF(rect.width() / 3, _handleAreasize.height()));
    _handleArea[_BottomRight] = QRectF(QPointF(rect.right() - _handleAreasize.width() / 2, rect.bottom() - _handleAreasize.height() / 2), _handleAreasize);

}

RectItem::MouseHandlePos RectItem::getHandleArea(QPointF mousePos)
{
    if(this->isSelected())
    {
        for(auto it : _handleArea)
        {
            if(it.second.contains(mousePos))
            {
                return it.first;
            }
        }
    }
    return _None;
}

void RectItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    if(this->isSelected())
    {
        QPointF mouseCurPos = event->pos();
        MouseHandlePos mouseHandle = getHandleArea(mouseCurPos);
        _curHandle = mouseHandle;
//        qDebug() << "RectItem INFO: mouseHandle " << mouseHandle;
        if(mouseHandle == _TopMiddle || mouseHandle == _BottomMiddle)
        {
            this->setCursor(Qt::SizeVerCursor);
        }
        else if(mouseHandle == _LeftMiddle || mouseHandle == _RightMiddle)
        {
            this->setCursor(Qt::SizeHorCursor);
        }
        else if(mouseHandle == _TopLeft || mouseHandle == _BottomRight)
        {
            this->setCursor(Qt::SizeFDiagCursor);
        }
        else if(mouseHandle == _TopRight || mouseHandle == _BottomLeft)
        {
            this->setCursor(Qt::SizeBDiagCursor);
        }
        else
        {
            this->setCursor(Qt::SizeAllCursor);
        }
    }
    else
    {
        this->setCursor(Qt::SizeAllCursor);
    }
    QGraphicsRectItem::hoverEnterEvent(event);
}

void RectItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    _curHandle = _None;
    this->setCursor(Qt::ArrowCursor);
    QGraphicsRectItem::hoverLeaveEvent(event);
}

void RectItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
//    qDebug() << "RectItem INFO: current handle " << _curHandle;
    if(event->buttons() & Qt::LeftButton)
    {
        if(_curHandle != _None)
        {
            adjustRectSize(event->pos(), _curHandle);
            return;
        }
    }
    QGraphicsRectItem::mouseMoveEvent(event);
}

void RectItem::setRect(const QRectF &rect)
{
    QGraphicsRectItem::setRect(rect);
    updateHandleArea();
}

void RectItem::adjustRectSize(QPointF mousePos, MouseHandlePos curHandle)
{
    if(curHandle == _None)
    {
        return;
    }
    this->prepareGeometryChange();
    QPointF topLeft = this->rect().topLeft();
    QPointF bottomRight = this->rect().bottomRight();
    if(curHandle == _TopLeft)
    {
        topLeft = mousePos;
    }
    else if(curHandle == _TopMiddle)
    {
        topLeft.setY(mousePos.y());
    }
    else if(curHandle == _LeftMiddle)
    {
        topLeft.setX(mousePos.x());
    }
    else if(curHandle == _TopRight)
    {
        topLeft.setY(mousePos.y());
        bottomRight.setX(mousePos.x());
    }
    else if(curHandle == _RightMiddle)
    {
        bottomRight.setX(mousePos.x());
    }
    else if(curHandle == _BottomRight)
    {
        bottomRight = mousePos;
    }
    else if(curHandle == _BottomMiddle)
    {
        bottomRight.setY(mousePos.y());
    }
    else if(curHandle == _BottomLeft)
    {
        topLeft.setX(mousePos.x());
        bottomRight.setY(mousePos.y());
    }

//     qDebug() << "RectItem INFO: " << topLeft <<", " <<bottomRight;
    setRect(QRectF(topLeft, bottomRight));
}
