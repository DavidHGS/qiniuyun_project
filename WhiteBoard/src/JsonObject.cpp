#include "JsonObject.h"
#include <sstream>
#include <iostream>
#include <string>
#include <stack>

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
//    LOG(_content.size());
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
    for (int i = 0; i < msgString.length();)
    {
        std::string key, value;
        //切分key
        if (msgString[i] == '\"')
        {
            for (int j = i + 1; j < msgString.length(); ++j)
            {
                if(msgString[j] == '\"')
                {
                    key = msgString.substr(i, j - i + 1);
                    // LOG("Key: " << key);
                    i = j + 1;
                    break;
                }
            }
            if(key[0] != '\"' || key[key.length() - 1] != '\"')
            {
                LOG("Json format error");
                return resObject;
            }

            //切分value
            if(msgString[i] == ':')
            {
                ++i;
                if(msgString[i] == '\"') //value是字符串
                {
                    for (int j = i + 1; j < msgString.length(); ++j)
                    {
                        if(msgString[j] == '\"')
                        {
                            value = msgString.substr(i, j - i + 1);
                            i = j + 1;
                            break;
                        }
                    }
                }
                else if(msgString[i] == '[')//value是数组
                {
                    for (int j = i + 1; j < msgString.length(); ++j)
                    {
                        if(msgString[j] == ']')
                        {
                            value = msgString.substr(i, j - i + 1);
                            i = j + 1;
                            break;
                        }
                    }
                }
                else if(msgString[i] == '{')//value是json
                {
                    std::stack<char> st;
                    st.push(msgString[i]);
                    for (int j = i + 1; j < msgString.length(); ++j)
                    {
                        if(msgString[j] == '{')
                        {
                            st.push(msgString[j]);
                        }
                        else if(msgString[j] == '}')
                        {
                            st.pop();
                            if(st.empty())
                            {
                                value = msgString.substr(i, j - i + 1);
                                i = j + 1;
                                break;
                            }
                        }
                    }
                }
                else
                {
                    int j;
                    for (j = i + 1; j < msgString.length(); ++j)
                    {
                        if(msgString[j] == ',')
                        {
                            break;
                        }
                    }
                    value = msgString.substr(i, j - i);
                }
                // LOG(value);
                resObject[key] = value;
            }
        }
        else
        {
            ++i;
        }

    }

    return resObject;
}

void JsonObject::strToArry(std::vector<double> &arr, std::string value)
{
    arr.clear();
    int len = value.length();
    if (value[0] == '[' && value[len - 1] == ']')
    {
        value.erase(0, 1);
        value.erase(len - 1, 0);
    }
    else
    {
        return;
    }
    std::stringstream valueStream(value);
    while(!valueStream.eof())
    {
        std::string subValue;
        std::getline(valueStream, subValue, ',');
        arr.emplace_back(atof(subValue.c_str()));
    }
}
