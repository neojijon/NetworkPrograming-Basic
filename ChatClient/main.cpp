#include "ChatClient.h"

int main() {
    ChatClient client;
    if (client.connectToServer("127.0.0.1", 8888)) 
    {
        client.sendMessage(1, "Hello, Server!");

        while (true) 
        {
            client.receiveMessage();
        }
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