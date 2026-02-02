#pragma once

#include <string_view>
#include <map>
#include <functional>
#include <string>

class Request;

class Response { 
private:
    std::string m_response{};

public:
    Response() = default;

    bool findRoute(const std::string& path, const std::map<std::string, std::function<void(Request&, Response&)>>& routes) const;
    void sendPage(const std::string& filePath);
    void readHTMLFile(std::string& file, const std::string& filePath);
    void redirect(const std::string& url, std::string& response);
    void setStatus(int code);
    std::string returnResponse() { return m_response; };
};