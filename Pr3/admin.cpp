#include <iostream>
#include <string>
#include <fstream>

using namespace std;

unsigned int construirBloques(int bitsEnBloque,int bitInicial, const unsigned char* msjCodificado);
void escribirBits(int valorBit, unsigned char* decodificado, int &byteIndex, int &bitIndex);
int calcularBitsEnBloque(int bitInicial, int n, int numBits);
string decodificador(unsigned char* msjCodificado, int tamanoCodificado, int n, int metodo);
void metodo1(const int bitsOriginal[], int bitsResultado[], int total, int n);
void metodo2(const int bitsOriginal[], int bitsResultado[], int total, int n);

#include "usuario.h"

bool registroAdmin(int n, int metodo) {
    ifstream file("sudo.txt");
    string claveEncriptada;
    getline(file, claveEncriptada);
    file.close();

    int tamano = static_cast<int>(claveEncriptada.size());

    string claveReal = decodificador(claveEncriptada, tamano, n, metodo);

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

void crearUsuario(int n, int metodo){
    string cedula, clave, saldo;

    cout << "Cedula: ";
    cin >> cedula;
    cout << "Clave: ";
    cin >> clave;
    cout << "Saldo inicial: ";
    cin >> saldo;

    ofstream file("usuarios.txt", ios::app);

    if (metodo==1){
        string resultadoCedula="";
        string resultadoClave="";
        string resultadoSaldo="";
        metodo1(cedula,resultadoCedula,cedula.size(),n);
        metodo1(clave, resultadoClave, clave.size(),n);
        metodo1(saldo, resultadoSaldo, saldo.size(),n);
        file << resultadoCedula << " " << resultadoClave << " " << resultadoSaldo << endl;
    }
    else if(metodo==2){
        string resultadoCedula="";
        string resultadoClave="";
        string resultadoSaldo="";
        metodo2(cedula,resultadoCedula,cedula.size(),n);
        metodo2(clave, resultadoClave, clave.size(),n);
        metodo2(saldo, resultadoSaldo, saldo.size(),n);
        file << resultadoCedula << " " << resultadoClave << " " << resultadoSaldo << endl;
    }

    file.close();
    cout << "Usuario registrado con exito.\n";
}

usuario* registroUsuario(int n, int metodo, string cedula, string clave){

    string cedulaEncriptada = "";
    string claveEncriptada = "";
    if (metodo == 1) {
        metodo1(cedula, cedulaEncriptada, cedula.size(), n);
        metodo1(clave, claveEncriptada, clave.size(), n);
    } else if (metodo == 2) {
        metodo2(cedula, cedulaEncriptada, cedula.size(), n);
        metodo2(clave, claveEncriptada, clave.size(), n);
    }

    ifstream file("usuarios.txt");

    string linea;
    while (std::getline(file, linea)) {
        size_t pos1 = linea.find(' ');
        size_t pos2 = linea.find(' ', pos1 + 1);

        std::string ced = linea.substr(0, pos1);
        std::string cla = linea.substr(pos1 + 1, pos2 - pos1 - 1);
        std::string sal = linea.substr(pos2 + 1);

        if (ced == cedulaEncriptada && cla == claveEncriptada) {
            int saldo = stoi(sal);
            file.close();
            usuario* userActual;
            userActual=new usuario(cedula, clave, saldo);
            return userActual;
        }
    }
    file.close();
    return nullptr;
}
