#include <iostream>
#include <map>
#include <utility>

typedef std::map<std::pair<int, int>, int> Matriz;

Matriz soma(const Matriz& A, const Matriz& B) {
    Matriz resultado;

    for (const auto& [pos, valor] : A) {
        resultado[pos] = valor + B.at(pos);  
    }
    
    for (const auto& [pos, valor] : B) {
        if (resultado.find(pos) == resultado.end()) { 
            resultado[pos] = valor;
        }
    }
    
    return resultado;
}

int main() {
    Matriz A = { {{-1, -1}, 2}, {{0, 0}, 1} };
    Matriz B = { {{-1, -1}, 2}, {{1, 0}, 5} };

    Matriz C = soma(A, B);

    for (const auto& [k, v] : C) {
        std::cout << k.first << " " << k.second << " " << v << std::endl;
    }

    return 0;
}
