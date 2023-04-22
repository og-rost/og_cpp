#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>


std::vector<std::string> splitString(const std::string& sentence) {
    std::vector<std::string> words;
    std::istringstream iss(sentence);
    std::string word;

    while (iss >> word) {
        words.push_back(word);
    }

    return words;
}



int main() {
    std::string s = "gandon gyot xaxpitxa klir chort xerscceq boz gyotveranitxa";
    auto words = splitString(s);

    std::sort(words.begin(), words.end(), [](const std::string& a, const std::string& b) {
        return a.size() > b.size();
    });


    for (std::string word : words) {
        std::cout << word << " ";
    }
    std::cout << std::endl;

    return 0;
}