#include "single_list.h"
#include <iostream>

int main() {
	list l1, l2;
	l1.push_front(2);
	l1.push_front(1);
	l1.push_front(9);
	l1.push_front(8);
	l1.push_front(7);

	l2.push_front(6);
	l2.push_front(5);
	l2.push_front(4);
	l2.push_front(3);
	l2.push_front(2);
	l2.push_front(8);

	l1.print();
	l2.print();

	node* res = list::addTwoNumbers(l1.head, l2.head);
	l1.print_rec(res);
	
}