/*

In C++, type traits are a set of templates that provide compile-time information about types.
They are a powerful tool that allows you to write generic code that can adapt to different types in a flexible and efficient way.

Type traits are used to extract information about a type, such as whether it is a pointer or a reference, whether it is an arithmetic or a class type,
or whether it has a certain member function or data member. They are typically implemented as a set of template classes with static constants or functions
that provide the requested information.

Type traits are used extensively in template metaprogramming, where they allow you to write generic code that can handle different
types in a type-safe and efficient way. They are also used in the implementation of standard library containers and algorithms
where they allow the containers and algorithms to work with a wide range of types without sacrificing performance or safety.

*/

#include <type_traits>
#include <iostream>

template <typename T>
void print_pointer_info(const T& t) {
    if (std::is_pointer<T>::value) {
        std::cout << "Type is a pointer" << std::endl;
    }
    else {
        std::cout << "Type is not a pointer" << std::endl;
    }
}

template <typename T>
typename std::enable_if<std::is_arithmetic<T>::value, T>::type
square(T x) {
    return x * x;
}

int main() {
    int x = 42;
    int* p = &x;
    print_pointer_info(x);  // Output: Type is not a pointer
    print_pointer_info(p);  // Output: Type is a pointer

    std::cout << square(2) << std::endl;       // Output: 4
    std::cout << square(3.14) << std::endl;    // Output: 9.8596
    // std::cout << square("hello") << std::endl;  // Error: does not compile
    return 0;
}
