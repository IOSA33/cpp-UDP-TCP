#include <iostream>
#include <WS2tcpip.h>
#include <windows.h>
#include <winsock2.h>
#include <stdio.h>
#include <vector>
#include <string>
#include "Server.h"

#pragma comment (lib, "ws2_32.lib");

// Declarations:
void redirect(const std::string& url, std::string& response);

using namespace std;

// HTTP server in c++
// https://itsfuad.medium.com/understanding-http-at-a-low-level-a-developers-guide-with-c-213728d6c41d

// Declarations
std::vector<std::string> splitURL(const std::string& url);

// To compile  "g++ server.cpp -lws2_32 -o server"
int Server::run() {
    // Linking DLL
    // Starting WinSock
    WSADATA wsadata;
    int wsaerr;
    wsaerr = WSAStartup(MAKEWORD(2,2), &wsadata);
    if (wsaerr != 0) {
        cout << "Winsock dll not found" << endl;
        return 1;
    } else {
        cout << "winsock DLL Found" << endl;
        cout << "Status: " << wsadata.szSystemStatus << endl;
    }

    // Creating a socket
    SOCKET in = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (in == INVALID_SOCKET) {
        cout << "Error at socket()" << WSAGetLastError() << endl;
        WSACleanup();
        return 1;
    } else {
        cout << "Socket is OK" << endl;
    }

    // SOCKADDR_IN is local endpoint address to 
    // which connect a socket
    sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons();
    addr.sin_addr.S_un.S_addr = ADDR_ANY;

    // Binding the socket
    // If bind is okay return 0, else SOCKET_ERROR
    if (bind(in, (sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR) {
        cout << "Can't bind socket! " << WSAGetLastError() << endl;
		return 1;
    }

    // Listen on port TCP
    if (listen(in, 1) == SOCKET_ERROR) {
        cout << "error in listen() : " << WSAGetLastError << endl;
    } else {
        cout << "Listen() is OK, I'm waiting for connections..." << endl;
    }

    while (true) {
        // Accept functions
        SOCKET acceptSocket;
        acceptSocket = accept(in, NULL, NULL);
        if(acceptSocket == INVALID_SOCKET) {
            cout << "accept failed:" << WSAGetLastError() << endl;
            WSACleanup();
            return 1;
        } else { 
            cout << "accept() is working" << endl; 
        } 
        
        // recv() Receives data from the client
        char recvBuf[1024];
        int recvBuflen = sizeof(recvBuf);

        int bytesRecv = recv(acceptSocket, recvBuf, recvBuflen, 0);
        if (bytesRecv > 0) {
            recvBuf[bytesRecv] = '\0';
            cout << "Recived from client: \n" << recvBuf << endl;

            // send() Send back to the client
            std::string response{};
            redirect("https://www.youtube.com/?app", response);
            
            // response.append("HTTP1.1 200 OK\r\n");
            // response.append("Content-Type: text/html\r\n");
            // response.append("Content-Length: 46\r\n"); // Length of the HTML content
            // response.append("\r\n");
            // response.append("<html><body><h1>Hello, World!</h1></body></html>");

            int bytes_sent = send(acceptSocket, response.c_str(), response.size(), 0);
            if (bytes_sent == SOCKET_ERROR) {
                // If sending fails, print an error
                std::cerr << "send failed: " << WSAGetLastError() << std::endl;
            } else {
                // Print the number of bytes sent
                std::cout << "Sent " << bytes_sent << " bytes to client." << std::endl;
            }


        } else {
            // If no data is received, print an error message
            std::cerr << "recv failed: " << WSAGetLastError() << std::endl;
        }
    }

    // Terminating a Winsock2 dll
    WSACleanup();
    return 0;
}

// about/example  :  {"abour", "example"}
std::vector<std::string> splitURL(const std::string& url) {
    std::vector<std::string> res{};
    std::string token{};

    for (const auto& i: url) {
        if (i == '/') {
            res.push_back(token);
            token.clear();
        } else {
            token.push_back(i);
        }
    }

    return res;
}

void redirect(const std::string& url, std::string& response) {
    response.append("HTTP1.1 301 Moved Permanently\r\n");
    response.append("Location:" + url + "\r\n");
}

void Server::Get(const std::string& path, const auto& lambda) {
    m_routes.insert({path, lambda});
}