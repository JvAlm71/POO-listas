#include <iostream>

int fib(unsigned long long int n, int m) {
    if (n <= 2) return 1;
    return (fib(n-1, m) + fib(n-2, m)) % m;
}

int main() {
    unsigned long long int n;
    int m;
    std::cin >> n >> m;
    std::cout << fib(n, m) << std::endl;
    return 0;
}
