#include <iostream>
#include <typeinfo>
#include <string>

template <typename T>
struct type_name;

#define REGISTER_TYPE_NAME(type) template <> struct type_name<type> { static std::string get() { return #type; } }

REGISTER_TYPE_NAME(int);
REGISTER_TYPE_NAME(float);
REGISTER_TYPE_NAME(double);
REGISTER_TYPE_NAME(char);
REGISTER_TYPE_NAME(const int);
REGISTER_TYPE_NAME(const float);
REGISTER_TYPE_NAME(const double);
REGISTER_TYPE_NAME(const char);
REGISTER_TYPE_NAME(std::string);

template <typename T>
std::string type_id_with_cvr_pretty_name() {
    return type_name<T>::get();
}

int main() {
    int a = 5;
    const int b = 6;
    std::string s;

    std::cout << "Type of 'a': " << type_id_with_cvr_pretty_name<decltype(a)>() << std::endl;
    std::cout << "Type of 'b': " << type_id_with_cvr_pretty_name<decltype(b)>() << std::endl;
    std::cout << "Type of 's': " << type_id_with_cvr_pretty_name<decltype(s)>() << std::endl;

    return 0;
}
