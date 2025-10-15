#ifndef CAJERO_H
#define CAJERO_H

#include <string>
#include "usuario.h"
#include "administrador.h"

using namespace std;


class Cajero {
private:
    usuario* usuarioActual;
    int semilla;
    int metodo;
    string archivoUsuarios;
    administrador admin;

public:
    Cajero();
    ~Cajero();

    void iniciarSesion();
    void menuCliente();
    void consultarSaldo();
    void retirarDinero();
    void ejecutar();
    void setCodificacionUsuario();
    void configurarSistema();
    void procesoAdmin();

};

#endif // CAJERO_H
