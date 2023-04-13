#include <iostream>
 
class queue {  
public:
    queue(size_t c) : cap(c) {
        if (c > 1) {
            array = new int(c);
        }
    }
    ~queue() { 
        delete [] array;
    }
    void push(int);
    void pop();
    int& front();
    int& back();
private:
    size_t cap;
    int size = 0;
    int fr = 0;
    int bck = -1;
    int* array;
    bool isFull();
    bool isEmpty();
};
 
bool queue::isFull() {
    return size == cap;
}
 
bool queue::isEmpty() { 
    return size == 0;
}

void queue::push(int item) {
    if (!isFull()) {
        bck = (bck + 1) % cap;
        array[bck] = item;
        ++size;
    }
}
 
void queue::pop() {
    if (!isEmpty()) {
        fr = (fr + 1) % cap;
        --size;
    } else {
		throw std::out_of_range("Error: q is empty, cannot pop");
	}
}
 
int& queue::front() {
    if (!isEmpty()) {
       return array[fr];
    } else {
		throw std::out_of_range("Error: q is empty, cannot get the front element");
	}
} 

int& queue::back() {
    if (!isEmpty()) {
       return array[bck];
    } else {
		throw std::out_of_range("Error: q is empty, cannot get the back element");
	}
} 

int main() {
    queue qq(10); 
    qq.push(10);
    qq.push(20);
    qq.push(30);
    std::cout << qq.front() << std::endl;
    std::cout << qq.back() << std::endl;
    qq.front() = 100;
    qq.back()  = 200;
    std::cout << qq.front() << std::endl;
    std::cout << qq.back() << std::endl;
    qq.pop();
    std::cout << qq.front() << std::endl;
    std::cout << qq.back() << std::endl;
    qq.pop();
    std::cout << qq.front() << std::endl;
    std::cout << qq.back() << std::endl;
    qq.pop();
    
    try {
		qq.pop();
	} catch (std::out_of_range& ex) {
		std::cout << ex.what() << std::endl;
	}
	try {
		std::cout << qq.front() << std::endl;
	} catch (std::out_of_range& ex) {
		std::cout << ex.what() << std::endl;
	}
    try {
		std::cout << qq.back() << std::endl;
	} catch (std::out_of_range& ex) {
		std::cout << ex.what() << std::endl;
	}
    return 0;
}