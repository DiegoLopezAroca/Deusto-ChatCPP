#pragma once

#include <iostream>
#include <string>
#include "socket.h"

#define MAX_LINE 2

class Cliente {
private:
    std::string mensajeInstruccion;
    char correo[MAX_BUFFER_SIZE];
    char contrasenya[MAX_BUFFER_SIZE];
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
    void solicitarCorreoYContrasenya(char* correo, char* contrasenya);
    void opcionSalir();
    void ingresarCorreo(char* correo);
    void ingresarContrasenya(char* contrasenya);
    void pantallaCrearNuevoGrupo();
    char pantallaPerfil(char *correo, char* nombre, char *dni);
    void pantallaChatConversacion(int idConversacion);
};