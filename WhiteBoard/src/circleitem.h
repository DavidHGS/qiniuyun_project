#ifndef CIRCLEITEM_H
#define CIRCLEITEM_H

#include "define.h"
#include <QObject>
#include <QGraphicsItem>
#include <map>

class CircleItem : public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
public:
    explicit CircleItem(QObject *parent = nullptr);
    ~CircleItem();
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
signals:
    void selected();
private:
    Board::Attribute _attribute;
    QSizeF _handleAreasize;
    std::map<Board::MouseHandlePos, QRectF> _handleArea;
    Board::MouseHandlePos _curHandle;
};

#endif // CIRCLEITEM_H
