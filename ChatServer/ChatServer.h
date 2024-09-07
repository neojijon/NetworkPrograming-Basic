#ifndef CHATSERVER_H
#define CHATSERVER_H

#include "../common/SocketHandler.h"
#include "../common/BasePacket.h"
#include "../common/ChatMessagePacket.h"
#include "../common/GroupMessagePacket.h"
#include "../common/AnnouncementPacket.h"

#include <thread>
#include <vector>


class ChatServer : public SocketHandler 
{
private:        
    sockaddr_in serverAddr;
    std::vector<SOCKET> clientSockets;
    std::vector<std::thread> clientThreads;

public:
    ChatServer() {}

    bool startServer(int port);

    void acceptClient();

    void handleClient(SOCKET clientSocket);
    
};

#endif // CHATSERVER_H