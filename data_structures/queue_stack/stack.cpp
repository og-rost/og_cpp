#include <iostream>
#include <stdexcept>

class stack {
public:
	stack() {
        array = new int(100);
	}
	~stack() {
		delete [] array;
	}
	void push(int);
	void pop();
	int& top();
private:
	int size = 0;
    int* array;
    bool isFull();
	bool isEmpty();
};
 
bool stack::isFull() {
	return size == 99;
}
 
bool stack::isEmpty() {
	return size == 0;
}
 
void stack::push(int val) {
    if (!isFull()) {
		array[size++] = val;
	} else {
		// relocate
		// push
	}
}
 
void stack::pop() {
    if (!isEmpty()) {
		--size;
	} else {
		throw std::out_of_range("Error: stack is empty, cannot pop");
	}
}
 
int& stack::top() {
    if (!isEmpty()) {
		return array[size - 1];
	} else {
		throw std::out_of_range("Error: stack is empty, cannot get the top element");
	}
}

int main() {
	stack stk;
	stk.push(10);
	stk.push(20);
	stk.push(30);
	std::cout << stk.top() << std::endl;
	stk.top() = 50;
	std::cout << stk.top() << std::endl;
	stk.pop();
	std::cout << stk.top() << std::endl;
	stk.pop();
	std::cout << stk.top() << std::endl;
	stk.pop();
	try {
		std::cout << stk.top() << std::endl;
	} catch (std::out_of_range& ex) {
		std::cout << ex.what() << std::endl;
	}
	try {
		stk.pop();
	} catch (std::out_of_range& ex) {
		std::cout << ex.what() << std::endl;
	}

	return 0;
}