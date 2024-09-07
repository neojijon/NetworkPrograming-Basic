#ifndef CHATMESSAGEPACKET_H
#define CHATMESSAGEPACKET_H

#include "BasePacket.h"
#include <string>

class ChatMessagePacket : public BasePacket {
public:
    ChatMessagePacket() : BasePacket(PacketType::CHAT_MESSAGE) {}

    // 채팅 메시지를 설정
    void setMessage(const std::string& message) {
        std::vector<uint8_t> messageData(message.begin(), message.end());
        setData(messageData);
    }

    // 채팅 메시지를 가져오기
    std::string getMessage() const {
        return std::string(data.begin(), data.end());
    }
};

#endif // CHATMESSAGEPACKET_H