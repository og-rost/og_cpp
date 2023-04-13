#include "single_list.h"
#include <iostream>

node* list::copy() {	
	node* new_list = nullptr;
	if (head) new_list = new node(head->data);
	else return new_list;

	node* temp = head;
	node* t = new_list;
	while (temp->next) {
		t->next = new node(temp->next->data);
		temp = temp->next;
		t = t->next;
	}
	return new_list;
}

void list::clear() {
	while (head) {
		node* temp = head->next;
		delete head;
		head = temp;
	}
	head = nullptr;
}

void list::clear_rec(node*& del) {
	if (del) {
		clear_rec(del->next);
		delete del;
		del = nullptr;
	}
}

void list::print() {
	node* hd = head;
	while (hd) {
		std::cout << hd->data << "  ";
		hd = hd->next;
	}
	std::cout << std::endl;
}

void list::print_rec(node* hd) {
	if (hd) {
		std::cout << hd->data << "  ";
		print_rec(hd->next);
	}	
}

void list::print_rev(node* head) {
	if (head) {
		print_rev(head->next);
		std::cout << head->data << "  ";
	}
}

void list::push_front(int val) {
	node* p = new node(val);
	p->next = head;
	head = p;
}

void list::pop_front() {
	if (head) {
		node* temp = head->next;
		delete head;
		head = temp;
	}
}

void list::insert(node* p, int val) {
	if (p) {
		node* nn = new node(val);
		nn->next = p->next;
		p->next = nn;
	}
}

void list::remove(node* p) {
	if (p) {
		node* temp = p->next;
		p->data = p->next->data;
		p->next = p->next->next;
		delete temp;
	}
}

void list::remove(int val) {
	if (head && val == head->data) {
		pop_front();
		return;
	}

	node* temp = head->next;
	while (temp && temp->data != val)
		temp = temp->next;
	if (temp)
		remove(temp);
}

void list::remove_all_x(int x) {
	node* temp = head;
	while (temp && temp->next) {
		if (temp->data == x) {
			remove(temp);
		}		
		if (temp->next->data == x) {
			remove(temp->next);
		}
		temp = temp->next;
	}	
	
	if (temp->data == x)
		pop_back();
}

void list::push_back(int val){
	node* temp = head;
	while (temp->next->next)
		temp = temp->next;
	temp->next->next = new node(val);
}

void list::pop_back() {
	node* temp = head;
	while (temp->next->next)
		temp = temp->next;	
	delete temp->next;;
	temp->next = nullptr;
}

void list::reverse() {
	node* next = nullptr;
	node* prev = nullptr;

	node* curr = head;
	while (curr) {
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	head = prev;
}

void list::reverse_rec(node*& head) {
	if (!head) return;
	node* first = head;
	node* rest = first->next;
	if (!rest) return;
	reverse_rec(rest);
	first->next->next = first;
	first->next = nullptr;
	head = rest;
}

node* list::getMid(node* head) {
	if (!head)
		return nullptr;
	node* slow = head;
	node* fast = head;
	while (fast && fast->next) {
		fast = fast->next->next;
		slow = slow->next;
	}
	return slow;
}

node* list::getMid_(node* head) {
	if (!head)
		return nullptr;
	
	int count = 0;
	node* mid = head;
	while (head) {
		if (count & 1)
			mid = mid->next;
		++count;
		head = head->next;
	}
	return mid;
}

node* list::getNth(node* head, int n) {
	if (!head)
		return nullptr;
	while (--n) {
		if (head->next)
			head = head->next;
		else return nullptr;
	}
	return head;
}

node* list::getNthFromEnd(node* head, int n) {
	if (!head)
		return nullptr;
	int cnt = 0;
	node* helper = head;
	while (cnt++ < n) {
		if (!helper)
			return nullptr;
		helper = helper->next;
	}
	while (helper) {
		head = head->next;
		helper = helper->next;
	}
	return head;
}

size_t list::getCount(node* head) {
	int cnt = 0;
	while (head) {
		++cnt;
		head = head->next;
	}
	return cnt;
}

void list::detect_n_remove_loop(node* head) {
	node* slow = head;
	node* fast = head;
	bool hasLoop = false;
	while (slow && fast && fast->next) {
		slow = slow->next;
		fast = fast->next->next;
		if (slow == fast) {
			hasLoop = true;
			break;
		}		
	}
	if (hasLoop) {
		fast = head;
		node* p = nullptr;
		while (slow != fast) {
			p = slow;
			slow = slow->next;
			fast = fast->next;
		}
		p->next = nullptr;
	}
}

bool list::isPalindrom(node*& left, node* right) {
	if (!right)
		return true;
	bool pal = isPalindrom(left, right->next);
	if (!pal) 
		return false;
	bool ispal = (right->data == left->data);
	left = left->next;
	return ispal;
}

bool list::isPalindrom(node* head) {
	return isPalindrom(head, head);
}

void list::sortedInsert(node*& head, int insert) {
	node* new_elem = new node(insert);
	if (!head || head->data >= insert) {
		new_elem->next = head;
		head = new_elem;
	}

	else {
		node* curr = head;
		while (curr->next && curr->next->data <= insert)
			curr = curr->next;
		new_elem->next = curr->next;
		curr->next = new_elem;
	}		
}

void list::swapKthWithN_Kth(node* head, int k) {
	if (getCount(head) < k) return;
	node* curr = head;
	while (--k)
		curr = curr->next;
	node* x = curr;
	node* y = head;
	while (curr->next) {
		curr = curr->next;
		y = y->next;
	}
	std::swap(y->data, x->data);
}

node* list::intersecHelper(node* h1, node* h2, int dist) {
	node* c1 = h1;
	node* c2 = h2;

	for (int i = 0; i < dist; ++i) {
		if (!c1) return nullptr;
		c1 = c1->next;
	}

	while (c1 && c2) {
		if (c1 == c2)
			return c1;
		c1 = c1->next;
		c2 = c2->next;
	}
	return nullptr;
}

node* list::getIntersectionPoint(node* h1, node* h2) {
	int c1 = getCount(h1);
	int c2 = getCount(h2);
	if (c1 > c2)
		return intersecHelper(h1, h2, c1 - c2);
	else
		return intersecHelper(h2, h1, c2 - c1);
}

void list::pairwiseswap(node* head) {
	node* temp = head;
	while (temp && temp->next) {
		std::swap(temp->data, temp->next->data);
		temp = temp->next->next;
	}
}

void list::pairwiseswapRec(node* head) {
	if (head && head->next) {
		std::swap(head->data, head->next->data);
		pairwiseswapRec(head->next->next);
	}
}

void list::moveLastToFront(node*& head) {
	if (!head || !head->next)
		return;
	node* tempLast = nullptr;
	node* last = head;

	while (last->next) {
		tempLast = last;
		last = last->next;
	}

	tempLast->next = nullptr;
	last -> next = head;
	head = last;
}

void list::deleteAlternateNodes(node* head) {
	if (!head)
		return;
	node* prev = head;
	node* temp = head->next;
	while (prev && temp) {
		prev->next = temp->next;
		delete temp;
		prev = prev->next;
		if (prev)
			temp = prev->next;
	}
}

bool list::areIdentical(node* l1, node* l2) {
	while (true) {
		if (!l1 && !l2)
			return true;
		if (!l1 && l2)
			return false;
		if (l1 && !l2)
			return false;
		if (l1->data != l2->data)
			return false;
		l1 = l1->next;
		l2 = l2->next;
	}
}

bool list::areIdenticalRec(node* l1, node* l2) {
	if (!l1 && !l2)  return true;
	if (!l1 && l2)   return false;
	if (l1 && !l2)   return false;
	if (l1->data != l2->data) return false;
	return areIdenticalRec(l1->next, l2->next);
}

node* list::merge(node* list1, node* list2) {
	node* result = nullptr;
	if (!list1) return list2;
	if (!list2) return list1;

	if (list1->data <= list2->data) {
		result = list1;
		result->next = merge(list1->next, list2);
	}
	else {
		result = list2;
		result->next = merge(list1, list2->next);
	}

	return result;
}

void list::mergeSort(node*& head) {
	node* a;
	node* b;
	if (!head || !head->next)
		return;
	frontBackSplit(head, a, b);
	mergeSort(a);
	mergeSort(b);
	head = merge(a, b);
}

void list::frontBackSplit(node* source, node*& front, node*& back) {
	node* fast;
	node* slow;
	if (!source || !source->next) {
		front = source;
		back = nullptr;
	}
	else {
		slow = source;
		fast = source->next;
		while (fast) {
			fast = fast->next;
			if (fast) {
				slow = slow->next;
				fast = fast->next;
			}
		}
		front = source;
		back = slow->next;
		slow->next = nullptr;
	}
}

node* list::getTail(node* curr) {
	while (curr && curr->next)
		curr = curr->next;
	return curr;
}

node* list::partition(node* head, node* end, node*& newHead, node*& newEnd) {
	node* pivot = end;
	node* prev = nullptr;
	node* curr = head;
	node* tail = pivot;

	while (curr != pivot) {
		if (curr->data < pivot->data) {
			if (!newHead)
				newHead = curr;
			prev = curr;
			curr = curr->next;
		}
		else {
			if (prev)
				prev->next = curr->next;
			node* tmp = curr->next;
			curr->next = nullptr;
			tail->next = curr;
			tail = curr;
			curr = tmp;
		}
	}
	if (!newHead)
		newHead = pivot;
	newEnd = tail;
	return pivot;
}

node* list::quickSortRec(node* head, node* end) {
	if (!head || head == end)
		return head;
	node* newHead = nullptr;
	node* newEnd = nullptr;
	node* pivot = partition(head, end, newHead, newEnd);

	if (newHead != pivot) {
		node* tmp = newHead;
		while (tmp->next != pivot)
			tmp = tmp->next;
		tmp->next = nullptr;
		newHead = quickSortRec(newHead, tmp);
		tmp = getTail(newHead);
		tmp->next = pivot;
	}
	pivot->next = quickSortRec(pivot->next, newEnd);
	return newHead;
}

void list::quickSort(node*& head) {
	head = quickSortRec(head, getTail(head));
}

node* list::reverseInGroupsOfGivenSize(node* head, int k) {
	node* curr = head;
	node* next = nullptr;
	node* prev = nullptr;
	int count = 0;
	while (curr && count < k) {
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
		++count;
	}
	if (next)
		head->next = reverseInGroupsOfGivenSize(next, k);
	return prev;
}

node* list::reverseAlternateKNodes(node* head, int k) {
	node* curr = head;
	node* next = nullptr;
	node* prev = nullptr;
	int count = 0;
	while (curr && count < k) {
		next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
		++count;
	}
	if (head)
		head->next = curr;
	while (count-- && curr)
		curr = curr->next;
	if (curr)
		curr->next = reverseAlternateKNodes(curr->next, k);
	return prev;
}

void list::deleteNodesWithGreaterValueOnRightSide(node*& head) {
	list::reverse_rec(head);
	list::delHelper(head);
	list::reverse_rec(head);
}

void list::delHelper(node* head) {
	node* curr = head;
	node* max  = head;
	node* temp = nullptr;
	while (curr && curr->next) {
		if (curr->next->data < max->data) {
			temp = curr->next;
			curr->next = temp->next;
			delete temp;
		}
		else {
			curr = curr->next;
			max = curr;
		}
	}
}

void list::segregateEvenAndOddNodes(node*& head) {
	node* end = head;
	node* prev = nullptr;
	node* curr = head;
	while (end->next)
		end = end->next;
	node* new_end = end;
	while (curr->data % 2 && curr != end) {
		new_end->next = curr;
		curr = curr->next;
		new_end->next->next = nullptr;
		new_end = new_end->next;
	}
	//do the following only if even node left
	if (curr->data % 2 == 0) {
		head = curr;
		while (curr != end) {
			if (curr->data % 2 == 0) {
				prev = curr;
				curr = curr->next;
			}
			else {
				prev->next = curr->next;
				curr->next = nullptr;
				new_end->next = curr;
				new_end = curr;
				curr = prev->next;
			}
		}
	}
	else
		prev = curr;
	if (new_end != end && end->data % 2 != 0) {
		prev->next = end->next;
		end->next = nullptr;
		new_end->next = end;
	}
}

node* list::addTwoNumbers(node* first, node* second) {
	node* res = nullptr;
	node* temp = nullptr;
	node* prev = nullptr;
	int carry = 0; 

	while (first || second) {
		int sum = carry +
			(first ? first->data : 0) +
			(second ? second->data : 0);
		carry = (sum > 10) ? 1 : 0;
		sum = sum % 10;
		temp = new node(sum);
		temp->next = nullptr;
		if (!res)
			res = temp;
		else
			prev->next = temp;
		prev = temp;
		if (first)	first = first->next;
		if (second)	second = second->next;
	}
	if (carry > 0) {
		temp->next = new node(carry);
		temp->next->next = nullptr;
	}
	return res;
}