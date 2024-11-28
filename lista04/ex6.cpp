#include <iostream>
#include <vector>

// Função para remover duplicatas e ordenar o vetor sem usar bibliotecas externas
std::vector<int> retira(std::vector<int> v, int n) {
    std::vector<int> resultado;
    
    // Inserir os elementos de 'v' na ordem e sem duplicatas
    for (int i = 0; i < v.size(); ++i) {
        bool encontrado = false;
        
        // Verificar se o elemento já está no vetor 'resultado' (remover duplicatas)
        for (int j = 0; j < resultado.size(); ++j) {
            if (resultado[j] == v[i]) {
                encontrado = true;
                break;
            }
        }
        
        // Se o elemento não foi encontrado em 'resultado', adiciona ele
        if (!encontrado || v[i] == n) {
            resultado.push_back(v[i]);
        }
    }
    
    // Ordenar o vetor 'resultado' manualmente (bubble sort)
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
        std::cout << e << std::endl;  // Saída esperada: 1, 3, 4, 5
    }
    
    return 0;
}
