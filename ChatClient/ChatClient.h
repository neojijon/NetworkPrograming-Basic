#ifndef CHATCLIENT_H
#define CHATCLIENT_H

#include "../common/Packet.h"
#include "../common/SocketHandler.h"

class ChatClient : public SocketHandler {
private:
    sockaddr_in serverAddr;

public:
    bool connectToServer(const char* serverIP, int port);

    // ������ �޽��� ����
    void sendMessage(uint32_t senderID, const char* message);

    // �����κ��� �޽��� ����
    void receiveMessage();
};

#endif // CHATCLIENT_H