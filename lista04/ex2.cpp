#include <iostream>
#include <stack>
#include <queue>
#include <string>

std::string jogo(std::stack<int> cartas, std::queue<std::string> jogadores) {
    
    int soma[3] = {0};  
    
    int i = 0;
    while (!cartas.empty()) {
        soma[i] += cartas.top();
        cartas.pop();
        
        i = (i + 1) % 3;
    }

    std::string vencedor;
    int menor_soma = 1000;  

    jogadores.push(jogadores.front()); jogadores.pop();  
    jogadores.push(jogadores.front()); jogadores.pop();  
    jogadores.push(jogadores.front()); jogadores.pop();  

    for (int j = 0; !jogadores.empty(); j++) {
        std::string jogador = jogadores.front();
        jogadores.pop();
        
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
        cartas.push(e);
    }

    std::queue<std::string> jogadores;
    jogadores.push("andre");
    jogadores.push("bruno");
    jogadores.push("carla");

    std::cout << jogo(cartas, jogadores) << std::endl;  

    return 0;
}
