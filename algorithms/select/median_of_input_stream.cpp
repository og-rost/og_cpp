#include <iostream>
#include <vector>
#include <cmath>
using std::vector;

void max_heapify(vector<int>& vec, size_t i, size_t size) {     
    while (i*2 + 1 < size) { 
        size_t child = 2 * i + 1;           
        if (child + 1 < size && vec[child] < vec[child + 1]) 
            ++child;       

        if (vec[i] < vec[child]) {     
            std::swap (vec[child], vec[i]);                    
            i = child;  
        }        
        else return;
    }
} 

void min_heapify(vector<int>& vec, size_t i, size_t size) {     
    while (i*2 + 1 < size) { 
        size_t child = 2 * i + 1;           
        if (child + 1 < size && vec[child] > vec[child + 1]) 
            ++child;       

        if (vec[i] > vec[child]) {     
            std::swap (vec[child], vec[i]);                    
            i = child;  
        }        
        else return;
    }
} 

int getMax(const vector<int>& vec) {
    return vec[0];
}

int getMin(const vector<int>& vec) {
    return vec[0];
}

void min_insert(vector<int>& vec, int key) {
    vec.push_back(key);
    min_heapify(vec,0,vec.size());
}

void max_insert(vector<int>& vec, int key) {
    vec.push_back(key);
    max_heapify(vec,0,vec.size());
}

int extract_max(vector<int>& vec) {
    int max = vec[0];
    std::swap(vec[0], vec[vec.size()-1]);
    vec.pop_back();
    max_heapify(vec, 0, vec.size());
    return max;
}

int extract_min(vector<int>& vec) {
    int min = vec[0];
    std::swap(vec[0], vec[vec.size()-1]);
    vec.pop_back();
    min_heapify(vec, 0, vec.size());
    return min;
}

int median(const vector<int>& vec) {  
    vector<int> maxHeap;
    vector<int> minHeap;
    int med = vec[0];    
    for(size_t i = 1; i < vec.size(); ++i) {        
        if(vec[i] <= med) 
            max_insert(maxHeap, vec[i]);
        else 
            min_insert(minHeap, vec[i]);

        if (std::abs(minHeap.size() - maxHeap.size())<=1)  {
            if(minHeap.size() >= maxHeap.size())
                med = getMin(minHeap);
            else 
                med = getMax(maxHeap);
        }
        else if (maxHeap.size() > minHeap.size()) {
            min_insert(minHeap, extract_max(maxHeap));
            med = std::max(getMax(maxHeap), getMin(minHeap));
        }
        else {
            max_insert(maxHeap, extract_min(minHeap));
            med = std::max(getMax(maxHeap), getMin(minHeap));
        }
    }
    //std::cout<<minHeap.size()<<std::endl;
    //std::cout<<minHeap.size()<<std::endl;
    return med;
}

int main() {
    vector<int> vec = {11, 22, 33, 777, 199, 99, 44, 111, 33, 555};
    for(int i : vec)
        std::cout<<i<<"  ";
    std::cout<<std::endl;
    std::cout<<median(vec)<<std::endl;

    return 0;
}
