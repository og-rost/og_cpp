/*

Write a unary metafunction add_const_ref<T> that returns T if it is a reference type,
and otherwise returns T const&.

Write a program to test your metafunction.

*/

#include <type_traits>

#include <iostream>
#include <type_traits>
#include <boost/type_index.hpp>

template <typename T, bool = std::is_reference<T>::value>
struct add_const_ref;

// Partial specialization for reference types
template <typename T>
struct add_const_ref<T, true> {
    using type = T;
};

// Partial specialization for non-reference types
template <typename T>
struct add_const_ref<T, false> {
    using type = const T&;
};


int main() {
    // Test for ref type
    using boost::typeindex::type_id_with_cvr;
    using ref_type = int&;
    using result1 = add_const_ref<ref_type>::type;

    std::cout << "Original type: " << type_id_with_cvr<ref_type>().pretty_name() << std::endl;
    std::cout << "Resulting type: " << type_id_with_cvr<result1>().pretty_name() << std::endl;
    std::cout << std::boolalpha << "Is same: " << std::is_same<ref_type, result1>::value << std::endl << std::endl;

    // Test for non ref type
    using non_ref_type = int;
    using result2 = add_const_ref<non_ref_type>::type;

    std::cout << "Original type: " << type_id_with_cvr<non_ref_type>().pretty_name() << std::endl;
    std::cout << "Resulting type: " << type_id_with_cvr<result2>().pretty_name() << std::endl;
    std::cout << std::boolalpha << "Is same: " << std::is_same<const non_ref_type&, result2>::value << std::endl;

    return 0;
}
