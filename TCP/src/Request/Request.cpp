#include "Request.h"
#include <string>
#include <vector>
#include <algorithm>
#include <print>

void Request::parser(const std::string& req) {
    auto it = req.find("\r\n\r\n");

    if (it != std::string::npos) {
        m_method = req.substr(0, it);
        m_body = req.substr(it);

        // TODO: do something with req
    } else {
        std::println("Request::parser, didnt found any body!");
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