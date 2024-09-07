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

    // ���� �ʱ�ȭ
    bool initializeSocket();

    // ���� ����
    bool createSocket();

    // ���� �ݱ�
    void closeSocket();

    // �����͸� ������ �Լ�
    bool sendData(const char* data, int dataSize);

    // �����͸� �����ϴ� �Լ�
    bool receiveData(char* buffer, int bufferSize);
};

#endif // SOCKETHANDLER_H