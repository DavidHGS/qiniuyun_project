#include "graphicsscene.h"
#include "JsonObject.h"
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>
#include <QCursor>
#include <QMetaObject>
#include <QDebug>
#include <iostream>
#include <string>
GraphicsScene::GraphicsScene(WhiteBoardClient *client):
    _client(client)
{
    init();
}

void GraphicsScene::init()
{
    _itemId = -1;
    _curGraphicsItem = nullptr;
    _mouseMove = false;
    connect(_client, SIGNAL(readData(const char*,int)), this, SLOT(dealServerInfo(const char*,int)));
}

void GraphicsScene::createItem(Board::GraphicsType type, QPointF itemPos)
{
    qDebug() << "itemPos: " << itemPos;
    if(Board::GraphicsType::_NoneType == type)
    {
        return;
    }
    if(Board::GraphicsType::_Rect == type)
    {
        ++_itemId;
        RectItem *temp = new RectItem(_itemId, _client);
        _curGraphicsItem = temp;
        this->addItem(_curGraphicsItem);
        _graphicsItems[_curGraphicsItem] = Board::GraphicsType::_Rect;
        _curGraphicsItem->setPos(itemPos);
        connect(temp, SIGNAL(selected()), this, SLOT(itemSelected()));
    }
    if(Board::GraphicsType::_Circle == type)
    {
        ++_itemId;
        CircleItem *temp = new CircleItem(_itemId, _client);
        _curGraphicsItem = temp;
        _curGraphicsItem->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);
        this->addItem(_curGraphicsItem);
        _graphicsItems[_curGraphicsItem] = Board::GraphicsType::_Circle;
        _curGraphicsItem->setPos(itemPos);
        connect(temp, SIGNAL(selected()), this, SLOT(itemSelected()));
    }
}

void GraphicsScene::drawItem(BaseItem *item, Board::GraphicsType type, QPointF mouseCurPos)
{
    if(Board::GraphicsType::_NoneType == type)
    {
        return;
    }
    QPointF topLeft(0, 0);
    QPointF bottomRight(0, 0);
    if(mouseCurPos.x() < _mouseStartPos.x() && mouseCurPos.y() < _mouseStartPos.y())
    {
        topLeft = mouseCurPos - _mouseStartPos;
    }
    else if(mouseCurPos.x() < _mouseStartPos.x() && mouseCurPos.y() > _mouseStartPos.y())
    {
        topLeft = QPointF(mouseCurPos.x() - _mouseStartPos.x(), 0);
        bottomRight = QPointF(0, mouseCurPos.y() - _mouseStartPos.y());
    }
    else if(mouseCurPos.x() > _mouseStartPos.x() && mouseCurPos.y() < _mouseStartPos.y())
    {
        topLeft = QPointF(0, mouseCurPos.y() - _mouseStartPos.y());
        bottomRight = QPointF(mouseCurPos.x() - _mouseStartPos.x(), 0);
    }
    else if(mouseCurPos.x() > _mouseStartPos.x() && mouseCurPos.y() > _mouseStartPos.y())
    {
        bottomRight = mouseCurPos - _mouseStartPos;
    }
    if(Board::GraphicsType::_Rect == type)
    {
        RectItem *rectItem = dynamic_cast<RectItem *>(item);
        rectItem->setRect(QRectF(topLeft, bottomRight));
        emit rectItem->selected();
    }
    if(Board::GraphicsType::_Circle == type)
    {
        CircleItem *circleItem = dynamic_cast<CircleItem *>(item);
        QRectF itemRect(topLeft, bottomRight);
        itemRect.setHeight(itemRect.width());
        circleItem->setRect(itemRect);
        emit circleItem->selected();
    }
}

void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        _mouseStartPos = event->scenePos();
//        qDebug() << "GraphicsScene INFO: mouse start pos " <<_mouseStartPos;
        if(_mouseAction == Board::MouseAction::_Draw)
        {
            createItem(_curGraphicsType, _mouseStartPos);
            Json::JsonObject msgJson;
            msgJson["\"msg_type\""] = MSG_ITEM_STATE;
            msgJson["\"itemType\""] = std::to_string(_curGraphicsType);
            Json::JsonObject itemInfoJson;
            itemInfoJson = _curGraphicsItem->getItemInfo();
            itemInfoJson["\"pos\""] = QString("[%1,%2]").arg(_mouseStartPos.x()).arg(_mouseStartPos.y()).toStdString();
            itemInfoJson["\"state_type\""] = ITEM_BEGIN;
            msgJson["\"state\""] = itemInfoJson.toStr();
            msgJson["\"item\""] = std::to_string(_curGraphicsItem->getAttribute()._itemId);
            _client->sendData(msgJson.toStr().c_str(), strlen(msgJson.toStr().c_str()));

        }
        else
        {
            QGraphicsScene::mousePressEvent(event);
        }
    }
}

void GraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{

    if(event->buttons() & Qt::LeftButton)
    {
        QPointF mouseCurPos = event->scenePos();
//        qDebug() << "GraphicsScene INFO: mouse current pos " <<mouseCurPos;
        if(_mouseAction == Board::_Draw)
        {
            drawItem(_curGraphicsItem, _curGraphicsType, mouseCurPos);
            _mouseMove = true;
            sendItemInfo(MSG_ITEM_STATE, ITEM_MIDDLE, _curGraphicsItem);
        }
        else
        {
            QGraphicsScene::mouseMoveEvent(event);
        }
    }
    QGraphicsScene::mouseMoveEvent(event);
}

void GraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if(_mouseAction == Board::_Draw)
    {
        if(_mouseMove == true)
        {
            sendItemInfo(MSG_ITEM_STATE, ITEM_END, _curGraphicsItem);
            _mouseMove = false;
        }
    }
    QGraphicsScene::mouseReleaseEvent(event);
}

void GraphicsScene::setCurGraphicsType(Board::GraphicsType type)
{
    _curGraphicsType = type;
}

void GraphicsScene::setMouseAction(Board::MouseAction mouseAction)
{
    _mouseAction = mouseAction;  
}

void GraphicsScene::itemSelected()
{
    _curGraphicsItem = dynamic_cast<BaseItem*>(sender());
    _curGraphicsType = _graphicsItems[_curGraphicsItem];
//     qDebug() << "GraphicsScene INFO: itemSelected " << _curGraphicsItem;
    for(auto it : _graphicsItems)
    {
        if(it.first == _curGraphicsItem)
        {
            it.first->setZValue(1);
        }
        else
        {
            it.first->setZValue(0);
            it.first->setSelected(false);
        }
    }
    emit itemSelected(_curGraphicsItem, _curGraphicsType);
//    qDebug() << "GraphicsScene INFO: current ZValue: " << _curGraphicsItem->zValue();
}

void GraphicsScene::sendItemInfo(const char *msg_type, const char *state_type, BaseItem *item)
{
    Json::JsonObject msgJson;
    msgJson["\"msg_type\""] = msg_type;
    msgJson["\"itemType\""] = std::to_string(_graphicsItems[item]);
    Json::JsonObject itemInfoJson;
    itemInfoJson = item->getItemInfo();
    itemInfoJson["\"state_type\""] = state_type;
    msgJson["\"state\""] = itemInfoJson.toStr();
    msgJson["\"item\""] = std::to_string(_curGraphicsItem->getAttribute()._itemId);
    _client->sendData(msgJson.toStr().c_str(), strlen(msgJson.toStr().c_str()));
    qDebug() << QString(msgJson.toStr().c_str());
}

void GraphicsScene::dealServerInfo(const char *info, int len)
{
    qDebug() << info;
    Json::JsonObject infoJson = Json::toJsonObject(info);
    if(infoJson["\"msg_type\""] == MSG_ITEM_STATE)
    {
        std::string id = infoJson["\"item\""];
        auto it = _graphicsItems.begin();
        //item已经存在，修改属性
        for(it = _graphicsItems.begin(); it != _graphicsItems.end(); ++it)
        {
            BaseItem *item = it->first;
            Board::Attribute attr = item->getAttribute();
            if(std::to_string(attr._itemId) == id)
            {
                Json::JsonObject stateJson = Json::toJsonObject(infoJson["\"state\""].c_str());
                std::vector<double> pos;
                stateJson.strToArry(pos, stateJson["\"pos\""]);
                qreal width = atof(stateJson["\"width\""].c_str());
                qreal height = atof(stateJson["\"height\""].c_str());
                qreal angle = atof(stateJson["\"angle\""].c_str());
                Json::JsonObject attrJosn = Json::toJsonObject(stateJson["\"attribute\""].c_str());
                int lineWidth = atoi(attrJosn["\"lineWidth\""].c_str());
                int lineType = atoi(attrJosn["\"lineType\""].c_str());
                std::vector<double> lineColor, fillColor;
                attrJosn.strToArry(lineColor, attrJosn["\"lineColor\""]);
                attrJosn.strToArry(fillColor, attrJosn["\"fillColor\""]);
                attr._boundingLineWidth = lineWidth;
                attr._boundingLineType =  (Qt::PenStyle)lineType;
                attr._boundingColor = QColor(lineColor[0], lineColor[1], lineColor[2], lineColor[3]);
                attr._fillColor = QColor(fillColor[0], fillColor[1],fillColor[2], fillColor[3]);
                item->setRect(QRectF(pos[0], pos[1], width, height));
                item->setTransformOriginPoint(item->boundingRect().center());
                item->setRotation(angle);
                item->setAttribute(attr);
                return;
            }
        }
        //item不存在，先创建
        int itemType = atoi(infoJson["\"itemType\""].c_str());
        Json::JsonObject stateJson = Json::toJsonObject(infoJson["\"state\""].c_str());
        std::vector<double> pos;
        stateJson.strToArry(pos, stateJson["\"pos\""]);
        createItem((Board::GraphicsType)itemType, QPointF(pos[0], pos[1]));
    }
}
