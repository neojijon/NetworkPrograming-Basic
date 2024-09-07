#ifndef CHATCLIENT_H
#define CHATCLIENT_H

#include "../common/Packet.h"
#include "../common/SocketHandler.h"

class ChatClient : public SocketHandler {
private:
    sockaddr_in serverAddr;

public:
    bool connectToServer(const char* serverIP, int port);

    // 서버로 메시지 전송
    void sendMessage(uint32_t senderID, const char* message);

    // 서버로부터 메시지 수신
    void receiveMessage();
};

#endif // CHATCLIENT_H