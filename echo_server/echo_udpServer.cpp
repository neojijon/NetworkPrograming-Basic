#include <iostream>
#include <string>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")

int main()
{
	//윈속 초기화
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	SOCKET server_fd;
	struct sockaddr_in serveraddress, clientaddr;
	int addrlen = sizeof(serveraddress);
	int clientaddrLen = sizeof(clientaddr);
	char buffer[1024] = { 0 };
	const int PORT = 8080;

	//소켓생성
	server_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (server_fd == INVALID_SOCKET) {
		std::cerr << "소켓 실패" << std::endl;
		WSACleanup();
		return 1;
	}

	serveraddress.sin_family = AF_INET;
	serveraddress.sin_addr.s_addr = INADDR_ANY;
	serveraddress.sin_port = htons(PORT);

	//소켓 바인딩
	if (bind(server_fd, (struct sockaddr*)&serveraddress, sizeof(serveraddress)) == SOCKET_ERROR) {
		std::cerr << "바인딩 실패" << std::endl;
		closesocket(server_fd);
		WSACleanup();
		return 1;
	}

	//UDP 경우
	// listen 부분이 없음.

	std::cout << "에코 서버가 시작되었습니다. 포트: " << PORT << std::endl;

	
	while (true)
	{	
		memset(buffer, 0, sizeof(buffer));

		//UDP함수 recvfrom
		int valread = recvfrom(server_fd, buffer, 1024, 0, (struct sockaddr*)&clientaddr, &clientaddrLen);


		if (valread > 0) {
			std::cout << "클라이언트로부터 받은 메시지: " << buffer << std::endl;
			//UDP함수 sendto
			sendto(server_fd, buffer, valread, 0, (struct sockaddr*)&clientaddr, clientaddrLen);
			std::cout << "에코 메시지 전송 완료" << std::endl;
		}
		else if (valread == 0) {
			std::cout << "클라이언트 연결 종료" << std::endl;
			break;  // 클라이언트 연결 종료
		}
		else {
			std::cerr << "recvfrom() 실패" << std::endl;
			break;  // 오류 발생 시 종료
		}		
	}

	closesocket(server_fd);

	WSACleanup();
	return 0;
}