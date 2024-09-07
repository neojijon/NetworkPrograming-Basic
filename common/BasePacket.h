#ifndef BASEPACKET_H
#define BASEPACKET_H

#include <cstdint>
#include <cstring>
#include <iostream>
#include <vector>

// 패킷 타입 정의
enum class PacketType {
    CHAT_MESSAGE = 0x01,
    GROUP_MESSAGE = 0x02,
    ANNOUNCEMENT = 0x03,
    PRIVATE_MESSAGE = 0x04
};

// 기본 패킷 헤더 클래스
class PacketHeader {
public:
    PacketType packetType;
    uint32_t dataLength;
    uint32_t senderID;
    uint32_t receiverID;

    PacketHeader(PacketType type = PacketType::CHAT_MESSAGE)
        : packetType(type), dataLength(0), senderID(0), receiverID(0) {}

    // 패킷 헤더를 직렬화
    std::vector<uint8_t> serialize() const {
        std::vector<uint8_t> buffer(sizeof(PacketHeader));
        std::memcpy(buffer.data(), this, sizeof(PacketHeader));
        return buffer;
    }

    // 패킷 헤더를 역직렬화
    static PacketHeader deserialize(const uint8_t* data) {
        PacketHeader header;
        std::memcpy(&header, data, sizeof(PacketHeader));
        return header;
    }
};

// 기본 패킷 클래스
class BasePacket {
public:
    PacketHeader header;
    std::vector<uint8_t> data;

    BasePacket(PacketType type) : header(type) {}

    virtual ~BasePacket() {}

    // 패킷을 직렬화 (헤더 + 데이터)
    virtual std::vector<uint8_t> serialize() const {
        std::vector<uint8_t> buffer = header.serialize();
        buffer.insert(buffer.end(), data.begin(), data.end());
        return buffer;
    }

    // 데이터 설정
    virtual void setData(const std::vector<uint8_t>& newData) {
        data = newData;
        header.dataLength = (uint32_t)data.size();
    }

    // 데이터 가져오기
    const std::vector<uint8_t>& getData() const {
        return data;
    }
};

#endif // BASEPACKET_H
