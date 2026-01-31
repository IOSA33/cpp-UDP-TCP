#include <string>
#include <map>
#include <functional>
#include <iostream>
#include <fstream>
#include <print>
#include "Response.h"
#include "../Request/Request.h"

bool Response::findRoute(const std::string& path, const std::map<std::string, std::function<void(const Request&, const Response&)>>& routes) const {
    auto it { routes.find(path) };

    if (it != routes.end()) {
        std::cout << "Found Route!\n";
        return true;
    }

    std::cout << "Didn't found any Route!\n";
    return false;
}

void Response::sendPage(const std::string& filePath, std::string& response) {
    response.append("HTTP1.1 200 OK\r\n");
    response.append("Content-Type: text/html\r\n");

    std::string filestring{};
    readHTMLFile(filestring, filePath);    

    // C++20
    response.append(std::format("Content-Length: {}\r\n", filestring.size()));
    // response.append("Content-Length: " + std::to_string(filestring.size()) + "\r\n");
    response.append("\r\n");


    response.append(filestring);
    response.append("\r\n");
}

void Response::readHTMLFile(std::string& file, const std::string& filePath) {
    const std::string op {"Server.readHTMLFile"};
    
    std::ifstream myFile { filePath };

    if(!myFile.is_open()) {
        std::println("{}, Cannot open a file", op);
        return;
    }

    std::string line{};

    while(std::getline(myFile, line)) {
        file += line;
    }

    myFile.close();
}

void Response::redirect(const std::string& url, std::string& response) {
    response.append("HTTP1.1 301 Moved Permanently\r\n");
    response.append("Location:" + url + "\r\n");
    response.append("\r\n");
}