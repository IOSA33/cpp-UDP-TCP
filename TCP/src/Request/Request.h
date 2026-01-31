#pragma once

#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

class Request {
private:
    std::string m_method{};
    std::vector<std::string> m_vec_path{};
    std::unordered_map<std::string, std::string> m_{};
    std::string m_body{};

public:
    Request() = default;

    void parser(const char arr[], int length);
    void splitURL(const std::string& url);
    std::string_view getMethod() const { return m_method; }
    std::string getPath(const std::string_view buf);
};
