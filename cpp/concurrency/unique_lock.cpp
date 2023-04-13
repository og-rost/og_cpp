#include <iostream>
#include <thread>
#include <fstream>
#include <mutex>

/*
Defer lock
Value used as possible argument to unique_lock's constructor.

unique_lock objects constructed with defer_lock do not lock the 
mutex object automatically on construction, initializing 
them as not owning a lock.

The value is a compile-time constant that carries no state
and is merely used to disambiguate between constructor signatures.

defer_lock_t is an empty class.

The difference is that you can lock and unlock a std::unique_lock. 
std::lock_guard will be locked only once on construction 
and unlocked on destruction.

lock_guard can never be moved, but unique_lock can
*/

// Deferred Lock
class LogFile {
	std::mutex m_mutex;
	std::ofstream f;
public:
	LogFile() {
		f.open("log.txt");
	}
	void shared_print(std::string id, int value) {
		std::unique_lock<std::mutex> locker(m_mutex, std::defer_lock);
		// do something thread safe
		locker.lock();  // Now the mutex is locked
		f << "From " << id << ": " << value << std::endl;
		// here we have some thread safe code
		// locker.unlock();
		// some staff
		// here can lock again which is impossible for lock_guard
		// locker.lock()
	}
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

// Objects cannot be copied but can be moved: 
// thread, packaged_task, fstream, unique_ptr, unique_lock
// mutex can neither be copied nor moved

