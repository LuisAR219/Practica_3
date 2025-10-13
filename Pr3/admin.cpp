#include <iostream>
#include <string>
#include <fstream>
using namespace std;

unsigned int construirBloques(int bitsEnBloque,int bitInicial, const unsigned char* msjCodificado);
void escribirBits(int valorBit, unsigned char* decodificado, int &byteIndex, int &bitIndex);
int calcularBitsEnBloque(int bitInicial, int n, int numBits);
string decodificador(unsigned char* msjCodificado, int tamanoCodificado, int n, int metodo);
string metodo1(const string& texto, int n);
string metodo2(const string& texto, int n);

#include "usuario.h"

bool registroAdmin(int n, int metodo) {
    ifstream file("sudo.txt");
    string claveEncriptada;
    getline(file, claveEncriptada);
    file.close();

    int tamano = static_cast<int>(claveEncriptada.size());
    unsigned char* buffer = new unsigned char[tamano];
    for (int i = 0; i < tamano; i++) buffer[i] = claveEncriptada[i];

    string claveReal = decodificador(buffer, tamano, n, metodo);
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

void crearUsuario(int n, int metodo) {
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

    if (metodo == 1) {
        resultadoCedula = metodo1(cedula, n);
        resultadoClave  = metodo1(clave, n);
        resultadoSaldo  = metodo1(saldo, n);
    }
    else if (metodo == 2) {
        resultadoCedula = metodo2(cedula, n);
        resultadoClave  = metodo2(clave, n);
        resultadoSaldo  = metodo2(saldo, n);
    }

    file << resultadoCedula << " " << resultadoClave << " " << resultadoSaldo << endl;
    file.close();

    cout << "Usuario registrado con exito.\n";
}

usuario* registroUsuario(int n, int metodo, string cedula, string clave) {
    string cedulaEncriptada = "";
    string claveEncriptada = "";

    if (metodo == 1) {
        cedulaEncriptada = metodo1(cedula, n);
        claveEncriptada  = metodo1(clave, n);
    }
    else if (metodo == 2) {
        cedulaEncriptada = metodo2(cedula, n);
        claveEncriptada  = metodo2(clave, n);
    }

    ifstream file("usuarios.txt");
    string linea;
    while (getline(file, linea)) {
        size_t pos1 = linea.find(' ');
        size_t pos2 = linea.find(' ', pos1 + 1);

        string ced = linea.substr(0, pos1);
        string cla = linea.substr(pos1 + 1, pos2 - pos1 - 1);
        string sal = linea.substr(pos2 + 1);

        if (ced == cedulaEncriptada && cla == claveEncriptada) {
            int saldo = stoi(sal);
            file.close();
            usuario* userActual = new usuario(cedula, clave, saldo);
            return userActual;
        }
    }
    file.close();
    return nullptr;
}

