#pragma once

#include <iostream>
#include <string>
#include "socket.h"

class Cliente {
private:
    std::string correo;
    std::string contrasenya;
    SocketCliente socketCliente;

public:
    Cliente();
    void iniciarSesion();
    void mainLoop();
    int menuEstudiante();
    int menuProfesorado();
};