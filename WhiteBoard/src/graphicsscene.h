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
        _Rect = 0,
        _Circle,
        _Text
    };
    GraphicsScene();
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void setCurGraphicsType(GraphicsType type);

private:
    std::vector<QGraphicsItem*> _graphicsItems;
    GraphicsType _curGraphicsType;
    QGraphicsItem* _curGraphicsItem;
    QPointF _mouseStartPos;
};

#endif // GRAPHICSSCENE_H
