#ifndef ADMINISTRADOR_H
#define ADMINISTRADOR_H

#include <iostream>
#include <string>
using namespace std;

class administrador{

private:

    int n, metodo;
    string archivoAdmin, archivoUsuario;

public:
    administrador():n(0),metodo(0),archivoUsuario(""),archivoAdmin("sudo.txt"){}
    void setAdmin(int n_, int metodo_, string archivoUsuario_);
    void crearUsuario();
    bool registroAdmin(int n, int metodo);
};

#endif // ADMINISTRADOR_H
