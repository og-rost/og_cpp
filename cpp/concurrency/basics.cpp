#include <iostream>
#include <fstream>
#include <thread>
#include <string>

void f1() {
	auto print_message = []() {
        std::cout << "Hello from the new thread!" << std::endl;
    };

	std::thread t1(print_message);
	t1.join();       // main thread wait for t1 to finish
	// t1.detach();  // main thread let t1 to run on its own: t1 is a daemon process.
}

/*

If you don't call join() or detach() on a std::thread object before it goes out of scope,
the program will terminate with a call to std::terminate() when the std::thread destructor is called.
This will typically result in an abrupt termination of your program.

When you create a std::thread, you have two options to manage its lifecycle:

	1) Joining the thread using join(): This will block the calling thread until the newly created thread has finished execution.
	This is useful when you need to ensure that the new thread completes its work before the calling thread can proceed.

	2) Detaching the thread using detach(): This will allow the newly created thread to run independently of the calling thread.
	The new thread will continue to execute even after the calling thread has finished, and it will be cleaned up by the system when it completes.
	This is useful when you want to create a background task that doesn't need to be explicitly waited for.

If you don't call either join() or detach() before a std::thread object is destroyed, the C++ runtime considers this a programming error
and will call std::terminate() to abort the program.

If you don't want to join or detach a thread explicitly, you can use a wrapper class like std::scoped_thread (available since C++20)
or create your own wrapper that takes care of detaching or joining the thread in its destructor.
This will ensure that the thread is properly managed, and your program will not terminate unexpectedly.

*/

// using functor
class Fctor {
	std::ofstream& m_str;
public:
	Fctor(std::ofstream& s) : m_str(s) {}
	void operator()() {
		for (int i = 0; i > -100; --i) {
			m_str << "from t1: " << i << std::endl;
		}
	}
};

void f2() {
	std::ofstream f;
	f.open("log.txt");

	Fctor fctor(f);
	std::thread t1(fctor);

	t1.join();
	f.close();
}


// using a wrapper to join the thread
class ThreadJoiner {
	std::thread& m_th;
public:
	explicit ThreadJoiner(std::thread& t) : m_th(t) {}
	~ThreadJoiner() {
		if(m_th.joinable()) {
			m_th.join();
		}
	}
};

void f3() {
	auto print_message = []() {
        std::cout << "Hello from the new thread!" << std::endl;
    };

	std::thread t1(print_message);
	ThreadJoiner tj(t1);
}


// Passing parameters to a thread
void call_from_thread1(std::string& msg) {
	msg = "Beauty is only skin-deep";
	std::cout << "t1 says: " << msg << std::endl;
}

void f4() {
	std::string s = "A friend in need is a friend indeed.";
	std::thread t1(call_from_thread1, std::ref(s));
	// Function templates ref and cref are helper functions that generate an object of type std::reference_wrapper

	t1.join();

	std::cout << "main says: " << s << std::endl;
}

// Paramters are always passed by value (copied). 
// why? same reason as bind(): deferred execution means the parmeter objects might not be valid at the time of execution
// To pass by reference:
// 1. use std::ref
// 2. use pointer


// passing a class method as thread function
class A {
public:
	void call_from_thread(std::string& msg) {
		msg = "Beauty is only skin-deep";
		std::cout << "t1 says: " << msg << std::endl;
	}
};


void f5() {
	std::string s = "A friend in need is a friend indeed.";
	A a;
	std::thread t1(&A::call_from_thread, &a, std::ref(s));
	t1.join();

	std::cout << "main says: " << s << std::endl;
}


// A thread object cannot be copied
// But it can be moved.  Like fstream, unique_ptr, etc.
void f6() {
	auto print_message = []() {
        std::cout << "Hello from the new thread!" << std::endl;
    };
	std::thread t1(print_message);
	std::thread t2 = std::move(t1);  // t2 become the owner of the thread
	t2.join();
}


int main() {
	f1();
	f2();
	f3();
	f4();
	f5();
	f6();

	return 0;
}
