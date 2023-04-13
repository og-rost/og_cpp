/*

The Template Method pattern is a behavioral pattern that defines the skeleton of an algorithm
in a base class and allows its subclasses to override certain steps of the algorithm without changing its structure.

Problem
Code duplication.

Solution
The Template Method pattern suggests that you break down an algorithm into a series of steps,
turn these steps into methods, and put a series of calls to these methods inside a single template method.
The steps may either be abstract, or have some default implementation. To use the algorithm, the client is supposed
to provide its own subclass, implement all abstract steps, and override some of the optional ones
if needed (but not the template method itself).

*/


#include <iostream>

class AbstractClass {
public:
    void templateMethod() const {
        baseOperation1();
        requiredOperations1();
        baseOperation2();
        requiredOperation2();
    }
protected:
    void baseOperation1() const {
        std::cout << "AbstractClass says: I am doing the bulk of the work" << std::endl;
    }
    void baseOperation2() const {
        std::cout << "AbstractClass says: But I let subclasses override some operations" << std::endl;
    }

    virtual void requiredOperations1() const = 0;
    virtual void requiredOperation2() const = 0;
};


class ConcreteClass1 : public AbstractClass {
protected:
    void requiredOperations1() const override {
        std::cout << "ConcreteClass1 says: Implemented Operation1" << std::endl;
    }
    void requiredOperation2() const override {
        std::cout << "ConcreteClass1 says: Implemented Operation2" << std::endl;
    }
};

class ConcreteClass2 : public AbstractClass {
protected:
    void requiredOperations1() const override {
        std::cout << "ConcreteClass2 says: Implemented Operation1" << std::endl;
    }
    void requiredOperation2() const override {
        std::cout << "ConcreteClass2 says: Implemented Operation2" << std::endl;
    }
};

void ClientCode(AbstractClass* obj) {
    obj->templateMethod();
}

int main() {
    std::cout << "Same client code can work with different subclasses:" << std::endl;
    ConcreteClass1* concreteClass1 = new ConcreteClass1;
    ClientCode(concreteClass1);
    std::cout << "Same client code can work with different subclasses:" << std::endl;
    ConcreteClass2* concreteClass2 = new ConcreteClass2;
    ClientCode(concreteClass2);
    delete concreteClass1;
    delete concreteClass2;
    return 0;
}