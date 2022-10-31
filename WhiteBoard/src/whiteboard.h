#ifndef WHITEBOARD_H
#define WHITEBOARD_H

#include <QMainWindow>
#include <vector>
#include <QGraphicsItem>
#include "graphicsscene.h"

namespace Ui {
class WhiteBoard;
}

class WhiteBoard : public QMainWindow
{
    Q_OBJECT

public:

    explicit WhiteBoard(QWidget *parent = 0);
    ~WhiteBoard();

private slots:
    void on_radioButton_rect_clicked();
    
    void on_radioButton_circle_clicked();
    
    void on_radioButton_clicked();

private:
    void init();

private:
    Ui::WhiteBoard *ui = nullptr;
    GraphicsScene * _scene = nullptr;
};

#endif // WHITEBOARD_H
