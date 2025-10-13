#include <iostream>
#include <fstream>
#include "Cajero.h"
using namespace std;


Cajero::Cajero() {
    usuarioActual = nullptr;
    semilla = 0;
    metodo = 1;
    archivoUsuarios = "usuarios.txt";
}


Cajero::~Cajero() {
    delete usuarioActual;
}


void Cajero::iniciarSesion() {
    string cedulaIngresada, claveIngresada;
    cout << "\n=== INICIO DE SESIÓN ===\n";
    cout << "Cédula: ";
    cin >> cedulaIngresada;
    cout << "Clave: ";
    cin >> claveIngresada;

    ifstream archivo(archivoUsuarios);
    if (!archivo.is_open()) {
        cout << "Error al abrir el archivo de usuarios.\n";
        return;
    }

    bool encontrado = false;
    string cedula, clave;
    int saldo;

    while (archivo >> cedula >> clave >> saldo) {
        if (cedula == cedulaIngresada && clave == claveIngresada) {
            usuarioActual = new usuario(cedula, clave, saldo);
            encontrado = true;
            break;
        }
    }
    archivo.close();

    if (!encontrado) {
        cout << "Usuario o clave incorrectos.\n";
        return;
    }

    cout << "\nBienvenido al sistema, " << cedulaIngresada << ".\n";
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
        cout << "1. Iniciar sesión\n";
        cout << "2. Salir\n";
        cout << "Opción: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            iniciarSesion();
            break;
        case 2:
            cout << "Hasta pronto.\n";
            break;
        default:
            cout << "Opción inválida.\n";
        }
    } while (opcion != 2);
}
