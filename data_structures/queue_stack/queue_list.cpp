#include <iostream>

struct node {
    int data;
    node* next = nullptr;
    node(int d) : data(d) {}
}; 

class queue {
public:
    queue() {}
    ~queue() {
        clear();
    }
    void push(int);
    void pop();
    int& front();
    int& back();
private:
    void clear();
    node* fr = nullptr;
    node* bck = nullptr;
};
 
void queue::clear() {
    while (fr) {
        node* temp = fr->next;
        delete fr;
        fr = temp;
    }
}

void queue::push(int k) {
    node* temp = new node(k);
    if (!bck) {
       fr = bck = temp;
    }
    else {
       bck->next = temp;
       bck = temp;
   }
}

void queue::pop() {    
    if (fr) {
        node* temp = fr;
        fr = fr->next;
        delete temp;
        if (!fr) {
           fr = bck = nullptr;
        } else if(!fr->next) {
            bck = fr;
        }
    } else {
		throw std::out_of_range("Error: q is empty, cannot pop");
	}
}
 
int& queue::front() {
    if (fr) {
        return fr->data;
    } else {
		throw std::out_of_range("Error: q is empty, cannot get the front element");
	}
}

int& queue::back() {
    if (bck) {
        return bck->data;
    } else if (fr) {
        return fr->data;
    } else {
		throw std::out_of_range("Error: q is empty, cannot get the back element");
	}
}

int main() {
    queue qq;
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