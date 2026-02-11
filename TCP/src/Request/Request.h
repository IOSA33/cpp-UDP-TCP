#pragma once

#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

class Request {
private:
    std::string m_method{};
    std::vector<std::string> m_vec_path{};
    std::string m_headers{};
    short m_content_length{};
    std::string m_body{};

public:
    Request() = default;

    void parser(const std::string& req);
    void splitURL(const std::string& url);
    const std::string& getMethod(const std::string_view buf);
    std::string getPath(const std::string_view buf);
};
