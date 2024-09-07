#include "ChatServer.h"

int main(int argc, char* argv[]) 
{
    // ��Ʈ ��ȣ�� �⺻���� ����
    int port = 8888;

    // ����� ���� ó��
    if (argc > 1) {
        port = std::atoi(argv[1]);
    }

    ChatServer server;

    if (server.startServer(8888)) 
    {

        std::thread acceptThread(&ChatServer::acceptClient, &server);
        acceptThread.join();
    }
    else
    {
        std::cerr << "Failed to start server" << std::endl;
    }

    return 0;
}