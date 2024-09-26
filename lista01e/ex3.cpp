#include <iostream>
#include <cmath>

int main() {
    double n1, n2, n3;
    std::cin >> n1 >> n2 >> n3;

    double mediaAritmetica = (n1 + n2 + n3) / 3;
    double mediaHarmonica = 3 / (1/n1 + 1/n2 + 1/n3);
    double mediaGeometrica = pow(n1 * n2 * n3, 1.0/3);
    double mediaQuadratica = std::sqrt((n1*n1 + n2*n2 + n3*n3) / 3);

    std::cout << "Menor: " << mediaHarmonica << std::endl;
    std::cout << "Maior: " << mediaQuadratica << std::endl;

    return 0;
}
