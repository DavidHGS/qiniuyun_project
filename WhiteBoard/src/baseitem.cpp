#include "baseitem.h"
#include <QGraphicsSceneHoverEvent>
#include <QRect>
#include <QCursor>
#include <QPen>
#include <QPainter>
#include <QBrush>
#include <QStyleOptionGraphicsItem>
#include <qmath.h>
#include <QDebug>

BaseItem::BaseItem(int id, const QRectF &rect, QGraphicsItem *parent): QGraphicsItem(parent), _rect(rect)
{
    _attribute._itemId = id;
   init();
}

BaseItem::~BaseItem()
{

}

void BaseItem::setRect(const QRectF &rect)
{
//    qDebug() <<"BaseItem INFO: draw rect " << rect;
    _rect = rect;
    setAttribute(_attribute);
    updateHandleArea(rect);
    this->update();
}

void BaseItem::setAttribute(Board::Attribute attr)
{
    _attribute._boundingColor = attr._boundingColor;
    _attribute._boundingLineType = attr._boundingLineType;
    _attribute._boundingLineWidth = attr._boundingLineWidth;
    _attribute._fillColor = attr._fillColor;
    this->update();
}

Board::Attribute BaseItem::getAttribute()
{
    return _attribute;
}

void BaseItem::init()
{
    _handleAreasize = QSizeF(20.0, 20.0);
    _lineLength = 30;
    _radius = 15;
    this->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable );
    this->setAcceptHoverEvents(true);
}

void BaseItem::updateHandleArea(QRectF rect)
{
    _handleArea[Board::MouseHandlePos::_TopLeft] = QRectF(QPointF(rect.left() - _handleAreasize.width() / 2, rect.top() - _handleAreasize.height() / 2), _handleAreasize);
    _handleArea[Board::MouseHandlePos::_TopMiddle] = QRectF(QPointF(rect.center().x() - rect.width() / 6, rect.top() - _handleAreasize.height() / 2), QSizeF(rect.width() / 3, _handleAreasize.height()));
    _handleArea[Board::MouseHandlePos::_TopRight] = QRectF(QPointF(rect.right() - _handleAreasize.width() / 2, rect.top() - _handleAreasize.height() / 2), _handleAreasize);
    _handleArea[Board::MouseHandlePos::_LeftMiddle] = QRectF(QPointF(rect.left() - _handleAreasize.width() / 2, rect.center().y() - rect.height() / 6), QSizeF(_handleAreasize.width(), rect.height() / 3));
    _handleArea[Board::MouseHandlePos::_RightMiddle] = QRectF(QPointF(rect.right() - _handleAreasize.width() / 2, rect.center().y() - rect.height() / 6), QSizeF(_handleAreasize.width(), rect.height() / 3));
    _handleArea[Board::MouseHandlePos::_BottomLeft] = QRectF(QPointF(rect.left() - _handleAreasize.width() / 2, rect.bottom() - _handleAreasize.height() / 2), _handleAreasize);
    _handleArea[Board::MouseHandlePos::_BottomMiddle] = QRectF(QPointF(rect.center().x() - rect.width() / 6, rect.bottom() - _handleAreasize.height() / 2), QSizeF(rect.width() / 3, _handleAreasize.height()));
    _handleArea[Board::MouseHandlePos::_BottomRight] = QRectF(QPointF(rect.right() - _handleAreasize.width() / 2, rect.bottom() - _handleAreasize.height() / 2), _handleAreasize);
    _handleArea[Board::MouseHandlePos::_Rotate] = QRectF(QPointF(rect.center().x()- _radius, rect.top() - _lineLength - 2 * _radius), QSize(2 * _radius, 2 * _radius));
}

Board::MouseHandlePos BaseItem::getHandleArea(QPointF mousePos)
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

void BaseItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    if(this->isSelected())
    {
        QPointF mouseCurPos = event->pos();
        Board::MouseHandlePos mouseHandle = getHandleArea(mouseCurPos);
        _curHandle = mouseHandle;
//        qDebug() << "BaseItem INFO: mouseHandle " << mouseHandle;
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
        else if(mouseHandle == Board::MouseHandlePos::_Rotate)
        {
            QPixmap mMap(":/source/rotate.png");
            QSize msize(40, 40);
            QPixmap mScaleMap = mMap.scaled(msize, Qt::KeepAspectRatio);
            QCursor mCursor(mScaleMap);
            this->setCursor(mCursor);
        }
        else
        {
            this->setCursor(Qt::SizeAllCursor);
        }
    }
    else
    {
        this->setCursor(Qt::ArrowCursor);
    }
}

void BaseItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    _curHandle = Board::MouseHandlePos::_NoneHandle;
    this->setCursor(Qt::ArrowCursor);
    QGraphicsItem::hoverLeaveEvent(event);
}

void BaseItem::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    if(this->isSelected())
    {
        QPointF mouseCurPos = event->pos();
        Board::MouseHandlePos mouseHandle = getHandleArea(mouseCurPos);
        _curHandle = mouseHandle;
        //    qDebug() << "BaseItem INFO: current handle " << _curHandle;
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
        else if(mouseHandle == Board::MouseHandlePos::_Rotate)
        {
            QPixmap mMap(":/source/rotate.png");
            QSize msize(40, 40);
            QPixmap mScaleMap = mMap.scaled(msize, Qt::KeepAspectRatio);

            QCursor mCursor(mScaleMap);
            this->setCursor(mCursor);
        }
        else
        {
            this->setCursor(Qt::SizeAllCursor);
        }
    }
}

void BaseItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
//    qDebug() << "BaseItem INFO: current handle " << _curHandle;
    if(event->buttons() & Qt::LeftButton)
    {
        this->setSelected(true);
        emit selected();
        if(_curHandle != Board::MouseHandlePos::_NoneHandle)
        {
            if(_curHandle != Board::MouseHandlePos::_Rotate)
            {
                adjustRectSize(event->pos(), _curHandle);
            }
            if(_curHandle == Board::MouseHandlePos::_Rotate)
            {
                QPointF rotateCenter = _rect.center();
                this->setTransformOriginPoint(rotateCenter);
                QLineF l1 = QLineF(rotateCenter, _mousePressPos);
                QLineF l2 = QLineF(rotateCenter, event->pos());
                qreal angle = l2.angleTo(l1);
                rotate(angle);
            }
            return;
        }
    }
    if(this->isSelected())
    {
        QGraphicsItem::mouseMoveEvent(event);
    }
}

void BaseItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
//        qDebug() << "BaseItem INFO: is selected ";
        this->setSelected(true);
        emit selected();
    }
    if(this->isSelected())
    {
        if(_curHandle == Board::MouseHandlePos::_Rotate)
        {
            _mousePressPos = event->pos();
        }
    }
}

void BaseItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        if(_curHandle != Board::MouseHandlePos::_NoneHandle)
        {
            auto rr = _rect;
            auto angle = qDegreesToRadians(this->rotation());

            auto p1 = rr.center();
            auto origin = this->transformOriginPoint();
            QPointF p2 = QPointF(0, 0);

            p2.setX(origin.x() + qCos(angle)*(p1.x() - origin.x()) - qSin(angle)*(p1.y() - origin.y()));
            p2.setY(origin.y() + qSin(angle)*(p1.x() - origin.x()) + qCos(angle)*(p1.y() - origin.y()));

            auto diff = p1 - p2;

            this->setRect(rr.adjusted(-diff.x(), -diff.y(), -diff.x(), -diff.y()));
            this->setTransformOriginPoint(_rect.center());

            this->update();
            this->setSelected(true);
        }
    }

    return QGraphicsItem::mouseReleaseEvent(event);
}



void BaseItem::adjustRectSize(QPointF mousePos, Board::MouseHandlePos curHandle)
{
    if(curHandle == Board::MouseHandlePos::_NoneHandle)
    {
        return;
    }
    this->prepareGeometryChange();
    QPointF topLeft = _rect.topLeft();
    QPointF bottomRight = _rect.bottomRight();
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
    if(topLeft.x() < bottomRight.x() && topLeft.y() < bottomRight.y())
    {
        setRect(QRectF(topLeft, bottomRight));
    }
}





void BaseItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
//    qDebug() << "BaseItem::paint";
    Q_UNUSED(widget);
    if(_rect.isEmpty())
    {
        return;
    }

    if(option->state & QStyle::State_Selected)
    {
        QRectF rect = _rect;
        painter->setPen(QPen(option->palette.windowText(), 0, Qt::DashLine));
        painter->setBrush(Qt::NoBrush);
        const qreal pad = painter->pen().widthF() / 2 + _attribute._boundingLineWidth;
        painter->drawRect(rect.adjusted(-pad, -pad, pad, pad));
        painter->drawLine(rect.center().x(), rect.top(), rect.center().x(), rect.top() - _lineLength);
        painter->drawEllipse(rect.center().x() - _radius, rect.top() - _lineLength - 2 *_radius,
                             2 * _radius, 2 * _radius);
    }
}

QRectF BaseItem::boundingRect() const
{
    const qreal pad = _attribute._boundingLineWidth + 1;
    return QRectF(_rect.x() - pad, _rect.y() - pad - _lineLength - 2 * _radius,
                  _rect.width() + 2 * pad, _rect.height() + 2 * pad + _lineLength + 2 * _radius);
}

void BaseItem::rotate(qreal angle)
{
    qreal rotateAngle = this->rotation() + angle;
    if(rotateAngle > 360.0)
    {
        rotateAngle -= 360.0;
    }
    this->setRotation(rotateAngle);
    this->update();
}

void BaseItem::rotateCursor(qreal angle)
{
    if(_curHandle != Board::MouseHandlePos::_NoneHandle && _curHandle != Board::MouseHandlePos::_Rotate)
    {
        QMatrix matrix;
        matrix.rotate(angle);;
//        this->setCursor(this->cursor().bitmap()->transformed(matrix));
    }
}

Json::JsonObject BaseItem::getItemInfo()
{
    Json::JsonObject infoJson;
    infoJson["\"pos\""] = QString("[%1,%2]").arg(_rect.x()).arg(_rect.y()).toStdString();
    infoJson["\"width\""] = QString("%1").arg(_rect.width()).toStdString();
    infoJson["\"height\""] = QString("%1").arg(_rect.height()).toStdString();
    infoJson["\"angle\""] = QString("%1").arg(this->rotation()).toStdString();
    infoJson["\"attribute\""] = QString("{\"id\":%1,\"lineWidth\":%2,\"lineWidth\":%3,\"lineColor\":[%4,%5,%6,%7],\"fillColor\":[%8,%9,%10,%11]}")\
                                .arg(_attribute._itemId).arg(_attribute._boundingLineWidth).arg(_attribute._boundingLineType)\
                                .arg(_attribute._boundingColor.redF()).arg(_attribute._boundingColor.greenF()).arg(_attribute._boundingColor.blueF()).arg(_attribute._boundingColor.alphaF())\
                                .arg(_attribute._fillColor.red()).arg(_attribute._fillColor.greenF()).arg(_attribute._fillColor.blueF()).arg(_attribute._fillColor.alphaF()).toStdString();

    return infoJson;
}
