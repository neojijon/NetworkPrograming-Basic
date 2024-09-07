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

    // 채팅 메시지 전송
    void sendChatMessage(uint32_t senderID, const std::string& message);

    // 그룹 메시지 전송
    void sendGroupMessage(uint32_t senderID, const std::string& message);

    // 공지 메시지 전송
    void sendAnnouncement(const std::string& message);

    // 서버에서 메시지 수신
    void receiveMessages();

};

#endif // CHATCLIENT_H