#include "cliente.h"

using namespace std;

// Esto no es realmente funcional es para que podamos ver que el socket se crea cuando contruyamos un objeto cliente.

Cliente::Cliente() : socketCliente() {}

void Cliente::iniciarSesion() {

    cout << ("================================\n");
    cout << ("          Deusto Chat           \n");
    cout << ("================================\n");

    cout << "Correo electronico (@opendeusto.es): ";
    getline(cin, correo);

    cout << "Contrasenya: ";
    getline(cin, contrasenya);

    // Enviar correo y contraseña al servidor para iniciar sesión
    socketCliente.enviarMensaje(correo.c_str());
    socketCliente.enviarMensaje(contrasenya.c_str());

    // Esperar la respuesta del servidor y manejarla en consecuencia
    // Puedes implementar la lógica para manejar la respuesta del servidor aquí
}


void Cliente::mainLoop() {
    bool sigo = true;
    // Espera la respuesta del servidor
    bool autenticado = socketCliente.recibirRespuestaAutenticacion();

    if (autenticado) {
        // Continuar con la sesión
        char tipoUsuario[MAX_BUFFER_SIZE];
        socketCliente.recibirMensaje(tipoUsuario);

        // Continuar con la sesión según el tipo de usuario
        if (strcmp(tipoUsuario, "Profesor") == 0) {
            menuProfesorado();
        } else if (strcmp(tipoUsuario, "Estudiante") == 0) {
            menuEstudiante();
        } else {
            cout << "Tipo de usuario no reconocido." << endl;
        }
    } else {
        // Mostrar mensaje de error y finalizar
        cout << "Error de autenticación. Credenciales incorrectas o usuario no existe." << endl;
    }

}

int Cliente::menuProfesorado() {
    system("cls");
    cout << "***MENU PROFESORADO***\n";
    cout << "1. Tu perfil.\n";
    cout << "2. Tus grupos/asignaturas.\n";
    cout << "3. Crear nuevo grupo.\n";
    cout << "4. Chat iniciados.\n";
    cout << "5. Iniciar nueva conversacion.\n";
    cout << "6. SALIR\n\n";
    cout << "Elija una opcion:  ";
    //return recogerEntero();
}

int Cliente::menuEstudiante() {
    system("cls");
    cout << "***MENU ESTUDIANTE***\n";
    cout << "1. Tu perfil.\n";
    cout << "2. Tus profesores.\n";
    cout << "3. Chat iniciados.\n";
    cout << "4. Iniciar nueva conversacion.\n";
    cout << "5. SALIR\n\n";
    cout << "Elija una opcion:  ";
    //return recogerEntero();
}