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
    _BottomRight,
    _Rotate
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
    int _itemId;
};

}

const char* const SERVERIP          = "10.252.1.171";
const unsigned int SERVERPORT       = 8000;             //服务器监听端口

const unsigned int RECVBUFLEN       = 1024;             //接收缓存大小

const unsigned int SENDBUFLEN       = 1024;             //发送缓存大小

const unsigned int USERNAMELEN      = 64;               //用户名最大长度

const unsigned int PASSWORDLEN      = 64;               //登录密码最大长度

const unsigned int ITEMNAMELEN      = 64;               //图元名称长度

//登录状态
const char * const LOGINSUCCESS     = "\"ok\"";         //成功登录

const char * const NOUSER           = "\"no_user\"";    //用户不存在

const char * const PSWERROR         = "\"psw_err\"";    //密码错误

//消息类型
const char * const MSG_LOGIN        = "\"L\"";          //登录消息

const char * const MSG_REPLY        = "\"R\"";          //服务器回复

const char * const MSG_ITEM_STATE   = "\"S\"";          //图元状态

const char *const MSG_BACK          = "\"B\"";          //回滚

//客户端类型
const char * const WINDOWS          = "\"WINDOWS\"";    //windows端

const char * const WEB              = "\"WEB\"";        //web端

//图元消息类型
const char *const ITEM_BEGIN        = "\"b\"";          //begin

const char *const ITEM_END          = "\"e\"";          //end

const char *const ITEM_MIDDLE       = "\"m\"";          //middle
#endif // DEFINE_H
