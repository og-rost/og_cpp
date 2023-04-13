#include <iostream>

template<int N, int P> 
struct Power {
    static constexpr unsigned long long val = N * Power<N, P - 1>::val;
};

template<int N> 
struct Power<N, 0> {
    static constexpr unsigned long long val = 1;
};

/***************************************************/

int power(int numb, int pow) {
    if (pow == 0)
        return 1;
    else
        return numb * power(numb, --pow);
}

int main() {
    std::cout << Power<2, 10>::val << std::endl;
    std::cout << power(2, 10) << std::endl;
    return 0;
}
