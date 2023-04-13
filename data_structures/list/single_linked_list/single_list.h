struct node {
	node* next;
	int data;
	node(int d) : data(d), next(nullptr) {}
};

struct list {
	node* head;
	list() : head(nullptr) {}
	node* copy();

	void print();
	void print_rec(node*);
	void print_rev(node*);

	void clear();
	void clear_rec(node*&);

	void push_front(int); 
	void pop_front();

	void reverse();
	void reverse_rec(node*&);
	node* reverseInGroupsOfGivenSize(node*, int);
	node* reverseAlternateKNodes(node*, int);

	void insert(node*, int);
	void remove(node*);
	void remove(int);
	void remove_all_x(int);
	

	void push_back(int); //linear
	void pop_back(); //linear
	

	node* getNth(node*, int);
	node* getMid(node*);
	node* getMid_(node*);
	node* getNthFromEnd(node*, int);
	size_t getCount(node*);
	
	void detect_n_remove_loop(node*);
	bool isPalindrom(node*);
	bool isPalindrom(node*&, node*);
	void sortedInsert(node*&, int);
	void swapKthWithN_Kth(node*, int);

	node* getIntersectionPoint(node*, node*);
	node* intersecHelper(node*, node*, int);

	void pairwiseswap(node*);
	void pairwiseswapRec(node*);

	void moveLastToFront(node*&);
	void deleteAlternateNodes(node*);

	static node* merge(node*, node*);
	void mergeSort(node*&);
	void frontBackSplit(node*, node*&, node*&);

	static bool areIdentical(node*, node*);
	static bool areIdenticalRec(node*, node*);

	node* getTail(node*);
	node* partition(node*, node*, node*&, node*&);
	node* quickSortRec(node*, node*);
	void quickSort(node*&);

	void deleteNodesWithGreaterValueOnRightSide(node*&);
	void delHelper(node*);

	void segregateEvenAndOddNodes(node*&);
	static node* addTwoNumbers(node*, node*);
	
};