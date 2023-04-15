#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <thread>
#include <mutex>


// Using mutex to synchronize threads
std::mutex m_mutex;

void shared_print(std::string id, int value) {
	std::lock_guard<std::mutex> locker(m_mutex);
	std::cout << "From " << id << ": " << value << std::endl;
}

class Fctor {
public:
	void operator()() {
		for (int i = 0; i > -100; --i) 
			shared_print("t1", i);
	}
};

void f1() {
	Fctor fctor;
	std::thread t1(fctor);

	for (int i = 0; i < 100; ++i) {
		shared_print("main", i);
	}

	t1.join();
}


// 1. Avoid global variables
// 2. Mutex should bundle together with the resource it is protecting.

class LogFile {
	std::mutex m_mutex;
	std::ofstream f;
public:
	LogFile() {
		f.open("log.txt");
	} // Need destructor to close file
	void shared_print(std::string id, int value) {
		std::lock_guard<std::mutex> locker(m_mutex);
		f << "From " << id << ": " << value << std::endl;
	}
	// Never leak f to outside world
};

class Fctor2 {
	LogFile& m_log;
public:
	Fctor2(LogFile& log) : m_log(log) {}
	void operator()() {
		for (int i = 0; i > -100; --i) { 
			m_log.shared_print("t1", i);
		}
	}
};

void f2() {
	LogFile log;
	Fctor2 fctor(log);
	std::thread t1(fctor);

	for (int i=0; i<100; i++)
		log.shared_print("main", i);

	t1.join();
}

// Deadlock
class LogFile2 {
	std::mutex _mu;
	std::mutex _mu_2;
	std::ofstream f;
public:
	LogFile2() {
		f.open("log.txt");
	}
	void shared_print(std::string id, int value) {
		std::lock_guard<std::mutex> locker(_mu);
		std::lock_guard<std::mutex> locker1(_mu_2);
		f << "From " << id << ": " << value << std::endl;
	}
	void shared_print_2(std::string id, int value) {
		std::lock_guard<std::mutex> locker1(_mu_2);
		std::lock_guard<std::mutex> locker(_mu);
		f << "From " << id << ": " << value << std::endl;
	}
};


// Solution: lock the mutexes in a fixed order

class LogFile3 {
	std::mutex m_mutex;
	std::mutex m_mutex_2;
	std::ofstream f;
public:
	LogFile3() {
		f.open("log.txt");
	}
	void shared_print(std::string id, int value) {
		std::lock(m_mutex, m_mutex_2);
		f << "From " << id << ": " << value << std::endl;
	}
	void shared_print_2(std::string id, int value) {
		std::lock(m_mutex, m_mutex_2);
		f << "From " << id << ": " << value << std::endl;
	}
};


// Deferred Lock
class LogFile4 {
	std::mutex m_mutex;
	std::ofstream f;
public:
	LogFile4() {
		f.open("log.txt");
	}
	void shared_print(std::string id, int value) {
		std::unique_lock<std::mutex> locker(m_mutex, std::defer_lock);
		locker.lock();  // Now the mutex is locked
		f << "From " << id << ": " << value << std::endl;
	}
};

/*

defer_lock_t	do not acquire ownership of the mutex
try_to_lock_t	try to acquire ownership of the mutex without blocking
adopt_lock_t	assume the calling thread already has ownership of the mutex

*/


int main() {
	f1();
	f2();

	return 0;
}
