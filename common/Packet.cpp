#include "Packet.h"

// �α��� ��û ��Ŷ ���� �Լ�
void sendLoginPacket(int clientSocket, const char* username, uint32_t userID) 
{
    struct LoginPacket packet;

    // ��� ����
    packet.header.packetType = PACKET_TYPE_LOGIN;
    packet.header.dataLength = strlen(username);
    packet.header.senderID = userID;
    packet.header.receiverID = 0;

    // �������� ����
    strncpy_s(packet.username, username, sizeof(packet.username) - 1);
    packet.username[sizeof(packet.username) - 1] = '\0';

    // ��Ŷ ũ�� ���
    size_t packetSize = sizeof(packet.header) + packet.header.dataLength;

    // ��Ŷ ����
    send(clientSocket, (char*)&packet, packetSize, 0);
}

// ä�� �޽��� ��Ŷ ���� �Լ�
void sendChatPacket(int clientSocket, const char* message, uint32_t userID, uint32_t receiverID) 
{
    struct ChatPacket packet;

    // ��� ����
    packet.header.packetType = PACKET_TYPE_CHAT;
    packet.header.dataLength = strlen(message);
    packet.header.senderID = userID;
    packet.header.receiverID = receiverID;

    // �޽��� ����
    strncpy_s(packet.message, message, sizeof(packet.message) - 1);
    packet.message[sizeof(packet.message) - 1] = '\0';

    // ��Ŷ ũ�� ���
    size_t packetSize = sizeof(packet.header) + packet.header.dataLength;

    // ��Ŷ ����
    send(clientSocket, (char*)&packet, packetSize, 0);
}

// ���� ��Ŷ�� ó���ϴ� �Լ�
void handleReceivedPacket(SOCKET clientSocket)
{
    while (true)
    {
        struct PacketHeader header;
        size_t receivedBytes = 0;

        // ��Ŷ ��� ���� ����
        receivedBytes = recv(clientSocket, (char*)&header, sizeof(header), 0);
        if (receivedBytes > 0) 
        {
            // ��Ŷ Ÿ�Կ� ���� �б� ó��
            if (header.packetType == PACKET_TYPE_LOGIN) {
                struct LoginPacket loginPacket;

                // ������ ������ ���� (��������)
                recv(clientSocket, loginPacket.username, header.dataLength, 0);
                loginPacket.username[header.dataLength] = '\0';  // null-terminated

                // �α��� ��Ŷ ó��
                printf("�α��� ��û: ����� �̸� = %s\n", loginPacket.username);

            }
            else if (header.packetType == PACKET_TYPE_CHAT) {
                struct ChatPacket chatPacket;

                // ������ ������ ���� (ä�� �޽���)
                recv(clientSocket, chatPacket.message, header.dataLength, 0);
                chatPacket.message[header.dataLength] = '\0';  // null-terminated

                // ä�� ��Ŷ ó��
                printf("ä�� �޽���: �߽��� = %d, �޽��� = %s\n", header.senderID, chatPacket.message);

            }
            else {
                printf("�� �� ���� ��Ŷ Ÿ��: %d\n", header.packetType);
            }
        }
        else
        {
            break;
        }
    }

    std::cout << "Ŭ���̾�Ʈ ��Ĺ ����" << std::endl;
    closesocket(clientSocket);
}
