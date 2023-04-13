#include <iostream>
#include <thread>

// Passing parameters to a thread


// Paramters are always passed by value (copied).  
// why? same reason as bind(): deferred execution means the parmeter objects might 
// not be valid at the time of execution
// To pass by reference:
// 1. use std::ref
// 2. use pointer

void call_from_thread(std::string& msg) {
	msg = "Beauty is only skin-deep";
	std::cout << "t1 says: " << msg << std::endl;
}

void f1() {

	std::string s = "A friend in need is a friend indeed.";
	std::thread t1(call_from_thread, std::ref(s));
	// Function templates ref and cref are helper functions that 
	// generate an object of type std::reference_wrapper

	t1.join();

	std::cout << "f1 says: " << s << std::endl;
}


// To pass a class method as thread's initial function, use pointers
class A {
public:
	void call_from_thread(std::string* msg) {
		*msg = "Beauty is only skin-deep";
		std::cout << "t1 says: " << *msg << std::endl;
	}
};

void f2() {

	std::string s = "A friend in need is a friend indeed.";
	A a;
	std::thread t1(&A::call_from_thread, &a, &s);
	t1.join();

	std::cout << "f2 says: " << s << std::endl;
}

// Thread with moving parameters

void call_from_thread2(std::string msg) {
	std::cout << "t1 says: " << msg << std::endl;
}

void f3() {
	std::string* ps = new std::string("A friend in need is a friend indeed.");
	std::thread t1(call_from_thread2, std::move(*ps));
	t1.join();

	std::cout << "f3 says: " << *ps << std::endl;
}


// A thread object cannot be copied
// But it can be moved.  Like fstream, unique_ptr, etc.

//Case 1:

void f4() {
	std::string s = "aabbccdd";
	std::thread t1(call_from_thread2, s);
	std::thread t2 = std::move(t1);  // t2 become the owner of the thread
	t2.join();
}


int main() {
	f1();
	f2();
	f3();
	f4();

	return 0;
}