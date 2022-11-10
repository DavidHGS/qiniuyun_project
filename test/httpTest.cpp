#include "../src/HttpHandler.h"
#include <iostream>

int main()
{
    HttpHandler handler;
    std::string httpresponse;
    handler.setResponseContent("hello world\n hello", httpresponse);
    const char *request =  "HTTP/1.1 200 ok\nContent-Length: 14\nContent-Type: application/json\nKeep-Alive: timeout=5, max=5\n\n{msg: \"hello\"}";
    std::string content;
    handler.getRequestContent(request, content);
    // std::cout <<"content: " << content << std::endl;
}