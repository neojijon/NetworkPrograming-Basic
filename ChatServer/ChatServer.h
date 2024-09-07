#ifndef CHATSERVER_H
#define CHATSERVER_H

#include "../common/Packet.h"
#include "../common/SocketHandler.h"


class ChatServer : public SocketHandler 
{
private:
    WSADATA wsa;
    // �ִ� 100���� Ŭ���̾�Ʈ ó��
    SOCKET clientSockets[100];
    sockaddr_in serverAddr;
    int clientCount;    

public:
    ChatServer();

    bool startServer(int port);

    void acceptClient();

    // ��� Ŭ���̾�Ʈ���� �޽��� ��ε�ĳ��Ʈ
    void broadcastMessage(const char* message, PacketHeader header);

    // �޽����� �޾� ��ε�ĳ��Ʈ
    void receiveAndBroadcast();
    
};

#endif // CHATSERVER_H