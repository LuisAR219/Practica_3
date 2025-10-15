#include <iostream>
#include <fstream>
#include "administrador.h"

string metodo1(const string& texto, int n);
string metodo2(const string& texto, int n);

void administrador::crearUsuario() {
    string cedula, clave, saldo;
    cout << "Cedula: ";
    cin >> cedula;
    cout << "Clave: ";
    cin >> clave;
    cout << "Saldo inicial: ";
    cin >> saldo;

    ofstream file("usuarios.txt", ios::app);

    string resultadoCedula = "";
    string resultadoClave = "";
    string resultadoSaldo = "";

    if (this->metodo == 1) {
        resultadoCedula = metodo1(cedula, this->n);
        resultadoClave  = metodo1(clave, this->n);
        resultadoSaldo  = metodo1(saldo, this->n);
    }
    else if (this->metodo == 2) {
        resultadoCedula = metodo2(cedula, this->n);
        resultadoClave  = metodo2(clave, this->n);
        resultadoSaldo  = metodo2(saldo, this->n);
    }

    file << resultadoCedula << " " << resultadoClave << " " << resultadoSaldo << endl;
    file.close();

    cout << "Usuario registrado con exito.\n";
}

void administrador::setAdmin(int n_, int metodo_, string archivoUsuario_){

    this->n=n_;
    this->metodo=metodo_;
    this->archivoUsuario=archivoUsuario_;

}

bool administrador::registroAdmin(){

    ifstream file("sudo.txt");
    string claveEncriptada;
    getline(file, claveEncriptada);
    file.close();

    int tamano = static_cast<int>(claveEncriptada.size());
    unsigned char* buffer = new unsigned char[tamano];
    for (int i = 0; i < tamano; i++) buffer[i] = claveEncriptada[i];

    string claveReal = decodificador(buffer, tamano, this->n, this->metodo);
    delete[] buffer;

    string intento;
    cout << "Ingrese clave de administrador: ";
    cin >> intento;

    if (intento != claveReal) {
        cout << "Clave incorrecta.\n";
        return false;
    }

    cout << "Acceso concedido.\n";
    return true;

}
