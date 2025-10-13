#ifndef CAJERO_H
#define CAJERO_H

#include <string>
#include "usuario.h"

using namespace std;


class Cajero {
private:
    usuario* usuarioActual;
    int semilla;
    int metodo;
    string archivoUsuarios;

public:
    Cajero();
    ~Cajero();

    void iniciarSesion();
    void menuCliente();
    void consultarSaldo();
    void retirarDinero();
    void ejecutar();
};

#endif // CAJERO_H
