#include <iostream>
#include <WS2tcpip.h>
#include <windows.h>
#include <winsock2.h>
#include <stdio.h>
#include <vector>
#include <string>
#include <fstream>
#include "Server.h"
#include "Request/Request.h"
#include "Response/Response.h"
#include <format>
#include <print>
#include <utility>

#pragma comment (lib, "ws2_32.lib");

using namespace std;

// HTTP server in c++, I did my own custom implementation

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
    addr.sin_port = htons(m_port);
    addr.sin_addr.S_un.S_addr = ADDR_ANY;

    // Binding the socket for the server
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

            const std::string& method { m_request.getMethod(recvBuf) };
            std::println("Method is: {}", method);

            std::string path { m_request.getPath(recvBuf) };
            std::println("Path is: {}", path);
            
            m_request.parser(recvBuf);
            // The Main logic to response Client
            m_response.findRouteAndExecute(method, path, m_routes, response, m_request, m_response);

            std::cout << response << '\n'; 

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

void Server::Get(const std::string& path, const std::function<void(Request&, Response&)>& lambda) {
    m_routes["GET"][path] = std::make_pair(path, lambda);
}

void Server::Post(const std::string& path, const std::function<void(Request&, Response&)>& lambda) {
    m_routes["POST"][path] = std::make_pair(path, lambda);
}

void Server::Delete(const std::string& path, const std::function<void(Request&, Response&)>& lambda) {
    m_routes["DELETE"][path] = std::make_pair(path, lambda);
}

void Server::Put(const std::string& path, const std::function<void(Request&, Response&)>& lambda) {
    m_routes["PUT"][path] = std::make_pair(path, lambda);
}


// Pretty Cool huh :)

