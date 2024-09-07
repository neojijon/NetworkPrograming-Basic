#ifndef BASEPACKET_H
#define BASEPACKET_H

#include <cstdint>
#include <cstring>
#include <iostream>
#include <vector>

// ��Ŷ Ÿ�� ����
enum class PacketType {
    CHAT_MESSAGE = 0x01,
    GROUP_MESSAGE = 0x02,
    ANNOUNCEMENT = 0x03,
    PRIVATE_MESSAGE = 0x04
};

// �⺻ ��Ŷ ��� Ŭ����
class PacketHeader {
public:
    PacketType packetType;
    uint32_t dataLength;
    uint32_t senderID;
    uint32_t receiverID;

    PacketHeader(PacketType type = PacketType::CHAT_MESSAGE)
        : packetType(type), dataLength(0), senderID(0), receiverID(0) {}

    // ��Ŷ ����� ����ȭ
    std::vector<uint8_t> serialize() const {
        std::vector<uint8_t> buffer(sizeof(PacketHeader));
        std::memcpy(buffer.data(), this, sizeof(PacketHeader));
        return buffer;
    }

    // ��Ŷ ����� ������ȭ
    static PacketHeader deserialize(const uint8_t* data) {
        PacketHeader header;
        std::memcpy(&header, data, sizeof(PacketHeader));
        return header;
    }
};

// �⺻ ��Ŷ Ŭ����
class BasePacket {
public:
    PacketHeader header;
    std::vector<uint8_t> data;

    BasePacket(PacketType type) : header(type) {}

    virtual ~BasePacket() {}

    // ��Ŷ�� ����ȭ (��� + ������)
    virtual std::vector<uint8_t> serialize() const {
        std::vector<uint8_t> buffer = header.serialize();
        buffer.insert(buffer.end(), data.begin(), data.end());
        return buffer;
    }

    // ������ ����
    virtual void setData(const std::vector<uint8_t>& newData) {
        data = newData;
        header.dataLength = (uint32_t)data.size();
    }

    // ������ ��������
    const std::vector<uint8_t>& getData() const {
        return data;
    }
};

#endif // BASEPACKET_H
