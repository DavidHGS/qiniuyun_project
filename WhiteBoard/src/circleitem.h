#ifndef CIRCLEITEM_H
#define CIRCLEITEM_H

#include "baseitem.h"

class CircleItem : public BaseItem
{
    Q_OBJECT
public:
    explicit CircleItem(int id);
    ~CircleItem();
protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // CIRCLEITEM_H
