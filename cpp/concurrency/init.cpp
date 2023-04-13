#include <iostream>
#include <thread>
#include <mutex>
#include <fstream>

// Lock for Initialization
class LogFileBad1 {
	std::mutex m_mutex;
	std::ofstream f;
public:
	void shared_print(std::string id, int value) {
		if (!f.is_open()) {   // lazy initialization
			std::unique_lock<std::mutex> locker(m_mutex);
			f.open("log.txt");   // This must be synchronized
		}
		f << "From " << id << ": " << value << std::endl;  // I don't care this is not synchronized
	}
};

// Problem: log.txt still will be opened multiple times

class LogFileBad2 {
	std::mutex m_mutex;
	std::ofstream f;
public:
	void shared_print(std::string id, int value) {
		if (!f.is_open()) {   // lazy initialization   -- A
			std::unique_lock<std::mutex> locker(m_mutex);
			if (!f.is_open()) {
				f.open("log.txt");   // This must be synchronized  -- B
			}
		}
		f << "From " << id << ": " << value << std::endl;  // I don't care this is not synchronized
	}
};
// Double-checked locking
// Problem: race condition between point A and point B


// C++ 11 solution:
class LogFile {
	static int x;
	std::mutex m_mutex;
	std::ofstream f;
	std::once_flag m_flag;
	void init() { 
		f.open("log.txt"); 
	}
public:
	void shared_print(std::string id, int value) {
		std::call_once(m_flag, &LogFile::init, this); 
		// init() will only be called once by one thread
		//std::call_once(m_flag, [&](){ f.open("log.txt"); });  // Lambda solution
		std::lock_guard<std::mutex> locker(m_mutex);

		f << "From " << id << ": " << value << std::endl;
	}
};
int LogFile::x = 9;

// Note: once_flag and mutex cannot be copied or moved.
// LogFile can neither be copy constructed nor copy assigned

// static member data are guaranteed to be initialized only once.

class Fctor {
	LogFile& m_log;
public:
	Fctor(LogFile& log) : m_log(log) {}
	void operator()() {
		for (int i = 0; i >- 100; --i)
			m_log.shared_print("t1", i);
	}
};

int main() {
	LogFile log;
	Fctor fctor(log);
	std::thread t1(fctor);

	for (int i = 0; i < 100; ++i)
		log.shared_print("main", i);

	t1.join();

	return 0;
}
