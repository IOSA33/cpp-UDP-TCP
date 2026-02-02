#pragma once

#include <string_view>
#include <map>
#include <functional>
#include <string>
#include <string_view>

class Request;

class Response { 
private:
    std::string m_response{};

public:
    Response() = default;

    void findRouteAndExecute(const std::string& path, const std::map<std::string, std::function<void(Request&, Response&)>>& routes, std::string& responseToClient, Request& request, Response& response);
    void sendPage(const std::string& filePath);
    void readHTMLFile(std::string& file, const std::string& filePath);
    void redirect(const std::string& url);
    void setStatus(int code);
    std::string_view returnResponse() { return m_response; };
    void setHeader(const std::string& header);
    void pageNotFound();
};