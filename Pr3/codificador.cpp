#include <iostream>
using namespace std;

bool leerBit(const unsigned char bits[], int pos) {
    int byteIndex = pos / 8;
    int bitIndex = 7 - (pos % 8);
    return (bits[byteIndex] >> bitIndex) & 1;
}

void escribirBit(unsigned char bits[], int pos, bool valor) {
    int byteIndex = pos / 8;
    int bitIndex = 7 - (pos % 8);
    if (valor)
        bits[byteIndex] |= (1 << bitIndex);
    else
        bits[byteIndex] &= ~(1 << bitIndex);
}

int textoABits(const char texto[], unsigned char bits[]) {
    int totalBits = 0;
    for (int k = 0; texto[k] != '\0'; k++) {
        unsigned char c = texto[k];
        for (int i = 7; i >= 0; i--) {
            bool bit = (c >> i) & 1;
            escribirBit(bits, totalBits++, bit);
        }
    }
    return totalBits;
}

void metodo1(const unsigned char bitsOriginal[], unsigned char bitsResultado[], int total, int n) {
    for (int i = 0; i < total; i++)
        escribirBit(bitsResultado, i, leerBit(bitsOriginal, i));

    int i = 0;
    while (i < total) {
        int unos = 0, ceros = 0;
        for (int j = 0; j < n && i + j < total; j++)
            leerBit(bitsOriginal, i + j) ? unos++ : ceros++;

        if (unos == ceros) {
            for (int j = 0; j < n && i + j < total; j++)
                escribirBit(bitsResultado, i + j, !leerBit(bitsOriginal, i + j));
        } else if (ceros > unos) {
            for (int j = 1; j < n && i + j < total; j += 2)
                escribirBit(bitsResultado, i + j, !leerBit(bitsOriginal, i + j));
        } else {
            for (int j = 2; j < n && i + j < total; j += 3)
                escribirBit(bitsResultado, i + j, !leerBit(bitsOriginal, i + j));
        }
        i += n;
    }
}

void metodo2(const unsigned char bitsOriginal[], unsigned char bitsResultado[], int total, int n) {
    for (int i = 0; i < total; i++)
        escribirBit(bitsResultado, i, leerBit(bitsOriginal, i));

    int i = 0;
    while (i < total) {
        if (i + n <= total) {
            bool ultimo = leerBit(bitsOriginal, i + n - 1);
            for (int j = n - 1; j > 0; j--)
                escribirBit(bitsResultado, i + j, leerBit(bitsOriginal, i + j - 1));
            escribirBit(bitsResultado, i, ultimo);
        }
        i += n;
    }
}

bool codificarTexto(const char texto[], int n, int metodo, unsigned char bitsCodificado[], int &totalBits) {
    if (texto[0] == '\0') {
        cout << "Error: texto vacío." << endl;
        return false;
    }

    if (n <= 0) {
        cout << "Error: n debe ser mayor que 0." << endl;
        return false;
    }

    if (metodo != 1 && metodo != 2) {
        cout << "Error: método inválido." << endl;
        return false;
    }

    unsigned char bitsOriginal[100] = {0};
    unsigned char bitsResultado[100] = {0};
    totalBits = textoABits(texto, bitsOriginal);

    if (n > totalBits) {
        cout << "Error: n no puede ser mayor que el total de bits (" << totalBits << ")." << endl;
        return false;
    }

    if (metodo == 1)
        metodo1(bitsOriginal, bitsResultado, totalBits, n);
    else
        metodo2(bitsOriginal, bitsResultado, totalBits, n);

    for (int i = 0; i < (totalBits + 7) / 8; i++)
        bitsCodificado[i] = bitsResultado[i];

    return true;
}

void imprimirBits(const unsigned char bits[], int totalBits) {
    for (int i = 0; i < totalBits; i++)
        cout << leerBit(bits, i);
    cout << endl;
}
