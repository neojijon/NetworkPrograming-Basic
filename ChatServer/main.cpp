#include "ChatServer.h"

int main() {
    ChatServer server;
    if (server.startServer(8888)) {
        while (true) {
            server.acceptClient();
            server.receiveAndBroadcast();
        }
    }
    return 0;
}



/*
// ���� ���� ����
int main() {
    WSADATA wsa;
    SOCKET serverSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    int clientAddrLen = sizeof(clientAddr);
    char buffer[BUFFER_SIZE];

    // ���� �ʱ�ȭ
    WSAStartup(MAKEWORD(2, 2), &wsa);

    // ���� ���� ����
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == INVALID_SOCKET) {
        printf("Socket creation failed\n");
        return 1;
    }

    // ���� �ּ� ����ü ����
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(SERVER_PORT);

    // ���� ���� ���ε�
    if (bind(serverSocket, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        printf("Bind failed\n");
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    // ���� ���� ������
        //Ŭ���̾�Ʈ ���Ӵ��
    if (listen(serverSocket, 3) == SOCKET_ERROR) {
        std::cerr << "������ ����" << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    std::cout << "Server is listening on port ��Ʈ: " << SERVER_PORT << std::endl;

    while (1) {
        clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddr, &clientAddrLen);
        if (clientSocket == INVALID_SOCKET) {
            std::cerr << "���� ���� ����" << std::endl;
            closesocket(serverSocket);
            WSACleanup();
            return 1;
        }

        // Ŭ���̾�Ʈ�� ��Ŷ ����
        int recvSize = recv(clientSocket, buffer, BUFFER_SIZE, 0);
        if (recvSize == SOCKET_ERROR) {
            std::cerr << "���� ��Ŷ ���� ����" << std::endl;
            closesocket(serverSocket);
            WSACleanup();
            return 1;
        }

        std::cout << "Ŭ���̾�Ʈ �����!" << std::endl;

        std::lock_guard<std::mutex> lock(clientsMutex);
        clients.push_back(clientSocket);

        //������ ���� Ŭ���̾�Ʈ �޼���ó��
        std::thread clientThread(handleReceivedPacket, clientSocket);
        clientThread.detach();
    }

    closesocket(serverSocket);
    WSACleanup();
    return 0;
}
*/