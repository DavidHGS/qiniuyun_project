#include "../src/JsonObject.h"
#include <iostream>

int main()
{
    // JsonObject json;
    // json["user1"] = "\"12345\"";
    // json["user2"] = "12345";
    // json["user2"] = "345678";
    // std::cout << json["user1"] << std::endl;
    // std::cout << json.toStr() << std::endl;
    const char *jsonStr = "{\"user\":\"jianglinxin\",\"password\":\"1234567890\",\"type\":\"L\"}";
    Json::JsonObject temp = Json::toJsonObject(jsonStr);
    // temp = Json::toJsonObject(jsonStr);
    std::cout << temp["\"user\""] << std::endl;
    std::cout << temp["\"password\""] << std::endl;
    std::cout << temp["\"type\""] << std::endl;
}