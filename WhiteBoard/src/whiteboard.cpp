#include <QDebug>
#include "whiteboard.h"
#include "ui_whiteboard.h"

WhiteBoard::WhiteBoard(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WhiteBoard)
{
    ui->setupUi(this);
    init();

}

WhiteBoard::~WhiteBoard()
{
    delete ui;
}

void WhiteBoard::init()
{
    _scene = new GraphicsScene();
    _scene->setSceneRect(0, 0, ui->graphicsView_whiteBoard->width(), ui->graphicsView_whiteBoard->height());
    ui->graphicsView_whiteBoard->setScene(_scene);
    ui->graphicsView_whiteBoard->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
}

void WhiteBoard::on_radioButton_rect_clicked()
{
    _scene->setCurGraphicsType(GraphicsScene::GraphicsType::_Rect);
    _scene->setMouseAction(GraphicsScene::MouseAction::_Draw);
}

void WhiteBoard::on_radioButton_circle_clicked()
{
    _scene->setCurGraphicsType(GraphicsScene::GraphicsType::_Circle);
    _scene->setMouseAction(GraphicsScene::MouseAction::_Draw);
}

void WhiteBoard::on_radioButton_clicked()
{
    _scene->setCurGraphicsType(GraphicsScene::GraphicsType::_Hand);
    _scene->setMouseAction(GraphicsScene::MouseAction::_Normal);
}
