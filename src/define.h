#pragma once 
/*
* 此文件定义一些常量
*/

const unsigned int SERVERPORT       = 6002;             //服务器监听端口

const unsigned int RECVBUFLEN       = 1024;             //接收缓存大小

const unsigned int SENDBUFLEN       = 1024;             //发送缓存大小

const unsigned int USERNAMELEN      = 64;               //用户名最大长度

const unsigned int PASSWORDLEN      = 64;               //登录密码最大长度

const unsigned int ITEMNAMELEN      = 64;               //图元名称长度

//登录状态
const short int LOGINSUCCESS        = 0;                //成功登录

const short int NOUSER              = 1;                //用户不存在

const short int PSWERROR            = 2;                //密码错误

//消息类型
const char MSG_LOGIN                = 'L';              //登录消息

const char MSG_REPLY                = 'R';              //服务器回复

const char MSG_ITEM_STATE           = 'S';              //图元状态
