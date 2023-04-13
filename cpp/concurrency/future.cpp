#include <iostream>
#include <future>

// For threads to return values: future
int factorial(int N) {
	int res = 1;
	for (int i = N; i>1; i--)
		res *= i;

	return res;
}

int main() {
	//future<int> fu = std::async(factorial, 4); 
	std::future<int> fu = std::async(std::launch::deferred | std::launch::async, factorial, 4); 
									// creating thread is determined by implementation
	//std::future<int> fu = std::async(std::launch::deferred, factorial, 4); 
									// do not create a thread
	//std::future<int> fu = std::async(std::launch::async, factorial, 4); 
									// create a thread
	std::cout << "Got from child thread #: " << fu.get() << std::endl;
	// fu.get();  // crash

	return 0;
}