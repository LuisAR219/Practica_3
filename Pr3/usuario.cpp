#include <iostream>
#include <fstream>
#include "usuario.h"
#include "codificador.cpp"

string metodo1(const string& texto, int n);
string metodo2(const string& texto, int n);

bool usuario::retirarSaldo(int cantidadRetirar){

    if (this->saldo<cantidadRetirar+1000){
        return false;
    }
    else{
        this->saldo-=cantidadRetirar;
        this->saldo-=1000;
        return true;
    }

}

int usuario::consultarSaldo(){

    if (this->saldo<1000){
        return -1;
    }
    else{
        this->saldo-=1000;
        return saldo;
    }

}

usuario::~usuario(){

    ifstream fileIn(archivoUsuarios);
    ofstream fileTemp("temp.txt");

    string linea;
    while (std::getline(fileIn, linea)) {
        size_t pos1 = linea.find(' ');
        size_t pos2 = linea.find(' ', pos1 + 1);

        string ced = linea.substr(0, pos1);
        string cla = linea.substr(pos1 + 1, pos2 - pos1 - 1);

        string cedulaEncriptada = "";
        string claveEncriptada = "";
        string saldoEncriptado = "";
        if (this->metodo == 1) {
            cedulaEncriptada =metodo1(this->cedula, this->n);
            claveEncriptada =metodo1(this->clave, this->n);
            saldoEncriptado =metodo1(to_string(this->saldo), this->n);
        }
        else if (this->metodo == 2) {
            cedulaEncriptada =metodo2(this->cedula, this->n);
            claveEncriptada =metodo2(this->clave, this->n);
            saldoEncriptado =metodo2(to_string(this->saldo), this->n);
        }

        if (ced == cedulaEncriptada && cla == claveEncriptada) {
            fileTemp << cedulaEncriptada << " " << claveEncriptada << " " << saldoEncriptado << "\n";
        }
        else {
            fileTemp << linea << "\n";
        }
    }

    fileIn.close();
    fileTemp.close();

    std::remove("usuarios.txt");
    std::rename("temp.txt", "usuarios.txt");
}
