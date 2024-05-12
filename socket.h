#pragma once

#include <winsock2.h>
#include <stdio.h>
#include <string.h>
#include <iostream>

#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 6000
#define MAX_BUFFER_SIZE 1024

class SocketCliente {
private:
    WSADATA wsaData;
    SOCKET s;
    struct sockaddr_in server;

public:
    SocketCliente();
    ~SocketCliente();

    void enviarMensaje(const char *mensaje);
    void recibirMensaje(char *buffer);
    bool recibirRespuestaAutenticacion();
};
