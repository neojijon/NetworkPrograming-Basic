#pragma once
#include <iostream>
#include <string.h>
#include <winsock2.h>
#include <stdint.h>


// ��Ŷ Ÿ�� ��� ����
#define PACKET_TYPE_LOGIN 0x07
#define PACKET_TYPE_CHAT  0x08

struct PacketHeader {
    uint8_t packetType;
    uint32_t dataLength;
    uint32_t senderID;
    uint32_t receiverID;
};

// �α��� ��Ŷ ����ü ����
struct LoginPacket {
    struct PacketHeader header;
    char username[256];
};

// ä�� ��Ŷ ����ü ����
struct ChatPacket {
    struct PacketHeader header;
    char message[512];
};


// �α��� ��û ��Ŷ ���� �Լ�
void sendLoginPacket(int clientSocket, const char* username, uint32_t userID);

// ä�� �޽��� ��Ŷ ���� �Լ�
void sendChatPacket(int clientSocket, const char* message, uint32_t userID, uint32_t receiverID);

// ���� ��Ŷ�� ó���ϴ� �Լ�
void handleReceivedPacket(SOCKET clientSocket);