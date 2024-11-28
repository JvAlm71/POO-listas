#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>

void ordena_versoes(std::vector<std::string>& versoes) {
    std::sort(versoes.begin(), versoes.end(), [](const std::string& a, const std::string& b) {
        std::stringstream ss_a(a), ss_b(b);
        std::string token_a, token_b;
        int num_a, num_b;

        // Compare as versões token por token
        while (std::getline(ss_a, token_a, '.') && std::getline(ss_b, token_b, '.')) {
            num_a = std::stoi(token_a);
            num_b = std::stoi(token_b);
            if (num_a != num_b) {
                return num_a < num_b;
            }
        }

        // Se uma versão tem mais números, ela é maior
        return ss_a.eof() && !ss_b.eof(); 
    });
}

int main() {
    std::vector<std::string> vs = {"1.2.3", "1.2", "1.2.0", "3.0", "0"};
    
    ordena_versoes(vs);
    
    for (auto v : vs) {
        std::cout << v << std::endl;
    }
    
    return 0;
}
