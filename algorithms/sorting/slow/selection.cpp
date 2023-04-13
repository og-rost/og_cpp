#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

using iter = std::vector<int>::iterator;

iter get_min(iter beg, iter end) {
	iter min = beg;
	for(iter i = beg + 1; i != end; ++i) {
		if(*i < *min) {
			min = i;
		}
	}
	return min;
}

void selection_sort(iter beg, iter end) {
	for(iter i = beg; i != end; ++i ) {
		iter min = get_min(i, end);
		std::swap(*min, *i);
	}
}

bool test(unsigned int max_array_size, unsigned int max_test_count, unsigned int max_number) {

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis1(0, max_array_size);
	std::uniform_int_distribution<> dis2(0, max_test_count);
	std::uniform_int_distribution<> dis3(0, max_number);
	
	max_array_size = dis1(gen);
	max_test_count = dis2(gen);

	std::cout << "Running test for <max_array_size>: " << max_array_size << "  ";
	std::cout << "<max_test_count>: " << max_test_count << std::endl;

	std::vector<int> vec;

	unsigned int count = max_test_count;

	while(max_test_count--) {
		std::cout << "running test " << count - max_test_count << std::endl;
		vec.reserve(max_array_size);

		for(int i = 0; i < max_array_size; ++i) {
			vec.push_back(dis3(gen));
		}

		std::shuffle(vec.begin(), vec.end(), std::default_random_engine(1000000));
		selection_sort(vec.begin(), vec.end());
		if (!std::is_sorted(vec.begin(), vec.end())) {
			return false;
		}
		vec.clear();
	}
	return true;
}

int main() {
	if (test(100, 100, 100)) {
		std::cout << "Selection Sort works PERFECT" << std::endl;	
	}
	else {
		std::cout << "Selection Sort developed by BITCH" << std::endl;
	}
}
