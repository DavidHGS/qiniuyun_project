#include "whiteboard.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    WhiteBoard w;
    w.show();

    return a.exec();
}
