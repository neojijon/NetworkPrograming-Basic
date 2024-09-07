#include "SocketHandler.h"

// 소켓 초기화
bool SocketHandler::initializeSocket() {
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        std::cerr << "WSAStartup failed: " << WSAGetLastError() << std::endl;
        return false;
    }
    return true;
}

// 소켓 생성
bool SocketHandler::createSocket() {
    socketDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (socketDescriptor == INVALID_SOCKET) {
        std::cerr << "Socket creation failed: " << WSAGetLastError() << std::endl;
        return false;
    }
    return true;
}

// 소켓 닫기
void SocketHandler::closeSocket() {
    closesocket(socketDescriptor);
    WSACleanup();
}

// 데이터를 보내는 함수
bool SocketHandler::sendData(const char* data, int dataSize) {
    if (send(socketDescriptor, data, dataSize, 0) == SOCKET_ERROR) {
        std::cerr << "Send failed: " << WSAGetLastError() << std::endl;
        return false;
    }
    return true;
}

// 데이터를 수신하는 함수
bool SocketHandler::receiveData(char* buffer, int bufferSize) {
    int receivedBytes = recv(socketDescriptor, buffer, bufferSize, 0);
    if (receivedBytes == SOCKET_ERROR) {
        std::cerr << "Receive failed: " << WSAGetLastError() << std::endl;
        return false;
    }
    buffer[receivedBytes] = '\0'; // 문자열로 처리
    return true;
}