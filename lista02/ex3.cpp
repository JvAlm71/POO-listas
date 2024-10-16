#include <iostream>
#include <math.h> 

class Vetor {
private:
    int _x;
    int _y;

public:
    Vetor(int x = 0, int y = 0) : _x(x), _y(y) {}

    friend Vetor operator+(const Vetor &a, const Vetor &b) {
        return Vetor(a._x + b._x, a._y + b._y);
    }

    friend Vetor operator-(const Vetor &a, const Vetor &b) {
        return Vetor(a._x - b._x, a._y - b._y);
    }

    friend int operator*(const Vetor &a, const Vetor &b) {
        return a._x * b._x + a._y * b._y;
    }

    friend int operator^(const Vetor &a, const Vetor &b) {
        return a._x * b._y - a._y * b._x;
    }

    friend double operator<(const Vetor &a, const Vetor &b) {
        double dotProduct = a * b;
        double magnitudes = a.abs() * b.abs();
        if (magnitudes == 0) return 0.0;
        double cosTheta = dotProduct / magnitudes;
        return acos(cosTheta) * (180.0 / M_PI); // conversão para graus
    }

    double abs() const {
        return sqrt(_x * _x + _y * _y);
    }

    friend std::ostream& operator<<(std::ostream &out, const Vetor &v) {
        out << "(" << v._x << ", " << v._y << ")";
        return out;
    }
};

int main() {
    Vetor v;
    std::cout << v << std::endl;
    v = v + Vetor(1, 2);
    std::cout << v << std::endl;
    v = v + Vetor(1, 2);
    std::cout << v << std::endl;
    v = v - Vetor(1, 6);
    std::cout << v << std::endl;
    int a = v * Vetor(3, 2);
    std::cout << a << std::endl;
    int b = v ^ Vetor(-4501, 9002);
    std::cout << b << std::endl;
    double c = v.abs();
    std::cout << c << std::endl;

    return 0;
}
