#include <cmath>
#include <iostream>

// sin -- sin(x) := x - x^3/3! + x^5/5! - x^7/7! + ... (1)

double __sin(double x) {
    double res = 0, pow = x, fact = 1;
    for(int i = 0;  i < 5; ++i) {
        res += pow / fact;
        pow *= x * x;
        fact *= (2 * (i + 1)) * (2 * (i + 1) + 1);
    }

    return res;
}

double _pow(double a, double b) {
    double c = 1;
    for (int i = 0; i < b; ++i)
        c *= a;
    return c;
}

double _fact(double x) {
    double ret = 1;
    for (int i = 1; i <= x; ++i) 
        ret *= i;
    return ret;
}

double _sin(double x) {
    double y = x, s = -1;
    for (int i = 3; i <= 100; i += 2) {
        y += s * (_pow(x, i) / _fact(i));
        s *= -1;
    }  
    return y;
}

double _cos(double x) {
    double y = 1, s = -1;
    for (int i = 2; i <= 100; i += 2) {
        y += s * (_pow(x, i) / _fact(i));
        s *= -1;
    }  
    return y;
}

double _tan(double x) {
    return (_sin(x) / _cos(x));  
}

int main() {
    std::cout << __sin(69)    << "  __sin"    << std::endl;
    std::cout << _sin(69)     << "  _sin"     << std::endl;
    std::cout << std::sin(69) << "  std::sin" << std::endl;
    std::cout << sin(69)      << "  sin"      << std::endl;
    std::cout << _cos(69)     << "  _cos"     << std::endl;
    std::cout << std::cos(69) << "  std::cos" << std::endl;
    std::cout << cos(69)      << "  cos"      << std::endl;
    std::cout << _tan(69)     << "  _tan"     << std::endl;
    std::cout << std::tan(69) << "  std::tan" << std::endl;
    std::cout << tan(69)      << "  tan"      << std::endl;
    return 0;
}
