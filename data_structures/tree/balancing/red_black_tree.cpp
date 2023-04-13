#include <iostream>
#include <stack>
#include <queue>
#include <stdexcept>

template <typename T>
class RBTree;

const bool RED   = 0;
const bool BLACK = 1;

template <typename T>
class node {
public:
	node();  		 
	node(const T&);
	T key;
	node<T>* parent;
	node<T>* left;
	node<T>* right;
	bool color;
};

template <typename T>
node<T>::node() : key(T()), color(BLACK), parent(RBTree<T>::NIL), 
			left(RBTree<T>::NIL), right(RBTree<T>::NIL)  {}

template <typename T>
node<T>::node(const T& k) : key(k), color(RED), parent(RBTree<T>::NIL), 
    		left(RBTree<T>::NIL), right(RBTree<T>::NIL)  {}								   		 

template <typename T>
class RBTree {
public:
	RBTree();	
	T min() const;
	T max() const;
	T next(const T&) const;
	T prev(const T&) const;

	void insert(const T&);
	void erase(const T&);
	void inorder() const;
	void BFS() const;	
	bool find(const T&) const;	
	int height(node<T>*) const;

	node<T>* getRoot() const;
	~RBTree();
	static node<T>* NIL;
private:
	node<T>* root;	
	
	void rotateLeft(node<T>*);
	void rotateRight(node<T>*);
	node<T>* max(node<T>*) const;
	node<T>* min(node<T>*) const;
	node<T>* next(node<T>*) const;
	node<T>* prev(node<T>*) const;
	node<T>* findNode(const T&) const;
	void clear(node<T>*);

	void insertCase1(node<T>*);
	void insertCase2(node<T>*);
	void insertCase3(node<T>*);
	void insertCase4(node<T>*);
	void insertCase5(node<T>*);

	void eraseCase1(node<T>*);
	void eraseCase2(node<T>*);
	void eraseCase3(node<T>*);
	void eraseCase4(node<T>*);
	void eraseCase5(node<T>*);
	void eraseCase6(node<T>*);

	node<T>* grandpa(node<T>*);
	node<T>* uncle(node<T>*);
	node<T>* sibling(node<T>*);
};

template <typename T>
node<T>* RBTree<T>::NIL = new node<T>;

template <typename T>
RBTree<T>::RBTree() : root(NIL) {}

template <typename T>
RBTree<T>::~RBTree() {
	clear(root);
}

template <typename T>
node<T>* RBTree<T>::getRoot() const {
	return root;
}

template <typename T>
node<T>* RBTree<T>::grandpa(node<T>* n) {
	if(n != NIL && n->parent != NIL && n->parent->parent != NIL)
		return n->parent->parent;
	else return NIL;
}

template <typename T>
node<T>* RBTree<T>::sibling(node<T>* n) {
	if (n == n->parent->left)
		 return n->parent->right;
	else return n->parent->left;
}

template <typename T>
node<T>* RBTree<T>::uncle(node<T>* n) {
	node<T>* g = grandpa(n);
	if(g) {
		if(n->parent == g->left)
			 return g->right;
		else return g->left;
	}
	else return NIL;
}

template <typename T>
bool RBTree<T>::find(const T& k) const {
	return (NIL != findNode(k));
}

template <typename T>
T RBTree<T>::min() const {
	if (root) return min(root)->key;
	else throw std::runtime_error("empty tree");
}

template <typename T>
T RBTree<T>::max() const {
	if (root) return max(root)->key;
	else throw std::runtime_error("empty tree");		
}

template <typename T>
int RBTree<T>::height(node<T>* rt) const {
	if (rt == NIL) return 0;
	
	int left  = height(rt->left);
	int right = height(rt->right);
	if (left > right)
		return left + 1;
	else
		return right + 1;	
}

template <typename T>
T RBTree<T>::next(const T& k) const {
	node<T>* par = findNode(k);

	if (par != NIL) {
		par = next(par);
		if (par != NIL)
			return par->key;
	}			
	throw std::runtime_error("no  next");
}

template <typename T>
T RBTree<T>::prev(const T& k) const {
	node<T>* par = findNode(k);
	if (par != NIL) {
		par = prev(par);
		if (par != NIL)
			return par->key;
	}
	throw std::runtime_error("no  prev");			
}

template <typename T>
void RBTree<T>::insert(const T& k) {
	if (find(k))
		return;
	node<T>* newnode = new node<T>(k);

	if (NIL == root)
		root = newnode;
	else {
		node<T>* par = root;
		node<T>* tmp = root;
		while (par != NIL) {
			tmp = par;
			if (par->key > newnode->key)
				par = par->left;
			else
				par = par->right;
		}
		newnode->parent = tmp;
		if (tmp->key > newnode->key)
			tmp->left = newnode;
		else
			tmp->right = newnode;
	}
	insertCase1(newnode);
}

template <typename T>
void RBTree<T>::insertCase1(node<T>* n) {
	if(n->parent ==  NIL)
		n->color = BLACK;
	else insertCase2(n);
}

template <typename T>
void RBTree<T>::insertCase2(node<T>* n) {
	if(n->parent->color == BLACK)
		return;
	insertCase3(n);
}

template <typename T>
void RBTree<T>::insertCase3(node<T>* n) {
	node<T>* u = uncle(n);
	if(u && u->color != BLACK) {
		n->parent->color = BLACK;
		u->color = BLACK;
		node<T>* g = grandpa(n);
		g->color = RED;
		insertCase1(g);		
	}
	else insertCase4(n);
}

template <typename T>
void RBTree<T>::insertCase4(node<T>* n) {
	node<T>* g = grandpa(n);
	if(n == n->parent->right && n->parent == g->left) {
		rotateLeft(n->parent);
		n = n->left;
	}
	else if (n == n->parent->left && n->parent == g->right) {
		rotateRight(n->parent);
		n = n->right;
	}
	insertCase5(n);
}

template <typename T>
void RBTree<T>::insertCase5(node<T>* n) {
	node<T>* g = grandpa(n);
	n->parent->color = BLACK;
	g->color = RED;
	if (n == n->parent->left)
		rotateRight(g);
	else rotateLeft(g);
}

template <typename T>
void RBTree<T>::erase(const T& k) {
	node<T>* par = findNode(k);
	if (NIL == par)
		return;
	node<T>* tmp; 
	node<T>* temp;
	if (par->left == NIL || par->right == NIL)
		tmp = par;
	else
		tmp = next(par);

	if (tmp->left != NIL)
		temp = tmp->left;
	else
		temp = tmp->right;

	temp->parent = tmp->parent;
	if (tmp->parent == NIL)
		root = temp;
	else if (tmp == tmp->parent->left)
		tmp->parent->left = temp;
	else
		tmp->parent->right = temp;
	if (tmp != par)
		par->key = tmp->key;

	if (tmp->color == BLACK)
		eraseCase1(temp);

	delete tmp;	
}

template <typename T>
void RBTree<T>::eraseCase1(node<T>* n) {
	if (n->parent == NIL) 
		return;
	eraseCase2(n);
}

template <typename T>
void RBTree<T>::eraseCase2(node<T>* n) {
	node<T>* s = sibling(n);
	if (s->color != BLACK) {
		n->parent->color = RED;
		s->color = BLACK;
		if (n == n->parent->left)
			 rotateLeft(n->parent);
		else rotateRight(n->parent);
	}
	eraseCase3(n);
}

template <typename T>
void RBTree<T>::eraseCase3(node<T>* n) {
	node<T>* s = sibling(n);
	if (n->parent->color == BLACK 
			&& s->color == BLACK 
			&& s->left->color == BLACK
			&& s->right->color == BLACK) {

		s->color = RED;
		eraseCase1(n->parent);
	}
	else eraseCase4(n);
}

template <typename T>
void RBTree<T>::eraseCase4(node<T>* n) {
	node<T>* s = sibling(n);
	if (n->parent->color == RED
			&& s->color == BLACK
			&& s->left->color  == BLACK
			&& s->right->color == BLACK) {
		s->color = RED;
		n->parent->color = BLACK;
	}
	else eraseCase5(n);
}

template <typename T>
void RBTree<T>::eraseCase5(node<T>* n) {
	node<T>* s = sibling(n);
	if (n == n->parent->left
			&& s->color == BLACK
			&& s->left->color == RED
			&& s->right->color == BLACK) {
		s->color = RED;
		s->left->color = BLACK;
		rotateRight(s);
	}
	else if (n == n->parent->right
			&& s->color == BLACK
			&& s->right->color == RED
			&& s->left->color == BLACK) {
		s->color = RED;
		s->right->color = BLACK;
		rotateLeft(s);
	}
	eraseCase6(n);
}

template <typename T>
void RBTree<T>::eraseCase6(node<T>* n) {
	node<T>* s = sibling(n);
	s->color = n->parent->color;
	n->parent->color = BLACK;
	if (n == n->parent->left) {
		s->right->color = BLACK;
		rotateLeft(n->parent);
	}
	else {
		s->left->color = BLACK;
		rotateRight(n->parent);
	}
}

template <typename T>
void RBTree<T>::rotateLeft(node<T>* par) {
	node<T>* r = par->right;
	par->right = r->left;
	if (r->left != NIL)
		r->left->parent = par;
	r->parent = par->parent;
	if (par->parent == NIL)
		root = r;
	else if (par == par->parent->left)
		par->parent->left = r;
	else
		par->parent->right = r;
	r->left = par;
	par->parent = r;
}

template <typename T>
void RBTree<T>::rotateRight(node<T>* par) {
	node<T>* l = par->left;
	par->left = l->right;
	if (l->right != NIL)
		l->right->parent = par;
	l->parent = par->parent;
	if (par->parent == NIL)
		root = l;
	else if (par == par->parent->left)
		par->parent->left = l;
	else
		par->parent->right = l;
	l->right = par;
	par->parent = l;
}

template <typename T>
node<T>* RBTree<T>::max(node<T>* root) const {
	node<T>* par = root;
	while (par->right != NIL)
		par = par->right;
	return par;
}

template <typename T>
node<T>* RBTree<T>::min(node<T>* root) const {
	node<T>* par = root;
	while (par->left != NIL)
		par = par->left;
	return par;
}

template <typename T>
node<T>* RBTree<T>::next(node<T>* par) const {
	if (par->right != NIL)
		return min(par->right);
	node<T>* parentemp = par->parent;
	while (parentemp != NIL && parentemp->right == par) {
		par = parentemp;
		parentemp = par->parent;
	}
	return parentemp;
}

template <typename T>
node<T>* RBTree<T>::prev(node<T>* par) const {
	if (par->left != NIL)
		return max(par->left);
	node<T>* parentemp = par->parent;
	while (parentemp != NIL && parentemp->left == par) {
		par = parentemp;
		parentemp = par->parent;
	}
	return parentemp;
}

template <typename T>
node<T>* RBTree<T>::findNode(const T& k) const {
	node<T>* par = root;
	while (par != NIL) {
		if (par->key == k)
			break;
		else if (par->key > k)
			par = par->left;
		else
			par = par->right;
	}
	return par;
}

template <typename T>
void RBTree<T>::clear(node<T>* root) {
	if (root) {
		node<T>* pleft  = root->left;
		node<T>* pright = root->right;
		delete root;
		if (pleft != NIL)
			clear(pleft);
		if (pright != NIL)
			clear(pright);
	}
}

template <typename T>
void RBTree<T>::inorder() const {
	if (NIL != root) {
		std::stack<node<T>*> s;
		node<T>* par;
		par = root;
		while (NIL != par || !s.empty()) {
			if (NIL != par) {
				s.push(par);
				par = par->left;
			}
			else {
				par = s.top();
				s.pop();
				std::cout << par->key << " -> ";
				if (par->color == BLACK)
					std::cout << "Black  ";
				else
					std::cout << "Red    ";
				par = par->right;
			}
		}
	}
}	

template <typename T>
void RBTree<T>::BFS() const {
	if(root == NIL)
		return;
	std::queue<node<T>*> q;
	q.push(root);
	while (!q.empty()) {
		std::cout << q.front()->key << " -> " << (q.front()->color ? "Black  " : "Red    ");
		if (q.front()->left != NIL)
			q.push(q.front()->left);
		if (q.front()->right != NIL)
			q.push(q.front()->right);
		q.pop();
	}	
}

int main() {
	RBTree<int> rostTree;
	
	rostTree.insert(10);
	rostTree.insert(85);
	rostTree.insert(15);
	rostTree.insert(70);
	rostTree.insert(20);
	rostTree.insert(60);
	rostTree.insert(30);
	rostTree.insert(50);
	rostTree.insert(65);
	rostTree.insert(80);
	rostTree.insert(90);
	rostTree.insert(40);
	rostTree.insert(25);
	rostTree.insert(55);

	std::cout << std::endl << "Inorder :" << std::endl;	
	rostTree.inorder();
	std::cout << std::endl << std::endl;

	try {
		int val = rostTree.min();
		std::cout << "min =  " << val << std::endl;
	}
	catch (std::runtime_error& err) {
		std::cout << err.what() << std::endl;
	}
	
	try {
		int val = rostTree.max();
		std::cout << "max =  " << val << std::endl;
	}
	catch (std::runtime_error& err) {
		std::cout << err.what() << std::endl;
	}
	
	try {
		int val = rostTree.next(20);
		std::cout << "next of 20 is: " << val << std::endl;
	}
	catch (std::runtime_error& err) {
		std::cout << err.what() << std::endl;
	}

	try {		
		int val = rostTree.prev(20);
		std::cout << "prev of 20 is: " << val << std::endl;
	}
	catch (std::runtime_error& err) {
		std::cout << err.what() << std::endl;
	}

	std::cout << "height is  " << rostTree.height(rostTree.getRoot()) << std::endl;

	rostTree.erase(30);
	std::cout << "30 is deleted" << std::endl;
	std::cout << "root is: " << rostTree.getRoot()->key << std::endl;
	
	rostTree.erase(40);
	std::cout << "40 is deleted" << std::endl;
	std::cout << "root is: " << rostTree.getRoot()->key << std::endl;
	
	rostTree.erase(20);
	std::cout << "20 is deleted" << std::endl;
	std::cout << "root is: " << rostTree.getRoot()->key << std::endl;
	
	std::cout << std::endl << "Inorder :" << std::endl;
	rostTree.inorder();
	std::cout << std::endl << std::endl;

	std::cout << "BFS  " << std::endl;
	rostTree.BFS();
	std::cout << std::endl << std::endl;
	
	std::cout << "height is  " << rostTree.height(rostTree.getRoot()) << std::endl << std::endl;
}