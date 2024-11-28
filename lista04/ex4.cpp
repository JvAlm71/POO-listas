#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

// Função para ordenar as strings conforme o critério especificado
void ordena_strings(std::vector<std::string>& vetor) {
    // Ordenando as strings com a condição desejada
    std::sort(vetor.begin(), vetor.end(), [](const std::string& a, const std::string& b) {
        if (a.size() == b.size()) {
            // Se o tamanho for o mesmo, ordena em ordem alfabética reversa
            return a > b;
        }
        // Caso contrário, ordena em ordem alfabética normal
        return a < b;
    });
}

int main() {
    // Inicializando o vetor de strings
    std::vector<std::string> v;
    v.push_back("aaaaaaaaaaa");
    v.push_back("zzzzzezzzzz");
    v.push_back("test");
    v.push_back("testando");
    v.push_back("testados");
    v.push_back("teste");

    // Chamando a função para ordenar o vetor
    ordena_strings(v);

    // Exibindo o vetor ordenado
    for (auto& s : v) { // Aqui usamos uma referência para evitar cópias desnecessárias
        std::cout << s << std::endl;
    }

    return 0;
}
