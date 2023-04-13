#include <iostream>
#include <thread>
#include <mutex>
#include <fstream>

// C++ 11 std::lock
class LogFile {
	std::mutex m_mutex;
	std::mutex m_mutex_2;
	std::ofstream f;
public:
	LogFile() {
		f.open("log.txt");
	}
	void shared_print(std::string id, int value) {
		std::lock(m_mutex, m_mutex_2);
		std::lock_guard<std::mutex> locker(m_mutex, std::adopt_lock);
		std::lock_guard<std::mutex> locker1(m_mutex_2, std::adopt_lock);
		f << "From " << id << ": " << value << std::endl;
	}
	void shared_print_2(std::string id, int value) {
		std::lock(m_mutex, m_mutex_2);
		std::lock_guard<std::mutex> locker1(m_mutex_2, std::adopt_lock);
		std::lock_guard<std::mutex> locker(m_mutex, std::adopt_lock);
		f << "From " << id << ": " << value << std::endl;
	}
};

void f(LogFile& log) {
	for(int i = 0; i > -100; --i) {
		log.shared_print(std::string("From f"), i);
	}
}

int main() {
	LogFile lf;

	std::thread t(f, std::ref(lf));

	for(int i = 0; i < 100; ++i) {
		lf.shared_print_2(std::string("From main"), i);
	}

	t.join();
	return 0;
}

// Avoiding deadlock
// 1. Prefer locking single mutex.
// 2. Avoid locking a mutex and then calling a user provided function.
// 3. Use std::lock() to lock more than one mutex.
// 4. Lock the mutex in same order.


// Locking Granularity:
// - Fine-grained lock:  protects small amount of data
// - Coarse-grained lock: protects big amount of data