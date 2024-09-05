#include <iostream>
#include <string>
#include <ws2tcpip.h>  //InetPton �Լ�
#include <winsock2.h>  // Windows ���� ���
#pragma comment(lib, "ws2_32.lib")  // WinSock ���̺귯�� ��ũ

//#define _WINSOCK_DEPRECATED_NO_WARNINGS

int main() {
    //SetConsoleOutputCP(CP_UTF8);
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);  // WinSock �ʱ�ȭ

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
        std::cerr << "���� ���� ����" << std::endl;
        WSACleanup();
        return 1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    // ���� IP �ּ� ����
    //serv_addr.sin_addr.s_addr = inet_addr("172.28.80.1");

    //SDL�˻� ����
    //#include <ws2tcpip.h>  //InetPton �Լ�
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("\n ��ȿ���� ���� �ּ�/�������� �ʴ� �ּ� \n");
        return -1;
    }

    //TCP
    /*
    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == SOCKET_ERROR) {
        std::cerr << "���� ����" << std::endl;
        closesocket(sock);
        WSACleanup();
        return 1;
    }
    */

    std::string input;

    while (true)
    {
        std::cout << "�޽��� �Է� ('exit' �Է� �� ����): ";
        std::getline(std::cin, input);  // ����ڷκ��� �Է¹���

        if (input == "exit") {
            break;  // 'exit' �Է� �� �ݺ��� Ż��
        }

        if (input.length() > 0)
        {
            //send(sock, input.c_str(), input.size(), 0);
            if (sendto(sock, input.c_str(), input.size(), 0, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == SOCKET_ERROR)
            {
                std::cerr << "�����κ��� �����͸� ������ �� ���� �߻�" << std::endl;
                break;
            }

            std::cout << "������ �޽��� ����: " << input << std::endl;


            // ���� �ʱ�ȭ
            memset(buffer, 0, sizeof(buffer));
            serverAddrLen = sizeof(serv_addr);

            int valread = recvfrom(sock, buffer, 1024, 0, (struct sockaddr*)&serv_addr, &serverAddrLen);

            if (valread > 0) {
                buffer[valread] = '\0';  // ���� ���� �� ���� �߰�
                std::cout << "�����κ��� ���� �޽���: " << buffer << std::endl;
            }
            else {
                std::cerr << "�����κ��� �����͸� �д� �� ���� �߻�" << std::endl;
                break;  // ���� �߻� �� �ݺ��� Ż��
            }
        }
    }

    closesocket(sock);
    WSACleanup();  // WinSock ����
    return 0;
}
