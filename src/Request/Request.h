#pragma once

#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>
#include <map>
#include <print>

class Request {
private:
    std::string m_method{};
    std::string m_path{};
    std::map<std::string, std::string> m_headers{};
    std::map<std::string, std::string> m_body{};
    std::string m_body_string{};

public:
    Request() = default;

    void parser(const std::string& req);
    void addBody(const std::string& req);
    void parseBody();
    void printBodyString() const { std::println("{}", m_body_string); }
    const std::map<std::string, std::string>& getBody() const { return m_body; }
    const int getReceivedDataSize() const { return static_cast<int>(m_body_string.size()); }
    const std::string& getMethod(const std::string_view buf);
    const std::string& getPath(const std::string_view buf);
    std::string getHeader(const std::string& headerToFind) const;
};
