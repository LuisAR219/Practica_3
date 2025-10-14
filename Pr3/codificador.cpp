#include <string>
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

int textoABits(const string& texto, unsigned char bits[]) {
    int totalBits = 0;
    for (size_t k = 0; k < texto.size(); k++) {
        unsigned char c = texto[k];
        for (int i = 7; i >= 0; i--) {
            bool bit = (c >> i) & 1;
            escribirBit(bits, totalBits++, bit);
        }
    }
    return totalBits;
}

string bitsATexto(const unsigned char bits[], int totalBits) {
    string texto;
    for (int i = 0; i < totalBits; i += 8) {
        unsigned char c = 0;
        for (int j = 0; j < 8 && i + j < totalBits; j++) {
            c <<= 1;
            c |= leerBit(bits, i + j);
        }
        texto.push_back(c);
    }
    return texto;
}


string metodo1(const string& texto, int n) {
    unsigned char bitsOriginal[100] = {0};
    unsigned char bitsResultado[100] = {0};

    int total = textoABits(texto, bitsOriginal);

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

    return bitsATexto(bitsResultado, total);
}

string metodo2(const string& texto, int n) {
    unsigned char bitsOriginal[100] = {0};
    unsigned char bitsResultado[100] = {0};

    int total = textoABits(texto, bitsOriginal);

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

    return bitsATexto(bitsResultado, total);
}
