#include "SocketHandler.h"

// ���� �ʱ�ȭ
bool SocketHandler::initializeSocket() {
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        std::cerr << "WSAStartup failed: " << WSAGetLastError() << std::endl;
        return false;
    }
    return true;
}

// ���� ����
bool SocketHandler::createSocket() {
    socketDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (socketDescriptor == INVALID_SOCKET) {
        std::cerr << "Socket creation failed: " << WSAGetLastError() << std::endl;
        return false;
    }
    return true;
}

// ���� �ݱ�
void SocketHandler::closeSocket() {
    closesocket(socketDescriptor);
    WSACleanup();
}

// �����͸� ������ �Լ�
bool SocketHandler::sendData(const char* data, int dataSize) {
    if (send(socketDescriptor, data, dataSize, 0) == SOCKET_ERROR) {
        std::cerr << "Send failed: " << WSAGetLastError() << std::endl;
        return false;
    }
    return true;
}

// �����͸� �����ϴ� �Լ�
bool SocketHandler::receiveData(char* buffer, int bufferSize) {
    int receivedBytes = recv(socketDescriptor, buffer, bufferSize, 0);
    if (receivedBytes == SOCKET_ERROR) {
        std::cerr << "Receive failed: " << WSAGetLastError() << std::endl;
        return false;
    }
    buffer[receivedBytes] = '\0'; // ���ڿ��� ó��
    return true;
}