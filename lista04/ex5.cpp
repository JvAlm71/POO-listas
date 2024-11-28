#include <iostream>
#include <map>
#include <utility>

// Tipo para representar uma matriz esparsa
typedef std::map<std::pair<int, int>, int> Matriz;

// Função para somar duas matrizes esparsas
Matriz soma(const Matriz& A, const Matriz& B) {
    Matriz resultado;

    // Iterar sobre todos os elementos de A
    for (const auto& [pos, valor] : A) {
        resultado[pos] = valor + B.at(pos);  // Somar com o valor correspondente de B
    }
    
    // Iterar sobre todos os elementos de B
    for (const auto& [pos, valor] : B) {
        if (resultado.find(pos) == resultado.end()) { // Se ainda não foi somado, adicionar
            resultado[pos] = valor;
        }
    }
    
    return resultado;
}

int main() {
    // Definindo duas matrizes A e B
    Matriz A = { {{-1, -1}, 2}, {{0, 0}, 1} };
    Matriz B = { {{-1, -1}, 2}, {{1, 0}, 5} };

    // Somando as duas matrizes
    Matriz C = soma(A, B);

    // Imprimindo a matriz resultante
    for (const auto& [k, v] : C) {
        std::cout << k.first << " " << k.second << " " << v << std::endl;
    }

    return 0;
}
