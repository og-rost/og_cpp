#include <iostream>

// Metafunctions are functions that operate on types, values, or other metafunctions at compile-time.
// They are typically implemented as class templates with a nested typedef or a static constexpr member.

template <unsigned int N>
struct Factorial {
    static constexpr unsigned long long value = N * Factorial<N - 1>::value;
};

template <>
struct Factorial<0> {
    static constexpr unsigned long long value = 1;
};

int main() {
    constexpr unsigned long long factorial_10 = Factorial<10>::value;
    std::cout << "10! = " << factorial_10 << std::endl;
    return 0;
}
