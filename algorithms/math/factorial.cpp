#include <iostream>
#include <vector>

long factorial(int n) {
    if (n == 0) return 1;
    else return  n * factorial(n - 1);
} 

/*================================================*/

// C++ 11 style

template <int N>
struct Fact1 {
    static constexpr int value = N * Fact1<N - 1>::value;
};

template <>
struct Fact1<0> {
    static constexpr int value = 1;
};

/*================================================*/

// C++ 98 style

template <int n>
struct Fact2 {
    enum { value = n * Fact2<n - 1>::value };
};

template <>
struct Fact2<0> {
    enum { value = 1 };
};

/*================================================*/

void multiply(int x, std::vector<int>& res) {
    int carry = 0;      
    for (int& i : res)  {
        int prod = i * x + carry;
        i = prod % 10; 
        carry  = prod / 10;
    }

    while (carry) {
        res.push_back(carry % 10);
        carry = carry / 10;
    }
}

void large_factorial(int n) {
    std::vector<int> res;
    res.push_back(1);

    for (int x = 2; x <= n; ++x)
        multiply(x, res);

    for (int i = res.size() - 1; i >= 0; --i)
        std::cout << res[i];
    std::cout << std::endl;
}

/*================================================*/

int main() {
    std::cout << factorial(10) << std::endl;
    std::cout << Fact1<10>::value << std::endl;
    std::cout << Fact2<10>::value << std::endl;
    large_factorial(10);
    return 0;
}
