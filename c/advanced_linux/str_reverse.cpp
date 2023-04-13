#include <iostream>
#include <string>

std::string reverseStringRec(const std::string& str) {
    if (str.length() == 1)
        return str;
    else
        return reverseStringRec(str.substr(1, str.length())) + str.at(0);    
}

int main() {
    std::string str;
    std::cin >> str;
    std::cout << reverseStringRec(str) << std::endl;
}
