#include <iostream>

// A metaprogram is a program that manipulates code.

template <unsigned long N>
struct binary {
    static unsigned const value = binary<N / 10>::value << 1 | N % 10; // prepend higher bits to lowest bit
};

template <> // specialization
struct binary<0> { // terminates recursion
    static unsigned const value = 0;
};

/*

When we access the nested ::value member of binary<N>, the binary template is instantiated again with a smaller N,
until N reaches zero and the specialization is used as a termination condition.

Because binary does its work at compile time, its ::value is available as a compile-time constant,
and the compiler can encode it directly in the object code, saving a memory lookup when it is used.

*/


// runtime version

unsigned binaryRuntime(unsigned long N) {
    unsigned result = 0;
    for (unsigned bit = 1; N; N /= 10, bit <<= 1) {
        if (N % 10) {
            result += bit;
        }
    }
    return result;
}

int main() {
    unsigned const one = binary<1>::value;
    unsigned const three = binary<11>::value;
    unsigned const five = binary<101>::value;
    unsigned const seven = binary<111>::value;
    unsigned const nine = binary<1001>::value;

    std::cout << one << " " << three << " " << five << " " << seven << " " << nine << std::endl;

    std::cout << binaryRuntime(1) << " " << binaryRuntime(11) << " " << binaryRuntime(101) << " " << binaryRuntime(111) << " " << binaryRuntime(1001) << std::endl;

    return 0;
}


/*

In C++, the entities that can be manipulated at compile time, called metadata, are divided roughly into two categories:
types and non-types.
Not coincidentally, all the kinds of metadata can be used as template parameters.
The constant integer values used in the above code are among the non-types.

*/