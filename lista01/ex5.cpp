#include <iostream>

void funcvetor(int vetor[], int n) {
    //int n = 7;
    //std::cin >> n;
    const int MAX_VAL = 1000000;
    int vetor[MAX_VAL];
    // int count = 0;
    int count[MAX_VAL + 1] = {0};

    for (int i = 0; i < n; i++) {
        std::cin >> vetor[i];  
        count[vetor[i]]++;
    }

     for (int i = 0; i < n; i++) {
        if (count[vetor[i]] % 2 != 0) {  
            std::cout << vetor[i] << " ";  
            count[vetor[i]] = 0;  
        }
    }

    std::cout << std::endl;
}

/*
int main() {
    int n = 7;
    //std::cin >> n;
    const int MAX_VAL = 1000000;
    int vetor[MAX_VAL];
    // int count = 0;
    int count[MAX_VAL + 1] = {0};

    for (int i = 0; i < n; i++) {
        std::cin >> vetor[i];  
        count[vetor[i]]++;
    }

     for (int i = 0; i < n; i++) {
        if (count[vetor[i]] % 2 != 0) {  
            std::cout << vetor[i] << " ";  
            count[vetor[i]] = 0;  
        }
    }

    std::cout << std::endl;

    return 0;
}*/
