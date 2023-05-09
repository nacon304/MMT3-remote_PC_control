#define MAX_LEN 512
#include <stdio.h>
#include <string.h>
#include <WinSock2.h>

// g++ server.cpp -o server.exe -lgdi32 -lws2_32
// HBD@657336

int main() {
    WORD verRequested = MAKEWORD(2, 2);
    WSADATA wsaData;

    int wsaErr = WSAStartup(verRequested, &wsaData);
    if (wsaErr != 0) {
        printf("WSAStartup fail - error: %d", wsaErr);
        return 0;
    }
    else
        printf("WSAStartup success - status: %s\n", wsaData.szSystemStatus);

    SOCKET m_socket;
    m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (m_socket == INVALID_SOCKET) {
        printf("socket fail - error: ", WSAGetLastError());
        WSACleanup();
        return 0;
    }
    else
        printf("socket success\n");

    sockaddr_in service;
    service.sin_family = AF_INET;
    service.sin_addr.s_addr = inet_addr("127.0.1.1");
    service.sin_port = htons(12345); // [1024;49151]

    int bindErr = bind(m_socket, (SOCKADDR *)&service, sizeof(service));
    if (bindErr != 0) {
        printf("bind fail - error: %d", WSAGetLastError());
        closesocket(m_socket);
        WSACleanup();
        return 0;
    }
    else
        printf("bind success\n");

    int listenErr = listen(m_socket, 1);
    if (listenErr != 0) {
        printf("listen fail - error: %d", WSAGetLastError());
        closesocket(m_socket);
        WSACleanup();
        return 0;
    }
    else
        printf("listen success\n");

    SOCKET ac_socket;
    printf("Server waiting for Client...\n");

    ac_socket = accept(m_socket, NULL, NULL);
    if (ac_socket == INVALID_SOCKET) {
        printf("conect fail - error: %d", WSAGetLastError());
        closesocket(m_socket);
        WSACleanup();
        return 0;
    }
    else
        printf("connect success\n");

    while (true) {
        // receive msg
        char Rmsg[MAX_LEN] = "";
        int recvBytes;

        do {
            recvBytes = recv(ac_socket, Rmsg, MAX_LEN, 0);
        } while (recvBytes == SOCKET_ERROR);

        if (recvBytes == 0) {
            printf("Connection closed\n");
            break;
        } 
        else {
            // printf("Recv msg = %s - Length: %d\n", Rmsg, recvBytes);
            printf("Client: %s\n", Rmsg);
            // wprintf(L"Client: %s\n", Rmsg);

            if (strcmp(Rmsg, "x") == 0)
                break;

            // send msg
            int sendBytes;
            char Smsg[MAX_LEN] = "";

            // printf("Enter your message: ");
            printf("Server: ");
            scanf("%[^\n]s", Smsg);
            // wscanf(L"%[^\n]s", Smsg);

            fflush(stdin);

            sendBytes = send(ac_socket, Smsg, strlen(Smsg), 0);

            // printf("msg = .%s.\n", Smsg);
            // printf("Send %d/%d bytes\n", sendBytes, strlen(Smsg));
            
            if (strcmp(Smsg, "x") == 0)
                break;
        }
    }

    closesocket(ac_socket);
    printf("Close ac_socket\n");
    closesocket(m_socket);
    printf("Close m_socket\n");
    WSACleanup();

    return 0;
}