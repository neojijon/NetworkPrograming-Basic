#include "ChatClient.h"
#include <iostream>
#include <string>


int main(int argc, char* argv[])
{
    // �⺻�� ����
    std::string serverIP = "127.0.0.1";
    int port = 8888;

    // ����� ���� ó��
    if (argc > 1) {
        serverIP = argv[1];
    }
    if (argc > 2) {
        port = std::atoi(argv[2]);
    }


    ChatClient client;
    if (client.connectToServer(serverIP, port))
    {
        uint32_t userID = 1;  // Ŭ���̾�Ʈ���� �����ϴ� ���� ID
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

    // �α��� ��û ��Ŷ ����    
    sendLoginPacket(clientSocket, username, userID);

    //������ ���� Ŭ���̾�Ʈ �޼���ó��		
    std::thread clientThread(handleReceivedPacket, clientSocket);
    clientThread.detach();


    std::string message;

    while (1) {
        // �޽��� �Է�
        std::cout << "�޽��� �Է� ('exit' �Է� �� ����): ";
        std::getline(std::cin, message);  // ����ڷκ��� �Է¹���      

        if (message == "exit") {
            break;  // 'exit' �Է� �� �ݺ��� Ż��
        }

        //�Ϲ�ä�� ��Ŷ
        sendChatPacket(clientSocket, message.c_str(), userID, 0);
    }
}
*/