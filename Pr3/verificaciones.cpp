#include <iostream>
#include <string>

using namespace std;

bool esSoloNumeros(const string& texto) {
    for (size_t i = 0; i < texto.size(); i++) {
        if (texto[i] < '0' || texto[i] > '9') {
            return false;
        }
    }
    return true;
}

bool esAlfaNumerico(const string& texto) {
    for (size_t i = 0; i < texto.size(); i++) {
        char c = texto[i];
        bool esLetraMay = (c >= 'A' && c <= 'Z');
        bool esLetraMin = (c >= 'a' && c <= 'z');
        bool esNumero   = (c >= '0' && c <= '9');

        if (!(esLetraMay || esLetraMin || esNumero)) {
            return false;
        }
    }
    return true;
}
