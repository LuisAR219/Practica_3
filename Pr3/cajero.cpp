#include <iostream>
#include "cajero.h"
using namespace std;


Cajero::Cajero() {
    usuarioActual = nullptr;
    semilla = 0;
    metodo = 1;
    archivoUsuarios = "usuarios.dat";
}

void Cajero::configurarSistema() {
    cout << "=== CONFIGURACIÓN DEL SISTEMA ===" << endl;
    cout << "Ingrese la semilla de codificación: ";
    cin >> semilla;
    cout << "Ingrese el método (1 o 2): ";
    cin >> metodo;
    cout << "Nombre del archivo de usuarios: ";
    cin >> archivoUsuarios;

    sistema.setArchivoUsuarios(archivoUsuarios);
    sistema.cargarUsuarios(semilla, metodo);
}


void Cajero::iniciarSesion() {
    string cedula, clave;
    cout << "\n=== INICIO DE SESIÓN ===" << endl;
    cout << "Cédula: ";
    cin >> cedula;
    cout << "Clave: ";
    cin >> clave;

    usuarioActual = sistema.buscarUsuario(cedula);

    if (usuarioActual == nullptr) {
        cout << "Usuario no encontrado.\n";
        return;
    }

    if (!usuarioActual->verificarClave(clave, semilla, metodo)) {
        cout << "Clave incorrecta.\n";
        usuarioActual = nullptr;
        return;
    }

    cout << "\nBienvenido, " << usuarioActual->getCedula() << endl;

    if (usuarioActual->esAdministrador()) {
        menuAdministrador();
    } else {
        menuCliente();
    }
}


void Cajero::menuAdministrador() {
    int opcion;
    do {
        cout << "\n=== MENÚ ADMINISTRADOR ===" << endl;
        cout << "1. Registrar nuevo usuario\n";
        cout << "2. Mostrar todos los usuarios\n";
        cout << "3. Guardar y salir\n";
        cout << "Opción: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            registrarNuevoUsuario();
            break;
        case 2:
            sistema.mostrarUsuarios();
            break;
        case 3:
            sistema.guardarUsuarios(semilla, metodo);
            cout << "Cambios guardados exitosamente.\n";
            break;
        default:
            cout << "Opción inválida.\n";
        }
    } while (opcion != 3);
}

void Cajero::registrarNuevoUsuario() {
    string cedula, clave;
    double saldo;

    cout << "\n=== REGISTRAR USUARIO ===" << endl;
    cout << "Cédula: ";
    cin >> cedula;

    if (sistema.existeUsuario(cedula)) {
        cout << "Ya existe un usuario con esa cédula.\n";
        return;
    }

    cout << "Clave: ";
    cin >> clave;
    cout << "Saldo inicial: ";
    cin >> saldo;

    sistema.registrarUsuario(cedula, clave, saldo, false);
    cout << "Usuario registrado exitosamente.\n";
}


void Cajero::menuCliente() {
    int opcion;
    do {
        cout << "\n=== MENÚ CLIENTE ===" << endl;
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
            sistema.guardarUsuarios(semilla, metodo);
            cout << "Sesión cerrada.\n";
            break;
        default:
            cout << "Opción inválida.\n";
        }
    } while (opcion != 3);
}


void Cajero::consultarSaldo() {
    cout << "\nConsultando saldo..." << endl;

    if (usuarioActual->getSaldo() < 1000) {
        cout << "No tienes suficiente saldo para realizar esta operación.\n";
        return;
    }

    usuarioActual->actualizarSaldo(usuarioActual->getSaldo() - 1000);
    cout << "Saldo actual: " << usuarioActual->getSaldo() << " COP\n";
}


void Cajero::retirarDinero() {
    double monto;
    cout << "\nIngrese el monto a retirar: ";
    cin >> monto;

    double total = monto + 1000; // incluye el costo del servicio
    if (usuarioActual->getSaldo() < total) {
        cout << "Saldo insuficiente.\n";
        return;
    }

    usuarioActual->actualizarSaldo(usuarioActual->getSaldo() - total);
    cout << "Retiro exitoso. Nuevo saldo: "
         << usuarioActual->getSaldo() << " COP\n";
}


void Cajero::ejecutar() {
    configurarSistema();

    int opcion;
    do {
        cout << "\n=== SISTEMA DE CAJERO ===" << endl;
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
