#include <iostream>

int main() {
    int n, num, result = 0;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        std::cin >> num;
        result ^= num;
    }
    std::cout << (result != 0 ? result : 0) << std::endl;
    return 0;
}
