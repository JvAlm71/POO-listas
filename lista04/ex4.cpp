#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

void ordena_strings(std::vector<std::string>& vetor) {
    std::sort(vetor.begin(), vetor.end(), [](const std::string& a, const std::string& b) {
        if (a.size() == b.size()) {
            return a > b;
        }
        return a < b;
    });
}

int main() {
    std::vector<std::string> v;
    v.push_back("aaaaaaaaaaa");
    v.push_back("zzzzzezzzzz");
    v.push_back("test");
    v.push_back("testando");
    v.push_back("testados");
    v.push_back("teste");

    ordena_strings(v);

    for (auto& s : v) { 
        std::cout << s << std::endl;
    }

    return 0;
}
