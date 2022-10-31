#ifndef RECTITEM_H
#define RECTITEM_H

#include <QObject>
#include <QGraphicsItem>
#include <map>

class RectItem : public QGraphicsRectItem
{
    enum MouseHandlePos
    {
        _None = -1,
        _TopLeft,
        _TopMiddle,
        _TopRight,
        _LeftMiddle,
        _RightMiddle,
        _BottomLeft,
        _BottomMiddle,
        _BottomRight
    };
public:
    RectItem();
    void setRect(const QRectF &rect);
protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
private:
    void updateHandleArea();
    MouseHandlePos getHandleArea(QPointF mousePos);
    void adjustRectSize(QPointF mousePos, MouseHandlePos curHandle);

private:
    QSizeF _handleAreasize;
    std::map<MouseHandlePos, QRectF> _handleArea;
    MouseHandlePos _curHandle;
};

#endif // RECTITEM_H
