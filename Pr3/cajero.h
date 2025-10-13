#ifndef CAJERO_H
#define CAJERO_H

#include <string>
#include "usuario.h"

using namespace std;


class Cajero {
private:
    usuario sistema;
    usuario* usuarioActual;
    int semilla;
    int metodo;
    string archivoUsuarios;

public:

    Cajero();
    void configurarSistema();
    void iniciarSesion();
    void menuAdministrador();
};

#endif
