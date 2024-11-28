#include <iostream>
#include <stack>
#include <queue>
#include <string>

std::string jogo(std::stack<int> cartas, std::queue<std::string> jogadores) {
    // Array para armazenar as somas das cartas de cada jogador
    int soma[3] = {0}; 
    int i = 0; // Índice para iterar sobre os jogadores

    // Distribui as cartas entre os jogadores
    while (!cartas.empty()) {
        soma[i] += cartas.top();  // Adiciona a carta ao jogador i
        cartas.pop();  // Remove a carta da pilha

        i = (i + 1) % 3; // Avança para o próximo jogador (circular)
    }

    // Variáveis para determinar o vencedor
    std::string vencedor;
    int menor_soma = 1000;  // Valor alto inicial para garantir que qualquer soma será menor

    // Processa os jogadores e calcula quem tem a menor soma ou, em caso de empate, o nome lexicograficamente menor
    for (int j = 0; j < 3; j++) {  // Limitar a 3 jogadores
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
    // Pilha de cartas (inicializando com 5 cartas de 1 a 5)
    std::stack<int> cartas;
    for (int e = 1; e <= 5; e++) {
        cartas.push(e);
    }

    // Fila de jogadores
    std::queue<std::string> jogadores;
    jogadores.push("andre");
    jogadores.push("bruno");
    jogadores.push("carla");

    // Chama a função para determinar o vencedor e imprime o resultado
    std::cout << jogo(cartas, jogadores) << std::endl;

    return 0;
}
