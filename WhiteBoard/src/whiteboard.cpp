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
    connect(_scene, SIGNAL(updateAttributePanel(Board::Attribute&)), this, SLOT(updateAttributePanel(Board::Attribute&)));
}

void WhiteBoard::on_radioButton_rect_clicked()
{
    _scene->setCurGraphicsType(Board::GraphicsType::_Rect);
    _scene->setMouseAction(Board::MouseAction::_Draw);
}

void WhiteBoard::on_radioButton_circle_clicked()
{
    _scene->setCurGraphicsType(Board::GraphicsType::_Circle);
    _scene->setMouseAction(Board::MouseAction::_Draw);
}

void WhiteBoard::on_radioButton_choose_clicked()
{
    _scene->setCurGraphicsType(Board::GraphicsType::_NoneType);
    _scene->setMouseAction(Board::MouseAction::_Normal);
}

void WhiteBoard::updateAttributePanel(Board::Attribute &attr)
{
    qDebug() << "WhiteBoard INFO : update panel, attribute(" << attr._boundingColor
             <<", " << attr._boundingLineType << ", "<<attr._boundingLineWidth << ", "
            << attr._fillColor << ")";
    QColor boundingColor = attr._boundingColor;
    ui->pushButton_boundingColor->setStyleSheet(QString("background-color: rgb(%1, %2, %3)")
                                                .arg(boundingColor.red()).arg(boundingColor.green()).arg(boundingColor.blue()));
    QColor fillColor = attr._fillColor;
    ui->pushButton_fillColor->setStyleSheet(QString("background-color: rgb(%1, %2, %3)")
                                            .arg(fillColor.red()).arg(fillColor.green()).arg(fillColor.blue()));
    int lineWidth = attr._boundingLineWidth;
    ui->spinBox_lineWidth->setValue(lineWidth);
    Qt::PenStyle lineType = attr._boundingLineType;
    int lineTypeIndex = 0;
    if(lineType == Qt::PenStyle::SolidLine)
    {
        lineTypeIndex = 0;
    }
    if(lineType == Qt::PenStyle::DashLine)
    {
        lineTypeIndex = 1;
    }
    ui->comboBox_lineType->setCurrentIndex(lineTypeIndex);
}
