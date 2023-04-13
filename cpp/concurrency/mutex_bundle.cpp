#include <iostream>
#include <thread>
#include <fstream>
#include <mutex>

// 1. Avoid global variables
// 2. Mutex should bundle together with the resource it is protecting.

class LogFile {
	std::mutex m_mutex;
	std::ofstream f;
public:
	LogFile() {
		f.open("log.txt");
	}
	~LogFile() {
		f.close();
	}
	void shared_print(std::string id, int value) {
		std::lock_guard<std::mutex> locker(m_mutex);
		f << "From " << id << ": " << value << std::endl;
	}
	// Never leak f to outside world
};

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

// STL stack is not thread safe
// to be thread safe it must combine top and pop
// but it will make stack not exception safe