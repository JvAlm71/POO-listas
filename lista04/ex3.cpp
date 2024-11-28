#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <algorithm>

void advinha_estrutura(std::vector<std::string>& operacoes) {
    std::stack<int> pilha;
    std::queue<int> fila;
    std::priority_queue<int> prioridade;

    bool isPilha = true;
    bool isFila = true;
    bool isPrioridade = true;

    for (const auto& operacao : operacoes) {
        std::string comando;
        int numero;
        size_t pos = operacao.find(" ");
        comando = operacao.substr(0, pos);
        numero = std::stoi(operacao.substr(pos + 1));

        if (comando == "add") {
            pilha.push(numero);
            fila.push(numero);
            prioridade.push(numero);
        } else if (comando == "pop") {
            if (isPilha) {
                if (pilha.empty() || pilha.top() != numero) {
                    isPilha = false;
                } else {
                    pilha.pop();
                }
            }
            if (isFila) {
                if (fila.empty() || fila.front() != numero) {
                    isFila = false;
                } else {
                    fila.pop();
                }
            }
            if (isPrioridade) {
                if (prioridade.empty() || prioridade.top() != numero) {
                    isPrioridade = false;
                } else {
                    prioridade.pop();
                }
            }
        }
    }

    if (isPilha && !isFila && !isPrioridade) {
        std::cout << "stack" << std::endl;
    } else if (!isPilha && isFila && !isPrioridade) {
        std::cout << "queue" << std::endl;
    } else if (!isPilha && !isFila && isPrioridade) {
        std::cout << "priority" << std::endl;
    } else if (isPilha && isFila && !isPrioridade) {
        std::cout << "both" << std::endl;
    } else if (isPilha && !isFila && isPrioridade) {
        std::cout << "both" << std::endl;
    } else if (!isPilha && isFila && isPrioridade) {
        std::cout << "both" << std::endl;
    } else {
        std::cout << "none" << std::endl;
    }
}

int main() {
    std::vector<std::string> operacoes = {
        "add 1",
        "add 2",
        "add 3",
        "pop 3",
        "pop 2",
        "pop 1"
    };

    advinha_estrutura(operacoes);

    return 0;
}
