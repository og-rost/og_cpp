#include <functional> // std::bind
#include <iostream>
#include <fstream>
#include <thread>
#include <string>
#include <mutex>
#include <future>
#include <deque>


// thread to return values
int factorial1(int N) {
	int res = 1;
	for (int i = N; i > 1; --i) {
		res *= i;
	}

	return res;
}

void f1() {
	//future<int> fu = std::async(factorial, 4); 
	std::future<int> fu = std::async(std::launch::deferred | std::launch::async, factorial1, 4);
	// creating thread is determined by implementation
	//std::future<int> fu = std::async(std::launch::deferred, factorial, 4); // do not create a thread
	//std::future<int> fu = std::async(std::launch::async, factorial, 4); // create a thread
	std::cout << "Got from child thread #: " << fu.get() << std::endl;
	// fu.get();  // crash
}


// Asynchronously provide data with promise
int factorial2(std::future<int>& f) {
	int N = f.get();     // If promise is distroyed, exception: std::future_errc::broken_promise
	std::cout << "Got from parent: " << N << std::endl; 
	int res = 1;
	for (int i = N; i > 1; --i) {
		res *= i;
	}

	return res;
}

void f2() {
	std::promise<int> p;
	std::future<int> f = p.get_future();

	std::future<int> fu = std::async(std::launch::async, factorial2, std::ref(f));

	// Do something else
	std::this_thread::sleep_for(std::chrono::milliseconds(20));
	p.set_value(5);   
	//p.set_value(28);  // It can only be set once

	std::cout << "Got from child thread #: " << fu.get() << std::endl;
}


// shared_future
int factorial3(std::shared_future<int> f) {
	int N = f.get();     // If promise is distroyed, exception: std::future_errc::broken_promise
	f.get();
	std::cout << "Got from parent: " << N << std::endl; 
	int res = 1;
	for (int i = N; i > 1; --i) {
		res *= i;
	}

	return res;
}

void f3() {
	// Both promise and future cannot be copied, they can only be moved.
	std::promise<int> p;
	std::future<int> f = p.get_future();
	std::shared_future<int> sf = f.share();

	std::future<int> fu = std::async(std::launch::async, factorial3, sf);
	std::future<int> fu2 = std::async(std::launch::async, factorial3, sf);

	std::this_thread::sleep_for(std::chrono::milliseconds(20));
	p.set_value(5);

	std::cout << "Got from child thread #: " << fu.get() << std::endl;
	std::cout << "Got from child thread #: " << fu2.get() << std::endl;
}


// async() is used in the same ways as thread(), bind() */
class A {
public:
	std::string note;
	void f(int x, char c) {}
	long g(double x) { note = "changed"; return 0; }
	int operator()(int N) { return 0; }
};
A a;

void f4() {
	a.note = "Original"; 
	std::future<int> fu3 = std::async(A(), 4);    // A tmpA;  tmpA is moved to async(); create a task/thread with tmpA(4);
	std::future<int> fu4 = std::async(a, 7);    
	std::future<int> fu5 = std::async(std::ref(a), 7); // a(7);  Must use reference wrapper
	//std::future<int> fu5 = std::async(&a, 7); // Won't compile

	std::future<void> fu1 = std::async(&A::f, a, 56, 'z'); // A copy of a invokes f(56, 'z')
	std::future<long> fu2 = std::async(&A::g, &a, 5.6);    // a.g(5.6);  a is passed by reference
		// note: the parameter of the invocable are always passed by value, but the invokeable itself can be passed by ref.
	std::cout << a.note << std::endl;
}


/*
	std::thread t1(a, 6);   
	std::async(a, 6);   
    std::bind(a, 6);
    std::call_once(once_flag, a, 6);

	std::thread t2(a, 6); 
	std::thread t3(std::ref(a), 6); 
	std::thread t4(std::move(a), 6);
	std::thread t4([](int x){return x*x;}, 6);

	std::thread t5(&A::f, a, 56, 'z');  // copy_of_a.f(56, 'z')
	std::thread t6(&A::f, &a, 56, 'z');  // a.f(56, 'z') 
*/



// packaged_task

std::mutex mu;
std::deque<std::packaged_task<int()>> task_q;

int factorial4(int N) {
	int res = 1;
	for (int i = N; i > 1; --i)
		res *= i;

	return res;
}

void thread_1() {
	for (int i = 0; i < 10000; ++i) {
		std::packaged_task<int()> t;
		{
			std::lock_guard<std::mutex> locker(mu);
			if (task_q.empty()) {
				continue;
			}
			t = std::move(task_q.front());
			task_q.pop_front();
		}
		t();
	}
}

void f5() {
	std::thread th(thread_1);

	std::packaged_task<int()> t(std::bind(factorial4, 6));  
	std::future<int> ret = t.get_future();
	std::packaged_task<int()> t2(std::bind(factorial4, 9));
	std::future<int> ret2 = t2.get_future();
	{
		std::lock_guard<std::mutex> locker(mu);
		task_q.push_back(std::move(t));
		task_q.push_back(std::move(t2));
	}
	std::cout << "I see: " << ret.get() << std::endl;
	std::cout << "I see: " << ret2.get() << std::endl;

	th.join();
}

/*

3 ways to get a future:

1) promise::get_future()
2) packaged_task::get_future()
3) async() returns a future

*/


// threads with time constrains

void f6() {
    std::thread t1(factorial4, 6);
    std::this_thread::sleep_for(std::chrono::milliseconds(3));
    std::chrono::steady_clock::time_point tp = std::chrono::steady_clock::now() + std::chrono::microseconds(4);
    std::this_thread::sleep_until(tp);

    std::mutex mu;
    std::lock_guard<std::mutex> locker(mu);
    std::unique_lock<std::mutex> ulocker(mu);
    ulocker.try_lock();
    //ulocker.try_lock_for(std::chrono::nanoseconds(500));
    //ulocker.try_lock_until(tp);

    std::condition_variable cond;
    cond.wait_for(ulocker, std::chrono::microseconds(2));
    cond.wait_until(ulocker, tp);

    /* Future and Promise */
    std::promise<int> p; 
    std::future<int> f = p.get_future();
    f.get();
    f.wait();
    f.wait_for(std::chrono::milliseconds(2));
    f.wait_until(tp);

    /* async() */
    std::future<int> fu = std::async(factorial4, 6);

    /* Packaged Task */
    std::packaged_task<int(int)> t(factorial4);
    std::future<int> fu2 = t.get_future();
    t(6);
}


void f7() {
	std::this_thread::sleep_until(std::chrono::steady_clock::now() + std::chrono::seconds(3));

	std::future<int> fu;
	fu.wait_for(std::chrono::seconds(3));
	fu.wait_until(std::chrono::steady_clock::now() + std::chrono::seconds(3));

	std::condition_variable c;
	std::mutex mu;
	std::unique_lock<std::mutex> locker(mu);
	c.wait_for(locker, std::chrono::seconds(3));
	c.wait_until(locker, std::chrono::steady_clock::now() + std::chrono::seconds(3));
}
 

int main() {
	f1();
	f2();
	f3();
	f4();
	f5();
	f6();
	f7();
	return 0;
}