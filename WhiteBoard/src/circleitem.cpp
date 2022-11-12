#include "circleitem.h"
#include <QPainter>

CircleItem::CircleItem(int id) : BaseItem(id)
{

}

CircleItem::~CircleItem()
{

}

void CircleItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
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
    painter->drawEllipse(_rect);
    BaseItem::paint(painter, option, widget);
}

