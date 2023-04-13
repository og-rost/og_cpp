#include <iostream>
#include <future>

// shared_future
int factorial(std::shared_future<int> f) {
	// do something else

	int N = f.get();     // If promise is distroyed, exception: std::future_errc::broken_promise
	f.get();
	std::cout << "Got from parent: " << N << std::endl;
	int res = 1;
	for (int i = N; i>1; i--)
		res *= i;

	return res;
}

int main() {
	// Both promise and future cannot be copied, they can only be moved.
	std::promise<int> p;
	std::future<int> f = p.get_future();
	std::shared_future<int> sf = f.share(); // shared future can be copied

	std::future<int> fu = std::async(std::launch::async, factorial, sf);
	std::future<int> fu2 = std::async(std::launch::async, factorial, sf);

	// Do something else
	std::this_thread::sleep_for(std::chrono::milliseconds(20));
	p.set_value(5);

	std::cout << "Got from child thread #: " << fu.get() << std::endl;
	std::cout << "Got from child thread #: " << fu2.get() << std::endl;
}
