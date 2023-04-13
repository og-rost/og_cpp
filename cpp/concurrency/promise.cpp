#include <iostream>
#include <future>

// Asynchronously provide data with promise 
int factorial(std::future<int>& f) {
	// do something else

	int N = f.get();     // If promise is distroyed, exception: std::future_errc::broken_promise
	std::cout << "Got from parent: " << N << std::endl;
	int res = 1;
	for (int i = N; i>1; i--)
		res *= i;

	return res;
}

int main() {
	std::promise<int> p;
	std::future<int> f = p.get_future();

	std::future<int> fu = std::async(std::launch::async, factorial, std::ref(f));

	// Do something else
	std::this_thread::sleep_for(std::chrono::milliseconds(20));
	p.set_value(5);   
	//p.set_value(28);  // It can only be set once
	//p.set_exception(std::make_exception_ptr(std::runtime_error("Flat tire")));

	std::cout << "Got from child thread #: " << fu.get() << std::endl;

	return 0;
}
