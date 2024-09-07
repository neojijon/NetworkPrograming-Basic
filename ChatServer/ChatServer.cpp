#include <string.h>
#include <thread>
#include <vector>
#include <mutex>
#include <thread>

#include "ChatServer.h"


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

    while (true) {
        newSocket = accept(socketDescriptor, (struct sockaddr*)&clientAddr, &addrSize);
        if (newSocket != INVALID_SOCKET) {
            clientSockets.push_back(newSocket);
            clientThreads.push_back(std::thread(&ChatServer::handleClient, this, newSocket));
            std::cout << "Client connected. Total clients: " << clientSockets.size() << std::endl;
        }
    }
}

void ChatServer::handleClient(SOCKET clientSocket) {
    uint8_t buffer[1024];
    PacketHeader header;

    while (true) {
        // 패킷 헤더를 먼저 받음
        int recvSize = recv(clientSocket, (char*)&header, sizeof(PacketHeader), 0);
        if (recvSize > 0) {
            // 헤더에서 dataLength 만큼 데이터를 buffer에 읽음
            recv(clientSocket, (char*)buffer, header.dataLength, 0);

            // 패킷 타입에 따라 처리
            switch (header.packetType) {
            case PacketType::CHAT_MESSAGE: {
                ChatMessagePacket chatPacket;
                chatPacket.setData(std::vector<uint8_t>(buffer, buffer + header.dataLength));
                std::cout << "Chat Message: " << chatPacket.getMessage() << std::endl;
                break;
            }
            case PacketType::GROUP_MESSAGE: {
                GroupMessagePacket groupPacket;
                groupPacket.setData(std::vector<uint8_t>(buffer, buffer + header.dataLength));
                std::cout << "Group Message: " << groupPacket.getGroupMessage() << std::endl;
                break;
            }
            case PacketType::ANNOUNCEMENT: {
                AnnouncementPacket announcementPacket;
                announcementPacket.setData(std::vector<uint8_t>(buffer, buffer + header.dataLength));
                std::cout << "Announcement: " << announcementPacket.getAnnouncement() << std::endl;
                break;
            }
            default:
                std::cerr << "Unknown packet type" << std::endl;
                break;
            }
        }
    }
}

