#include <iostream>
#include <vector>

std::vector<int> retira(std::vector<int> v, int n) {
    std::vector<int> resultado;
    
    for (int i = 0; i < v.size(); ++i) {
        bool encontrado = false;
        
        for (int j = 0; j < resultado.size(); ++j) {
            if (resultado[j] == v[i]) {
                encontrado = true;
                break;
            }
        }
        
        if (!encontrado || v[i] == n) {
            resultado.push_back(v[i]);
        }
    }
    
    for (int i = 0; i < resultado.size(); ++i) {
        for (int j = i + 1; j < resultado.size(); ++j) {
            if (resultado[i] > resultado[j]) {
                std::swap(resultado[i], resultado[j]);
            }
        }
    }
    
    return resultado;
}

int main() {
    std::vector<int> v = {5, 1, 8, 4, 3, 5};
    
    for (auto e : retira(v, 8)) {
        std::cout << e << std::endl;  
    }
    
    return 0;
}
