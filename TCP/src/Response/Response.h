#pragma once

#include <string_view>
#include <map>
#include <functional>

class Request;

class Response { 
private:

public:
    Response() = default;

    bool findRoute(const std::string& path, const std::map<std::string, std::function<void(const Request&, const Response&)>>& routes) const;
};