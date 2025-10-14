#ifndef USUARIO_H
#define USUARIO_H

#include <iostream>
#include <string>

using namespace std;

class usuario{

private:
    string cedula, clave;
    int saldo;

public:
    int n, metodo;
    string archivoUsuarios;
    usuario() : cedula(""), clave(""), saldo(0) {}
    usuario(string cedula_, string clave_, int saldo_):cedula(cedula_),clave(clave_),saldo(saldo_){}
    int consultarSaldo();
    bool retirarSaldo(int cantidadRetirar);
    ~usuario();

};

#endif // USUARIO_H
