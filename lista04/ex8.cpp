#include <iostream>
#include <vector>
#include <algorithm>

typedef std::vector<std::vector<int>> Matriz;

void ordena_par(Matriz& M) {
    std::sort(M.begin(), M.end(), [](const std::vector<int>& a, const std::vector<int>& b) {
        int pares_a = std::count_if(a.begin(), a.end(), [](int x) { return x % 2 == 0; });
        int pares_b = std::count_if(b.begin(), b.end(), [](int x) { return x % 2 == 0; });

        if (pares_a != pares_b) {
            return pares_a < pares_b;
        }
        return a < b;
    });
}

int main() {
    int nl, nc;
    std::cin >> nl >> nc;

    Matriz m(nl, std::vector<int>(nc));
    for (int i = 0; i < nl; i++) {
        for (int j = 0; j < nc; j++) {
            std::cin >> m[i][j];
        }
    }

    ordena_par(m);

    for (int i = 0; i < nl; i++) {
        for (int j = 0; j < nc; j++) {
            std::cout << m[i][j] << " ";
        }
        std::cout << std::endl;
    }

    return 0;
}
