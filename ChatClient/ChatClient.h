#ifndef CHATCLIENT_H
#define CHATCLIENT_H

#include "../common/SocketHandler.h"
#include "../common/ChatMessagePacket.h"
#include "../common/GroupMessagePacket.h"
#include "../common/AnnouncementPacket.h"
#include <thread>
#include <iostream>

class ChatClient : public SocketHandler 
{
private:
    sockaddr_in serverAddr;
    std::thread receiveThread;

public:
    bool connectToServer(std::string serverIP, int port);

    // ä�� �޽��� ����
    void sendChatMessage(uint32_t senderID, const std::string& message);

    // �׷� �޽��� ����
    void sendGroupMessage(uint32_t senderID, const std::string& message);

    // ���� �޽��� ����
    void sendAnnouncement(const std::string& message);

    // �������� �޽��� ����
    void receiveMessages();

};

#endif // CHATCLIENT_H