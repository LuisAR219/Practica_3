#ifndef ADMINISTRADOR_H
#define ADMINISTRADOR_H

#include <iostream>
#include <string>
using namespace std;

class administrador{

private:

    int n, metodo;
    string archivoAdmin="sudo.txt", archivoUsuario;

public:
    administrador():n(0),metodo(0),archivoUsuario(""){}
    void setAdmin(int n_, int metodo_, string archivoUsuario_);
    void crearUsuario();
    bool registroAdmin();
};

#endif // ADMINISTRADOR_H
