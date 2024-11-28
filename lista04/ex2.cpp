#include <iostream>
#include <stack>
#include <queue>
#include <string>

std::string jogo(std::stack<int> cartas, std::queue<std::string> jogadores) {
    int soma[3] = {0}; // Armazena as somas das cartas para os 3 jogadores
    int i = 0; // Índice do jogador atual

    // Distribui as cartas entre os jogadores
    while (!cartas.empty()) {
        soma[i] += cartas.top();  // Adiciona a carta ao jogador i
        cartas.pop();  // Remove a carta da pilha

        // Avança para o próximo jogador
        i = (i + 1) % 3;
    }

    // Determina o vencedor
    std::string vencedor;
    int menor_soma = 1000;  // Valor alto inicial para garantir que qualquer soma será menor

    // Processa os jogadores
    for (int j = 0; !jogadores.empty(); j++) {
        std::string jogador = jogadores.front();
        jogadores.pop();
        
        // Verifica se o jogador atual tem a menor soma ou, em caso de empate, é lexicograficamente menor
        if (soma[j] < menor_soma || (soma[j] == menor_soma && jogador < vencedor)) {
            vencedor = jogador;
            menor_soma = soma[j];
        }
    }

    return vencedor;
}

int main() {
    std::stack<int> cartas;
    for (int e = 1; e <= 5; e++) {
        cartas.push(e);  // Adiciona as cartas de 1 a 5 na pilha
    }

    std::queue<std::string> jogadores;
    jogadores.push("andre");
    jogadores.push("bruno");
    jogadores.push("carla");

    // Chama a função e imprime o vencedor
    std::cout << jogo(cartas, jogadores) << std::endl;

    return 0;
}
