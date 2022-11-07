#ifndef CIRCLEITEM_H
#define CIRCLEITEM_H

#include "define.h"
#include "rectitem.h"
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
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
private:
    void init();
signals:
    void selected();
public slots:
    void boundingShow();
    void adjustSize(QRectF rect);
private:
    RectItem *_boundingRect;//边界矩形
    Board::Attribute _attribute;
    QSizeF _handleAreasize;
    std::map<Board::MouseHandlePos, QRectF> _handleArea;
    Board::MouseHandlePos _curHandle;
};

#endif // CIRCLEITEM_H
