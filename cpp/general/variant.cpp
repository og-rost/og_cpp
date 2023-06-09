/*

Variant: a type-safe union for C++17

An instance of std::variant at any given time either holds a value of 
one of its alternative types, or in the case of error - no value

As with unions, if a variant holds a value of some object type T, 
the object representation of T is allocated directly within the object 
representation of the variant itself. Variant is not allowed to allocate 
additional (dynamic) memory.

A variant is not permitted to hold references, arrays, or the type void.

*/

#include <variant>
#include <string>
#include <cassert>
 
int main() {
    std::variant<int, float> v, w;
    v = 12; // v contains int
    int i = std::get<int>(v);
    w = std::get<int>(v);
    w = std::get<0>(v); // same effect as the previous line
    w = v; // same effect as the previous line
 
//  std::get<double>(v); // error: no double in [int, float]
//  std::get<3>(v);      // error: valid index values are 0 and 1
 
    try {
        std::get<float>(w); // w contains int, not float: will throw
    }
    catch (const std::bad_variant_access&) {}
 
    using namespace std::literals;
 
    std::variant<std::string> x("abc");
    // converting constructors work when unambiguous
    x = "def"; // converting assignment also works when unambiguous
 
    std::variant<std::string, void const*> y("abc");
    // casts to void const * when passed a char const *
    assert(std::holds_alternative<void const*>(y)); // succeeds
    y = "xyz"s;
    assert(std::holds_alternative<std::string>(y)); // succeeds
}