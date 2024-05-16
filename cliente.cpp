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
    socketCliente.enviarMensaje(correo);

    cout << "Contrasenya: ";
    cin >> contrasenya;
    socketCliente.enviarMensaje(contrasenya);
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
                    solicitarCorreoYContrasenya(correo, contrasenya);  // Usar correo y contrasenya almacenados
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
            switch (opcionEstudiante) {
                case 1:
                    //pantallaPerfilAlumno(db, correo, nombre, dni);
                    break;
                case 2:
                    //Mostramos los profesores del estudiante
                    //pantallaTusProfesores(db,correo);
                    break;
                case 3:
                    //Mostramos los chats iniciados
                    //pantallaChatIniciados(db, correo);
                    break;
                case 4:
                    //Creamos un nuevo chat
                    //pantallaIniciarNuevaConversacion(db, correo);
                    break;
                case 5:
                    sigo = false;
                    mensajeInstruccion = "EXIT";
                    socketCliente.enviarMensaje(mensajeInstruccion.c_str());
                    opcionSalir();
                    break;
                default:
                    break;
            }
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
    cout << ("================================\n");
    cout << ("        MENU ESTUDIANTE         \n");
    cout << ("================================\n");
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
    system("cls");
    return atoi(linea); // Utilizamos atoi para convertir la entrada a un entero
}







void Cliente::pantallaChatConversacion(int idConversacion) {
    char buffer[MAX_BUFFER_SIZE * 10]; // Buffer grande para todos los mensajes
    string mensajeInstruccion = "CHAT_CONVERSATION";
    socketCliente.enviarMensaje(mensajeInstruccion.c_str());

    // Enviar id de la conversación
    socketCliente.enviarDatos((char*)&idConversacion, sizeof(int));

    while (true) {
        system("cls");
        cout << "================================\n";
        cout << "       Conversacion " << idConversacion << "        \n";
        cout << "================================\n";

        // Solicitar mensajes de la conversación
        mensajeInstruccion = "GET_MESSAGES";
        socketCliente.enviarMensaje(mensajeInstruccion.c_str());

        // Recibir mensajes
        socketCliente.recibirMensaje(buffer);
        cout << buffer;
        cout << "================================\n";
        cout << "Escriba un mensaje o 'salir' para volver al menu: ";
        string mensaje;
        getline(cin, mensaje);

        if (mensaje == "salir") {
            mensajeInstruccion = "RETURN_MENU";
            socketCliente.enviarMensaje(mensajeInstruccion.c_str());
            break;
        } else {
            // Enviar mensaje al servidor
            socketCliente.enviarMensaje(mensaje.c_str());
        }
    }
}

// Modificar pantallaChatIniciados para seleccionar una conversación
void Cliente::pantallaChatIniciados() {
    char buffer[MAX_BUFFER_SIZE * 10]; // Buffer grande para todas las conversaciones
    socketCliente.recibirMensaje(buffer);
    system("cls");
    cout << "================================\n";
    cout << "    Conversaciones iniciadas    \n";
    cout << "================================\n";
    cout << buffer;
    cout << "================================\n";
    cout << "Seleccione una conversacion o pulse 0 para volver al menu: ";
    int opcion;
    cin >> opcion;
    if (opcion == 0) {
        return;
    } else {
        pantallaChatConversacion(opcion);
    }
}






// void Cliente::pantallaChatIniciados() {
//     char buffer[MAX_BUFFER_SIZE * 10]; // Buffer grande para todas las conversaciones
//     socketCliente.recibirMensaje(buffer);
//     system("cls");
//     cout << "================================\n";
//     cout << "    Conversaciones iniciadas    \n";
//     cout << "================================\n";
//     cout << buffer;
//     cout << "================================\n";
//     cout << "Introduce un caracter cualquiera para volver al menu: ";
//     int entero;
//     cin >> entero;
//     if(entero == 1) {
//         return;
//     }
// }

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
    char volverMenu[MAX_LINE];
    char correoPersonaDeseada[MAX_BUFFER_SIZE];
    do {
        cout << "1. Para volver al menu pulse 1\n";
        cout << "2. Para iniciar una conversacion introduzca un caracter cualquiera\n\n";
        cout << "Eliga una opcion: ";
        cin >> volverMenu;

        if(volverMenu[0] == '1') {
            mensajeInstruccion = "RETURN_MENU";
            socketCliente.enviarMensaje(mensajeInstruccion.c_str());
            correoValido = true;
            return;
        } else {
            system("cls");
            cout << "================================\n";
            cout << "  Iniciando Nueva Conversacion  \n";
            cout << "================================\n";
            cout << "Correo del destinatario (@opendeusto.es): ";
            cin >> correoPersonaDeseada;

            // Enviamos el correo de la persona
            mensajeInstruccion = correoPersonaDeseada;
            socketCliente.enviarMensaje(mensajeInstruccion.c_str());

            // Recibimos una respuesta
            char buffer[MAX_BUFFER_SIZE];
            socketCliente.recibirMensaje(buffer);

            if (strcmp(buffer, "SAME_USER_ERROR") == 0) {
                cout << "\nNo puedes iniciar una conversacion contigo mismo.\n\n";
            } else if (strcmp(buffer, "CHAT_EXIST_ERROR") == 0) {
                cout << "\nYa has iniciado una conversacion con este usuario.\n\n";
            } else if (strcmp(buffer, "USER_NOT_FOUND_ERROR") == 0) {
                cout << "\nEl usuario no existe.\n\n";
            } else if (strcmp(buffer, "OK") == 0) {
                cout << "\nSe ha iniciado la conversacion con el usuario " << correoPersonaDeseada << "\n\n";
            } else {
                cout << "\nError desconocido.\n";
            }
        }

    } while (!correoValido);
}


// Modifica el usuario
void Cliente::solicitarCorreoYContrasenya(char* correo, char* contrasenya) {
    system("cls");
    cout << "================================\n";
    cout << " Modificar tus datos personales \n";
    cout << "================================\n";
    
    bool datosValidos = false;
    char volverMenu[MAX_BUFFER_SIZE];
    char nuevoCorreo[MAX_BUFFER_SIZE];
    char nuevaContrasenya[MAX_BUFFER_SIZE];

    do {
        cout << "1. Para volver al menu pulse 1\n";
        cout << "2. Para introducir nuevos datos pulse otra tecla\n\n";
        cout << "Eliga una opcion: ";
        cin >> volverMenu;

        if (volverMenu[0] == '1') {
            mensajeInstruccion = "RETURN_MENU";
            socketCliente.enviarMensaje(mensajeInstruccion.c_str());
            datosValidos = true;
            break;
        } else {
            system("cls");
            cout << "================================\n";
            cout << " Modificar tus datos personales \n";
            cout << "================================\n";
            ingresarCorreo(nuevoCorreo);
            ingresarContrasenya(nuevaContrasenya);

            // Enviar los datos al servidor
            socketCliente.enviarMensaje(nuevoCorreo);
            socketCliente.enviarMensaje(nuevaContrasenya);

            // Recibimos una respuesta
            char buffer[MAX_BUFFER_SIZE];
            socketCliente.recibirMensaje(buffer);

            if (strcmp(buffer, "USER_EXISTS") == 0) {
                cout << "\nEl correo nuevo ya esta en uso. Intentelo de nuevo.\n\n";
            } else if (strcmp(buffer, "MODIFY_SUCCESS") == 0) {
                cout << "\nUsuario modificado con exito.\n\n";
                // Actualizar el correo y la contraseña del cliente después de la modificación exitosa
                strcpy(correo, nuevoCorreo);
                strcpy(contrasenya, nuevaContrasenya);
            } else {
                cout << "\nError al modificar el usuario.\n\n";
            }
        }

    } while (!datosValidos);
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