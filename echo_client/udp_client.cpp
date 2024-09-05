#include <iostream>
#include <string>
#include <ws2tcpip.h>  //InetPton 함수
#include <winsock2.h>  // Windows 소켓 헤더
#pragma comment(lib, "ws2_32.lib")  // WinSock 라이브러리 링크

//#define _WINSOCK_DEPRECATED_NO_WARNINGS

int main() {
    //SetConsoleOutputCP(CP_UTF8);
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);  // WinSock 초기화

    SOCKET sock;
    struct sockaddr_in serv_addr;
    const int PORT = 8080;
    char buffer[1024] = { 0 };

    int serverAddrLen;

    //TCP
    //sock = socket(AF_INET, SOCK_STREAM, 0);
    //UDP
    sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock == INVALID_SOCKET) {
        std::cerr << "소켓 생성 실패" << std::endl;
        WSACleanup();
        return 1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    // 서버 IP 주소 설정
    //serv_addr.sin_addr.s_addr = inet_addr("172.28.80.1");

    //SDL검사 사용시
    //#include <ws2tcpip.h>  //InetPton 함수
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("\n 유효하지 않은 주소/지원되지 않는 주소 \n");
        return -1;
    }

    //TCP
    /*
    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == SOCKET_ERROR) {
        std::cerr << "연결 실패" << std::endl;
        closesocket(sock);
        WSACleanup();
        return 1;
    }
    */

    std::string input;

    while (true)
    {
        std::cout << "메시지 입력 ('exit' 입력 시 종료): ";
        std::getline(std::cin, input);  // 사용자로부터 입력받음

        if (input == "exit") {
            break;  // 'exit' 입력 시 반복문 탈출
        }

        if (input.length() > 0)
        {
            //send(sock, input.c_str(), input.size(), 0);
            if (sendto(sock, input.c_str(), input.size(), 0, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == SOCKET_ERROR)
            {
                std::cerr << "서버로부터 데이터를 보내는 중 오류 발생" << std::endl;
                break;
            }

            std::cout << "서버로 메시지 전송: " << input << std::endl;


            // 버퍼 초기화
            memset(buffer, 0, sizeof(buffer));
            serverAddrLen = sizeof(serv_addr);

            int valread = recvfrom(sock, buffer, 1024, 0, (struct sockaddr*)&serv_addr, &serverAddrLen);

            if (valread > 0) {
                buffer[valread] = '\0';  // 버퍼 끝에 널 문자 추가
                std::cout << "서버로부터 받은 메시지: " << buffer << std::endl;
            }
            else {
                std::cerr << "서버로부터 데이터를 읽는 중 오류 발생" << std::endl;
                break;  // 오류 발생 시 반복문 탈출
            }
        }
    }

    closesocket(sock);
    WSACleanup();  // WinSock 정리
    return 0;
}
