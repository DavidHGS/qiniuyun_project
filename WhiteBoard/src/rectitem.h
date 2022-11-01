#ifndef RECTITEM_H
#define RECTITEM_H
#include "define.h"
#include <QObject>
#include <QGraphicsItem>
#include <map>

class RectItem : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
signals:
    void selected();
public:
    explicit RectItem();
    void setRect(const QRectF &rect);//绘制矩形
    void setAttribute(Board::Attribute attr);//设置图形属性
    Board::Attribute getAttribute();//返回图形属性
protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
private:
    void init();
    void updateHandleArea();
    Board::MouseHandlePos getHandleArea(QPointF mousePos);
    void adjustRectSize(QPointF mousePos, Board::MouseHandlePos curHandle);

private:
    Board::Attribute _attribute;
    QSizeF _handleAreasize;
    std::map<Board::MouseHandlePos, QRectF> _handleArea;
    Board::MouseHandlePos _curHandle;
};

#endif // RECTITEM_H
