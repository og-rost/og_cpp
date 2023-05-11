/*

Provides a convenient way to perform input/output operations on strings,
just like you would do with standard streams such as cin and cout.

The primary use cases for std::stringstream are parsing, formatting, and converting data between strings and other data types.

There are three types of string streams:

istringstream: Input string stream, used for reading from strings.
ostringstream: Output string stream, used for writing to strings.
stringstream: Both input and output string stream, used for reading from and writing to strings.



*/


#include <iostream>
#include <sstream>
#include <string>

void f1() {
    std::string input = "10 20 30 40";
    std::stringstream ss(input);
    int num;

    while (ss >> num) {
        std::cout << "Parsed integer: " << num << std::endl;
    }
}

void f2() {
    int age = 30;
    std::string name = "Gor";
    std::ostringstream oss;

    oss << "My name is " << name << " and I am " << age << " years old.";
    std::string formatted = oss.str();

    std::cout << "Formatted string: " << formatted << std::endl;
}

void f3() {
    std::string date = "2023-05-10";
    std::istringstream iss(date);

    int year, month, day;
    char delim;

    iss >> year >> delim >> month >> delim >> day;

    std::cout << "Year: " << year << ", Month: " << month << ", Day: " << day << std::endl;
}

void f4() {
    // Create a stringstream for output
    std::stringstream ss;
    ss << "Hello, " << "World! " << 123;

    // Get the string
    std::string str = ss.str();
    std::cout << "Output string: " << str << std::endl;

    // Clear the stringstream and use it for input
    ss.clear();
    ss.str("2023 05 10");

    int year, month, day;
    ss >> year >> month >> day;

    std::cout << "Year: " << year << ", Month: " << month << ", Day: " << day << std::endl;
}

void f5() {
    std::string input = "apple,banana,orange,grape";
    std::stringstream ss(input);
    std::string token;

    while (std::getline(ss, token, ',')) {
        std::cout << "Parsed token: " << token << std::endl;
    }
}



int main() {
    f1();
    f2();
    f3();
    f4();
    f5();
    return 0;
}
