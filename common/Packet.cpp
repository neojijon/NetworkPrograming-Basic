#include "Packet.h"

// 로그인 요청 패킷 전송 함수
void sendLoginPacket(int clientSocket, const char* username, uint32_t userID) 
{
    struct LoginPacket packet;

    // 헤더 설정
    packet.header.packetType = PACKET_TYPE_LOGIN;
    packet.header.dataLength = strlen(username);
    packet.header.senderID = userID;
    packet.header.receiverID = 0;

    // 유저네임 설정
    strncpy_s(packet.username, username, sizeof(packet.username) - 1);
    packet.username[sizeof(packet.username) - 1] = '\0';

    // 패킷 크기 계산
    size_t packetSize = sizeof(packet.header) + packet.header.dataLength;

    // 패킷 전송
    send(clientSocket, (char*)&packet, packetSize, 0);
}

// 채팅 메시지 패킷 전송 함수
void sendChatPacket(int clientSocket, const char* message, uint32_t userID, uint32_t receiverID) 
{
    struct ChatPacket packet;

    // 헤더 설정
    packet.header.packetType = PACKET_TYPE_CHAT;
    packet.header.dataLength = strlen(message);
    packet.header.senderID = userID;
    packet.header.receiverID = receiverID;

    // 메시지 설정
    strncpy_s(packet.message, message, sizeof(packet.message) - 1);
    packet.message[sizeof(packet.message) - 1] = '\0';

    // 패킷 크기 계산
    size_t packetSize = sizeof(packet.header) + packet.header.dataLength;

    // 패킷 전송
    send(clientSocket, (char*)&packet, packetSize, 0);
}

// 받은 패킷을 처리하는 함수
void handleReceivedPacket(SOCKET clientSocket)
{
    while (true)
    {
        struct PacketHeader header;
        size_t receivedBytes = 0;

        // 패킷 헤더 먼저 수신
        receivedBytes = recv(clientSocket, (char*)&header, sizeof(header), 0);
        if (receivedBytes > 0) 
        {
            // 패킷 타입에 따른 분기 처리
            if (header.packetType == PACKET_TYPE_LOGIN) {
                struct LoginPacket loginPacket;

                // 나머지 데이터 수신 (유저네임)
                recv(clientSocket, loginPacket.username, header.dataLength, 0);
                loginPacket.username[header.dataLength] = '\0';  // null-terminated

                // 로그인 패킷 처리
                printf("로그인 요청: 사용자 이름 = %s\n", loginPacket.username);

            }
            else if (header.packetType == PACKET_TYPE_CHAT) {
                struct ChatPacket chatPacket;

                // 나머지 데이터 수신 (채팅 메시지)
                recv(clientSocket, chatPacket.message, header.dataLength, 0);
                chatPacket.message[header.dataLength] = '\0';  // null-terminated

                // 채팅 패킷 처리
                printf("채팅 메시지: 발신자 = %d, 메시지 = %s\n", header.senderID, chatPacket.message);

            }
            else {
                printf("알 수 없는 패킷 타입: %d\n", header.packetType);
            }
        }
        else
        {
            break;
        }
    }

    std::cout << "클라이언트 소캣 종료" << std::endl;
    closesocket(clientSocket);
}
