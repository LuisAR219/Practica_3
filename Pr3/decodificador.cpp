#include <iostream>
#include <string>

using namespace std;

unsigned int construirBloques(int bitsEnBloque,int bitInicial, const unsigned char* msjCodificado);
void escribirBits(int valorBit, unsigned char* decodificado, int &byteIndex, int &bitIndex);
int calcularBitsEnBloque(int bitInicial, int n, int numBits);

bool leerBitDecodificador(const unsigned char* bits, int pos) {
    int byteIndex = pos / 8;
    int bitIndex = 7 - (pos % 8);
    return (bits[byteIndex] >> bitIndex) & 1;
}

string decodificador(unsigned char* msjCodificado, int tamanoCodificado, int n, int metodo) {
    unsigned char* decodificado = new unsigned char[tamanoCodificado]();

    if (metodo == 1) {
        int numBits = tamanoCodificado * 8;
        int numBloques = (numBits + n - 1) / n;

        int byteIndex = 0, bitIndex = 0;
        unsigned int mascara = 1;

        for (int bloqueNum = 0; bloqueNum < numBloques; bloqueNum++) {
            int bitInicial = bloqueNum * n;
            int bitsEnBloque = calcularBitsEnBloque(bitInicial, n, numBits);

            unsigned int bloqueCodificado = construirBloques(bitsEnBloque, bitInicial, msjCodificado);
            unsigned int bloqueProcesado = bloqueCodificado;

            if (bloqueNum == 0) {
                for (int i = bitsEnBloque - 1; i >= 0; i--) {
                    bloqueProcesado ^= (mascara << i);
                    bool valorBit = (bloqueProcesado >> i) & 1;
                    escribirBits(valorBit ? 1 : 0, decodificado, byteIndex, bitIndex);
                }
            } else {
                int unos = 0, ceros = 0;

                for (int j = bitInicial - n; j < bitInicial && j < numBits; j++) {
                    if (leerBitDecodificador(decodificado, j)) {
                        unos++;
                    } else {
                        ceros++;
                    }
                }

                if (unos == ceros) {
                    for (int i = bitsEnBloque - 1; i >= 0; i--) {
                        bloqueProcesado ^= (mascara << i);
                        bool valorBit = (bloqueProcesado >> i) & 1;
                        escribirBits(valorBit ? 1 : 0, decodificado, byteIndex, bitIndex);
                    }
                } else if (ceros > unos) {
                    for (int i = bitsEnBloque - 1; i >= 0; i--) {
                        int posRelativa = bitsEnBloque - 1 - i;
                        if (posRelativa % 2 == 1) {
                            bloqueProcesado ^= (mascara << i);
                        }
                        bool valorBit = (bloqueProcesado >> i) & 1;
                        escribirBits(valorBit ? 1 : 0, decodificado, byteIndex, bitIndex);
                    }
                } else {
                    for (int i = bitsEnBloque - 1; i >= 0; i--) {
                        int posRelativa = bitsEnBloque - 1 - i;
                        if ((posRelativa + 1) % 3 == 0) {
                            bloqueProcesado ^= (mascara << i);
                        }
                        bool valorBit = (bloqueProcesado >> i) & 1;
                        escribirBits(valorBit ? 1 : 0, decodificado, byteIndex, bitIndex);
                    }
                }
            }
        }

        string resultado(reinterpret_cast<char*>(decodificado), tamanoCodificado);
        delete[] decodificado;
        return resultado;
    }
    else if (metodo == 2) {
        int numBits = tamanoCodificado * 8;
        int numBloques = (numBits + n - 1) / n;

        int byteIndex = 0, bitIndex = 0, valorBit = 0;
        unsigned int bloque = 0, mascara = 1;

        for (int bloqueNum = 0; bloqueNum < numBloques; bloqueNum++) {
            int bitInicial = bloqueNum * n;
            int bitsEnBloque = calcularBitsEnBloque(bitInicial, n, numBits);

            bloque = construirBloques(bitsEnBloque, bitInicial, msjCodificado);

            unsigned int mascaraBits = (1u << bitsEnBloque) - 1;
            unsigned int bloqueModificado = ((bloque << 1) & mascaraBits) | ((bloque >> (bitsEnBloque - 1)) & mascara);

            for (int i = bitsEnBloque - 1; i >= 0; i--) {
                valorBit = (bloqueModificado >> i) & 1;
                escribirBits(valorBit, decodificado, byteIndex, bitIndex);
            }
        }

        string resultado(reinterpret_cast<char*>(decodificado), tamanoCodificado);
        delete[] decodificado;
        return resultado;
    }

    return "";
}

unsigned int construirBloques(int bitsEnBloque, int bitInicial, const unsigned char* msjCodificado) {
    unsigned int bloque = 0;
    int valorBit = 0;

    for (int i = 0; i < bitsEnBloque; i++) {
        int bitActual = bitInicial + i;
        int byteContenedor = bitActual / 8;
        int posicionBit = 7 - (bitActual % 8);
        unsigned char byte = msjCodificado[byteContenedor];
        valorBit = (byte >> posicionBit) & 1;
        bloque = (bloque << 1) | valorBit;
    }
    return bloque;
}

void escribirBits(int valorBit, unsigned char* decodificado, int &byteIndex, int &bitIndex) {
    if (valorBit == 1) {
        decodificado[byteIndex] |= (1u << (7 - bitIndex));
    } else {
        decodificado[byteIndex] &= ~(1u << (7 - bitIndex));
    }
    bitIndex++;
    if (bitIndex == 8) {
        bitIndex = 0;
        byteIndex++;
    }
}

int calcularBitsEnBloque(int bitInicial, int n, int numBits) {
    int bitsEnBloque;
    if (bitInicial + n <= numBits) {
        bitsEnBloque = n;
    } else {
        bitsEnBloque = numBits - bitInicial;
    }
    return bitsEnBloque;
}

