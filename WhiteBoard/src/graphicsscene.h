#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include <QObject>
#include <QGraphicsScene>

class GraphicsScene : public QGraphicsScene
{
public:
    enum GraphicsType
    {
        _Hand = -1,
        _Rect,
        _Circle,
        _Text
    };
    enum MouseAction
    {
        _Normal = 0,
        _Draw
    };

    GraphicsScene();
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void setCurGraphicsType(GraphicsType type);
    void setMouseAction(MouseAction mouseAction);
private:
    void createItem(GraphicsType type, QPointF itemPos);
    void drawItem(QGraphicsItem *item, GraphicsType type, QPointF mouseCurPos);

private:
    std::vector<QGraphicsItem*> _graphicsItems;
    GraphicsType _curGraphicsType;
    QGraphicsItem* _curGraphicsItem;
    MouseAction _mouseAction;
    QPointF _mouseStartPos;
};

#endif // GRAPHICSSCENE_H
