#include <iostream>

int main() {
    const int n = 7;  
    int vet[n] = {5, 1, 2, 3, 5, 1, 3}; 

    //numero maximo de frequencia
    const int maxfreq = 100000; 
    int freq[maxfreq] = {0}; 

  
    for (int i = 0; i < n; ++i) {
        freq[vet[i]]++; 
    }

    for (int i = 0; i < maxfreq; ++i) {
        if (freq[i] % 2 != 0) {
            std::cout << i << std::endl;
        }
    }

    return 0;
}
