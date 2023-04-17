#include <iostream>
#include <thread>
#include <mutex>
#include <deque>
#include <chrono>

std::deque<int> q;
std::mutex mu;
std::condition_variable cond;

// Problem

void producer1() {
	int count = 10;
	while (count > 0) {
		std::unique_lock<std::mutex> locker(mu);
		q.push_front(count);
		locker.unlock();
		std::cout << "t1 produced a value for t2: " << count << std::endl;
		//std::this_thread::sleep_for(std::chrono::seconds(1));
		--count;
	}
}

void consumer1() {
	int data = 0;
	while (data != 1) {
		std::unique_lock<std::mutex> locker(mu);
		if (!q.empty()) {
			data = q.back();
			q.pop_back();
			locker.unlock();
			std::cout << "t2 got a value from t1: " << data << std::endl;
		}
		else {
			locker.unlock();
		}
		//std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}

// Solution

// Using conditional variable and mutex
void producer() {
	int count = 10;
	while (count > 0) {
		std::unique_lock<std::mutex> locker(mu);
		q.push_front(count);
		std::cout << "t1 produced a value for t2: " << count << std::endl;
		locker.unlock();
		cond.notify_one();  // Notify one waiting thread, if there is one.
		// cond.notify_all();
		std::this_thread::sleep_for(std::chrono::seconds(1));
		--count;
	}
}

void consumer() {
	int data = 0;
	while (data != 1) {
		std::unique_lock<std::mutex> locker(mu);
		cond.wait(locker, []() { return !q.empty(); });  // Unlock mu and wait to be notified
														 // relock mu
		data = q.back();
		q.pop_back();
		locker.unlock();
		std::cout << "t2 got a value from t1: " << data << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}

int main() {
	std::thread t1(producer);
	std::thread t2(consumer);
	t1.join();
	t2.join();

	return 0;
}