#include "rectitem.h"
#include <QGraphicsSceneHoverEvent>
#include <QRect>
#include <QCursor>
#include <QPen>
#include <QPainter>
#include <QBrush>
#include <QStyleOptionGraphicsItem>
#include <qmath.h>
#include <QBitmap>
#include <QDebug>

RectItem::RectItem(int id):
    BaseItem(id)
{

}

RectItem::~RectItem()
{

}

void RectItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
//    qDebug() << "RectItem::paint";
    Q_UNUSED(widget);
    if(_rect.isEmpty())
    {
        return;
    }
    QPen pen;
    pen.setWidth(_attribute._boundingLineWidth);
    pen.setColor(_attribute._boundingColor);
    pen.setStyle(_attribute._boundingLineType);
    painter->setPen(pen);
    painter->setBrush(_attribute._fillColor);
    painter->drawRect(_rect);
    BaseItem::paint(painter, option, widget);
}

