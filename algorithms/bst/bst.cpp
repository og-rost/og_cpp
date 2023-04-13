/*

A Binary Search Tree is a special form of a binary tree.
The value in each node must be greater than (or equal to) any values in its left subtree
but less than (or equal to) any values in its right subtree.

*/


#include <iostream>
#include <stack>
#include <vector>

class Node {
private:
    int data;
    Node* left;
    Node* right;
public:
    Node(int data) : data(data), left(nullptr), right(nullptr) {}

    friend class BinarySearchTree;
    friend class BSTIterator;
};

class BSTIterator {
public:
    BSTIterator(Node* root) {
        leftmost(root);
    }
    
    int next() {
        Node* top = stk.top();
        stk.pop();

        if (top->right) {
            leftmost(top->right);
        }

        return top->data;
    }
    
    bool hasNext() {
        return stk.size() > 0;
    }
private:
    std::stack<Node*> stk;
private:
    void leftmost(Node* root) {
        while (root) {
            stk.push(root);
            root = root->left;
        }
    }
};

class BinarySearchTree {
public:
    BinarySearchTree() : root(nullptr) {}

    void insert(int data) {
        root = insert(root, data);
    }

    bool search(int data) {
        return search(root, data);
    }

    void remove(int data) {
        root = removeAlternative(root, data);
    }

    void inOrderTraversal() {
        inOrderTraversal(root);
    }

    BSTIterator getIterator() {
        return BSTIterator(root);
    }

    // The lowest common ancestor is defined between two nodes p and q as the lowest node in T
    // that has both p and q as descendants (where we allow a node to be a descendant of itself).
    Node* lowestCommonAncestor(Node* root, Node* p, Node* q) {
        if (!root) {
            return nullptr;
        }

        if (root->data > p->data && root->data > q->data) {
            return lowestCommonAncestor(root->left, p, q);
        }

        if (root->data < p->data && root->data < q->data) {
            return lowestCommonAncestor(root->right, p, q);
        }

        return root;
    }

    /*
    
        Depth:
        The depth of a node is the number of edges from the root of the tree to the node.
        In other words, it represents the node's level in the tree. The depth of the root node is 0.

        Height:
        The height of a node is the number of edges on the longest downward path from the node to a leaf node.
        The height of a leaf node is 0.

        When referring to the entire tree, the height of the tree is the height of the root node,
        which is also the maximum depth of the tree.
        The depth of the tree is the maximum number of edges from the root to any leaf node.

        In summary, the depth refers to the distance of a node from the root,
        while the height refers to the distance of a node from the farthest leaf node.
        When talking about the entire tree, the height of the tree is the maximum depth among all nodes.
    
    */

    int depth(Node* root, int value, int current_depth = 0) {
        if (!root) {
            return -1;
        }

        if (root->data == value) {
            return current_depth;
        }

        int left_depth = depth(root->left, value, current_depth + 1);
        if (left_depth != -1) {
            return left_depth;
        }

        return depth(root->right, value, current_depth + 1);
    }

    int height(Node* node) {
        if (!node) {
            return -1;
        }

        int left_height = height(node->left);
        int right_height = height(node->right);

        return std::max(left_height, right_height) + 1;
    }

    bool isBalanced(Node* root) {
        if (root == nullptr) {
            return true;
        }

        return abs(height(root->left) - height(root->right)) < 2 && isBalanced(root->left) && isBalanced(root->right);
    }

    Node* sortedArrayToBST(std::vector<int> nums, int left, int right) {
        if (left > right) {
            return nullptr;
        }

        int mid = left + (right - left) / 2;
        Node* root = new Node(nums[mid]);

        root->left = sortedArrayToBST(nums, left, mid - 1);
        root->right = sortedArrayToBST(nums, mid + 1, right);

        return root;
    }

    Node* sortedArrayToBST(std::vector<int> nums) {
        return sortedArrayToBST(nums, 0, nums.size() - 1);
    }


private:
    Node* insert(Node* node, int data) {
        if (node == nullptr) {
            return new Node(data);
        }

        if (data < node->data) {
            node->left = insert(node->left, data);
        } else if (data > node->data) {
            node->right = insert(node->right, data);
        }

        return node;
    }

    bool search(Node* node, int data) {
        if (node == nullptr) {
            return false;
        }

        if (data < node->data) {
            return search(node->left, data);
        } else if (data > node->data) {
            return search(node->right, data);
        } else {
            return true;
        }
    }

    int successor(Node* node) {
        node = node->right;
        while (node->left) {
            node = node->left;
        }
        return node->data;
    }


    int predecessor(Node* node) {
        node = node->left;
        while (node->right) {
            node = node->right;
        }
        return node->data;
    }

    Node* findSuccessor(Node* node) {
        node = node->right;
        while (node->left) {
            node = node->left;
        }
        return node;
    }

    Node* remove(Node* node, int key) {
        if (node == nullptr) {
            return node;
        }

        if (key > node->data) {
            node->right = remove(node->right, key);
        } else if (key < node->data) {
            node->left = remove(node->left, key);
        } else {
            if (!node->left && !node->right) {
                delete node;
                node = nullptr;
            } else if (node->right) {
                node->data = successor(node);
                node->right = remove(node->right, node->data);
            } else {
                node->data = predecessor(node);
                node->left = remove(node->left, node->data);
            }
        }
        return node;
    }

    Node* removeAlternative(Node* node, int key) {
        if (node == nullptr) {
            return node;
        }

        if (node->data == key) {
            // replace root with root->right if root->left is null					
            if (!node->left) {
                return node->right;
            }

            // replace root with root->left if root->right is null
            if (!node->right) {
                return node->left;							
            }

            Node* p = findSuccessor(node);
            node->data = p->data;
            node->right = removeAlternative(node->right, p->data);
            return node;
        }

        if (key > node->data) {
            node->right = removeAlternative(node->right, key);
        } else if (key < node->data) {
            node->left = removeAlternative(node->left, key);
        }
        return node;
    }


    void inOrderTraversal(Node* node) {
        if (node != nullptr) {
            inOrderTraversal(node->left);
            std::cout << node->data << " ";
            inOrderTraversal(node->right);
        }
    }
private:
    Node* root;
};

int main() {
    BinarySearchTree bst;
    bst.insert(8);
    bst.insert(3);
    bst.insert(10);
    bst.insert(1);
    bst.insert(6);
    bst.insert(14);
    bst.insert(4);
    bst.insert(7);
    bst.insert(13);

    std::cout << "In-order traversal: ";
    bst.inOrderTraversal();
    std::cout << std::endl;

    int searchValue = 6;
    std::cout << "Searching for " << searchValue << ": " << (bst.search(searchValue) ? "Found" : "Not found") << std::endl;

    auto iter = bst.getIterator();

    while (iter.hasNext()) {
        std::cout << iter.next() << " ";
    }
    std::cout << std::endl;

    bst.remove(1);
    bst.remove(14);
    bst.remove(3);
    bst.remove(8);

    iter = bst.getIterator();

    while (iter.hasNext()) {
        std::cout << iter.next() << " ";
    }
    std::cout << std::endl;

    return 0;
}
