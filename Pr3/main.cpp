#include <iostream>
using namespace std;

void metodo1(int bits[], int total, int n);

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


int main() {

}
