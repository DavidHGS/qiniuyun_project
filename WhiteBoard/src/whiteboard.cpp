#include "whiteboard.h"
#include "ui_whiteboard.h"
#include <QDebug>
#include <QColorDialog>

WhiteBoard::WhiteBoard(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::WhiteBoard),
    _scene(nullptr),
    _curItem(nullptr),
    _curItemType(Board::GraphicsType::_NoneType)
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
    _client = new WhiteBoardClient;
    _scene = new GraphicsScene(_client);
    _scene->setSceneRect(0, 0, ui->graphicsView_whiteBoard->width(), ui->graphicsView_whiteBoard->height());
    ui->graphicsView_whiteBoard->setScene(_scene);
    ui->graphicsView_whiteBoard->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    connect(_scene, SIGNAL(itemSelected(QGraphicsItem*,Board::GraphicsType)), this, SLOT(itemSelected(QGraphicsItem*,Board::GraphicsType)));
    _client->connectToServer(SERVERIP, SERVERPORT);
}

void WhiteBoard::on_radioButton_rect_clicked()
{
    _scene->setCurGraphicsType(Board::GraphicsType::_Rect);
    _scene->setMouseAction(Board::MouseAction::_Draw);
    setCursorShape(Board::MouseAction::_Draw);
}

void WhiteBoard::on_radioButton_circle_clicked()
{
    _scene->setCurGraphicsType(Board::GraphicsType::_Circle);
    _scene->setMouseAction(Board::MouseAction::_Draw);
    setCursorShape(Board::MouseAction::_Draw);
}

void WhiteBoard::on_radioButton_choose_clicked()
{
    _scene->setCurGraphicsType(Board::GraphicsType::_NoneType);
    _scene->setMouseAction(Board::MouseAction::_Normal);
    setCursorShape(Board::MouseAction::_Normal);
}

void WhiteBoard::updateAttributePanel(Board::Attribute &attr, Board::GraphicsType type)
{
//    qDebug() << "WhiteBoard INFO : update panel, attribute(" << attr._boundingColor
//             <<", " << attr._boundingLineType << ", "<<attr._boundingLineWidth << ", "
//            << attr._fillColor << ")";
    if(Board::GraphicsType::_Text != type)
    {
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
}

void WhiteBoard::on_spinBox_lineWidth_valueChanged(int arg1)
{
    _curAttribute._boundingLineWidth = arg1;
    updateItemAttribute(_curAttribute);
}

void WhiteBoard::on_comboBox_lineType_currentIndexChanged(int index)
{
    if(index == 0)
    {
        _curAttribute._boundingLineType = Qt::SolidLine;
    }
    if(index == 1)
    {
        _curAttribute._boundingLineType = Qt::DashLine;
    }
    updateItemAttribute(_curAttribute);
}

void WhiteBoard::on_pushButton_boundingColor_clicked()
{
    QColor boundingColor = QColorDialog::getColor(Qt::black);
    _curAttribute._boundingColor = boundingColor;
    updateItemAttribute(_curAttribute);
    ui->pushButton_boundingColor->setStyleSheet(QString("background-color: rgb(%1, %2, %3)")
                                                .arg(boundingColor.red()).arg(boundingColor.green()).arg(boundingColor.blue()));
}

void WhiteBoard::on_pushButton_fillColor_clicked()
{
    QColor fillColor = QColorDialog::getColor(Qt::black);
    _curAttribute._fillColor = fillColor;
    updateItemAttribute(_curAttribute);
    ui->pushButton_fillColor->setStyleSheet(QString("background-color: rgb(%1, %2, %3)")
                                            .arg(fillColor.red()).arg(fillColor.green()).arg(fillColor.blue()));
}

void WhiteBoard::itemSelected(QGraphicsItem *item, Board::GraphicsType type)
{
    _curItem = item;
    _curItemType = type;
    if(_curItem != nullptr)
    {
        if(type == Board::_Rect)
        {
            setPanelEditable(true);
            RectItem *temp = dynamic_cast<RectItem*>(_curItem);
            _curAttribute = temp->getAttribute();
            updateAttributePanel(_curAttribute, Board::GraphicsType::_Rect);
        }
        else if(type == Board::_Circle)
        {
            setPanelEditable(true);
            CircleItem *temp = dynamic_cast<CircleItem*>(_curItem);
            _curAttribute = temp->getAttribute();
            updateAttributePanel(_curAttribute, Board::GraphicsType::_Circle);
        }
    }
    else
    {
        setPanelEditable(false);
    }
}

void WhiteBoard::setPanelEditable(bool isEditable)
{
    ui->spinBox_lineWidth->setEnabled(isEditable);
    ui->comboBox_lineType->setEnabled(isEditable);
    ui->pushButton_boundingColor->setEnabled(isEditable);
    ui->pushButton_fillColor->setEnabled(isEditable);
}

void WhiteBoard::updateItemAttribute(Board::Attribute &attr)
{
    if(_curItem != nullptr)
    {
        if(_curItemType == Board::_Rect)
        {
            RectItem *temp = dynamic_cast<RectItem*>(_curItem);
            temp->setAttribute(attr);
        }
        else if(_curItemType == Board::_Circle)
        {
            CircleItem *temp = dynamic_cast<CircleItem*>(_curItem);
            temp->setAttribute(attr);
        }
    }
}

void WhiteBoard::setCursorShape(Board::MouseAction mouseAction)
{
    if(mouseAction == Board::MouseAction::_Draw)
    {
        QPixmap mMap(":/source/pen.png");
        QSize msize(20, 20);
        QPixmap mScaleMap = mMap.scaled(msize, Qt::KeepAspectRatio);
        QCursor mCursor(mScaleMap);
        ui->graphicsView_whiteBoard->viewport()->setCursor(mCursor);
    }
    else if(mouseAction == Board::MouseAction::_Normal)
    {
        ui->graphicsView_whiteBoard->viewport()->setCursor(Qt::ArrowCursor);
    }
}
