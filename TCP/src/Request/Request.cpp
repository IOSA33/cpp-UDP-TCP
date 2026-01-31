#include "Request.h"
#include <string>
#include <vector>

void Request::parser(const char arr[], int length) {

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

