#include <iostream>
#include <string>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")

int main()
{
	//���� �ʱ�ȭ
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	SOCKET server_fd;
	struct sockaddr_in serveraddress, clientaddr;
	int addrlen = sizeof(serveraddress);
	int clientaddrLen = sizeof(clientaddr);
	char buffer[1024] = { 0 };
	const int PORT = 8080;

	//���ϻ���
	server_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (server_fd == INVALID_SOCKET) {
		std::cerr << "���� ����" << std::endl;
		WSACleanup();
		return 1;
	}

	serveraddress.sin_family = AF_INET;
	serveraddress.sin_addr.s_addr = INADDR_ANY;
	serveraddress.sin_port = htons(PORT);

	//���� ���ε�
	if (bind(server_fd, (struct sockaddr*)&serveraddress, sizeof(serveraddress)) == SOCKET_ERROR) {
		std::cerr << "���ε� ����" << std::endl;
		closesocket(server_fd);
		WSACleanup();
		return 1;
	}

	//UDP ���
	// listen �κ��� ����.

	std::cout << "���� ������ ���۵Ǿ����ϴ�. ��Ʈ: " << PORT << std::endl;

	
	while (true)
	{	
		memset(buffer, 0, sizeof(buffer));

		//UDP�Լ� recvfrom
		int valread = recvfrom(server_fd, buffer, 1024, 0, (struct sockaddr*)&clientaddr, &clientaddrLen);


		if (valread > 0) {
			std::cout << "Ŭ���̾�Ʈ�κ��� ���� �޽���: " << buffer << std::endl;
			//UDP�Լ� sendto
			sendto(server_fd, buffer, valread, 0, (struct sockaddr*)&clientaddr, clientaddrLen);
			std::cout << "���� �޽��� ���� �Ϸ�" << std::endl;
		}
		else if (valread == 0) {
			std::cout << "Ŭ���̾�Ʈ ���� ����" << std::endl;
			break;  // Ŭ���̾�Ʈ ���� ����
		}
		else {
			std::cerr << "recvfrom() ����" << std::endl;
			break;  // ���� �߻� �� ����
		}		
	}

	closesocket(server_fd);

	WSACleanup();
	return 0;
}