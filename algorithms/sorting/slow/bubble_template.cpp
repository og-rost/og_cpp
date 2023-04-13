#include <iostream>
#include <vector>

template <typename T>
void bubbleSort(typename std::vector<T>::iterator beg, typename std::vector<T>::iterator end) {
	int n = std::distance(beg, end);
	while (--n) {
		bool isSorted = true;
		for (typename std::vector<T>::iterator it = beg; it != end - 1; ++it) {
			if (*it > *(it + 1)) {
				std::swap(*it, *(it + 1));
				isSorted = false;
			}
		}
		if (isSorted) break;
	}
}

int main() {
	std::vector<int> vec = { 7, 4, 3, 9, 8, 2, 6, 1, 5 };
	for (int i : vec)
		std::cout << i << " ";
	std::cout << std::endl;

	bubbleSort<int>(vec.begin(), vec.end());

	for (int i : vec)
		std::cout << i << " ";
	std::cout << std::endl;

	return 0;

}