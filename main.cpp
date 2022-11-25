#include <iostream>
using namespace std;

struct sFecha{
    int dia;
    int mes;
    int anio;
};

struct sPrivacidad{
    bool correoPublico;
    bool fechaNacimientoPublica;
};

struct sUsuario{
    string nombres;
    string apellidos;
    string correo;
    string contrasena;
    sFecha fechaNacimiento;
    sPrivacidad panelPrivacidad;
    sUsuario ** amigos;
    int cantAmigos;
    sUsuario ** solicitudesEntrantes;
    int entrantes;
    int codigoRed;
};

//MENUS
void friendBook();
int menuPrincipal();
int menuUser(string nombre);
int menuEditarPerfil();
int menuAmigos();

//CUENTAS
int crearCuenta(sUsuario users[], int &cantUsers);
void aumentarCapacidad (sUsuario ** apUsers, int &cantidadUsuarios);
void disminuirCapacidad (sUsuario ** apUsers, int &cantidadUsuarios);
int iniciarSesion (sUsuario * apUsers, int cantidadUsuarios);
void cambiarInformacion(sUsuario &user);
void modificarNacimiento(sUsuario &user);
void administrarSeguridad(sUsuario &user);
void printUser(sUsuario user);

//AMIGOS
void enviarSolicitud(int pos, sUsuario users[], int cantUsers);
void aumentarSolicitudes(sUsuario ** apUsers[], int &cantidadSolicitudes);
void disminuirSolicitudes(sUsuario ** apUsers[], int &cantidadSolicitudes);
void eliminarAmigo (sUsuario users [], int cantUsers, int pos);
void printSolicitudes(sUsuario users[], int pos, int cantUsers);
void printAmigos(sUsuario user);
void buscarAmigo (sUsuario users[], int pos);

/*********************************
                    _
                   (_)
  _ __ ___    __ _  _  _ __
 | '_ ` _ \  / _` || || '_ \
 | | | | | || (_| || || | | |
 |_| |_| |_| \__,_||_||_| |_|
***********************************/
int main()
{
    int cantUsers = 0;
    sUsuario * users = new sUsuario[cantUsers];
    sUsuario user;
    int pos;
    int menu = 1, opcion;
    while(1)
    {
        switch (menu)
        {
            //MENU PRINCIPAL
            case 1:
                opcion = menuPrincipal();
                switch (opcion)
                {
                    //Registrarse
                    case 1:
                        aumentarCapacidad(&users, cantUsers);
                        if(crearCuenta(users, cantUsers)==-1) disminuirCapacidad(&users, cantUsers);
                        break;
                        //Iniciar sesion
                    case 2:
                        pos = iniciarSesion(users,cantUsers);
                        if(pos != -1){
                            menu = 2;
                        }
                        break;
                        //Salir
                    case 3:
                        //printUsers(users,cantUsers);
                        return 0;
                        break;
                    default:
                        break;
                }
                break;
                //MENU DE USUARIO
            case 2:
                user = users[pos];
                opcion = menuUser(user.nombres);
                switch (opcion)
                {
                    //Editar perfil
                    case 1:
                        menu = 3;
                        break;
                        //Amigos
                    case 2:
                        menu = 4;
                        break;
                        //Cerrar sesion
                    case 3:
                        menu = 1;
                        break;
                    default:
                        break;
                }
                break;
                //EDITAR PERFIL
            case 3:
                opcion = menuEditarPerfil();
                switch (opcion)
                {
                    //Cambiar Informacion basica
                    case 1:
                        cambiarInformacion(user);
                        break;
                        //Modificar fecha de nacimiento
                    case 2:
                        modificarNacimiento(user);
                        break;
                        //Administrar seguridad
                    case 3:
                        administrarSeguridad(user);
                        break;
                        //Guardar cambios
                    case 4:
                        //funcion guardar cambios
                        users[pos] = user;
                        cout << "Cambios guardados con exito" << endl;
                        system("pause");
                        menu = 2;
                        break;
                    default:
                        break;
                }
                break;
                //MENU AMIGOS
            case 4:
                opcion = menuAmigos();
                switch (opcion)
                {
                    //Ver amigos
                    case 1:
                        printAmigos(user);
                        break;
                        //Buscar amigos
                    case 2:
                        buscarAmigo(users, pos);
                        user = users[pos];
                        break;
                        //Solicitudes de amistad
                    case 3:
                        printSolicitudes(users,pos,cantUsers);
                        user = users[pos];
                        break;
                        //Eliminar amigos
                    case 4:
                        eliminarAmigo(users, cantUsers, pos);
                        user = users[pos];
                        break;

                        //Agregar amigos
                    case 5:
                        enviarSolicitud(pos, users, cantUsers);
                        user = users[pos];
                        break;

                        //Atras
                    case 6:
                        menu = 2;
                        break;
                    default:
                        break;
                }
                break;
                //MENU ALMACENAMIENTO
            default:
                break;
        }
    }
    /**/
    return 0;
}
/************************************
  _ __ ___    ___  _ __   _   _  ___
 | '_ ` _ \  / _ \| '_ \ | | | |/ __|
 | | | | | ||  __/| | | || |_| |\__ \
 |_| |_| |_| \___||_| |_| \__,_||___/
 Funciones relacionadas con el despliegue de los menus
*************************************/
void friendBook(){
    cout << " --------------------------------------------------------------------------------" << endl;
    cout << "  ______      _                   _  ____    ____    ____   _  __ " << endl;
    cout << " |  ____|    (_)                 | ||  _ \\  / __ \\  / __ \\ | |/ / " << endl;
    cout << " | |__  _ __  _   ___  _ __    __| || |_) || |  | || |  | || ' / " << endl;
    cout << " |  __|| '__|| | / _ \\| '_ \\  / _` ||  _ < | |  | || |  | ||  <  " << endl;
    cout << " | |   | |   | ||  __/| | | || (_| || |_) || |__| || |__| || . \\ " << endl;
    cout << " |_|   |_|   |_| \\___||_| |_| \\__,_||____/  \\____/  \\____/ |_|\\_\\ " << endl;
    cout << " --------------------------------------------------------------------------------" << endl;
}

int menuPrincipal(){
    system("cls");
    friendBook();
    int opcion;
    cout << "\t|" << endl;
    cout << "\t| [1] Sign-up" << endl;
    cout << "\t| [2] Sign-in" << endl;
    cout << "\t| [3] Salir" << endl;
    cout << "\t|____________________________" << endl;
    cin >> opcion;
    return opcion;
}

int menuUser(string nombre){
    system("cls");
    friendBook();
    int opcion;
    cout << "\t|" << endl;
    cout << "\t| Hola " << nombre << ". Que deseas hacer?" << endl;
    cout << "\t|" << endl;
    cout << "\t| [1] Editar Perfil" << endl;
    cout << "\t| [2] Amigos" << endl;
    cout << "\t| [3] Sign-out" << endl;
    cout << "\t|____________________________" << endl;
    cin >> opcion;
    return opcion;
}

int menuEditarPerfil(){
    system("cls");
    cout << "----------------------------------------------" << endl;
    cout << "                  Editar Perfil" << endl;
    cout << "----------------------------------------------" << endl;
    int opcion;
    cout << "\t|" << endl;
    cout << "\t| [1] Cambiar informacion basica" << endl;
    cout << "\t| [2] Modificar fecha de nacimiento" << endl;
    cout << "\t| [3] Administrar seguridad" << endl;
    cout << "\t| [4] Guardar cambios" << endl;
    cout << "\t|____________________________" << endl;
    cin >> opcion;
    return opcion;
}

int menuAmigos(){
    system("cls");
    cout << "----------------------------------------------" << endl;
    cout << "                     Amigos" << endl;
    cout << "----------------------------------------------" << endl;
    int opcion;
    cout << "\t|" << endl;
    cout << "\t| [1] Ver amigos" << endl;
    cout << "\t| [2] Buscar amigos" << endl;
    cout << "\t| [3] Solicitudes de amistad" << endl;
    cout << "\t| [4] Eliminar amigos" << endl;
    cout << "\t| [5] Hacer solicitud" << endl;
    cout << "\t| [6] Atras" << endl;
    cout << "\t|____________________________" << endl;
    cin >> opcion;
    return opcion;
}

/************************************
                            _
                           | |
   ___  _   _   ___  _ __  | |_   __ _  ___
  / __|| | | | / _ \| '_ \ | __| / _` |/ __|
 | (__ | |_| ||  __/| | | || |_ | (_| |\__ \
  \___| \__,_| \___||_| |_| \__| \__,_||___/
 Funciones relacionadas con las cuentas
*************************************/
int crearCuenta(sUsuario users[], int &cantUsers){
    system("cls");
    cin.ignore(1);
    sUsuario user;
    bool existe = false;
    string auxString;
    cout << "------------------------------------------" << endl;
    cout << "              CREAR CUENTA" << endl;
    cout << "------------------------------------------" << endl;
    cout << "-Correo electronico: ";
    cin >> user.correo;

    cin.ignore(1);

    for(int i = 0 ; i < cantUsers ; i++)
        if(users[i].correo == user.correo) existe = true;

    if(existe){
        cout << "\n------------------------------------------" << endl;
        cout << "\aYa existe un usuario registrado con este correo electronico..." << endl;
        cout << "Intentelo de nuevo" << endl;
        cout << "------------------------------------------" << endl;
        system("pause");
        return -1;
    }
    cout << "-Nombres: ";
    getline(cin, user.nombres);
    cout << "-Apellidos: ";
    getline(cin, user.apellidos);
    cout << "-Contrasena: ";
    cin >> user.contrasena;
    user.codigoRed = cantUsers;
    user.entrantes = 0;
    user.cantAmigos = 0;
    user.fechaNacimiento.anio = 0;
    user.panelPrivacidad.correoPublico = true;
    user.panelPrivacidad.fechaNacimientoPublica = false;
    user.solicitudesEntrantes = new sUsuario * [0];
    user.amigos = new sUsuario * [0];
    users[cantUsers-1] = user;
    return 0;
}

void aumentarCapacidad (sUsuario ** apUsers, int &cantidadUsuarios){
    sUsuario * expansion = new sUsuario[cantidadUsuarios+1]; //Apuntador local
    for (int i = 0; i < cantidadUsuarios; i++) expansion[i] = (*apUsers)[i];
    delete[] *apUsers;
    *apUsers = expansion;
    cantidadUsuarios++;
}

void disminuirCapacidad (sUsuario ** apUsers, int &cantidadUsuarios){
    sUsuario * expansion = new sUsuario[cantidadUsuarios-1]; //Apuntador local
    for (int i = 0; i < cantidadUsuarios-1; i++) expansion[i] = (*apUsers)[i];
    delete[] *apUsers;
    *apUsers = expansion;
    cantidadUsuarios--;
}

int iniciarSesion (sUsuario * apUsers, int cantidadUsuarios){
    cin.ignore(1);
    system("cls");
    bool sesionIniciadaCorrectamente = false;
    int pos = -1;
    string buffer;
    cout << "-------------------------------" << endl;
    cout << "         INICIAR SESION        " << endl;
    cout << "-------------------------------" << endl;
    cout << "Escriba su correo Electronico: " << endl;
    getline(cin, buffer);
    for (int i = 0; i < cantidadUsuarios; i++){
        if (buffer == apUsers[i].correo){
            pos = i;
        }
    }
    if (pos != -1) {
        cout  << "Digite su Password: " << endl;
        getline(cin, buffer);
        if (buffer == apUsers[pos].contrasena) sesionIniciadaCorrectamente = true;
        if (sesionIniciadaCorrectamente) cout << endl << "Ha iniciado Sesion Correctamente..." << endl;
        else{
            cout << endl << "\aPassword Incorrecto" << endl;
            system("pause");
            return -1;
        }
    }
    else {
        cout << endl << "\aEl correo electronico digitado no coincide con ninguno de los registrados en FriendBook" << endl;
    }
    system("pause");
    return pos;
}

void cambiarInformacion(sUsuario &user){
    int opcion;
    string auxString;
    do{
        system("cls");
        cout << "-------------------------------" << endl;
        cout << "      CAMBIAR INFORMACION      " << endl;
        cout << "-------------------------------" << endl;
        cout << "\t| [1] Cambiar nombres" << endl;
        cout << "\t| [2] Cambiar apellidos" << endl;
        cout << "\t| [3] Correo" << endl;
        cout << "\t| [4] Salir" << endl;
        cout << "\t|____________________________" << endl;
        cin >> opcion;
        cin.ignore(1);
        switch (opcion)
        {
            case 1:
                cout << "Nuevo nombre: ";
                getline(cin, user.nombres);
                break;

            case 2:
                cout << "Nuevo apellido: ";
                getline(cin, user.apellidos);
                break;

            case 3:
                cout << "Nuevo correo: ";
                cin >> user.correo;
                break;

            default:
                break;
        }

        cout << "Cambios realizados con exito" << endl;

        system("pause");
    }
    while(opcion != 4);

}

void modificarNacimiento(sUsuario &user){
    system("cls");
    cout << "-------------------------------" << endl;
    cout << "      FECHA DE NACIMIENTO      " << endl;
    cout << "-------------------------------" << endl;
    cout << "Anio: ";
    cin >> user.fechaNacimiento.anio;
    cout << "Mes: ";
    cin >> user.fechaNacimiento.mes;
    cout << "Dia: ";
    cin >> user.fechaNacimiento.dia;

    cout << "Cambios realizados con exito" << endl;
    system("pause");
}

void administrarSeguridad(sUsuario &user){
    string opcion;
    system("cls");
    cout << "-------------------------------" << endl;
    cout << "           SEGURIDAD           " << endl;
    cout << "-------------------------------" << endl;
    cout << "Desea que su correo sea publico?" << endl;
    cin >> opcion;
    if(opcion == "si" || opcion == "s" || opcion == "SI" || opcion == "S" || opcion == "sI" || opcion == "Si") user.panelPrivacidad.correoPublico = true;
    else user.panelPrivacidad.correoPublico = false;

    cout << "Desea que su fecha de nacimiento sea publica?" << endl;
    cin >> opcion;
    if(opcion == "si" || opcion == "s" || opcion == "SI" || opcion == "S" || opcion == "sI" || opcion == "Si") user.panelPrivacidad.fechaNacimientoPublica = true;
    else user.panelPrivacidad.fechaNacimientoPublica = false;

    cout << "Cambios realizados con exito" << endl;
    system("pause");
}

void printUser(sUsuario user){
    cout << "-------------------------------" << endl;
    cout << "Nombre: " << user.nombres << " " << user.apellidos << endl;
    if(user.panelPrivacidad.correoPublico)
        cout << "Correo: " << user.correo << endl;
    if(user.panelPrivacidad.fechaNacimientoPublica && user.fechaNacimiento.anio !=0)
        cout << "Fecha de nacimiento: " << user.fechaNacimiento.dia << "/" << user.fechaNacimiento.mes << "/" << user.fechaNacimiento.anio << endl;
    cout << "-------------------------------" << endl;
}

/************************************
                    _
                   (_)
   __ _  _ __ ___   _   __ _   ___   ___
  / _` || '_ ` _ \ | | / _` | / _ \ / __|
 | (_| || | | | | || || (_| || (_) |\__ \
  \__,_||_| |_| |_||_| \__, | \___/ |___/
                        __/ |
                       |___/

 Funciones relacionadas con los amigos
*************************************/

void enviarSolicitud(int pos, sUsuario users[], int cantUsers){
    system("cls");
    string correo;
    int posAmigo = -1;

    cout << "-------------------------------" << endl;
    cout << "       TODOS LOS USUARIOS      " << endl;
    cout << "-------------------------------" << endl;

    for(int i = 0 ; i < cantUsers ; i++)
        printUser(users[i]);

    cout << "Ingrese el correo del usuario que quiere agregar de amigo" << endl;
    cin >> correo;

    bool esAmigo = false;
    bool yaTeAgregoElOtroMen = false;


    for(int i = 0 ; i < users[pos].cantAmigos ; i++)
        if((*users[pos].amigos[i]).correo == correo) esAmigo = true;

    for(int i = 0 ; i < cantUsers ; i++)
        if(correo == users[i].correo) posAmigo = i;

    if(correo == users[pos].correo) cout << "\aNo se puede enviar una solicitud de amistad a usted mismo" << endl;
    else if(esAmigo) cout << users[posAmigo].nombres << " " <<users[posAmigo].apellidos << "\a ya es su amigo" << endl;
    else
    {
        for (int i = 0; i < users[pos].entrantes; i++){
            if (users[pos].solicitudesEntrantes[i]->correo == users[posAmigo].correo){
                yaTeAgregoElOtroMen = true;
            }
        }

        if(pos != -1)
        {
            if (yaTeAgregoElOtroMen){
                cout << endl << " \a La persona ya te ha enviado la solicitud de amistad." << endl;
                cout << "Revisa tu buzon de solicitudes entrantes y aceptala para que puedan ser amigos" << endl << endl;
            }
            else {
                aumentarSolicitudes(&users[posAmigo].solicitudesEntrantes, users[posAmigo].entrantes);
                users[posAmigo].solicitudesEntrantes[users[posAmigo].entrantes - 1] = &users[pos];
                cout << endl << "Solicitud de amistad enviada Exitosamente" << endl;
            }
        } else cout << "\aUsuario no encontrado" << endl;
    }
    system("pause");
}

void buscarAmigo (sUsuario users[], int pos){
    int opcionBusqueda = 0;
    string datoBusqueda;
    cout << "---------------------" << endl;
    cout << "    BUSCAR AMIGOS" << endl;
    cout << "---------------------" << endl;
    cout << endl << "Desea buscar informacion por: " << endl;
    cout << "[1] Nombres" << endl; cout << "[2] Apellidos" << endl;
    cin >> opcionBusqueda;
    cin.ignore(1);

    system("cls");

    cout << "---------------------" << endl;
    cout << "    BUSCAR AMIGOS" << endl;
    cout << "---------------------" << endl;

    if (opcionBusqueda == 1)
    {
        cout << endl << "Escriba el Nombre de su amigo" << endl;
        getline(cin, datoBusqueda);

        cout << "-----------------------------------------------------" << endl;
        cout << "INFORMACION AMIGOS COINCIDENCIA DEL NOMBRE BUSQUEDA: " << endl;
        for (int i = 0; i < users[pos].cantAmigos; i++)
            if (datoBusqueda == users[pos].amigos[i]->nombres)
                printUser(*users[pos].amigos[i]);
    }
    else if (opcionBusqueda == 2)
    {
        cout << endl << "Escriba el Apellido como dato de busqueda" << endl;
        getline(cin, datoBusqueda);

        cout << "-----------------------------------------------------" << endl;
        cout << "INFORMACION AMIGOS COINCIDENCIA DEL APELLIDO BUSQUEDA: " << endl;
        for (int i = 0; i < users[pos].cantAmigos; i++)
            if (datoBusqueda == users[pos].amigos[i]->apellidos)
                printUser(*users[pos].amigos[i]);
    }
    else cout << endl << "\aOpcion No Valida" << endl;

    system("pause");
}

void eliminarAmigo (sUsuario users [], int cantUsers, int pos){
    system ("cls");
    cout << "--------------------------------" << endl;
    cout << "        ELIMINAR AMIGO" << endl;
    cout << "--------------------------------" << endl << endl;
    cout << "Lista de Amigos: " << endl;
    printAmigos(users[pos]);

    string correoAmigoEliminar;
    cout << endl << "Escriba el correo electronico del Usuario que desea eliminar de su lista de amigos: " << endl;
    cin >> correoAmigoEliminar;

    int posAmigo = -1;
    for (int i = 0; i < users[pos].cantAmigos; i++){
        if (correoAmigoEliminar == users[pos].amigos[i]->correo)
            posAmigo = i;
    }

    if (posAmigo == -1){
        cout << endl << "El correo escrito no coincide con el de alguno de sus amigos." << endl << "Opcion Invalida" << endl << endl;
        system ("pause");
    }
    else{
        for (int i = posAmigo; i < users[pos].cantAmigos - 1; i++)
            users[pos].amigos[i] = users[pos].amigos[i+1];

        disminuirSolicitudes(&users[pos].amigos, users[pos].cantAmigos);

        int posExAmigoDentroDeUsers = -1;
        int posUserDentroDelExAmigo = -1;

        //Hallar posicion del Ex Amigo dentro de Users
        for (int i = 0; i < cantUsers; i++){
            if (correoAmigoEliminar == users[i].correo)
                posExAmigoDentroDeUsers = i;
        }

        //Hallar la posicion del usuario que pasa como parametro para realizar el proceso
        for (int i = 0; i < users[posExAmigoDentroDeUsers].cantAmigos; i++){
            if (users[pos].correo == users[posExAmigoDentroDeUsers].amigos[i]->correo)
                posUserDentroDelExAmigo = i;
        }

        for (int i = posUserDentroDelExAmigo; i < users[posExAmigoDentroDeUsers].cantAmigos - 1; i++)
            users[posExAmigoDentroDeUsers].amigos[i] = users[posExAmigoDentroDeUsers].amigos[i+1];
        disminuirSolicitudes(&users[posExAmigoDentroDeUsers].amigos, users[posExAmigoDentroDeUsers].cantAmigos);

        cout << endl << users[posExAmigoDentroDeUsers].nombres << " " <<users[posExAmigoDentroDeUsers].apellidos << " ya no es su amigo." << endl;
        system("pause");
    }
}

void aumentarSolicitudes(sUsuario ** apUsers[], int &cantidadSolicitudes){
    sUsuario ** expansion = new sUsuario * [cantidadSolicitudes+1]; //Apuntador local
    for (int i = 0; i < cantidadSolicitudes; i++) expansion[i] = (*apUsers)[i];
    delete[] *apUsers;
    *apUsers = expansion;
    cantidadSolicitudes++;
}

void disminuirSolicitudes(sUsuario ** apUsers[], int &cantidadSolicitudes){
    sUsuario ** expansion = new sUsuario * [cantidadSolicitudes-1]; //Apuntador local
    for (int i = 0; i < cantidadSolicitudes-1; i++) expansion[i] = (*apUsers)[i];
    delete[] *apUsers;
    *apUsers = expansion;
    cantidadSolicitudes--;
}

void printSolicitudes(sUsuario users[], int pos, int cantUsers){
    system("cls");
    bool aceptoAlgunaSolicitud;
    for(int i = 0 ; i < users[pos].entrantes ; i++){
        system("cls");
        int frndpos = -1;
        for(int j = 0 ; j < cantUsers ; j++)
            if(users[j].codigoRed == (*users[pos].solicitudesEntrantes[i]).codigoRed) frndpos = j;

        cout << "-------------------------------" << endl;
        cout << "     SOLICITUDES ENTRANTES     " << endl;
        cout << "-------------------------------" << endl << endl;
        cout << (*users[pos].solicitudesEntrantes[i]).nombres << " " << (*users[pos].solicitudesEntrantes[i]).apellidos << endl;
        cout << "Amigos en comun: " << endl;

        for(int j = 0 ; j < users[pos].cantAmigos ; j++)
            for(int k = 0 ; k < users[frndpos].cantAmigos ; k++)
                if((*users[pos].amigos[j]).codigoRed == (*users[frndpos].amigos[k]).codigoRed)
                    cout << "- " << (*users[pos].amigos[j]).nombres << " " << (*users[pos].amigos[j]).apellidos << endl;

        cout << endl;

        int opcion;
        cout << "[1] Aceptar" << endl;
        cout << "[2] Rechazar" << endl;
        cin >> opcion;
        cin.ignore(1);
        switch (opcion){
            case 1:
                aumentarSolicitudes(&users[pos].amigos, users[pos].cantAmigos);
                aumentarSolicitudes(&users[frndpos].amigos, users[frndpos].cantAmigos);
                users[pos].amigos[users[pos].cantAmigos-1] = &users[frndpos];
                users[frndpos].amigos[users[frndpos].cantAmigos-1] = &users[pos];
                cout << (*users[pos].amigos[users[pos].cantAmigos-1]).nombres << " " << (*users[pos].amigos[users[pos].cantAmigos-1]).apellidos << " ahora es tu amigo" << endl;
                aceptoAlgunaSolicitud = true;
                system("pause");
                break;

            case 2:
                cout << "Solicitud de amistad rechazada" << endl;
                system("pause");
                break;
            default:
                cout << "\aOpcion no valida" << endl;
                i--;
                system("pause");
                break;
        }
    }
    for(int i = 0 ; i < users[pos].entrantes ; i++)
        disminuirSolicitudes(&users[pos].solicitudesEntrantes, users[pos].entrantes);

    if(users[pos].entrantes == 0 && !aceptoAlgunaSolicitud) {
        cout << "\aNo tiene solicitudes de amistad pendientes" << endl;
        system("pause");
    }
}

void printAmigos(sUsuario user){
    system("cls");
    cout << "-------------------------------" << endl;
    cout << "            AMIGOS             " << endl;
    cout << "-------------------------------" << endl << endl;

    for(int i = 0 ; i < user.cantAmigos ; i++)
        printUser(*user.amigos[i]);

    if(user.cantAmigos == 0) cout << "\aAun no tiene amigos" << endl;
    system("pause");
}