#include <iostream>
#include <thread>
#include <mutex>

void print() {
	for(int i = 0; i > -100; --i) {
		std::cout << i << std::endl;
	}
}

void f1() {
	std::thread t1(print);
	for(int i = 0; i < 100; ++i) {
		std::cout << i << std::endl;
	}

	t1.join();
}

/* ================================================= */

// Using mutex to synchronize threads

std::mutex m_mutex;

void shared_print(std::string id, int value) {
	std::lock_guard<std::mutex> locker(m_mutex); // RAII, when locker goes out of scope 
												 // the mutex gets automatically unlocked
	//m_mutex.lock(); // if cout throws exception mutex will stay locked forever
	std::cout << "From " << id << ": " << value << std::endl;
	//m_mutex.unlock();
}

class Fctor {
public:
	void operator()() {
		for (int i = 0; i > -100; --i)
			shared_print("t1", i);
	}
};

void f2() {
	Fctor fctor;
	std::thread t1(fctor);

	for (int i = 0; i < 100; ++i)
		shared_print("main", i);

	t1.join();
}

int main() {
	//f1();
	f2();
	return 0;
}