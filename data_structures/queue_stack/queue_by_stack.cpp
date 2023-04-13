#include <iostream>
#include <stack>

class queue_by_stack {
	std::stack<int> s1;
	std::stack<int> s2;
public:
	void push(const int&);
	void pop();
    int&  front();
};

void queue_by_stack::push(const int& val) {
	std::cout<<"push worked"<<std::endl;
	s1.push(val);
}

void queue_by_stack::pop() {
	if(s2.empty()) {
		while(!s1.empty()) {
			int q = s1.top();
			s1.pop();
			s2.push(q);
		}
	}
	s2.pop();
	std::cout<<"pop worked"<<std::endl;
}

 int& queue_by_stack::front() {
	if (s2.empty()) {
		while(!s1.empty()) {
			s2.push(s1.top());
			s1.pop();
		}
	}
	std::cout<<"front worked"<<std::endl;
	return s2.top();
}

int main() {
	queue_by_stack ob;
	ob.push(1);
	ob.push(2);
	ob.push(3);
	ob.push(4);
	ob.push(5);
	ob.push(6);
	ob.push(7);
	ob.pop();
	int b = ob.front();
	std::cout<<b<<std::endl;
	ob.pop();
    b = ob.front();
	std::cout<<b<<std::endl;
	ob.pop();
    b = ob.front();
	std::cout<<b<<std::endl;
	ob.pop();
	ob.pop();
	ob.pop();
	ob.pop();
	ob.push(10);
	ob.push(11);
	ob.push(12);
	b = ob.front();
	std::cout<<b<<std::endl;
	return 0;
}