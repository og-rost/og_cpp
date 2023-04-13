#include <iostream>
#include <thread>

// process vs thread
// thread is faster to start
// communication through shared memory is faster than through files, pipes
// multithreading is difficult to implement
// multiprocessing program can run on system with multiple computers

void thrd() {
	std::cout << "hello from thread" << std::endl;
}

int main() {
	std::thread t(thrd);	// t starts running
	t.join();               // wait for t to finish
	// t.detach();          // main thread let t to run on 
                            // its own as a daemon process and C++ runtime library 
							// is responsible for returning t's resources
				            // main thread may finish before t prints "Hello"

	if(t.joinable()) {
		t.join();
	}
	else {
		std::cout << "thread is not joinable" << std::endl;
	}

	std::cout << "program has completed" << std::endl;
	return 0;
}

// If neither detach nor join is called, terminate() will be called for the t1.
// A thread can only be joined once or detached once. After it is joined or detached
// it becomes unjoinable ( t.joinable() returns false )

// if you have not detached or joined a thread when the destructor 
// is called it will call std::terminate 