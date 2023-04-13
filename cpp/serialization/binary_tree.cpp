#include <iostream>
#include <limits>
 
struct Node {
    int key;
    Node* left;
    Node* right;
    Node(int k) : key(k), left(nullptr), right(nullptr) {}
};


void serialize(Node* root, FILE* fp) {
    if (root == nullptr) {
        fprintf(fp, "%d ", std::numeric_limits<int>::max());
        return;
    }

    fprintf(fp, "%d ", root->key);
    serialize(root->left, fp);
    serialize(root->right, fp);
}

void deSerialize(Node*& root, FILE* fp) {
    int val;
    if (!fscanf(fp, "%d ", &val) || val == std::numeric_limits<int>::max()) {
        return;
    }

    root = new Node(val);
    deSerialize(root->left, fp);
    deSerialize(root->right, fp);
}


void inorder(Node* root) {
    if (root) {
        inorder(root->left);
        std::cout << root->key << " ";
        inorder(root->right);
    }
}

int main() {
    Node* root = new Node(20);
    root->left = new Node(8);
    root->right = new Node(22);
    root->left->left = new Node(4);
    root->left->right = new Node(12);
    root->left->right->left = new Node(10);
    root->left->right->right = new Node(14);

    FILE* fp = fopen("tree.txt", "w");
    if (fp == nullptr) {
        return -1;
    }
    serialize(root, fp);
    fclose(fp);
 
    // Deserialize the stored tree into root1
    root = nullptr;
    fp = fopen("tree.txt", "r");
    deSerialize(root, fp);

    inorder(root);
    std::cout << std::endl;
 
    return 0;
}