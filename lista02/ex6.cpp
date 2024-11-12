#include <iostream>
#include <string>
#include <cstring>
#include <iomanip>

class BigInt {
private:
    int* partes;
    int npartes;
    bool positivo;

    static const int BASE = 1000000000; // Base 10^9
    static const int BASE_DIGITOS = 9;  // Dígitos por parte

public:
    // Construtor a partir de string
    BigInt(std::string numero) {
        positivo = true;
        if (numero.empty()) {
            npartes = 1;
            partes = new int[1];
            partes[0] = 0;
            return;
        }

        if (numero[0] == '-') {
            positivo = false;
            numero = numero.substr(1);
        }

        // Remover zeros à esquerda
        while (numero.size() > 1 && numero[0] == '0') {
            numero.erase(0, 1);
        }

        int len = numero.length();
        npartes = (len + BASE_DIGITOS - 1) / BASE_DIGITOS;
        partes = new int[npartes];

        int indice = 0;
        for (int i = len; i > 0; i -= BASE_DIGITOS) {
            int inicio = std::max(0, i - BASE_DIGITOS);
            int tamanho = i - inicio;
            partes[indice++] = std::stoi(numero.substr(inicio, tamanho));
        }
    }

    // Construtor a partir de int
    BigInt(int num, bool eh_num = true) {
        if (eh_num) {
            positivo = num >= 0;
            num = std::abs(num);

            if (num == 0) {
                npartes = 1;
                partes = new int[1];
                partes[0] = 0;
            } else {
                npartes = 0;
                int temp = num;
                while (temp > 0) {
                    temp /= BASE;
                    npartes++;
                }

                partes = new int[npartes];
                int indice = 0;
                while (num > 0) {
                    partes[indice++] = num % BASE;
                    num /= BASE;
                }
            }
        } else {
            npartes = num;
            positivo = true;
            partes = new int[npartes];
            for (int i = 0; i < npartes; i++) {
                partes[i] = 0;
            }
        }
    }

    // Construtor padrão
    BigInt() {
        positivo = true;
        npartes = 1;
        partes = new int[1];
        partes[0] = 0;
    }

    // Construtor de movimento
    BigInt(BigInt&& b) : partes(b.partes), npartes(b.npartes), positivo(b.positivo) {
        b.partes = nullptr;
        b.npartes = 0;
    }

    // Construtor de cópia
    BigInt(const BigInt& b) : npartes(b.npartes), positivo(b.positivo) {
        partes = new int[npartes];
        std::memcpy(partes, b.partes, npartes * sizeof(int));
    }

    // Destrutor
    ~BigInt() {
        delete[] partes;
    }

    // Método isPositivo()
    bool isPositivo() const {
        return positivo;
    }

    // Operador de atribuição
    BigInt& operator=(const BigInt& b) {
        if (this != &b) {
            delete[] partes;
            npartes = b.npartes;
            positivo = b.positivo;
            partes = new int[npartes];
            std::memcpy(partes, b.partes, npartes * sizeof(int));
        }
        return *this;
    }

    // Método abs()
    BigInt abs() const {
        BigInt resultado(*this);
        resultado.positivo = true;
        return resultado;
    }

    // Operador ==
    friend bool operator==(const BigInt& a, const BigInt& b) {
        if (a.positivo != b.positivo) return false;
        if (a.npartes != b.npartes) return false;
        for (int i = 0; i < a.npartes; i++) {
            if (a.partes[i] != b.partes[i]) return false;
        }
        return true;
    }

    // Operador >
    friend bool operator>(const BigInt& a, const BigInt& b) {
        if (a.positivo != b.positivo)
            return a.positivo;

        if (a.npartes != b.npartes)
            return a.npartes > b.npartes ? a.positivo : !a.positivo;

        for (int i = a.npartes - 1; i >= 0; i--) {
            if (a.partes[i] != b.partes[i])
                return a.partes[i] > b.partes[i] ? a.positivo : !a.positivo;
        }
        return false;
    }

    // Operador +
    friend BigInt operator+(const BigInt& a, const BigInt& b) {
        if (a.positivo == b.positivo) {
            BigInt resultado;
            resultado.positivo = a.positivo;
            int maxPartes = std::max(a.npartes, b.npartes) + 1;
            resultado.partes = new int[maxPartes];
            std::memset(resultado.partes, 0, sizeof(int) * maxPartes);
            resultado.npartes = maxPartes;

            int carry = 0;
            for (int i = 0; i < maxPartes - 1; i++) {
                long long soma = carry;
                if (i < a.npartes) soma += a.partes[i];
                if (i < b.npartes) soma += b.partes[i];
                if (soma >= BigInt::BASE) {
                    carry = 1;
                    soma -= BigInt::BASE;
                } else {
                    carry = 0;
                }
                resultado.partes[i] = soma;
            }
            if (carry == 0) {
                resultado.npartes--;
            } else {
                resultado.partes[maxPartes - 1] = carry;
            }
            return resultado;
        } else if (a.positivo && !b.positivo) {
            return a - b.abs();
        } else {
            return b - a.abs();
        }
    }

    // Operador -
    friend BigInt operator-(const BigInt& a, const BigInt& b) {
        if (a.positivo == b.positivo) {
            if (a.abs() >= b.abs()) {
                BigInt resultado;
                resultado.positivo = a.positivo;
                resultado.npartes = a.npartes;
                resultado.partes = new int[resultado.npartes];
                std::memset(resultado.partes, 0, sizeof(int) * resultado.npartes);

                int carry = 0;
                for (int i = 0; i < a.npartes; i++) {
                    long long sub = a.partes[i] - carry - (i < b.npartes ? b.partes[i] : 0);
                    if (sub < 0) {
                        sub += BigInt::BASE;
                        carry = 1;
                    } else {
                        carry = 0;
                    }
                    resultado.partes[i] = sub;
                }

                while (resultado.npartes > 1 && resultado.partes[resultado.npartes - 1] == 0) {
                    resultado.npartes--;
                }
                return resultado;
            } else {
                BigInt resultado = b - a;
                resultado.positivo = !a.positivo;
                return resultado;
            }
        } else if (a.positivo && !b.positivo) {
            return a + b.abs();
        } else {
            BigInt resultado = a.abs() + b;
            resultado.positivo = false;
            return resultado;
        }
    }

    // Operador unário -
    BigInt operator-() const {
        BigInt resultado(*this);
        if (resultado != BigInt(0)) {
            resultado.positivo = !resultado.positivo;
        }
        return resultado;
    }

    // Operador *
    friend BigInt operator*(const BigInt& a, const BigInt& b) {
        BigInt resultado;
        resultado.positivo = (a.positivo == b.positivo);
        resultado.npartes = a.npartes + b.npartes;
        resultado.partes = new int[resultado.npartes];
        std::memset(resultado.partes, 0, sizeof(int) * resultado.npartes);

        for (int i = 0; i < a.npartes; i++) {
            long long carry = 0;
            for (int j = 0; j < b.npartes || carry != 0; j++) {
                long long atual = resultado.partes[i + j] + carry +
                    (long long)a.partes[i] * (j < b.npartes ? b.partes[j] : 0);
                resultado.partes[i + j] = atual % BigInt::BASE;
                carry = atual / BigInt::BASE;
            }
        }

        while (resultado.npartes > 1 && resultado.partes[resultado.npartes - 1] == 0) {
            resultado.npartes--;
        }
        return resultado;
    }

    // Operador /(int)
    BigInt operator/(int b) const {
        BigInt resultado;
        resultado.positivo = (positivo == (b >= 0));
        int divisor = std::abs(b);

        resultado.npartes = npartes;
        resultado.partes = new int[resultado.npartes];
        std::memset(resultado.partes, 0, sizeof(int) * resultado.npartes);

        long long resto = 0;
        for (int i = npartes - 1; i >= 0; i--) {
            long long atual = partes[i] + resto * BigInt::BASE;
            resultado.partes[i] = atual / divisor;
            resto = atual % divisor;
        }

        while (resultado.npartes > 1 && resultado.partes[resultado.npartes - 1] == 0) {
            resultado.npartes--;
        }
        return resultado;
    }

    // Operador /(BigInt)
    BigInt operator/(const BigInt& b) const {
        return divmod(b).first;
    }

    // Operador %(BigInt)
    BigInt operator%(const BigInt& b) const {
        return divmod(b).second;
    }

    // Divisão e módulo simultâneos
    std::pair<BigInt, BigInt> divmod(const BigInt& b) const {
        BigInt divisor = b.abs();
        BigInt dividendo = this->abs();
        BigInt quociente(0);
        BigInt resto(0);

        if (dividendo < divisor) {
            resto = dividendo;
            return { quociente, resto };
        }

        int n = dividendo.npartes - 1;
        resto.partes = new int[dividendo.npartes];
        resto.npartes = 0;

        for (int i = n; i >= 0; i--) {
            // Shift resto à esquerda e adiciona a parte atual
            if (resto.npartes > 0 || dividendo.partes[i] != 0) {
                for (int j = resto.npartes - 1; j >= 0; j--) {
                    resto.partes[j + 1] = resto.partes[j];
                }
                resto.npartes++;
            }
            resto.partes[0] = dividendo.partes[i];

            // Busca binária para encontrar o maior x tal que divisor * x <= resto
            int x = 0, l = 0, r = BigInt::BASE - 1;
            while (l <= r) {
                int m = (l + r) / 2;
                BigInt t = divisor * m;
                if (t <= resto) {
                    x = m;
                    l = m + 1;
                } else {
                    r = m - 1;
                }
            }

            // Atualiza o quociente
            if (quociente.npartes > 0 || x != 0) {
                for (int j = quociente.npartes - 1; j >= 0; j--) {
                    quociente.partes[j + 1] = quociente.partes[j];
                }
                quociente.npartes++;
                quociente.partes[0] = x;
            }

            // Atualiza o resto
            BigInt subtrahend = divisor * x;
            resto = resto - subtrahend;

            // Remove zeros à esquerda do resto
            while (resto.npartes > 1 && resto.partes[resto.npartes - 1] == 0) {
                resto.npartes--;
            }
        }

        quociente.positivo = (this->positivo == b.positivo);
        resto.positivo = this->positivo;

        // Remove zeros à esquerda do quociente
        while (quociente.npartes > 1 && quociente.partes[quociente.npartes - 1] == 0) {
            quociente.npartes--;
        }

        return { quociente, resto };
    }

    // Operador ^
    friend BigInt operator^(const BigInt& a, const BigInt& b) {
        BigInt resultado(1);
        BigInt base = a;
        BigInt expoente = b;

        while (expoente > BigInt(0)) {
            if (expoente.partes[0] % 2 != 0) {
                resultado = resultado * base;
            }
            base = base * base;
            expoente = expoente / 2;
        }
        return resultado;
    }

    // Operador <<
    friend std::ostream& operator<<(std::ostream &out, const BigInt &a) {
        if (!a.positivo && !(a.npartes == 1 && a.partes[0] == 0)) {
            out << '-';
        }
        out << a.partes[a.npartes - 1];
        for (int i = a.npartes - 2; i >= 0; i--) {
            out << std::setw(BigInt::BASE_DIGITOS) << std::setfill('0') << a.partes[i];
        }
        return out;
    }

    // Comparação adicional necessária
    friend bool operator!=(const BigInt& a, const BigInt& b) {
        return !(a == b);
    }

    friend bool operator<(const BigInt& a, const BigInt& b) {
        return !(a > b || a == b);
    }

    friend bool operator>=(const BigInt& a, const BigInt& b) {
        return (a > b || a == b);
    }

    friend bool operator<=(const BigInt& a, const BigInt& b) {
        return !(a > b);
    }
};

class Fracao {
private:
    BigInt numerador;
    BigInt denominador;

    void simplificar() {
        BigInt divisor = mdc(numerador.abs(), denominador.abs());
        numerador = numerador / divisor;
        denominador = denominador / divisor;

        if (denominador < BigInt(0)) {
            denominador = -denominador;
            numerador = -numerador;
        }
    }

    BigInt mdc(BigInt a, BigInt b) {
        while (b != BigInt(0)) {
            BigInt resto = a % b;
            a = b;
            b = resto;
        }
        return a;
    }

public:
    // Construtor padrão
    Fracao() : numerador(0), denominador(1) {}

    // Construtor com BigInts
    Fracao(const BigInt& num, const BigInt& den) : numerador(num), denominador(den) {
        simplificar();
    }

    // Operador +
    Fracao operator+(const Fracao& outra) const {
        BigInt num = numerador * outra.denominador + outra.numerador * denominador;
        BigInt den = denominador * outra.denominador;
        return Fracao(num, den);
    }

    // Operador -
    Fracao operator-(const Fracao& outra) const {
        BigInt num = numerador * outra.denominador - outra.numerador * denominador;
        BigInt den = denominador * outra.denominador;
        return Fracao(num, den);
    }

    // Operador *
    Fracao operator*(const Fracao& outra) const {
        BigInt num = numerador * outra.numerador;
        BigInt den = denominador * outra.denominador;
        return Fracao(num, den);
    }

    // Operador /
    Fracao operator/(const Fracao& outra) const {
        BigInt num = numerador * outra.denominador;
        BigInt den = denominador * outra.numerador;
        return Fracao(num, den);
    }

    // Operador <<
    friend std::ostream& operator<<(std::ostream &out, const Fracao &f) {
        out << f.numerador << "/" << f.denominador;
        return out;
    }
};

// Função principal com o exemplo fornecido
int main() {
    Fracao f;
    std::cout << f << std::endl;
    f = f + Fracao(BigInt(1), BigInt(2));
    std::cout << f << std::endl;
    f = f + Fracao(BigInt(1), BigInt(2));
    std::cout << f << std::endl;
    f = f * Fracao(BigInt(3), BigInt(2));
    std::cout << f << std::endl;
    f = f / Fracao(BigInt(3), BigInt(4));
    std::cout << f << std::endl;
    f = f - Fracao(BigInt(1), BigInt(6));
    std::cout << f << std::endl;
    f = f * Fracao(BigInt(0), BigInt("999999999999999999"));
    std::cout << f << std::endl;

    return 0;
}
