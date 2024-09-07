#ifndef CHATSERVER_H
#define CHATSERVER_H

#include "../common/Packet.h"
#include "../common/SocketHandler.h"


class ChatServer : public SocketHandler 
{
private:
    WSADATA wsa;
    // 최대 100명의 클라이언트 처리
    SOCKET clientSockets[100];
    sockaddr_in serverAddr;
    int clientCount;    

public:
    ChatServer();

    bool startServer(int port);

    void acceptClient();

    // 모든 클라이언트에게 메시지 브로드캐스트
    void broadcastMessage(const char* message, PacketHeader header);

    // 메시지를 받아 브로드캐스트
    void receiveAndBroadcast();
    
};

#endif // CHATSERVER_H