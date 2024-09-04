#include <iostream>

int main() {
    int n;
    std::cin >> n;
    int* vet = new int[n];
    //numero maximo de frequencia
    const int maxfreq = 100000; 
    int freq[maxfreq] = {0}; 
    bool elemento_impresso = false;

    for (int i = 0; i < n; ++i) {
        std::cin >> vet[i]; 
    }

    for (int i = 0; i < n; ++i) {
        freq[vet[i]]++; 
    }

    for (int i = 0; i < maxfreq; ++i) {
        if (freq[i] % 2 != 0) {
            std::cout << i << std::endl;
            elemento_impresso = true;
        }
    }

    if (!elemento_impresso) {
        std::cout << 0 << std::endl;
    }
    
    delete[] vet;
    return 0;
}
