#include <iostream>
#include <fstream>
#include "Cajero.h"
#include "usuario.h"

using namespace std;

usuario* registroUsuario(int n, int metodo, string cedula, string clave);
string metodo1(const string& texto, int n);
string metodo2(const string& texto, int n);
string decodificador(unsigned char* msjCodificado, int tamanoCodificado, int n, int metodo);
bool esSoloNumeros(const string& texto);
bool esAlfaNumerico(const string& texto);

Cajero::Cajero() {
    usuarioActual = nullptr;
    semilla = 0;
    metodo = 1;
    archivoUsuarios = "usuarios.txt";
}


Cajero::~Cajero() {
    delete usuarioActual;
}

void Cajero::configurarSistema() {
    cout << "=== CONFIGURACIÓN DEL SISTEMA ===" << endl;

    string semillaStr;
    int semilla_;
    do {
        cout << "Semilla de codificacion(1-32): ";
        cin >> semillaStr;

        if (esSoloNumeros(semillaStr)==false) {
            cout << "La semilla tiene que ser un numero.\n";
            continue;
        }
        else{
            semilla_=stoi(semillaStr);
            if ((semilla_ < 1) || (semilla_ > 32)) {
                cout << "La semilla solo puede ser de 1 a 32.\n";
                continue;
            }
            break;
        }
    } while (true);

    string metodoStr;
    int metodo_;
    do {
        cout << "Metodo de codificacion (1-2): ";
        cin >> metodoStr;

        if (esSoloNumeros(metodoStr)==false) {
            cout << "La semilla tiene que ser un numero.\n";
            continue;
        }
        else{
            metodo_=stoi(metodoStr);
            if ((metodo_!=1)&&(metodo_!=2)) {
                cout << "El metodo solo puede ser 1 o 2.\n";
                continue;
            }
            break;
        }
    } while (true);

    string claveAdmin;
    do {
        cout << "Clave del administrador (solo letras y numeros): ";
        cin >> claveAdmin;

        if (!esAlfaNumerico(claveAdmin)) {
            cout << "La clave solo puede contener letras y numeros.\n";
            continue;
        }
        break;
    } while (true);

    this->semilla=semilla_;
    this->metodo=metodo_;

    ofstream file("sudo.txt", ios::out);
    if (!file) {
        cerr << "Error al abrir el archivo de administrador.\n";
        return;
    }

    string resultadoClaveAdmin;
    if (this->metodo == 1) {
        resultadoClaveAdmin = metodo1(claveAdmin, this->semilla);
    }
    else if (this->metodo == 2) {
        resultadoClaveAdmin = metodo2(claveAdmin, this->semilla);
    }

    file << resultadoClaveAdmin;
    file.close();
}

void Cajero::setCodificacionUsuario(){
    usuarioActual->n=this->semilla;
    usuarioActual->metodo=this->metodo;
    usuarioActual->archivoUsuarios=this->archivoUsuarios;
}

void Cajero::iniciarSesion() {
    string cedula, clave;
    cout << "\n=== INICIO DE SESIÓN ===\n";
    cout << "Cédula: ";
    cin >> cedula;
    cout << "Clave: ";
    cin >> clave;

    this->usuarioActual=registroUsuario(this->semilla, this->metodo, cedula, clave);

    if (this->usuarioActual==nullptr) {
        cout << "Usuario o clave incorrectos.\n";
        return;
    }

    cout << "\nBienvenido al sistema, " << cedula << ".\n";
    menuCliente();
}


void Cajero::menuCliente() {
    int opcion = 0;
    do {
        cout << "\n=== MENÚ CLIENTE ===\n";
        cout << "1. Consultar saldo\n";
        cout << "2. Retirar dinero\n";
        cout << "3. Salir\n";
        cout << "Opción: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            consultarSaldo();
            break;
        case 2:
            retirarDinero();
            break;
        case 3:
            cout << "Cerrando sesión...\n";
            break;
        default:
            cout << "Opción inválida.\n";
        }

    } while (opcion != 3);
}


void Cajero::consultarSaldo() {
    int saldoActual = usuarioActual->consultarSaldo();
    if (saldoActual == -1) {
        cout << "No tienes saldo suficiente para pagar la tarifa de 1000 COP.\n";
    } else {
        cout << "Saldo actual: " << saldoActual << " COP\n";
    }
}


void Cajero::retirarDinero() {
    int monto;
    cout << "Ingrese la cantidad a retirar: ";
    cin >> monto;

    if (usuarioActual->retirarSaldo(monto)) {
        cout << "Retiro exitoso.\n";
    } else {
        cout << "Saldo insuficiente (recuerda que se descuenta también la tarifa de 1000 COP).\n";
    }
}


void Cajero::ejecutar() {
    int opcion = 0;
    do {
        cout << "\n=== CAJERO ELECTRÓNICO ===\n";
        cout << "1. Iniciar sesión como usuario\n";
        cout << "2. Iniciar sesión como administrador\n";
        cout << "3. Salir\n";
        cout << "Opción: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            iniciarSesion();
            break;
        case 2:
            procesoAdmin();
            break;
        case 3:
            cout << "Hasta pronto.\n";
            break;
        default:
            cout << "Opción inválida.\n";
        }
    } while (opcion != 3);
}


void Cajero::procesoAdmin(){

    bool registro=admin.registroAdmin(this->semilla,this->metodo);

    if (registro){
        admin.setAdmin(this->semilla,this->metodo,this->archivoUsuarios);
        admin.crearUsuario();
    }

}


usuario* registroUsuario(int n, int metodo, string cedula, string clave) {
    string cedulaEncriptada = "";
    string claveEncriptada = "";

    if (metodo == 1) {
        cedulaEncriptada = metodo1(cedula, n);
        claveEncriptada  = metodo1(clave, n);
    }
    else if (metodo == 2) {
        cedulaEncriptada = metodo2(cedula, n);
        claveEncriptada  = metodo2(clave, n);
    }

    ifstream file("usuarios.txt");
    string linea;
    while (getline(file, linea)) {
        size_t pos1 = linea.find(' ');
        size_t pos2 = linea.find(' ', pos1 + 1);

        string ced = linea.substr(0, pos1);
        string cla = linea.substr(pos1 + 1, pos2 - pos1 - 1);
        string sal = linea.substr(pos2 + 1);

        if (ced == cedulaEncriptada && cla == claveEncriptada) {
            file.close();
            unsigned char* arr = new unsigned char[sal.size()];
            memcpy(arr, sal.data(), sal.size());
            string saldoDesencriptado=decodificador(arr,sal.size(),n,metodo);
            int saldoFinal=stoi(saldoDesencriptado);
            delete[] arr;
            usuario* userActual = new usuario(cedula, clave, saldoFinal);
            return userActual;
        }
    }
    file.close();
    return nullptr;
}
