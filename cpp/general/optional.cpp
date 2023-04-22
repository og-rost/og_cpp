#include <iostream>
#include <optional>

std::optional<int> get_even_number(int number) {
    if (number % 2 == 0) {
        return number; // Return the even number wrapped in std::optional
    }
    return std::nullopt; // Return an empty std::optional to indicate no value
}

int main() {
    auto result = get_even_number(3);

    if (result) { // Alternatively, you can use if (result.has_value())
        std::cout << "The even number is: " << *result << std::endl;
    } else {
        std::cout << "No even number found." << std::endl;
    }

    return 0;
}
