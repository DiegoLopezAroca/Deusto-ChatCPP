#include <stdio.h>
#include <winsock2.h>
#include "socket.h"

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 6000


SocketCliente::SocketCliente() {
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("Failed to initialize Winsock. Error Code: %d", WSAGetLastError());
        exit(EXIT_FAILURE);
    }

    if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        printf("Could not create socket : %d", WSAGetLastError());
        WSACleanup();
        exit(EXIT_FAILURE);
    }

    server.sin_addr.s_addr = inet_addr(SERVER_IP);
    server.sin_family = AF_INET;
    server.sin_port = htons(SERVER_PORT);

    if (connect(s, (struct sockaddr*) &server, sizeof(server)) == SOCKET_ERROR) {
        printf("Connection error: %d", WSAGetLastError());
        closesocket(s);
        WSACleanup();
        exit(EXIT_FAILURE);
    }
}

SocketCliente::~SocketCliente() {
    closesocket(s);
    WSACleanup();
}

void SocketCliente::enviarMensaje(const char *mensaje) {
    send(s, mensaje, strlen(mensaje), 0);
}

void SocketCliente::recibirMensaje(char *buffer) {
    recv(s, buffer, MAX_BUFFER_SIZE, 0);
}