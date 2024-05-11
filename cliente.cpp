#include "cliente.h"

using namespace std;

// Esto no es realmente funcional es para que podamos ver que el socket se crea cuando contruyamos un objeto cliente.

Cliente::Cliente() : socketCliente() {}

void Cliente::iniciarSesion() {

    printf("================================\n");
    printf("          Deusto Chat           \n");
    printf("================================\n");

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
