#ifndef RECTITEM_H
#define RECTITEM_H

#include "baseitem.h"

class RectItem : public BaseItem
{
    Q_OBJECT
public:
    explicit RectItem(int id, WhiteBoardClient *client);
    ~RectItem();

private:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
};

#endif // RECTITEM_H
