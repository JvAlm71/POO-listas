#include <iostream>

int* primos(int n) {
    static int lista[10000];
    int indice = 0;
    for (int i = 2; i <= n; i++) {
        bool primo = true;
        for (int j = 2; j*j <= i; j++) {
            if (i % j == 0) {
                primo = false;
                break;
            }
        }
        if (primo) {
            lista[indice++] = i;
        }
    }
    lista[indice] = 0;
    return lista;
}

int main() {
    int n;
    std::cin >> n;
    int* lista = primos(n);
    for (int i = 0; lista[i] != 0; i++) {
        std::cout << lista[i] << (lista[i + 1] != 0 ? ", " : "");
    }
    std::cout << std::endl;
    return 0;
}
