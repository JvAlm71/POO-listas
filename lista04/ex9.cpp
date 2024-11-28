#include <iostream>
#include <vector>
#include <string>
#include <sstream>

std::vector<double> notas(std::string s) {
    std::vector<double> notas_vec;
    std::stringstream ss(s);
    std::string token;
    
    while (std::getline(ss, token, ',')) {
        // Ignorar os nomes (que são em posições pares) e pegar as notas (em posições ímpares)
        if (std::getline(ss, token, ',')) {
            notas_vec.push_back(std::stod(token)); // Convertendo para double e adicionando ao vetor
        }
    }
    
    return notas_vec;
}

int main() {
    std::string s = "Andre,10,Smaira,5";
    
    for (double n : notas(s)) {
        std::cout << n << std::endl;
    }

    return 0;
}
