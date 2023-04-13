#include <iostream>
#include <vector>
#include <algorithm>

void shell(std::vector<int>& vec) {
    int h = 1;
    int n = vec.size();
    while(h < n / 3) {
        h = 3 * h + 1;
    }

    while (h >= 1) {
        for (auto it = vec.begin() + h; it != vec.end(); ++it) {
            for(auto iter = it; iter >= vec.begin() + h && *iter < *(iter - h); iter -= h) {
                std::swap(*iter, *(iter - h));
            }
        }
        h = h / 3;
    }
}

void print(const std::vector<int>& vec) {
    for(auto i : vec)
        std::cout << i << "  ";
    std::cout << std::endl;
}

int main() {
    std::vector<int> vec = {1,2,3,4,5,6,7,8,9,10};

    print(vec);
    shuffle(vec.begin(), vec.end(), std::default_random_engine(1000000));
    print(vec);
    shell(vec);
    print(vec);
    return 0;
}
