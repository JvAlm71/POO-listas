#include <iostream>
#include <stack>

int elementok(std::stack<int>& pilha, int k) {
    std::stack<int> pilha_copia = pilha;  
    int contagem = 0; 

    while (!pilha_copia.empty()) {
        int topo = pilha_copia.top();
        pilha_copia.pop();

        if (topo % 2 == 0) {
            contagem++;
            if (contagem == k) {
                return topo;
            }
        }
    }

    return -1;
}

int main() {
    // Inicialização da pilha
    std::stack<int> pilha;
    for (int e = 5; e >= 1; e--) {
        pilha.push(e);
    }

    // Teste de fato
    std::cout << elementok(pilha, 2) << std::endl;

    // Verificando se a pilha está igual após o teste
    while (!pilha.empty()) {
        std::cout << pilha.top() << " ";
        pilha.pop();
    }
    std::cout << std::endl;

    return 0;
}
