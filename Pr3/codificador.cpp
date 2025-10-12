#include <iostream>
using namespace std;

void charABinario(unsigned char c, int bin[8]) {
    for (int i = 7; i >= 0; i--) {
        bin[i] = c % 2;
        c = c / 2;
    }
}

void metodo1(int bits[], int total, int n) {
    int i = 0;
    while (i < total) {
        int unos = 0, ceros = 0;

        for (int j = 0; j < n && i + j < total; j++) {
            if (bits[i + j] == 1) unos++;
            else ceros++;
        }

        if (unos == ceros) {
            for (int j = 0; j < n && i + j < total; j++) {
                bits[i + j] = (bits[i + j] == 0 ? 1 : 0);
            }
        }
        else if (ceros > unos) {
            for (int j = 1; j < n && i + j < total; j += 2) {
                bits[i + j] = (bits[i + j] == 0 ? 1 : 0);
            }
        }
        else {
            for (int j = 2; j < n && i + j < total; j += 3) {
                bits[i + j] = (bits[i + j] == 0 ? 1 : 0);
            }
        }

        i += n;
    }
}

void metodo2(int bits[], int total, int n) {
    int i = 0;
    while (i < total) {
        if (i + n <= total) {
            int ultimo = bits[i + n - 1];
            for (int j = n - 1; j > 0; j--) {
                bits[i + j] = bits[i + j - 1];
            }
            bits[i] = ultimo;
        }
        i += n;
    }
}

bool codificarTexto(const char texto[], int n, int metodo, int bits[], int &total) {
    total = 0;

    if (texto[0] == '\0') {
        cout << "Error: no ingreso texto valido." << endl;
        return false;
    }

    if (n <= 0) {
        cout << "Error: n debe ser mayor que 0." << endl;
        return false;
    }

    if (metodo != 1 && metodo != 2) {
        cout << "Error: metodo invalido." << endl;
        return false;
    }

    for (int k = 0; texto[k] != '\0'; k++) {
        int bin[8];
        charABinario(texto[k], bin);
        for (int j = 0; j < 8; j++) {
            bits[total++] = bin[j];
        }
    }

    if (n > total) {
        cout << "Error: n no puede ser mayor al total de bits (" << total << ")." << endl;
        return false;
    }

    if (metodo == 1) metodo1(bits, total, n);
    else metodo2(bits, total, n);

    return true;
}
