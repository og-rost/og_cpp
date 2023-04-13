#include <iostream>
#include <thread>
#include <mutex>
#include <fstream>

// Deadlock 
class LogFile {
	std::mutex _mu;
	std::mutex _mu_2;
	std::ofstream f;
public:
	LogFile() {
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