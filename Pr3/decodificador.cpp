#include <iostream>
#include <string>

using namespace std;

unsigned int construirBloques(int bitsEnBloque, int bitInicial, const unsigned char* msjCodificado);
void escribirBits(int valorBit, unsigned char* decodificado, int &byteIndex, int &bitIndex);
int calcularBitsEnBloque(int bitInicial, int n, int numBits);

string decodificador(unsigned char* msjCodificado, int tamanoCodificado, int n, int metodo) {
    unsigned char* decodificado = new unsigned char[tamanoCodificado + 1]();

    if (metodo == 1) {
        int numBits = tamanoCodificado * 8;
        int numBloques = (numBits + n - 1) / n;

        int byteIndex = 0, bitIndex = 0;

        unsigned int* bloquesOriginales = new unsigned int[numBloques]();
        unsigned int* bloquesDecodificados = new unsigned int[numBloques]();

        for (int bloqueNum = 0; bloqueNum < numBloques; bloqueNum++) {
            int bitInicial = bloqueNum * n;
            int bitsEnBloque = calcularBitsEnBloque(bitInicial, n, numBits);
            bloquesOriginales[bloqueNum] = construirBloques(bitsEnBloque, bitInicial, msjCodificado);
        }

        for (int bloqueNum = 0; bloqueNum < numBloques; bloqueNum++) {
            int bitInicial = bloqueNum * n;
            int bitsEnBloque = calcularBitsEnBloque(bitInicial, n, numBits);
            unsigned int bloqueCodificado = bloquesOriginales[bloqueNum];
            unsigned int bloqueDecodificado = bloqueCodificado;

            if (bloqueNum == 0) {
                bloqueDecodificado = (~bloqueCodificado) & ((1u << bitsEnBloque) - 1);
            } else {
                unsigned int bloqueAnteriorDecod = bloquesDecodificados[bloqueNum - 1];
                int bitsAnterior = calcularBitsEnBloque((bloqueNum - 1) * n, n, numBits);

                int unos = 0, ceros = 0;
                for (int i = 0; i < bitsAnterior; i++) {
                    if ((bloqueAnteriorDecod >> (bitsAnterior - 1 - i)) & 1) {
                        unos++;
                    } else {
                        ceros++;
                    }
                }

                if (ceros == unos) {
                    bloqueDecodificado = (~bloqueCodificado) & ((1u << bitsEnBloque) - 1);
                } else if (ceros > unos) {
                    for (int pos = 1; pos <= bitsEnBloque; pos++) {
                        if (pos % 2 == 0) {
                            int bitIndex = bitsEnBloque - pos;
                            bloqueDecodificado ^= (1u << bitIndex);
                        }
                    }
                } else {
                    for (int pos = 1; pos <= bitsEnBloque; pos++) {
                        if (pos % 3 == 0) {
                            int bitIndex = bitsEnBloque - pos;
                            bloqueDecodificado ^= (1u << bitIndex);
                        }
                    }
                }
            }

            bloquesDecodificados[bloqueNum] = bloqueDecodificado;

            for (int i = bitsEnBloque - 1; i >= 0; i--) {
                int valorBit = (bloqueDecodificado >> i) & 1;
                escribirBits(valorBit, decodificado, byteIndex, bitIndex);
            }
        }

        delete[] bloquesOriginales;
        delete[] bloquesDecodificados;

        string resultado(reinterpret_cast<char*>(decodificado), byteIndex + (bitIndex > 0 ? 1 : 0));
        delete[] decodificado;
        return resultado;

    }
    else if (metodo == 2) {
        int numBits = tamanoCodificado * 8;
        int numBloques = (numBits + n - 1) / n;

        int byteIndex = 0, bitIndex = 0;

        for (int bloqueNum = 0; bloqueNum < numBloques; bloqueNum++) {
            int bitInicial = bloqueNum * n;
            int bitsEnBloque = calcularBitsEnBloque(bitInicial, n, numBits);

            if (bitsEnBloque < n) {
                for (int i = 0; i < bitsEnBloque; i++) {
                    int bitActual = bitInicial + i;
                    int byteContenedor = bitActual / 8;
                    int posicionBit = 7 - (bitActual % 8);
                    bool valorBit = (msjCodificado[byteContenedor] >> posicionBit) & 1;
                    escribirBits(valorBit, decodificado, byteIndex, bitIndex);
                }
            } else {
                unsigned int bloque = construirBloques(bitsEnBloque, bitInicial, msjCodificado);

                unsigned int mascaraBits = (1u << bitsEnBloque) - 1;
                unsigned int bitMasSignificativo = (bloque >> (bitsEnBloque - 1)) & 1;
                unsigned int bloqueDecodificado = ((bloque << 1) | bitMasSignificativo) & mascaraBits;

                for (int i = bitsEnBloque - 1; i >= 0; i--) {
                    int valorBit = (bloqueDecodificado >> i) & 1;
                    escribirBits(valorBit, decodificado, byteIndex, bitIndex);
                }
            }
        }

        string resultado(reinterpret_cast<char*>(decodificado), byteIndex + (bitIndex > 0 ? 1 : 0));
        delete[] decodificado;
        return resultado;
    }

    delete[] decodificado;
    return "";
}


unsigned int construirBloques(int bitsEnBloque,int bitInicial, const unsigned char* msjCodificado){

    unsigned int bloque=0;
    int valorBit=0;

    for (int i=0; i<bitsEnBloque; i++) {
        int bitActual=bitInicial+i;

        int byteContenedor=bitActual/8; //Byte de msjCodificado que contiene a bitActual
        int pocisionBit=7-(bitActual%8); //Posicion bitActual dentro de byteContenedor

        unsigned char byte=msjCodificado[byteContenedor];
        valorBit=(byte>>pocisionBit)&1;

        bloque=(bloque<<1)|valorBit; //Construyo el bloque de n bits
    }
    return bloque;
}

void escribirBits(int valorBit, unsigned char* decodificado, int &byteIndex, int &bitIndex){

    if (valorBit==true){
        decodificado[byteIndex] |= (1u << (7 - bitIndex)); //Escribo un 1
    }
    else {
        decodificado[byteIndex] &= ~(1u << (7 - bitIndex)); //Escribo un 0
    }
    bitIndex++;
    if (bitIndex == 8) { //Pasa al siguiente byte
        bitIndex = 0;
        byteIndex++;
    }

}

int calcularBitsEnBloque(int bitInicial, int n, int numBits){

    int bitsEnBloque;
    if (bitInicial + n <= numBits) {
        bitsEnBloque = n;  //Mensaje multiplo de n
    }
    else {
        bitsEnBloque = numBits - bitInicial;  //Bits sobrantes (no multiplo de n)
    }
    return bitsEnBloque;

}

