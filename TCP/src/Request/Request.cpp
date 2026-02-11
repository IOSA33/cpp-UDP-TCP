#include "Request.h"
#include <string>
#include <vector>
#include <algorithm>
#include <print>
#include <chrono>

void Request::parser(const std::string& req) {
    auto it = req.find("\r\n\r\n");

    if (it != std::string::npos) {
        
        std::string_view headers = req.substr(req.find("\r\n") + 2, it);
       
        while(!headers.empty()) {
            auto lineEnd { headers.find("\r\n") };
            if (lineEnd == 0 || lineEnd == std::string::npos) break;

            std::string_view line = headers.substr(0, lineEnd);
            size_t colomun { line.find(':') };
            if (colomun != std::string::npos) {
                std::string_view key { line.substr(0, colomun) };
                std::string_view value { line.substr(colomun + 1) };

                m_headers.emplace(std::string(key), std::string(value));
            } else {
                std::println("Request::parser, Didn't found ':' in the line!");
            }

            headers.remove_prefix(lineEnd + 2);
        }

        // +4 it means from "\r\n\r\n" and so on
        m_body = req.substr(it + 4);
        
    } else {
        std::println("Request::parser, Didn't found any body!");
        return;
    }

    return;
}

// about/example  :  {"abour", "example"}
void Request::splitURL(const std::string& url) {
    std::string token{};

    for (const auto& i: url) {
        if (i == '/') {
            m_vec_path.push_back(token);
            token.clear();
        } else {
            token.push_back(i);
        }
    }
}

std::string Request::getPath(const std::string_view buf) {
    std::string path{};
    
    // We know that http path is always second, so we do thr check for whitespacec
    short whitespaceAppear{ 0 };
    for (const auto& i : buf) {
        if (i == ' ') {
            ++whitespaceAppear;
            if (whitespaceAppear > 1) break;
            continue;
        }

        if (whitespaceAppear == 1) {
            path += i;
        }
    }

    return path;
}

const std::string& Request::getMethod(const std::string_view buf) {
    m_method.clear();
    // Longest method is 6 chars so we prevent from checking whole buf
    for (int i { 0 }; i < 5; ++i) {
        if (buf[i] == ' ') break;
        
        m_method += buf[i];
    }

    return m_method;
}