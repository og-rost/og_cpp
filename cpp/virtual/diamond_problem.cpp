// Virtual inheritance is a C++ technique that ensures that only one copy
// of a base class’s member variables are inherited by second-level derivatives
// (a.k.a. grandchild derived classes). Without virtual inheritance,
// if two classes B and C inherit from class A, and class D inherits from both B and C,
// then D will contain two copies of A’s member variables: one via B, and one via C.

#include <iostream>

class Person {
public:
    Person() {
        std::cout << "Person ctor" << std::endl;
    }
    ~Person() {
        std::cout << "Person dtor" << std::endl;
    }
private:
    int dna = 10;
};

class Mom : virtual public Person {
public:
    Mom() {
        std::cout << "Mom ctor" << std::endl;
    }
    ~Mom() {
        std::cout << "Mom dtor" << std::endl;
    }
};

class Dad : virtual public Person {
public:
    Dad() {
        std::cout << "Dad ctor" << std::endl;
    }
    ~Dad() {
        std::cout << "Dad dtor" << std::endl;
    }
};

class Child : public Mom, public Dad {
public:
    Child() {
        std::cout << "Child ctor" << std::endl;   
    }
    ~Child() {
        std::cout << "Child dtor" << std::endl;
    }
};

int main() {
    Child child;
    return 0;
}
