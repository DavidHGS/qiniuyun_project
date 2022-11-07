#ifndef DEFINE_H
#define DEFINE_H

#include <QColor>

namespace Board {
enum MouseAction
{
    _Normal = 0,
    _Draw
};
enum GraphicsType
{
    _NoneType = -1,
    _Rect,
    _Circle,
    _Text
};
enum MouseHandlePos
{
    _NoneHandle = -1,
    _TopLeft,
    _TopMiddle,
    _TopRight,
    _LeftMiddle,
    _RightMiddle,
    _BottomLeft,
    _BottomMiddle,
    _BottomRight
};
struct Attribute
{
    Attribute(int boundingWidth = 3, Qt::PenStyle boundingLineType = Qt::SolidLine,
              QColor boundingColor = Qt::black, QColor fillColor = QColor(255, 255, 255, 0)) :
        _boundingLineWidth(boundingWidth),
        _boundingLineType(boundingLineType),
        _boundingColor(boundingColor),
        _fillColor(fillColor)
    {}
    int _boundingLineWidth;
    Qt::PenStyle _boundingLineType;
    QColor _boundingColor;
    QColor _fillColor;
};

}
#endif // DEFINE_H
