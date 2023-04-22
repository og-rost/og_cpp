#include <iostream>
#include <algorithm>
 
struct node {
    int key;
    node* left; 
    node* right;
    int height;
    node(int k) : key(k), height(0), left(nullptr), right(nullptr) {}
};
 
struct AVL {
	void inorder(node*);
	int height(node*);
	node* rightRotate(node*);
	node* leftRotate(node*);
	int getBalance(node*);
	node* insert(node*, int);
	node* root;
	AVL() : root(nullptr) {}
};

void AVL::inorder(node* root) {
    if (root) {
        inorder(root->left);
 		std::cout << root->key <<"  ";
  	    inorder(root->right);
    }
}
 
int AVL::height(node* N) {
    if (!N)
        return 0;
    return N->height;
}
 
node* AVL::rightRotate(node* y) {
    node*  x = y->left;
    node* T2 = x->right;
 
    x->right = y;
    y->left  = T2;
 
    y->height = std::max(height(y->left), height(y->right)) + 1;
    x->height = std::max(height(x->left), height(x->right)) + 1;
 
    return x;
}
 
node* AVL::leftRotate(node* x) {
    node*  y = x->right;
    node* T2 = y->left;
 
    y->left  = x;
    x->right = T2;
 
    x->height = std::max(height(x->left), height(x->right)) + 1;
    y->height = std::max(height(y->left), height(y->right)) + 1;
 
    return y;
}
 
int AVL::getBalance(node* N) {
    if (!N)
        return 0;
    return height(N->left) - height(N->right);
}

node* AVL::insert(node* root, int key) {
    if (!root)
        return (new node(key));
 
    if (key == root->key) {
        return root;
    }
 
    if (key < root->key)
        root->left  = insert(root->left, key);
    else
        root->right = insert(root->right, key);
 
    root->height = std::max(height(root->left), height(root->right)) + 1;
 

    int balance = getBalance(root);
 
    if (balance > 1 && key < root->left->key)
        return rightRotate(root);
 
    if (balance < -1 && key > root->right->key)
        return leftRotate(root);
 
    if (balance > 1 && key > root->left->key) {
        root->left =  leftRotate(root->left);
        return rightRotate(root);
    }
 
    if (balance < -1 && key < root->right->key) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

int main() {
	AVL avl;
	avl.root = avl.insert(avl.root, 60);
	avl.root = avl.insert(avl.root, 70);
	avl.root = avl.insert(avl.root, 30);
	avl.root = avl.insert(avl.root, 10);
	avl.root = avl.insert(avl.root, 50);
	avl.root = avl.insert(avl.root, 80);
	avl.inorder(avl.root);
}