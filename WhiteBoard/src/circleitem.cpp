#include "circleitem.h"
#include <QGraphicsSceneHoverEvent>
#include <QRect>
#include <QCursor>
#include <QPen>
#include <QPainter>
#include <QBrush>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsScene>
#include <QDebug>

CircleItem::CircleItem(QObject *parent) : QObject(parent)
{
    init();
    connect(_boundingRect, SIGNAL(rectChange(QRectF)), this, SLOT(adjustSize(QRectF)));
}

CircleItem::~CircleItem()
{

}

void CircleItem::init()
{
    _boundingRect = new RectItem;
    _handleAreasize = QSizeF(20.0, 20.0);
    this->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable );
    this->setAcceptHoverEvents(true);

}


void CircleItem::setRect(const QRectF &rect)
{
    QGraphicsEllipseItem::setRect(rect);
    setAttribute(_attribute);
}

void CircleItem::setAttribute(Board::Attribute attr)
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

Board::Attribute CircleItem::getAttribute()
{
    return _attribute;
}

void CircleItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
//        qDebug() << "CircleItem INFO: is selected ";
        QRectF rect = this->boundingRect();
        Board::Attribute attr(1, Qt::DashLine, Qt::black);//边界矩形属性
        _boundingRect->setAttribute(attr);
        _boundingRect->setRect(rect);
        _boundingRect->setParentItem(this);
        this->setSelected(true);
        emit selected();
    }
}


void CircleItem::boundingShow()
{
    if(this->isSelected())
    {
        _boundingRect->show();
        _boundingRect->setSelected(true);
    }
    else
    {
        _boundingRect->hide();
    }
}

void CircleItem::adjustSize(QRectF rect)
{
    this->setRect(rect);
}
