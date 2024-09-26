#include <iostream>

int main() {
    int n;
    std::cin >> n;
    for (int i = 1; i <= n; i++) {
        std::cout << i * 3 * 5 * 7 * 11 * 17 << std::endl;
    }
    return 0;
}
