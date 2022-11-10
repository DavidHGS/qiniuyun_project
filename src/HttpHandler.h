#pragma once

#include <string>

class HttpHandler
{
public:
    HttpHandler();
    ~HttpHandler();
    void getRequestContent(const char *httpRequest, std::string &content);
    void setResponseContent(const char *content, std::string &httpResponse);
            
private:
    std::string _httpVersion;
    int _code;
    std::string _state;
    int _contentLen;
    std::string _contentType;
    std::string _mode;
};