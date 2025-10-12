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
