#pragma once

#include <string_view>
#include <map>
#include <functional>
#include <string>

class Request;

class Response { 
private:

public:
    Response() = default;

    bool findRoute(const std::string& path, const std::map<std::string, std::function<void(const Request&, const Response&)>>& routes) const;
    void sendPage(const std::string& filePath, std::string& response);
    void readHTMLFile(std::string& file, const std::string& filePath);
    void redirect(const std::string& url, std::string& response);
};