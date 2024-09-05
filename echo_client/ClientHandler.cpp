#define WIN32_LEAN_AND_MEAN  // winsock.h의 포함을 방지
#include <iostream>
#include <winsock2.h>
#include <windows.h>
#include <string>

#pragma comment(lib, "ws2_32.lib")

int main(int argc, char* argv[])
{
    if (argc != 2) {
        std::cerr << "Usage: ClientHandler.exe <socket_handle>\n";
        return 1;
    }

    SOCKET client_socket = static_cast<SOCKET>(std::stoull(argv[1]));


    char buffer[1024];
    int bytes_received;

    while ((bytes_received = recv(client_socket, buffer, sizeof(buffer), 0)) > 0) {
        send(client_socket, buffer, bytes_received, 0);
    }

    closesocket(client_socket);
    std::cout << "Client processing done.\n";

    return 0;
}