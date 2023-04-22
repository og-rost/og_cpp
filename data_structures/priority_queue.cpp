#include <iostream>
#include <vector>

void heapify(std::vector<int>& vec, size_t i, size_t size) {     
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

void build(std::vector<int>& vec, size_t size) { 
	for (int i = size/2; i >= 0; --i) 
		heapify(vec, i, size);  
}

int max(const std::vector<int>& vec) {
	return vec[0];
}

int extract_max(std::vector<int>& vec) {
	int max = vec[0];
	std::swap(vec[0], vec[vec.size() - 1]);
	vec.pop_back();
	heapify(vec, 0, vec.size());
	return max;
}

void increase_key(std::vector<int>& vec, size_t i, int key) {
	vec[i] = key;
    while (i > 0 && vec[i/2] < vec[i]) {
    	std::swap(vec[i], vec[i/2]);
    	i = i / 2;
    }
}

void insert(std::vector<int>& vec, int key) {
	vec.push_back(key);
	increase_key(vec, vec.size() - 1, key);
}

int main() {    	  
	std::vector<int>vec = {7, 11, 8, 4, 5};
	 
	for (int i : vec) 
		std::cout << i << " ";
	std::cout << std::endl;
	
	build(vec, vec.size());     
	std::cout << max(vec) << std::endl;
	std::cout << extract_max(vec) << std::endl;
	std::cout << max(vec) << std::endl;
	for (int i : vec) 
		std::cout << i << " ";
	std::cout << std::endl;

	increase_key(vec, 3, 10);

	for (int i : vec) 
		std::cout << i << " ";
	std::cout << std::endl;

	insert(vec, 25);

	for (int i : vec) 
		std::cout << i << " ";
	std::cout << std::endl;
	return 0;
}