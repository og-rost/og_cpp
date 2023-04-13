/*

The Iterator pattern is a behavioral pattern that provides a way to access the elements
of an aggregate object sequentially without exposing its underlying representation.
It separates the traversal of an aggregate object from the client that uses it,
making it easier to modify the traversal algorithm or the underlying collection of objects.

Iterator is a behavioral design pattern that lets you traverse elements of a collection
without exposing its underlying representation (list, stack, tree, etc.).

Problem
No matter how a collection is structured, it must provide some way of accessing its elements so that other code can use these elements.
There should be a way to go through each element of the collection without accessing the same elements over and over.

Solution
The main idea of the Iterator pattern is to extract the traversal behavior of a collection into a separate object called an iterator.

In addition to implementing the algorithm itself, an iterator object encapsulates all of the traversal details,
such as the current position and how many elements are left till the end. Because of this,
several iterators can go through the same collection at the same time, independently of each other.


*/

#include <iostream>
#include <memory>

// Node class for a singly-linked list
class Node {
public:
    friend class LinkedList;
    Node(int v, std::unique_ptr<Node> n = nullptr) : value(v), next(std::move(n)) {}

    int getValue() const {
        return value;
    }

    Node* getNext() const {
        return next.get();
    }

private:
    int value;
    std::unique_ptr<Node> next;
};

// Iterator interface
class Iterator {
public:
    virtual int next() = 0;
    virtual bool hasNext() const = 0;

    virtual ~Iterator() {}
};

// Iterator implementation for a singly-linked list
class ListIterator : public Iterator {
public:
    ListIterator(Node* head) : current(head) {}

    int next() override {
        int value = current->getValue();
        current = current->getNext();
        return value;
    }

    bool hasNext() const override {
        return current != nullptr;
    }

private:
    Node* current;
};

// Container interface
class Container {
public:
    virtual Iterator* createIterator() const = 0;

    virtual ~Container() {}
};

// Container implementation for a singly-linked list
class LinkedList : public Container {
public:
    LinkedList() : head(nullptr) {}

    Iterator* createIterator() const override {
        return new ListIterator(head.get());
    }

    void add(int value) {
        std::unique_ptr<Node> newNode(new Node(value));
        if (!head) {
            head = std::move(newNode);
            tail = head.get();
        } else {
            tail->next = std::move(newNode);
            tail = tail->getNext();
        }
    }

private:
    std::unique_ptr<Node> head;
    Node* tail;
};

int main() {
    LinkedList list;
    list.add(1);
    list.add(2);
    list.add(3);

    Iterator* it = list.createIterator();
    while (it->hasNext()) {
        std::cout << it->next() << std::endl;
    }

    delete it;
    return 0;
}
