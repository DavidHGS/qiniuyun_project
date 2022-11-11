#include "JsonObject.h"
#include <sstream>
#include <iostream>

#define LOG(s) (std::cout << "JsonObject INFO: " << s << std::endl \
                          << std::endl)

using namespace Json;
JsonObject::JsonObject()
{

}
JsonObject::JsonObject(const JsonObject &object)
{
    _content = object._content;
}
JsonObject::~JsonObject()
{

}

std::string& JsonObject::operator[](std::string key)
{
    if(_content.find(key) == _content.end())
    {
        _content.insert(std::make_pair(key, ""));        
    }
    // LOG(key);
    return _content[key];
}

JsonObject &JsonObject::operator=(const JsonObject &object)
{
    _content = object._content;
    LOG(_content.size());
    return *this;
}

std::string JsonObject::toStr()
{
    std::stringstream jsonStream;
    jsonStream << "{";
    for(auto it : _content)
    {
        jsonStream <<it.first << ":" << it.second << ",";
    }
    std::string res = jsonStream.str().erase(jsonStream.str().length() - 1, 1) + "}";
    return res;
}

bool JsonObject::isEmpty()
{
    return _content.empty();
}

JsonObject Json::toJsonObject(const char *msg)
{
    JsonObject resObject;
    std::string msgString(msg);
    if(msgString.length() <= 2)
    {
        return resObject;
    }
    if(msgString[0] != '{' || msgString[msgString.length() - 1] != '}')
    {
        return resObject;
    }
    msgString.erase(0, 1);
    msgString.erase(msgString.length() - 1, 1);
    // LOG(msgString);
    std::stringstream msgStream(msgString);
    while(!msgStream.eof())
    {
        std::string tempMsg;
        std::getline(msgStream, tempMsg, ',');
        // LOG(tempMsg);
        std::stringstream tempMsgStream(tempMsg);
        std::string key, value;
        std::getline(tempMsgStream, key, ':');
        std::getline(tempMsgStream, value);
        // LOG(key);
        // LOG(value);
        resObject[key] = value;
    }

    return resObject;
}