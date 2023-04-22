//Cointainer supporting constant time add, remove, get_random and search functions.

#include <unordered_map>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <climits>

class my_cont {
    std::vector<int> vec; 
    std::unordered_map<int, int>  hash;   
public:
    void add(int);
    void remove(int);
    int  get_random();
    int  search(int);
};

void my_cont::add(int x) {
    if (hash.find(x) != hash.end())
        return;        
    vec.emplace_back(x);
    hash.emplace(x, vec.size() - 1);
}

void my_cont::remove(int x) {
    auto iter = hash.find(x);
    if (iter == hash.end())
        return; 
    int index = iter->second;
    hash.erase(iter);
    int temp = vec[vec.size() - 1];
    std::swap(vec[index], vec[vec.size() - 1]); 
    vec.pop_back();   
    hash[vec[temp]] = index; 
}

int my_cont::get_random() {
    int index = rand() % vec.size();
    return vec[index];
} 

int my_cont::search(int x) {
    auto iter = hash.find(x);
    if (iter == hash.end())
        return INT_MAX;
    return iter->first;
} 

int main() {
    my_cont ob;
    ob.add(10);
    ob.add(20);
    ob.add(30);
    ob.add(40);

    std::cout << ob.search(40) << std::endl;
    ob.remove(20);

    ob.add(50);
    std::cout << ob.search(20) << std::endl;
    std::cout << ob.get_random() << std::endl;
    return 0;    
}
