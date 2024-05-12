#include <stdio.h>
#include <iostream>
#include <winsock2.h>
#include "socket.h"

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 6000

using namespace std;

SocketCliente::SocketCliente() {
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        cout << "Failed to initialize Winsock. Error Code: " << WSAGetLastError() << endl;
        exit(EXIT_FAILURE);
    }

    if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        cout << "Could not create socket : " << WSAGetLastError() << endl;
        WSACleanup();
        exit(EXIT_FAILURE);
    }

    server.sin_addr.s_addr = inet_addr(SERVER_IP);
    server.sin_family = AF_INET;
    server.sin_port = htons(SERVER_PORT);

    if (connect(s, (struct sockaddr*) &server, sizeof(server)) == SOCKET_ERROR) {
        cout << "Connection error: " << WSAGetLastError() << endl;
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
    int bytesEnviados = send(s, mensaje, strlen(mensaje), 0);
    if (bytesEnviados == SOCKET_ERROR) {
        // Manejar el error si la función send falla
        cout << "Error al enviar el mensaje: " << WSAGetLastError() << endl;
    }
}

void SocketCliente::recibirMensaje(char *buffer) {
    int bytesRecibidos = recv(s, buffer, MAX_BUFFER_SIZE - 1, 0); // -1 para dejar espacio para el carácter nulo
    if (bytesRecibidos == SOCKET_ERROR) {
        // Manejar el error si la función recv falla
        cout << "Error al recibir el mensaje: " << WSAGetLastError() << endl;
    } else {
        // Agregar un carácter nulo al final del buffer para asegurar que sea una cadena válida
        buffer[bytesRecibidos] = '\0';
    }
}

bool SocketCliente::recibirRespuestaAutenticacion() {
    bool autenticado = false; // Inicializar como falso en caso de error
    char buffer[sizeof(bool)]; // Buffer para almacenar el resultado de la autenticación
    recibirMensaje(buffer); // Recibir el resultado de la autenticación
    memcpy(&autenticado, buffer, sizeof(bool)); // Copiar el resultado al booleano autenticado
    return autenticado;
}