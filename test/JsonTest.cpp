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
    const char *jsonStr = "{ \"user\":\"jianglinxin\",\"password\":\"1234567890\",\"type\":{\"L\":1, \"R\":2, \"M\":{\"Q\":3, \"p\":4}} }";
    Json::JsonObject temp = Json::toJsonObject(jsonStr);
    // temp = Json::toJsonObject(jsonStr);
    std::cout << temp["\"user\""] << std::endl;
    std::cout << temp["\"password\""] << std::endl;
    std::cout << temp["\"type\""] << std::endl;
    std::cout << temp["\"type\""].c_str() << std::endl;
    Json::JsonObject temp2 = Json::toJsonObject(temp["\"type\""].c_str());
    std::cout << temp2["\"L\""] << std::endl;
    std::cout << temp2["\"R\""] << std::endl;
    std::cout << temp2["\"M\""] << std::endl;
}