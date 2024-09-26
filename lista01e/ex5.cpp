#include <iostream>

unsigned long long int pow(int b, unsigned long long int e, int m) {
    unsigned long long int result = 1;
    b = b % m;
    while (e > 0) {
        if (e % 2 == 1) result = (result * b) % m;
        e = e >> 1;
        b = (b * b) % m;
    }
    return result;
}

int main() {
    int b, m;
    unsigned long long int e;
    std::cin >> b >> e >> m;
    std::cout << pow(b, e, m) << std::endl;
    return 0;
}
