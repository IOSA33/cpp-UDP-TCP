#pragma once

#include <string>
#include <functional>
#include <map>
#include "Request/Request.h"
#include "Response/Response.h"

class Server {
private:
    int m_port{};
    std::string m_ip{};
    std::map<std::string, std::function<void(const Request&, const Response&)>> m_routes{};
    Request m_request{};
    Response m_response{};

public:
    Server(const std::string& ip, int port) 
        : m_port(port), m_ip(ip) {}
    int run();

    // Requests
    void Get(const std::string& path, const std::function<void(const Request&, const Response&)>& lambda);
    void Post(const std::string& path, const std::function<void(const Request&, const Response&)>& lambda);
    void Delete(const std::string& path, const std::function<void(const Request&, const Response&)>& lambda);
    void Updata(const std::string& path, const std::function<void(const Request&, const Response&)>& lambda);
};