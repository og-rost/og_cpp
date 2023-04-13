#include <iostream> 

struct node {
    int data;
    node* next = nullptr;
    node(int d) : data(d) {}
};
 
class stack {
public:
    stack() {}
    ~stack() {
        clear();
    }
    void push(int);
    void pop();
    int& top();
private:
    void clear();
    node* root = nullptr;
};

void stack::clear() {
    while(root) {
        node* temp = root->next;
        delete root;
        root = temp;
    }
    root = nullptr;
}

void stack::push(int data) {
    node* p = new node(data);
    p->next = root;
    root = p;    
}
 
void stack::pop() {
    bool last = false;;
    if (root && !root->next) {
        last = true;
    }
    if (root) {
		node* temp = root;
		root = root->next;
		delete temp;
	} else {
		throw std::out_of_range("Error: stack is empty, cannot pop");
	}
    if (last) {
        root = nullptr;
    }
}
 
int& stack::top() {
	if (root) {
        return root->data;
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