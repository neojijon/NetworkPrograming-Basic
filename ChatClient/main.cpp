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