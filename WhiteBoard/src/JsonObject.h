#pragma once

#include <string>
#include <map>
#include <vector>
namespace Json
{
    class JsonObject
    {
    public:
        JsonObject();
        JsonObject(const JsonObject &object);
        ~JsonObject();
        std::string& operator[](std::string key);
        JsonObject &operator=(const JsonObject &object);
        std::string toStr();
        bool isEmpty();
        void strToArry(std::vector<double> &arr, std::string value);

    private:
        std::map<std::string, std::string> _content;
    };

    JsonObject toJsonObject(const char *msg);
} // namespace Json

