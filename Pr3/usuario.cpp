#include "usuario.h"

void metodo1(const int bitsOriginal[], int bitsResultado[], int total, int n);
void metodo2(const int bitsOriginal[], int bitsResultado[], int total, int n);

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

    ifstream fileIn("usuarios.txt");
    ofstream fileTemp("temp.txt");

    string linea;
    while (std::getline(fileIn, linea)) {
        size_t pos1 = linea.find(' ');
        size_t pos2 = linea.find(' ', pos1 + 1);

        string ced = linea.substr(0, pos1);
        string cla = linea.substr(pos1 + 1, pos2 - pos1 - 1);

        string cedulaEncriptada = "";
        string claveEncriptada = "";
        if (metodo == 1) {
            metodo1(cedula, cedulaEncriptada, cedula.size(), n);
            metodo1(clave, claveEncriptada, clave.size(), n);
        }
        else if (metodo == 2) {
            metodo2(cedula, cedulaEncriptada, cedula.size(), n);
            metodo2(clave, claveEncriptada, clave.size(), n);
        }

        if (ced == cedulaEncriptada && cla == claveEncriptada) {
            fileTemp << cedulaEncriptada << " " << claveEncriptada << " " << saldo << "\n";
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
