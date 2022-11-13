#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include "define.h"
#include "rectitem.h"
#include "circleitem.h"
#include "whiteboardclient.h"
#include <QObject>
#include <QGraphicsScene>
#include <map>

class GraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    GraphicsScene(WhiteBoardClient *client);
    void setCurGraphicsType(Board::GraphicsType type);
    void setMouseAction(Board::MouseAction mouseAction);
    void sendItemInfo(const char* msg_type, const char* state_type, BaseItem *item);
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);  
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
private:
    void init();
    void createItem(Board::GraphicsType type, QPointF itemPos);
    void drawItem(BaseItem *item, Board::GraphicsType type, QPointF mouseCurPos);

signals:
    void updateAttributePanel(Board::Attribute&);
    void itemSelected(QGraphicsItem*, Board::GraphicsType);
private slots:
    void itemSelected();
    void dealServerInfo(const char* info, int len);

private:
    std::map<BaseItem*, Board::GraphicsType> _graphicsItems;
    BaseItem* _curGraphicsItem;
    Board::GraphicsType _curGraphicsType;
    Board::MouseAction _mouseAction;
    QPointF _mouseStartPos;
    int _itemId;
    WhiteBoardClient *_client;
    bool _mouseMove;
};

#endif // GRAPHICSSCENE_H
