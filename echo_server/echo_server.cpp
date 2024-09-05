// echo_server.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
//#include "stdafx.h"
#include <iostream>
#include <string>
#include <WinSock2.h>
#include <thread>
#include <vector>
#include <mutex>

#pragma comment(lib, "ws2_32.lib")


#define SERVER_PORT 8080
#define BUFFER_SIZE 1024


std::vector<SOCKET> clients;
std::mutex clientsMutex;


void broadcast_message(const std::string message)
{
	std::lock_guard<std::mutex> lock(clientsMutex);
	for (SOCKET clientsocket : clients) {
		send(clientsocket, message.c_str(), (int)message.size(), 0);
	}
}



void handleClient(SOCKET clientSocket)
{	
	char buffer[BUFFER_SIZE] = { 0 };

	while (true)
	{
		int valread = recv(clientSocket, buffer, BUFFER_SIZE, 0);

		std::string message(buffer);

		if (valread > 0) {
			std::cout << "클라이언트로부터 받은 메시지: " << buffer << std::endl;

			// b/ msg [pid]

			if (message.rfind("/b ", 0) == 0)
			{
				std::string broadcastMessage = message.substr(3);
				broadcast_message(broadcastMessage);
				std::cout << "Broadcasting 메시지 전송 완료" << std::endl;
			}
			else
			{
				send(clientSocket, buffer, valread, 0);
				std::cout << "에코 메시지 전송 완료" << std::endl;
			}			
		}
		else if (valread == 0) {
			std::cout << "클라이언트 연결 종료" << std::endl;
			break;  // 클라이언트 연결 종료
		}
		else {
			std::cerr << "recv() 실패" << std::endl;
			break;  // 오류 발생 시 종료
		}
	}

	std::cout << "클라이언트 소캣 종료" << std::endl;
	closesocket(clientSocket);
}


int main()
{
	//SetConsoleOutputCP(CP_UTF8);
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	SOCKET server_fd, client_socket;
	struct sockaddr_in address;
	int addrlen = sizeof(address);
	
	server_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (server_fd == INVALID_SOCKET) {
		std::cerr << "소켓 실패" << std::endl;
		WSACleanup();
		return 1;
	}

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(SERVER_PORT);

	//소캣바인딩
	if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) == SOCKET_ERROR) {
		std::cerr << "바인딩 실패" << std::endl;
		closesocket(server_fd);
		WSACleanup();
		return 1;
	}

	//클라이언트 접속대기
	if (listen(server_fd, 3) == SOCKET_ERROR) {
		std::cerr << "리스닝 실패" << std::endl;
		closesocket(server_fd);
		WSACleanup();
		return 1;
	}

	std::cout << "에코 서버가 시작되었습니다. 포트: " << SERVER_PORT << std::endl;

	while (true) {
		client_socket = accept(server_fd, (struct sockaddr*)&address, &addrlen);
		if (client_socket == INVALID_SOCKET) {
			std::cerr << "연결 수락 실패" << std::endl;
			closesocket(server_fd);
			WSACleanup();
			return 1;
		}

		std::cout << "클라이언트 연결됨!" << std::endl;

		std::lock_guard<std::mutex> lock(clientsMutex);
		clients.push_back(client_socket);

		//스래드 생성 클라이언트 메세지처리		
		std::thread clientThread(handleClient, client_socket);
		clientThread.detach();
	}

	closesocket(server_fd);

	WSACleanup();
	return 0;

}
