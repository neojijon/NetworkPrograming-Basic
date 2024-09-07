#include "ChatClient.h"
#include <iostream>
#include <string>


int main(int argc, char* argv[])
{
    // 기본값 설정
    std::string serverIP = "127.0.0.1";
    int port = 8888;

    // 명령줄 인자 처리
    if (argc > 1) {
        serverIP = argv[1];
    }
    if (argc > 2) {
        port = std::atoi(argv[2]);
    }


    ChatClient client;
    if (client.connectToServer(serverIP, port))
    {
        uint32_t userID = 1;  // 클라이언트에서 지정하는 유저 ID
        std::string message;

        while (true) {
            std::cout << "Enter message: ";
            std::getline(std::cin, message);

            if (message == "/quit") break;

            client.sendChatMessage(userID, message);
        }
    }
    else {
        std::cerr << "Failed to connect to server" << std::endl;
    }

    return 0;
}


/*
int main() {
   

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
}
*/