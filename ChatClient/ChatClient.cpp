#include "ChatClient.h"

#include <ws2tcpip.h>
#include <thread>
#include <iostream>


bool ChatClient::connectToServer(std::string serverIP, int port) {
    if (!initializeSocket()) return false;
    if (!createSocket()) return false;

    serverAddr.sin_family = AF_INET;    
    inet_pton(AF_INET, serverIP.c_str(), &serverAddr.sin_addr);
    serverAddr.sin_port = htons(port);

    if (connect(socketDescriptor, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Connection failed: " << WSAGetLastError() << std::endl;
        return false;
    }

    std::cout << "Connected to server" << std::endl;

    // 메시지 수신 쓰레드 시작
    receiveThread = std::thread(&ChatClient::receiveMessages, this);

    return true;
}

// 채팅 메시지 전송
void ChatClient::sendChatMessage(uint32_t senderID, const std::string& message) {
    ChatMessagePacket packet;
    packet.header.senderID = senderID;
    packet.setMessage(message);

    std::vector<uint8_t> serializedData = packet.serialize();
    send(socketDescriptor, (const char*)serializedData.data(), (int)serializedData.size(), 0);
}

// 그룹 메시지 전송
void ChatClient::sendGroupMessage(uint32_t senderID, const std::string& message) {
    GroupMessagePacket packet;
    packet.header.senderID = senderID;
    packet.setGroupMessage(message);

    std::vector<uint8_t> serializedData = packet.serialize();
    send(socketDescriptor, (const char*)serializedData.data(), (int)serializedData.size(), 0);
}

// 공지 메시지 전송
void ChatClient::sendAnnouncement(const std::string& message) {
    AnnouncementPacket packet;
    packet.setAnnouncement(message);

    std::vector<uint8_t> serializedData = packet.serialize();
    send(socketDescriptor, (const char*)serializedData.data(), (int)serializedData.size(), 0);
}

// 서버에서 메시지 수신
void ChatClient::receiveMessages() {
    uint8_t buffer[1024];
    PacketHeader header;

    while (true) {
        int recvSize = recv(socketDescriptor, (char*)&header, sizeof(PacketHeader), 0);
        if (recvSize > 0) {
            recv(socketDescriptor, (char*)&buffer, header.dataLength, 0);

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

