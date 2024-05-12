#include <iostream>
#include "socket.h"
#include "menu.h"
#include "cliente.h"

int main(int argc, char *argv[]) {

    Cliente cliente;
    cliente.iniciarSesion();
    cliente.mainLoop();

    return 0;
}