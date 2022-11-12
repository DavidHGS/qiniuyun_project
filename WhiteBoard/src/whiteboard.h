#ifndef WHITEBOARD_H
#define WHITEBOARD_H

#include <QMainWindow>
#include <vector>
#include <QGraphicsItem>
#include "graphicsscene.h"
#include "whiteboardclient.h"

namespace Ui {
class WhiteBoard;
}

class WhiteBoard : public QMainWindow
{
    Q_OBJECT

private slots:
    void on_radioButton_rect_clicked();    
    void on_radioButton_circle_clicked();   
    void on_radioButton_choose_clicked();
    void on_spinBox_lineWidth_valueChanged(int arg1);
    void on_comboBox_lineType_currentIndexChanged(int index);
    void on_pushButton_boundingColor_clicked();
    void on_pushButton_fillColor_clicked();
    void itemSelected(QGraphicsItem* item, Board::GraphicsType type);

private:
    void init();
    void setPanelEditable(bool isEditable);
    void updateAttributePanel(Board::Attribute &attr, Board::GraphicsType type);
    void updateItemAttribute(Board::Attribute &attr);
    void setCursorShape(Board::MouseAction mouseAction);

public:
    explicit WhiteBoard(QWidget *parent = 0);
    ~WhiteBoard();

private:
    Ui::WhiteBoard *ui;
    GraphicsScene * _scene;
    QGraphicsItem* _curItem;
    Board::GraphicsType _curItemType;
    Board::Attribute _curAttribute;
    WhiteBoardClient *_client;
};

#endif // WHITEBOARD_H
