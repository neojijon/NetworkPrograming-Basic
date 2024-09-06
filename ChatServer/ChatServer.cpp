#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <thread>
#include <vector>
#include <mutex>
#include "../common/Packet.h"

#pragma comment(lib, "ws2_32.lib")

#define SERVER_PORT 8888
#define MAX_CLIENTS 100
#define BUFFER_SIZE 1024

std::vector<SOCKET> clients;
std::mutex clientsMutex;

// 서버 메인 루프
int main() {
    WSADATA wsa;
    SOCKET serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    int clientAddrLen = sizeof(clientAddr);
    char buffer[BUFFER_SIZE];

    // 윈속 초기화
    WSAStartup(MAKEWORD(2, 2), &wsa);

    // 서버 소켓 생성
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET) {
        printf("Socket creation failed\n");
        return 1;
    }

    // 서버 주소 구조체 설정
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(SERVER_PORT);

    // 서버 소켓 바인딩
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        printf("Bind failed\n");
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    // 서버 소켓 리스닝
        //클라이언트 접속대기
    if (listen(serverSocket, 3) == SOCKET_ERROR) {
        std::cerr << "리스닝 실패" << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }
    
    std::cout << "Server is listening on port 포트: " << SERVER_PORT << std::endl;    

    while (1) {
        clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrLen);
        if (clientSocket == INVALID_SOCKET) {
            std::cerr << "연결 수락 실패" << std::endl;
            closesocket(serverSocket);
            WSACleanup();
            return 1;
        }

        // 클라이언트의 패킷 수신
        int recvSize = recv(clientSocket, buffer, BUFFER_SIZE, 0);
        if (recvSize == SOCKET_ERROR) {
            std::cerr << "연결 패킷 수신 실패" << std::endl;
            closesocket(serverSocket);
            WSACleanup();
            return 1;
        }

        std::cout << "클라이언트 연결됨!" << std::endl;

        std::lock_guard<std::mutex> lock(clientsMutex);
        clients.push_back(clientSocket);

        //스래드 생성 클라이언트 메세지처리		
        std::thread clientThread(handleReceivedPacket, clientSocket);
        clientThread.detach();
    }

    closesocket(serverSocket);
    WSACleanup();
    return 0;
}