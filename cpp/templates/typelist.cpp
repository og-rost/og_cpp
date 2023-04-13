#include <iostream>

// TypeList definition
template <typename... Ts>
struct TypeList {};

// Append a type to TypeList
template <typename TList, typename T>
struct Append;

template <typename... Ts, typename T>
struct Append<TypeList<Ts...>, T> {
    using type = TypeList<Ts..., T>;
};

// Get the length of a TypeList
template <typename TList>
struct Length;

template <typename... Ts>
struct Length<TypeList<Ts...>> {
    static constexpr int value = sizeof...(Ts);
};

int main() {
    using MyList = TypeList<int, double, char>;
    using ExtendedList = Append<MyList, bool>::type;

    constexpr int original_length = Length<MyList>::value;
    constexpr int extended_length = Length<ExtendedList>::value;

    std::cout << "Length of MyList: " << original_length << std::endl;
    std::cout << "Length of ExtendedList: " << extended_length << std::endl;

    return 0;
}
