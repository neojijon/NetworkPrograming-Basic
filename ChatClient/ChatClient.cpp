#include <string>
#include <thread>
#include <ws2tcpip.h>
#include "ChatClient.h"


bool ChatClient::connectToServer(const char* serverIP, int port) {
    if (!initializeSocket()) return false;
    if (!createSocket()) return false;

    // 서버 주소 설정
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(serverIP);
    serverAddr.sin_port = htons(port);

    // 서버에 연결
    if (connect(socketDescriptor, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Connection failed: " << WSAGetLastError() << std::endl;
        return false;
    }

    std::cout << "Connected to server" << std::endl;
    return true;
}

// 서버로 메시지 전송
void ChatClient::sendMessage(uint32_t senderID, const char* message) {
    PacketHeader header;
    header.packetType = 0x01;
    header.senderID = senderID;
    header.dataLength = strlen(message);

    send(socketDescriptor, (const char*)&header, sizeof(PacketHeader), 0);
    send(socketDescriptor, message, header.dataLength, 0);
}

// 서버로부터 메시지 수신
void ChatClient::receiveMessage() {
    char buffer[1024];
    PacketHeader header;

    int recvSize = recv(socketDescriptor, (char*)&header, sizeof(PacketHeader), 0);
    if (recvSize > 0) {
        recv(socketDescriptor, buffer, header.dataLength, 0);
        std::cout << "Message from server: " << buffer << std::endl;
    }
}

