/*

Use the type traits facilities to implement a type_descriptor class template,
whose instances, when streamed, print the type of their template parameters

*/

#include <iostream>
#include <typeinfo>
#include <string>

template <typename T>
class type_descriptor {
public:
    friend std::ostream& operator<<(std::ostream& os, const type_descriptor<T>&) {
        return os << typeid(T).name();
    }
};


int main() {
    type_descriptor<int> int_descriptor;
    type_descriptor<double> double_descriptor;
    type_descriptor<std::string> string_descriptor;

    std::cout << "Type of int: " << int_descriptor << std::endl;
    std::cout << "Type of double: " << double_descriptor << std::endl;
    std::cout << "Type of std::string: " << string_descriptor << std::endl;

    return 0;
}
