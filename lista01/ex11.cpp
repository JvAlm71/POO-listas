#include <iostream>
#include <sstream>
#include <string>
#include <math.h>

std::string raizes(double a, double b, double c) {
    if (a == 0 && b == 0 && c == 0) {
        return "Infinitas";
    }
    else if (a == 0 && b == 0) {
        return "Nenhuma";
    }
    else if (a == 0) {
        double x = -c / b;
        std::ostringstream os;
        os << x;
        return os.str();
    }

    double delta = b * b - 4 * a * c;

    if (delta > 0) {
        double x1 = (-b - sqrt(delta)) / (2 * a);
        double x2 = (-b + sqrt(delta)) / (2 * a);
        if (x1 > x2) std::swap(x1, x2);
        std::ostringstream os;
        os << x1 << " e " << x2;
        return os.str();
    }
    else if (delta == 0) {
        double x = -b / (2 * a);
        std::ostringstream os;
        os << x;
        return os.str();
    }
    else {
        return "Nenhuma";
    }
}

int main() {
    double a = 1, b = 2, c = 1;
    std::string resultado = raizes(a, b, c);
    std::cout << "\"" << resultado << "\"" << std::endl;   
    return 0;
}
