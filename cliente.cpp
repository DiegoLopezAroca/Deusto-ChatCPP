#include "cliente.h"

using namespace std;

// Esto no es realmente funcional es para que podamos ver que el socket se crea cuando contruyamos un objeto cliente.

Cliente::Cliente() : socketCliente() {}

void Cliente::iniciarSesion() {

    mensajeInstruccion = "LOG_IN";

    socketCliente.enviarMensaje(mensajeInstruccion.c_str());

    cout << ("================================\n");
    cout << ("          Deusto Chat           \n");
    cout << ("================================\n");

    // Enviar correo y contraseña al servidor para iniciar sesión
    cout << "Correo electronico (@opendeusto.es): ";
    cin >> correo;
    socketCliente.enviarMensaje(correo.c_str());

    cout << "Contrasenya: ";
    cin >> contrasenya;
    socketCliente.enviarMensaje(contrasenya.c_str());
}


void Cliente::mainLoop() {
    bool sigo = true;
    char esValido[MAX_BUFFER_SIZE];

    // Espera la respuesta del servidor
    socketCliente.recibirMensaje(esValido);

    if(strcmp(esValido, "TRUE") == 0) {
        sigo = true;
    } else if(strcmp(esValido, "FALSE") == 0) {
        sigo = false;
        cout << "El usuario introducido no existe o la contrasenya es invalida\n";
    }

    char tipoUsuario[MAX_BUFFER_SIZE];
    socketCliente.recibirMensaje(tipoUsuario);
    while (sigo) {
        char correo[MAX_BUFFER_SIZE];
        char nombre[MAX_BUFFER_SIZE];
        char dni[MAX_BUFFER_SIZE];
        // Continuar con la sesión según el tipo de usuario
        if (strcmp(tipoUsuario, "Profesor") == 0) {
            int opcionProfesor = menuProfesorado();
            switch (opcionProfesor) {
                case 1:
                    mensajeInstruccion = "SHOW_PROFILE";
                    socketCliente.enviarMensaje(mensajeInstruccion.c_str());

                    socketCliente.recibirMensaje(correo);
                    socketCliente.recibirMensaje(nombre);
                    socketCliente.recibirMensaje(dni);
                    
                    pantallaPerfilProfesor(correo, nombre, dni);
                    // Aquí debería continuar al menú principal después de mostrar el perfil
                    break;
                case 2:
                    mensajeInstruccion = "NEW_GROUP";
                    socketCliente.enviarMensaje(mensajeInstruccion.c_str());
                    pantallaCrearNuevoGrupo();
                    break;
                case 3:
                    mensajeInstruccion = "STARTED_CHATS";
                    socketCliente.enviarMensaje(mensajeInstruccion.c_str());
                    pantallaChatIniciados();
                    break;
                case 4:
                    mensajeInstruccion = "NEW_CHAT";
                    socketCliente.enviarMensaje(mensajeInstruccion.c_str());
                    pantallaIniciarNuevaConversacion();
                    break;
                case 5:
                    mensajeInstruccion = "MODIFY_USER";
                    socketCliente.enviarMensaje(mensajeInstruccion.c_str());
                    char nuevoCorreo[MAX_BUFFER_SIZE];
                    char nuevaContrasenya[MAX_BUFFER_SIZE];
                    solicitarCorreoYContrasenya(nuevoCorreo, nuevaContrasenya);
                    break;
                case 6:
                    sigo = false;
                    mensajeInstruccion = "EXIT";
                    socketCliente.enviarMensaje(mensajeInstruccion.c_str());
                    opcionSalir();
                    break;
                default:
                    cout << "Opcion no valida. Por favor, intenta de nuevo." << endl;
                    break;
            }
        } else if (strcmp(tipoUsuario, "Estudiante") == 0) {
            int opcionEstudiante = menuEstudiante();
            // Implementar lógica similar para estudiantes si es necesario
        } else {
            cout << "Tipo de usuario no reconocido." << endl;
            sigo = false;
        }
    }
}


int Cliente::menuProfesorado() {
    system("cls");
    cout << ("===============================\n");
    cout << ("       MENU PROFESORADO        \n");
    cout << ("===============================\n");
    cout << "1. Tu perfil.\n";
    cout << "2. Crear nuevo grupo.\n";
    cout << "3. Chat iniciados.\n";
    cout << "4. Iniciar nueva conversacion.\n";
    cout << "5. Modificar tu perfil.\n";
    cout << "6. SALIR\n\n";
    cout << "Elija una opcion:  ";
    return recogerEntero();
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
    return recogerEntero();
}

// Función para limpiar la entrada si se excede el tamaño máximo
void Cliente::clearIfNeeded(char *str, int max_line) {
    // Limpia los caracteres de más introducidos
    if ((strlen(str) == max_line-1) && (str[max_line-2] != '\n')) {
        while (getchar() != '\n');
    }
}

// Función para recoger un entero desde la entrada estándar
int Cliente::recogerEntero() {
    cin.clear(); // Limpiar cualquier error en cin
    cout.flush(); // Asegurar que se muestra el mensaje antes de leer la entrada
    char linea[MAX_LINE];
    cin >> linea; // Leer una línea de entrada
    while(!strlen(linea)) cin >> linea;
    clearIfNeeded(linea, MAX_LINE); // Limpiar si es necesario
    return atoi(linea); // Utilizamos atoi para convertir la entrada a un entero
}

void Cliente::pantallaChatIniciados() {
    char buffer[MAX_BUFFER_SIZE * 10]; // Buffer grande para todas las conversaciones
    socketCliente.recibirMensaje(buffer);
    system("cls");
    cout << "================================\n";
    cout << "    Conversaciones iniciadas    \n";
    cout << "================================\n";
    cout << buffer;
    cout << "================================\n";
    cout << "Introduce un caracter cualquiera para volver al menu: ";
    int entero;
    cin >> entero;
    if(entero == 1) {
        return;
    }
}

void Cliente::pantallaTusGruposAsignaturas() {
    socketCliente.enviarMensaje("GET_GRUPOS_ASIGNATURAS");
    char buffer[MAX_BUFFER_SIZE];
    socketCliente.recibirMensaje(buffer);

    system("cls");
    cout << "================================\n";
    cout << "    Tus grupos y asignaturas    \n";
    cout << "    (Todavia por programar)     \n";
    cout << "================================\n";
    cout << buffer;
    cout << "================================\n";
    cout << "Pulse una tecla para volver al menu: ";
    int entero;
    cin >> entero;
    if(entero == 1) {
        return;
    }
}

void Cliente::pantallaTusProfesores() {
    socketCliente.enviarMensaje("GET_PROFESORES");
    char buffer[MAX_BUFFER_SIZE];
    socketCliente.recibirMensaje(buffer);

    system("cls");
    cout << "================================\n";
    cout << "    Estos son tus profesores    \n";
    cout << "    (Todavia por programar)     \n";
    cout << "================================\n";
    cout << buffer;
    cout << "================================\n";
    cout << "Pulse una tecla para volver al menu: ";
    int entero;
    cin >> entero;
    if(entero == 1) {
        return;
    }
}

void Cliente::pantallaIniciarNuevaConversacion() {
    system("cls");
    cout << "================================\n";
    cout << "   Iniciar Nueva Conversacion   \n";
    cout << "================================\n";

    bool correoValido = false;
    string volverMenu;
    string correoPersonaDeseada;
    do {
        cout << "1. Para volver al menu pulse 1\n";
        cout << "2. Para iniciar una conversacion pulse otra tecla\n\n";
        cout << "Eliga una opcion: ";
        getline(cin, volverMenu);

        if(volverMenu[0] == '1') {
            return;
        } else {
            system("cls");
            cout << "================================\n";
            cout << "  Iniciando Nueva Conversacion  \n";
            cout << "================================\n";
            cout << "Correo del destinatario (@opendeusto.es): ";
            getline(cin, correoPersonaDeseada);

            // Enviar solicitud al servidor
            socketCliente.enviarMensaje("INICIAR_CONVERSACION");
            socketCliente.enviarMensaje(correoPersonaDeseada.c_str());

            char buffer[MAX_BUFFER_SIZE];
            socketCliente.recibirMensaje(buffer);

            if (strcmp(buffer, "ERROR") == 0) {
                cout << "\nEl usuario no existe o ya has iniciado una conversación con él.\n";
            } else {
                cout << "\nSe ha iniciado la conversacion con el usuario " << correoPersonaDeseada << "\n\n";
            }
        }

    } while (!correoValido);
}

// Modifica el usuario
void Cliente::solicitarCorreoYContrasenya(char* correoNuevo, char* contrasenyaNueva) {
    system("cls");
    cout << "================================\n";
    cout << " Modificar tus datos personales \n";
    cout << "================================\n";
    cout << "\nIntroduzca sus nuevos datos:\n";
    ingresarCorreo(correoNuevo);
    ingresarContrasenya(contrasenyaNueva);
}

void Cliente::opcionSalir() {
    system("cls");
    cout << "Gracias por usar Deusto Chat!\n";
}

void Cliente::ingresarCorreo(char* correo) {
    cout << "Correo electronico (@opendeusto.es): ";
    cin >> correo;
}

void Cliente::ingresarContrasenya(char* contrasenya) {
    cout << "Contrasenya: ";
    cin >> contrasenya;
}

void Cliente::pantallaCrearNuevoGrupo() {
    system("cls");
    cout << "================================\n";
    cout << "    Crear Nuevo Grupo     \n";
    cout << "================================\n";

    cout << "Nombre del nuevo grupo: ";
    string nombreGrupo;
    getline(cin, nombreGrupo);

    socketCliente.enviarMensaje("CREAR_GRUPO");
    socketCliente.enviarMensaje(nombreGrupo.c_str());

    cout << "\nEl grupo " << nombreGrupo << " ha sido creado!\n";
    cout << "\nPulse una tecla para volver al menu: ";
    getchar();
}

char Cliente::pantallaPerfilProfesor(char *correo, char* nombre, char *dni) {
    system("cls");
    printf("================================\n");
    printf("             -Perfil-           \n");
    printf("================================\n");
    printf("Correo electronico: %s\n", correo);
    printf("Nombre: %s\n", nombre);
    printf("DNI: %s\n", dni);
    printf("================================\n");
    printf("Pulse 1 para volver al menu.\n\n");
    int entero = recogerEntero();
    while (entero != 1) {
        cout << "Opcion no valida. Por favor, pulse 1 para volver al menu.\n";
        entero = recogerEntero();
    }
    return 0;
}