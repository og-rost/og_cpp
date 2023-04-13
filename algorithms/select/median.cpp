#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <random>
#include <vector>

int median(std::vector<int>& v) {
    if (v.size() < 5) {
        std::sort(v.begin(), v.end());
        return v[v.size() / 2];
    }
    std::vector<int> medians;
    for (int j = 0; j < v.size(); j += 5){
        int cnt = 5;
        if (j + 5 > v.size()){
            std::sort(v.begin() + j, v.end());
            medians.push_back(v[j + (v.size() - j) / 2]);
        } else {
            std::sort(v.begin() + j, v.begin() + j + 5);
            medians.push_back(v[j + 2]);
        }
    }
    return median(medians);
}


std::vector<int> generate_data() {
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<int> dist1(0, 100);
    std::uniform_int_distribution<int> dist2(1, 100);

    std::vector<int> data(dist2(rng));
    std::generate(data.begin(), data.end(), [&dist1, &rng]() { return dist1(rng); });
    return data;
}

int main() {
    int i = 10;
    while (i--) {
        std::vector<int> myVector = generate_data();
        int size = myVector.size();
        std::cout << "Median1: " << median(myVector) << std::endl;
        std::sort(myVector.begin(), myVector.end());
        std::cout << "Median2: " << myVector[myVector.size() / 2] << std::endl;
    }
    return 0;
}