#pragma once

#include <iostream>
#include <string>
#include "socket.h"

#define MAX_LINE 2

class Cliente {
private:
    std::string mensajeInstruccion;
    std::string correo;
    std::string contrasenya;
    SocketCliente socketCliente;

public:
    Cliente();
    void iniciarSesion();
    void mainLoop();
    int menuEstudiante();
    int menuProfesorado();
    void clearIfNeeded(char *str, int max_line);
    int recogerEntero();
    void pantallaChatIniciados();
    void pantallaTusGruposAsignaturas();
    void pantallaTusProfesores();
    void pantallaIniciarNuevaConversacion();
    void solicitarCorreoYContrasenya(char* correoNuevo, char* contrasenyaNueva);
    void opcionSalir();
    void ingresarCorreo(char* correo);
    void ingresarContrasenya(char* contrasenya);
    void pantallaCrearNuevoGrupo();
    void pantallaPerfilProfesor(char *correo, char* nombre, char *dni);
};