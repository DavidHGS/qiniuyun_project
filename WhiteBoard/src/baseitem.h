#ifndef BASEITEM_H
#define BASEITEM_H
#include "define.h"
#include "JsonObject.h"
#include "whiteboardclient.h"
#include <QObject>
#include <QGraphicsItem>
#include <map>

class BaseItem : public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit BaseItem(int id, WhiteBoardClient *client, const QRectF& rect = QRectF(), QGraphicsItem *parent = nullptr);
    ~BaseItem();
    void setRect(const QRectF &rect);//设置绘制图形的边界矩形
    void setAttribute(Board::Attribute attr);//设置要绘制的图形属性
    Board::Attribute getAttribute();//返回图形属性
    Json::JsonObject getItemInfo();
    void sendItemInfo(const char *msg_type, const char *state_type, BaseItem *item);
protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    virtual QRectF boundingRect() const;
private:
    void init();
    void updateHandleArea(QRectF rect);
    Board::MouseHandlePos getHandleArea(QPointF mousePos);
    void adjustRectSize(QPointF mousePos, Board::MouseHandlePos curHandle);
    void rotate(qreal angle);
    void rotateCursor(qreal angle);
signals:
    void selected();
    void rectChange(QRectF rect);

protected:
    Board::Attribute _attribute;
    QSizeF _handleAreasize;
    std::map<Board::MouseHandlePos, QRectF> _handleArea;
    Board::MouseHandlePos _curHandle;
    QRectF _rect;
    qreal _radius;
    qreal _lineLength;
    QPointF _mousePressPos;
    WhiteBoardClient *_client;
    bool _mouseMove;
};

#endif // BASEITEM_H
