#include <iostream>

class A {
public:
    virtual void show() {
        std::cout << "Base class " << std::endl;
    }
};

class B : public A {
private:
    virtual void show() {
        std::cout << "Derived class " << std::endl;
    }
};

int main() {
    B b;
    A* p = &b;
    p->show(); 
}