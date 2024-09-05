#include <iostream>
#include <string>
#include <ws2tcpip.h>  //InetPton �Լ�
#include <winsock2.h>  // Windows ���� ���
#include <process.h>   //_getpid() ���
#include <thread>

#pragma comment(lib, "ws2_32.lib")  // WinSock ���̺귯�� ��ũ

//#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define ECHO_PORT 8080
#define BUFFER_SIZE 1024


void receive_message(SOCKET connectSocket)
{
    while (true)
    {
        char recvbuffer[BUFFER_SIZE] = { 0 };

        int clientAddLen = recv(connectSocket, recvbuffer, BUFFER_SIZE, 0);
        if (clientAddLen > 0) {
            recvbuffer[clientAddLen] = '\0';  // ���� ���� �� ���� �߰�
            std::cout << "�����κ��� ���� �޽���: " << recvbuffer << std::endl;
        }
      /*  else if (clientAddLen == 0) {
            std::cout << "�������� ����" << std::endl;
            break;
        }*/
        else {
            std::cerr << "�����κ��� �����͸� �д� �� ���� �߻�" << std::endl;
            break;  // ���� �߻� �� �ݺ��� Ż��
        }
    }    
}



int main() {
    //SetConsoleOutputCP(CP_UTF8);
    WSADATA wsaData;    
    WSAStartup(MAKEWORD(2, 2), &wsaData);  // WinSock �ʱ�ȭ

    SOCKET sock;
    struct sockaddr_in serv_addr;    
    char buffer[BUFFER_SIZE] = { 0 };
    int serverAddrLen,clientAddLen;
   
    //TCP    
    sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    //UDP
    //sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock == INVALID_SOCKET) {
        std::cerr << "���� ���� ����" << std::endl;
        WSACleanup();
        return 1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(ECHO_PORT);
    // ���� IP �ּ� ����
    //serv_addr.sin_addr.s_addr = inet_addr("172.28.80.1");
    
    //SDL�˻� ����
    //#include <ws2tcpip.h>  //InetPton �Լ�
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        printf("\n ��ȿ���� ���� �ּ�/�������� �ʴ� �ּ� \n");
        return -1;        
    }
    
    //TCP    
    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == SOCKET_ERROR) {
        std::cerr << "���� ����" << std::endl;
        closesocket(sock);
        WSACleanup();
        return 1;
    }
    

    std::string input;

    int client_id = _getpid();
    std::cout << "Ŭ���̾�Ʈ id: " << client_id << "�� ������ ����Ǿ����ϴ�." << std::endl;

    //���� �޼����� ó���ϴ� ������ ����   
    std::thread clientThread(receive_message, sock);
    clientThread.detach();


    while (true)
    {
        std::cout << "�޽��� �Է� ('exit' �Է� �� ����): ";
        std::getline(std::cin, input);  // ����ڷκ��� �Է¹���

        if (input == "exit") {
            break;  // 'exit' �Է� �� �ݺ��� Ż��
        }

        if (input.length() > 0)
        {
            std::string fullMassage = input + ": [" + std::to_string(client_id) + "]" + "\n";

            send(sock, fullMassage.c_str(), (int)fullMassage.size(), 0);
            std::cout << "������ �޽��� ����: " << input << std::endl;

            //������� �ٲ�.
            //// ���� �ʱ�ȭ
            //memset(buffer, 0, sizeof(buffer));
            //serverAddrLen = sizeof(serv_addr);

            //clientAddLen = recv(sock, buffer, BUFFER_SIZE, 0);
            //if (clientAddLen > 0) {
            //    buffer[clientAddLen] = '\0';  // ���� ���� �� ���� �߰�
            //    std::cout << "�����κ��� ���� �޽���: " << buffer << std::endl;
            //}
            //else {
            //    std::cerr << "�����κ��� �����͸� �д� �� ���� �߻�" << std::endl;
            //    break;  // ���� �߻� �� �ݺ��� Ż��
            //}
        }
    }

    closesocket(sock);
    WSACleanup();  // WinSock ����
    return 0;
}
