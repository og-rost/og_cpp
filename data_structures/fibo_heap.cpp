#include <iostream>

struct node {
	node* prev;
	node* next;
	node* child;
	node* parent;
	int data;
	int degree;
	bool marked;

	node(int d) : data(d), degree(0), marked(false), child(nullptr), parent(nullptr) {
		prev = next = this;
	}
};

class FHeap {
protected:
	node* heap;
public:
	FHeap() : heap(nullptr) {}

	~FHeap() {
		if (heap) {
			clear(heap);
		}
	}

	node* push(int data) {
		node* ret = new node(data);
		heap = merge(heap, ret);
		return ret;
	}

	bool empty() {
		return heap == nullptr;
	}

	int top() {
		return heap->data;
	}

	int pop() {
		node* old = heap;
		heap = popHelper(heap);
		int ret = old->data;
		delete old;
		return ret;
	}

private:
	node* merge(node* a, node* b) {
		if(!a)
			return b;
		if(!b)
			return a;
		if(a->data > b->data)
			std::swap(a, b);
		
		node* an = a->next;
		node* bp = b->prev;
		a->next = b;
		b->prev = a;
		an->prev = bp;
		bp->next = an;
		return a;
	}

	void clear(node* n) {

	}
	
	void addChild(node* parent, node* child) {
		child->prev = child->next = child;
		child->parent = parent;
		++parent->degree;
		parent->child = merge(parent->child, child);
	}

	void unMarkunParentAll(node* n) {
		if(!n)
			return;
		node* c=n;
		do {
			c->marked = false;
			c->parent = nullptr;
			c = c->next;
		} while(c != n);
	}

	node* popHelper(node* n) {
		unMarkunParentAll(n->child);
		if(n->next == n) {
			n=n->child;
		} 
		else {
			n->next->prev = n->prev;
			n->prev->next = n->next;
			n = merge(n->next, n->child);
		}

		if(!n)
			return n;
		node* trees[64] = { nullptr };
		
		while(true) {
			if(trees[n->degree] != nullptr) {
				node* t = trees[n->degree];
				if (t == n)
					break;
				trees[n->degree] = nullptr;
				if(n->data < t->data) {
					t->prev->next = t->next;
					t->next->prev = t->prev;
					addChild(n, t);
				} 
				else {
					t->prev->next = t->next;
					t->next->prev = t->prev;
					if(n->next == n) {
						t->next = t->prev = t;
						addChild(t, n);
						n = t;
					} 
					else {
						n->prev->next = t;
						n->next->prev = t;
						t->next = n->next;
						t->prev = n->prev;
						addChild(t, n);
						n = t;
					}
				}
				continue;
			} 
			else {
				trees[n->degree] = n;
			}
			n = n->next;
		}
		node* min = n;
		do {
			if(n->data < min->data)
				min = n;
			n = n->next;
		} while(n != n);
		return min;
	}
};


int main() {
	FHeap fibo;
	fibo.push(10);
	fibo.push(20);
	fibo.push(1);
	fibo.push(30);
	std::cout << fibo.top() << std::endl;
	fibo.pop();
	std::cout << fibo.top() << std::endl;
	fibo.push(2);
	std::cout << fibo.top() << std::endl;
}