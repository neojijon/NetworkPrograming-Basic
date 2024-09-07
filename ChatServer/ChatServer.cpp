#include <string.h>
#include <thread>
#include <vector>
#include <mutex>

#include "ChatServer.h"

#pragma comment(lib, "ws2_32.lib")

#define SERVER_PORT 8888
#define MAX_CLIENTS 100
#define BUFFER_SIZE 1024

std::vector<SOCKET> clients;
std::mutex clientsMutex;


ChatServer::ChatServer() 
    : clientCount(0) 
{
    memset(clientSockets, 0, sizeof(clientSockets));
}

bool ChatServer::startServer(int port) 
{
    if (!initializeSocket()) return false;
    if (!createSocket()) return false;

    // 서버 주소 설정
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(port);

    // 소켓 바인딩
    if (bind(socketDescriptor, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Bind failed: " << WSAGetLastError() << std::endl;
        return false;
    }

    // 소켓 리스닝
    if (listen(socketDescriptor, 3) == SOCKET_ERROR) {
        std::cerr << "Listen failed: " << WSAGetLastError() << std::endl;
        return false;
    }

    std::cout << "Server started on port " << port << std::endl;
    return true;
}

void ChatServer::acceptClient() {
    SOCKET newSocket;
    sockaddr_in clientAddr;
    int addrSize = sizeof(clientAddr);

    newSocket = accept(socketDescriptor, (struct sockaddr*)&clientAddr, &addrSize);
    if (newSocket == INVALID_SOCKET) {
        std::cerr << "Accept failed: " << WSAGetLastError() << std::endl;
    }
    else {
        clientSockets[clientCount++] = newSocket;
        std::cout << "Client connected. Total clients: " << clientCount << std::endl;
    }
}

// 모든 클라이언트에게 메시지 브로드캐스트
void ChatServer::broadcastMessage(const char* message, PacketHeader header) {
    for (int i = 0; i < clientCount; i++) {
        send(clientSockets[i], (const char*)&header, sizeof(PacketHeader), 0);
        send(clientSockets[i], message, header.dataLength, 0);
    }
}

// 메시지를 받아 브로드캐스트
void ChatServer::receiveAndBroadcast() {
    char buffer[1024];
    PacketHeader header;

    for (int i = 0; i < clientCount; i++) {
        int recvSize = recv(clientSockets[i], (char*)&header, sizeof(PacketHeader), 0);
        if (recvSize > 0) {
            recv(clientSockets[i], buffer, header.dataLength, 0);
            std::cout << "Message received from client " << header.senderID << ": " << buffer << std::endl;
            broadcastMessage(buffer, header);
        }
    }
}
