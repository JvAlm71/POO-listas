#include <iostream>

int fib(unsigned long long int n, int m) {
    if (n <= 2) return 1;
    unsigned long long int a = 1, b = 1, c;
    for (unsigned long long int i = 3; i <= n; ++i) {
        c = (a + b) % m;
        a = b;
        b = c;
    }
    return b;
}

int main() {
    unsigned long long int n;
    int m;
    std::cin >> n >> m;
    std::cout << fib(n, m) << std::endl;
    return 0;
}
