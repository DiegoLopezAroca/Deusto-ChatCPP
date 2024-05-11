#include <iostream>
#include "socket.h"
#include "menu.h"

#define LONGITUD_DE_ENTRADA 256

int main(int argc, char *argv[]) {

    iniciarSocketCliente(argc, argv);

    char correo[LONGITUD_DE_ENTRADA];
    char contrasenya[LONGITUD_DE_ENTRADA];

    //iniciarSesion(correo, contrasenya);

    return 0;
}