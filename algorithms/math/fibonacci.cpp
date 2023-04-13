#include <iostream>

long fibo_iter(int n) {
    if (n == 0) return 0;
    unsigned long long prev = 0, curr = 1;
    for (int i = 1; i < n; ++i) {
        unsigned long long temp = prev + curr;
        prev = curr;
        curr = temp;
    }
    return curr;
}

/********************************************************/

long fibo_rec(int n) {
    return n < 2 ? n : fibo_rec(n - 1) + fibo_rec(n - 2);
}

/********************************************************/

// C++ 98 style

template <int N>
struct Fibo1 {
    enum  { value = Fibo1<N - 1>::value + Fibo1<N -2>::value  };
};

template <>
struct Fibo1<0> {
    enum  { value = 0 };
};

template <>
struct Fibo1<1> {
    enum  { value = 1 };
};

/********************************************************/

// C++ 11 style

template <int N>
struct Fibo2 {
    static constexpr unsigned long long value = Fibo2<N - 1>::value + Fibo2<N -2>::value;
};

template <>
struct Fibo2<0> {
    static constexpr unsigned long long value = 0;
};

template <>
struct Fibo2<1> {
    static constexpr unsigned long long value = 1;
};

/********************************************************/

int main() {

    int n = 11;

    for (int i = 0; i < n; ++i)
        std::cout << fibo_iter(i) << "   ";
    std::cout << std::endl;


    /********************************************************/

    for (int i = 0; i < n; ++i)
        std::cout << fibo_rec(i) << "   ";
    std::cout << std::endl;

    /********************************************************/

    std::cout << Fibo1<10>::value << std::endl;

    /********************************************************/

    std::cout << Fibo2<10>::value << std::endl;

    return 0;
}
