#ifndef ANNOUNCEMENTPACKET_H
#define ANNOUNCEMENTPACKET_H

#include "BasePacket.h"
#include <string>

class AnnouncementPacket : public BasePacket {
public:
    AnnouncementPacket() : BasePacket(PacketType::ANNOUNCEMENT) {}

    // ���� �޽����� ����
    void setAnnouncement(const std::string& message) {
        std::vector<uint8_t> messageData(message.begin(), message.end());
        setData(messageData);
    }

    // ���� �޽����� ��������
    std::string getAnnouncement() const {
        return std::string(data.begin(), data.end());
    }
};

#endif // ANNOUNCEMENTPACKET_H