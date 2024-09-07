#include "ChatServer.h"

int main(int argc, char* argv[]) 
{
    // 포트 번호는 기본값을 설정
    int port = 8888;

    // 명령줄 인자 처리
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