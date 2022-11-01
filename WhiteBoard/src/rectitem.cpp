#include "rectitem.h"
#include <QGraphicsSceneHoverEvent>
#include <QRect>
#include <QCursor>
#include <QPen>
#include <QPainter>
#include <QBrush>
#include <QStyleOptionGraphicsItem>
#include <QDebug>

RectItem::RectItem()
{
   init();
}

void RectItem::init()
{
    _handleAreasize = QSizeF(20.0, 20.0);
    updateHandleArea();
    this->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable );
    this->setAcceptHoverEvents(true);
}

void RectItem::updateHandleArea()
{
//    qDebug() << "RectItem INFO: updateHandleArea ";
    QRectF rect = this->boundingRect();
//    qDebug() << "RectItem INFO: rect size" << rect;
    _handleArea[Board::MouseHandlePos::_TopLeft] = QRectF(QPointF(rect.left() - _handleAreasize.width() / 2, rect.top() - _handleAreasize.height() / 2), _handleAreasize);
    _handleArea[Board::MouseHandlePos::_TopMiddle] = QRectF(QPointF(rect.center().x() - rect.width() / 6, rect.top() - _handleAreasize.height() / 2), QSizeF(rect.width() / 3, _handleAreasize.height()));
    _handleArea[Board::MouseHandlePos::_TopRight] = QRectF(QPointF(rect.right() - _handleAreasize.width() / 2, rect.top() - _handleAreasize.height() / 2), _handleAreasize);
    _handleArea[Board::MouseHandlePos::_LeftMiddle] = QRectF(QPointF(rect.left() - _handleAreasize.width() / 2, rect.center().y() - rect.height() / 6), QSizeF(_handleAreasize.width(), rect.height() / 3));
    _handleArea[Board::MouseHandlePos::_RightMiddle] = QRectF(QPointF(rect.right() - _handleAreasize.width() / 2, rect.center().y() - rect.height() / 6), QSizeF(_handleAreasize.width(), rect.height() / 3));
    _handleArea[Board::MouseHandlePos::_BottomLeft] = QRectF(QPointF(rect.left() - _handleAreasize.width() / 2, rect.bottom() - _handleAreasize.height() / 2), _handleAreasize);
    _handleArea[Board::MouseHandlePos::_BottomMiddle] = QRectF(QPointF(rect.center().x() - rect.width() / 6, rect.bottom() - _handleAreasize.height() / 2), QSizeF(rect.width() / 3, _handleAreasize.height()));
    _handleArea[Board::MouseHandlePos::_BottomRight] = QRectF(QPointF(rect.right() - _handleAreasize.width() / 2, rect.bottom() - _handleAreasize.height() / 2), _handleAreasize);

}

Board::MouseHandlePos RectItem::getHandleArea(QPointF mousePos)
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
    return Board::MouseHandlePos::_NoneHandle;
}

void RectItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    if(this->isSelected())
    {
        QPointF mouseCurPos = event->pos();
        Board::MouseHandlePos mouseHandle = getHandleArea(mouseCurPos);
        _curHandle = mouseHandle;
//        qDebug() << "RectItem INFO: mouseHandle " << mouseHandle;
        if(mouseHandle == Board::MouseHandlePos::_TopMiddle || mouseHandle == Board::MouseHandlePos::_BottomMiddle)
        {
            this->setCursor(Qt::SizeVerCursor);
        }
        else if(mouseHandle == Board::MouseHandlePos::_LeftMiddle || mouseHandle == Board::MouseHandlePos::_RightMiddle)
        {
            this->setCursor(Qt::SizeHorCursor);
        }
        else if(mouseHandle == Board::MouseHandlePos::_TopLeft || mouseHandle == Board::MouseHandlePos::_BottomRight)
        {
            this->setCursor(Qt::SizeFDiagCursor);
        }
        else if(mouseHandle == Board::MouseHandlePos::_TopRight || mouseHandle == Board::MouseHandlePos::_BottomLeft)
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
    _curHandle = Board::MouseHandlePos::_NoneHandle;
    this->setCursor(Qt::ArrowCursor);
    QGraphicsRectItem::hoverLeaveEvent(event);
}

void RectItem::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    QPointF mouseCurPos = event->pos();
    Board::MouseHandlePos mouseHandle = getHandleArea(mouseCurPos);
    _curHandle = mouseHandle;
//    qDebug() << "RectItem INFO: current handle " << _curHandle;
    if(mouseHandle == Board::MouseHandlePos::_TopMiddle || mouseHandle == Board::MouseHandlePos::_BottomMiddle)
    {
        this->setCursor(Qt::SizeVerCursor);
    }
    else if(mouseHandle == Board::MouseHandlePos::_LeftMiddle || mouseHandle == Board::MouseHandlePos::_RightMiddle)
    {
        this->setCursor(Qt::SizeHorCursor);
    }
    else if(mouseHandle == Board::MouseHandlePos::_TopLeft || mouseHandle == Board::MouseHandlePos::_BottomRight)
    {
        this->setCursor(Qt::SizeFDiagCursor);
    }
    else if(mouseHandle == Board::MouseHandlePos::_TopRight || mouseHandle == Board::MouseHandlePos::_BottomLeft)
    {
        this->setCursor(Qt::SizeBDiagCursor);
    }
    else
    {
        this->setCursor(Qt::SizeAllCursor);
    }
}

void RectItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
//    qDebug() << "RectItem INFO: current handle " << _curHandle;
    if(event->buttons() & Qt::LeftButton)
    {
        if(_curHandle != Board::MouseHandlePos::_NoneHandle)
        {
            adjustRectSize(event->pos(), _curHandle);
            return;
        }
    }
    if(this->isSelected())
    {
        QGraphicsRectItem::mouseMoveEvent(event);
    }
}

void RectItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
//        qDebug() << "RectItem INFO: is selected ";
        emit selected();
    }
}

void RectItem::setRect(const QRectF &rect)
{
    QGraphicsRectItem::setRect(rect);
    setAttribute(_attribute);
    updateHandleArea();
}

void RectItem::adjustRectSize(QPointF mousePos, Board::MouseHandlePos curHandle)
{
    if(curHandle == Board::MouseHandlePos::_NoneHandle)
    {
        return;
    }
    this->prepareGeometryChange();
    QPointF topLeft = this->rect().topLeft();
    QPointF bottomRight = this->rect().bottomRight();
    if(curHandle == Board::MouseHandlePos::_TopLeft)
    {
        topLeft = mousePos;
    }
    else if(curHandle == Board::MouseHandlePos::_TopMiddle)
    {
        topLeft.setY(mousePos.y());
    }
    else if(curHandle == Board::MouseHandlePos::_LeftMiddle)
    {
        topLeft.setX(mousePos.x());
    }
    else if(curHandle == Board::MouseHandlePos::_TopRight)
    {
        topLeft.setY(mousePos.y());
        bottomRight.setX(mousePos.x());
    }
    else if(curHandle == Board::MouseHandlePos::_RightMiddle)
    {
        bottomRight.setX(mousePos.x());
    }
    else if(curHandle == Board::MouseHandlePos::_BottomRight)
    {
        bottomRight = mousePos;
    }
    else if(curHandle == Board::MouseHandlePos::_BottomMiddle)
    {
        bottomRight.setY(mousePos.y());
    }
    else if(curHandle == Board::MouseHandlePos::_BottomLeft)
    {
        topLeft.setX(mousePos.x());
        bottomRight.setY(mousePos.y());
    }

//     qDebug() << "RectItem INFO: " << topLeft <<", " <<bottomRight;
    if(topLeft.x() < bottomRight.x() && topLeft.y() < bottomRight.y())
    {
        setRect(QRectF(topLeft, bottomRight));
    }
}

void RectItem::setAttribute(Board::Attribute attr)
{
    _attribute._boundingColor = attr._boundingColor;
    _attribute._boundingLineType = attr._boundingLineType;
    _attribute._boundingLineWidth = attr._boundingLineWidth;
    _attribute._fillColor = attr._fillColor;
    QPen pen = this->pen();
    pen.setWidth(_attribute._boundingLineWidth);
    pen.setColor(_attribute._boundingColor);
    pen.setStyle(_attribute._boundingLineType);
    this->setPen(pen);
    QBrush brush(_attribute._fillColor);
    this->setBrush(brush);
    this->update();
}

Board::Attribute RectItem::getAttribute()
{
    return _attribute;
}
