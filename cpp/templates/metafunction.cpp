/*

A metafunction in C++ is a function that operates on types instead of values.
It's defined as a template that takes one or more types as input and produces a type as output.

Metafunctions are used in template metaprogramming, which is a technique to perform computations at compile-time using templates.
By manipulating types and applying compile-time logic, we can create powerful and efficient templates
that can work with different types in a type-safe and generic way.

Metafunctions can be defined using a variety of techniques such as template specialization,
function overloading, and template parameter deduction.
They can also be composed using standard functional programming techniques such as function composition and currying.

A simple example of a metafunction is a type trait that checks if a type is a pointer:

*/

#include <type_traits>

template <typename T>
struct is_pointer {
    static constexpr bool value = std::is_pointer<T>::value;
};

/*

In this example, the is_pointer metafunction is defined as a struct that takes
a type T as input and checks if it's a pointer using the std::is_pointer type trait.
It then stores the result in a static value member, which is either true or false.

Metafunctions are a powerful tool that allow us to write generic code that
can adapt to different types in a flexible and efficient way.
They are extensively used in the C++ standard library and are an essential part of modern C++ programming.

*/

template <int A, int B>
struct gcd {
    static constexpr int value = gcd<B, A % B>::value;
};

template <int A>
struct gcd<A, 0> {
    static constexpr int value = A;
};

int main() {
    static_assert(gcd<12, 18>::value == 6, "gcd failed");
    static_assert(gcd<21, 28>::value == 7, "gcd failed");
    return 0;
}

/*

A "value" that can be manipulated by the C++ compile-time machinery can be thought of as metadata.

In template metaprogramming, the two most common kinds of metadata are types and integer (including bool) constants.
The compile-time part of C++ is often referred to as a "pure functional language" because metadata is immutable
and metafunctions can't have any side effects.

A "function" that operates on metadata and can be "invoked" at compile time is called metafunction.

*/
