#ifndef SOCKETHANDLER_H
#define SOCKETHANDLER_H

#include <iostream>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

class SocketHandler {
protected:
    SOCKET socketDescriptor;

public:
    SocketHandler() : socketDescriptor(INVALID_SOCKET) {}

    virtual ~SocketHandler() {
        closesocket(socketDescriptor);
    }

    // 소켓 초기화
    bool initializeSocket();

    // 소켓 생성
    bool createSocket();

    // 소켓 닫기
    void closeSocket();

    // 데이터를 보내는 함수
    bool sendData(const char* data, int dataSize);

    // 데이터를 수신하는 함수
    bool receiveData(char* buffer, int bufferSize);
};

#endif // SOCKETHANDLER_H