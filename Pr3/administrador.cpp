#include <iostream>
#include <fstream>
#include "administrador.h"

string metodo1(const string& texto, int n);
string metodo2(const string& texto, int n);
string decodificador(unsigned char* msjCodificado, int tamanoCodificado, int n, int metodo);
bool esSoloNumeros(const string& texto);
bool esAlfaNumerico(const string& texto);

void administrador::crearUsuario(){
    string cedula, clave, saldo;

    do {
        cout << "Cedula (10 digitos, solo numeros): ";
        cin >> cedula;

        if (cedula.length() != 10) {
            cout << "La cedula debe tener exactamente 10 caracteres.\n";
            continue;
        }
        if (!esSoloNumeros(cedula)) {
            cout << "La cedula solo puede contener numeros.\n";
            continue;
        }
        break;
    } while (true);

    do {
        cout << "Clave (solo letras y numeros): ";
        cin >> clave;

        if (!esAlfaNumerico(clave)) {
            cout << "La clave solo puede contener letras y numeros.\n";
            continue;
        }
        break;
    } while (true);

    do {
        cout << "Saldo inicial (solo numeros): ";
        cin >> saldo;

        if (!esSoloNumeros(saldo)) {
            cout << "El saldo solo puede contener numeros.\n";
            continue;
        }
        break;
    } while (true);

    ofstream file(this->archivoUsuario, ios::app);
    if (!file) {
        cerr << "Error al abrir el archivo de usuarios.\n";
        return;
    }

    string resultadoCedula, resultadoClave, resultadoSaldo;

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
    else {
        cout << "Metodo no valido.\n";
        file.close();
        return;
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

bool administrador::registroAdmin(int n, int metodo){

    ifstream file(this->archivoAdmin);
    if (!file.is_open()) {
        cerr << "Error: no se pudo abrir el archivo de administrador.\n";
        return false;
    }
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


