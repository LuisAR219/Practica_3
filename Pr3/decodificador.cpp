#include <iostream>

using namespace std;

unsigned int construirBloques(int bitsEnBloque,int bitInicial, const unsigned char* msjCodificado);
void escribirBits(int valorBit, unsigned char* decodificado, int &byteIndex, int &bitIndex);
int calcularBitsEnBloque(int bitInicial, int n, int numBits);

unsigned char* decodificador(unsigned char* msjCodificado, int tamanoCodificado, int n, int metodo){

    unsigned char* decodificado = new unsigned char[tamanoCodificado]();

    if (metodo==1){

        int numBits=tamanoCodificado*8, numBloques=(numBits+n-1)/n;

        int byteIndex=0, bitIndex=0, valorBit=0;
        unsigned int mascara=1, bloqueAnterior=0, bloque=0;

        for (int bloqueNum=0; bloqueNum<numBloques; bloqueNum++) {

            int bitInicial=bloqueNum*n;
            int bitsEnBloque=calcularBitsEnBloque(bitInicial,n,numBits);

            bloque=construirBloques(bitsEnBloque,bitInicial,msjCodificado);
            unsigned int bloqueCopia=bloque;

            if (bloqueNum==0){

                bloqueAnterior=bloqueCopia;

                for (int i=bitsEnBloque-1; i>=0; i--) {
                    bloqueCopia^=(mascara<<i);

                    valorBit=(bloqueCopia>>i)&1;
                    escribirBits(valorBit,decodificado,byteIndex,bitIndex);

                }

            }
            else {

                unsigned int bloqueAux=bloqueCopia;
                int ceros=0,unos=0;

                for (int i=bitsEnBloque-1; i>=0; i--) {
                    valorBit=(bloqueAnterior>>i)&1;

                    if (valorBit==true){
                        unos++;
                    }
                    else{
                        ceros++;
                    }
                }
                if (ceros==unos){

                    for (int i=bitsEnBloque-1; i>=0; i--) {
                        bloqueCopia^=(mascara<<i);

                        valorBit=(bloqueCopia>>i)&1;
                        escribirBits(valorBit,decodificado,byteIndex,bitIndex);
                    }
                }

                else if (ceros>unos){

                    for (int i=bitsEnBloque-1; i>=0; i--) {

                        if (i % 2 == 0) {
                            bloqueCopia^= (mascara << i);
                        }

                        valorBit = (bloqueCopia>> i) & 1;
                        escribirBits(valorBit,decodificado,byteIndex,bitIndex);

                    }
                }
                else{

                    for (int i=bitsEnBloque-1; i>=0; i--) {

                        if (i % 3 == 0) {
                            bloqueCopia^= (mascara << i);
                        }

                        valorBit = (bloqueCopia>> i) & 1;
                        escribirBits(valorBit,decodificado,byteIndex,bitIndex);

                    }
                }
                bloqueAnterior=bloqueAux;
            }
        }
        return decodificado;
    }

    else if (metodo==2){

        int numBits=tamanoCodificado*8, numBloques=(numBits+n-1)/n;

        int byteIndex=0, bitIndex=0, valorBit=0;
        unsigned int bloque=0, mascara=1;

        for (int bloqueNum=0; bloqueNum<numBloques; bloqueNum++) {

            int bitInicial=bloqueNum*n;
            int bitsEnBloque=calcularBitsEnBloque(bitInicial,n,numBits);

            bloque=construirBloques(bitsEnBloque,bitInicial,msjCodificado);

            unsigned int mascaraBits = (1u << bitsEnBloque) - 1;
            unsigned int bloqueModificado=((bloque << 1) & mascaraBits) | ((bloque >> (bitsEnBloque - 1)) & mascara);

            for (int i = bitsEnBloque - 1; i >= 0; i--) {
                valorBit = (bloqueModificado >> i) & 1;
                escribirBits(valorBit, decodificado, byteIndex, bitIndex);
            }
        }

        return decodificado;

    }
    else{
        delete[] decodificado;
        return nullptr;
    }
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

