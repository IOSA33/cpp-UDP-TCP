#include <string>
#include <map>
#include <functional>
#include <iostream>
#include <fstream>
#include <print>
#include <format>
#include "Response.h"
#include "../Request/Request.h"

void Response::findRouteAndExecute(const std::string& path, const std::map<std::string, std::function<void(Request&, Response&)>>& routes, std::string& responseToClient, Request& request, Response& response) {
    auto it { routes.find(path) };

    if (it != routes.end()) {
        std::cout << "Found Route!\n";
        it->second(request, response);
        responseToClient = response.returnResponse();
        return;
    }

    std::cout << "Didn't found any Route!\n";
    pageNotFound();
    responseToClient = response.returnResponse();
}

void Response::sendPage(const std::string& filePath) {
    m_response.append("Content-Type: text/html\r\n");

    std::string filestring{};
    readHTMLFile(filestring, filePath);    

    // C++20
    m_response.append(std::format("Content-Length: {}\r\n", filestring.size()));
    // response.append("Content-Length: " + std::to_string(filestring.size()) + "\r\n");
    m_response.append("\r\n");


    m_response.append(filestring);
    m_response.append("\r\n");
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

void Response::redirect(const std::string& url) {
    m_response.append("Location:" + url + "\r\n");
    m_response.append("\r\n");
}

void Response::setStatus(int code) {

    m_response.clear();

    if (!(code < 100) && !(code >= 600)) {
        switch (code) {
        case 100:
            m_response.append(std::format("HTTP/1.1 {} Continue\r\n", code)); break;
        case 101:
            m_response.append(std::format("HTTP/1.1 {} Switching Protocols\r\n", code)); break;
        case 200:
            m_response.append(std::format("HTTP/1.1 {} OK\r\n", code)); break;
        case 201:
            m_response.append(std::format("HTTP/1.1 {} Created\r\n", code)); break;
        case 204:
            m_response.append(std::format("HTTP/1.1 {} No Content\r\n", code)); break;
        case 301:
            m_response.append(std::format("HTTP/1.1 {} Moved Permanently\r\n", code)); break;
        case 302:
            m_response.append(std::format("HTTP/1.1 {} Found\r\n", code)); break;
        case 304:
            m_response.append(std::format("HTTP/1.1 {} Not Modified\r\n", code)); break;
        case 400:
            m_response.append(std::format("HTTP/1.1 {} Bad Request\r\n", code)); break;
        case 401:
            m_response.append(std::format("HTTP/1.1 {} Unauthorized\r\n", code)); break;
        case 403:
            m_response.append(std::format("HTTP/1.1 {} Forbidden\r\n", code)); break;
        case 404:
            m_response.append(std::format("HTTP/1.1 {} Not Found\r\n", code)); break;
        case 500:
            m_response.append(std::format("HTTP/1.1 {} Internal Server Error\r\n", code)); break;
        case 502:
            m_response.append(std::format("HTTP/1.1 {} Bad Gateway\r\n", code)); break;
        case 503:
            m_response.append(std::format("HTTP/1.1 {} Service Unavailable\r\n", code)); break;

        default:
            std::println("setStatus(), Default break!"); break;
        }
    } else {
       std::println("Invalid http code: {}!", code); 
    }
}

void Response::setHeader(const std::string& header) {
    m_response.append(std::format("Content-Type: {}", header));
}

void Response::pageNotFound() {
    setStatus(301);
    redirect("https://www.youtube.com/?app");
}