#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <thread>
#include <vector>
#include <mutex>
#include <ws2tcpip.h>
#include "../common/Packet.h"

#pragma comment(lib, "ws2_32.lib")

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 8888
#define BUFFER_SIZE 1024


int main() {
    WSADATA wsa;
    SOCKET clientSocket;
    struct sockaddr_in serverAddr;
    char buffer[BUFFER_SIZE];
    uint32_t userID = (uint32_t)_getpid(); // 예시 유저 ID
    const char* username = "testuser" + rand(); // 예시 유저 이름

    // 윈속 초기화
    WSAStartup(MAKEWORD(2, 2), &wsa);

    // 클라이언트 소켓 생성
    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == INVALID_SOCKET) {
        printf("Socket creation failed\n");
        return 1;
    }

    // 서버 주소 설정
    serverAddr.sin_family = AF_INET;
    //serverAddr.sin_addr.s_addr = inet_addr(SERVER_IP);
    inet_pton(AF_INET, SERVER_IP, &serverAddr.sin_addr);

    serverAddr.sin_port = htons(SERVER_PORT);

    // 서버에 연결
    if (connect(clientSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        printf("Connection failed\n");
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }

    printf("Connected to server\n");

    // 로그인 요청 패킷 전송    
    sendLoginPacket(clientSocket, username, userID);

    //스래드 생성 클라이언트 메세지처리		
    std::thread clientThread(handleReceivedPacket, clientSocket);
    clientThread.detach();

 
    std::string message;

    while (1) {
        // 메시지 입력
        std::cout << "메시지 입력 ('exit' 입력 시 종료): ";
        std::getline(std::cin, message);  // 사용자로부터 입력받음      

        if (message == "exit") {
            break;  // 'exit' 입력 시 반복문 탈출
        }

        //일반채팅 패킷
        sendChatPacket(clientSocket, message.c_str(), userID, 0);
    }

    closesocket(clientSocket);
    WSACleanup();
    return 0;
}