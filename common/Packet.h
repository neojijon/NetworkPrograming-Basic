#pragma once
#include <iostream>
#include <string.h>
#include <winsock2.h>
#include <stdint.h>


// 패킷 타입 상수 정의
#define PACKET_TYPE_LOGIN 0x07
#define PACKET_TYPE_CHAT  0x08

struct PacketHeader {
    uint8_t packetType;
    uint32_t dataLength;
    uint32_t senderID;
    uint32_t receiverID;
};

// 로그인 패킷 구조체 정의
struct LoginPacket {
    struct PacketHeader header;
    char username[256];
};

// 채팅 패킷 구조체 정의
struct ChatPacket {
    struct PacketHeader header;
    char message[512];
};


// 로그인 요청 패킷 전송 함수
void sendLoginPacket(int clientSocket, const char* username, uint32_t userID);

// 채팅 메시지 패킷 전송 함수
void sendChatPacket(int clientSocket, const char* message, uint32_t userID, uint32_t receiverID);

// 받은 패킷을 처리하는 함수
void handleReceivedPacket(SOCKET clientSocket);