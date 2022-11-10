#include "HttpHandler.h"
#include <memory.h>
#include <sstream>
#include <iostream>

#define LOG(s) (std::cout << "HttpHandler INFO: " << s << std::endl << std::endl) 

HttpHandler::HttpHandler()
{
// const char *head =  "HTTP/1.1 200 ok\nContent-Length: 14\nContent-Type: application/json\nKeep-Alive: timeout=5, max=5\n\n{msg: \"hello\"}";
    _httpVersion = std::string("HTTP/1.1");
    _code = 200;
    _contentType = std::string("application/json");
    _mode = std::string("Keep-Alive: timeout=5, max=5");
    _contentLen = 0;
}

HttpHandler::~HttpHandler()
{

}

void HttpHandler::getRequestContent(const char *httpRequest, std::string &content)
{
    std::stringstream request;
    request << httpRequest;
    LOG(request.str());
    std::string temp;
    while(getline(request, temp))
    {
        if(temp.length() == 0)
        {
            break;
        }
    }
    getline(request, content);
}

void HttpHandler::setResponseContent(const char *content, std::string &httpResponse)
{
    _contentLen = strlen(content);
    std::stringstream resStream;
    resStream << _httpVersion << " " << _code << " "
              << "ok"
              << "\n";
    resStream << "Content-Length: " << _contentLen << "\n";
    resStream << "Content-Type: " << _contentType << "\n";
    resStream << _mode << "\n";
    resStream << "\n";
    resStream << content;
    httpResponse = resStream.str();

    // LOG(httpResponse);
}
