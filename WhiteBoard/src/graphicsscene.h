#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include "define.h"
#include "rectitem.h"
#include "circleitem.h"
#include <QObject>
#include <QGraphicsScene>

class GraphicsScene : public QGraphicsScene
{
    Q_OBJECT

signals:
    void updateAttributePanel(Board::Attribute&);
    void itemSelected(QGraphicsItem*, Board::GraphicsType);
private slots:
    void itemSelected();
public:
    GraphicsScene();
    void setCurGraphicsType(Board::GraphicsType type);
    void setMouseAction(Board::MouseAction mouseAction);
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);  
private:
    void init();
    void createItem(Board::GraphicsType type, QPointF itemPos);
    void drawItem(QGraphicsItem *item, Board::GraphicsType type, QPointF mouseCurPos);

private:
    std::map<QGraphicsItem*, Board::GraphicsType> _graphicsItems;
    QGraphicsItem* _curGraphicsItem;
    Board::GraphicsType _curGraphicsType;
    Board::MouseAction _mouseAction;
    QPointF _mouseStartPos;
};

#endif // GRAPHICSSCENE_H
