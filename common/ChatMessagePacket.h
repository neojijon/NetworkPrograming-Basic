#ifndef CHATMESSAGEPACKET_H
#define CHATMESSAGEPACKET_H

#include "BasePacket.h"
#include <string>

class ChatMessagePacket : public BasePacket {
public:
    ChatMessagePacket() : BasePacket(PacketType::CHAT_MESSAGE) {}

    // ä�� �޽����� ����
    void setMessage(const std::string& message) {
        std::vector<uint8_t> messageData(message.begin(), message.end());
        setData(messageData);
    }

    // ä�� �޽����� ��������
    std::string getMessage() const {
        return std::string(data.begin(), data.end());
    }
};

#endif // CHATMESSAGEPACKET_H