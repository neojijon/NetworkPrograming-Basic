#ifndef GROUPMESSAGEPACKET_H
#define GROUPMESSAGEPACKET_H

#include "BasePacket.h"
#include <string>

class GroupMessagePacket : public BasePacket {
public:
    GroupMessagePacket() : BasePacket(PacketType::GROUP_MESSAGE) {}

    // 그룹 메시지를 설정
    void setGroupMessage(const std::string& message) {
        std::vector<uint8_t> messageData(message.begin(), message.end());
        setData(messageData);
    }

    // 그룹 메시지를 가져오기
    std::string getGroupMessage() const {
        return std::string(data.begin(), data.end());
    }
};

#endif // GROUPMESSAGEPACKET_H