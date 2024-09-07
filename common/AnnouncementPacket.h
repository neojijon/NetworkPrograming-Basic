#ifndef ANNOUNCEMENTPACKET_H
#define ANNOUNCEMENTPACKET_H

#include "BasePacket.h"
#include <string>

class AnnouncementPacket : public BasePacket {
public:
    AnnouncementPacket() : BasePacket(PacketType::ANNOUNCEMENT) {}

    // 공지 메시지를 설정
    void setAnnouncement(const std::string& message) {
        std::vector<uint8_t> messageData(message.begin(), message.end());
        setData(messageData);
    }

    // 공지 메시지를 가져오기
    std::string getAnnouncement() const {
        return std::string(data.begin(), data.end());
    }
};

#endif // ANNOUNCEMENTPACKET_H