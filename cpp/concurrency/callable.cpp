#include <iostream>
#include <thread>
#include <future>
#include <mutex>

// async() are used in the same ways as thread(), bind()
class A {
public:
	std::string note;
	void f(int x, char c) { }
	long g(double x) { note = "changed"; return 0; }
	int operator()(int N) { return 0; }
};
A a;

int main() {
	a.note = "Original";
	std::future<int> fu1 = std::async(A(), 4);       	// A tmpA;  tmpA is moved to async(); create a task/thread with tmpA(4);
	std::future<int> fu2 = std::async(a, 7);      		// copy
	std::future<int> fu3 = std::async(std::ref(a), 7); 	// a(7);  Must use reference wrapper
	// std::future<int> fu4 = std::async(&a, 7); 			// Won't compile
	A a1 = a;
	std::future<int> fu5 = std::async(std::move(a1), 7); // a is no longer usable
	std::future<void> fu6 = std::async(&A::f, a, 56, 'z'); // A copy of a invokes f(56, 'z')
	std::future<long> fu7 = std::async(&A::g, &a, 5.6);    // a.g(5.6);  a is passed by reference
														   // note: the parameter of the invocable
														   // are always passed by value, but the 
														   // invokeable itself can be passed by ref.
	

	std::thread t1(a, 6);
	std::async(a, 6);
	std::bind(a, 6);
	std::once_flag m_flag;
	std::call_once(m_flag, a, 6);
	std::thread t2(a, 6);
	std::thread t3(std::ref(a), 6);
	A a2 = a;
	std::thread t4(std::move(a2), 6);
	std::thread t5([](int x) {return x * x; }, 6);
	std::thread t6(&A::f, a, 56, 'z');  // copy_of_a.f(56, 'z')
	std::thread t7(&A::f, &a, 56, 'z');  // a.f(56, 'z')

	std::cout << a.note << std::endl;

	return 0;
}
