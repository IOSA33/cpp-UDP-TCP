#pragma once

#include <string>
#include <functional>
#include <map>
#include <print>
#include "Request/Request.h"
#include "Response/Response.h"

class Server {
private:
    int m_port{};
    std::string m_ip{};
    std::map<std::string, std::function<void(Request&, Response&)>> m_routes{};
    Request m_request{};
    Response m_response{};

public:
    Server(const std::string& ip, int port) 
        : m_port(port), m_ip(ip) {
            std::println("Server Started at Port: {}", port);
        }
    int run();

    // Requests
    void Get(const std::string& path, const std::function<void(Request&, Response&)>& lambda);
    void Post(const std::string& path, const std::function<void(Request&, Response&)>& lambda);
    void Delete(const std::string& path, const std::function<void(Request&, Response&)>& lambda);
    void Updata(const std::string& path, const std::function<void(Request&, Response&)>& lambda);
};