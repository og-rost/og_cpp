#include <iostream>
#include <exception>
#include <typeinfo> 

class Base {
public:
    virtual void f() {
        std::cout << "base " << std::endl;
    }
};

class Derived : public Base {
public:
    void f() {
        std::cout << "derived " << std::endl;
    }
    void not_virtual() {
        std::cout << "not virtual" << std::endl;
    }
};

void dyn_cast() {
    Base* p = new Derived;

    p->f();
    std::cout << "p: " << (p ? "not null" : "null ") << std::endl;
    std::cout << "p is " << typeid(p).name() << std::endl;

    std::cout << std::endl;

    Base* pb = dynamic_cast<Base*>(p);
    std::cout << "pb is " << typeid(pb).name() << std::endl;
    std::cout << "pb: " << (pb ? "not null" : "null ") << std::endl;
    // p->not_virtual(); // error

    std::cout << std::endl;

    Derived* pp = dynamic_cast<Derived*>(p);
    pp->not_virtual(); //ok
    std::cout << "pp is " << typeid(pp).name() << std::endl;
    std::cout << "pp: " << (pp ? "not null" : "null ") << std::endl;

    std::cout << std::endl;

    Base* bp = dynamic_cast<Base*>(pp);
    std::cout << "bp is " << typeid(bp).name() << std::endl;
    std::cout << "bp: " << (bp ? "not null" : "null ") << std::endl;
    bp->f();
    // bp->not_virtual(); // error

    std::cout << std::endl;
}

void stat_cast() {
    Base* p = new Derived;

    p->f();
    std::cout << "p is " << typeid(p).name() << std::endl;

    std::cout << std::endl;

    Base* pb = static_cast<Base*>(p);
    std::cout << "pb is " << typeid(pb).name() << std::endl;
    //p->not_virtual(); error

    std::cout << std::endl;

    Derived* pp = static_cast<Derived*>(p);
    pp->not_virtual(); //ok
    std::cout << "pp is " << typeid(pp).name() << std::endl;

    std::cout << std::endl;

    Base* bp = static_cast<Base*>(pp);
    std::cout << "bp is " << typeid(bp).name() << std::endl;
    bp->f();
    //bp->not_virtual(); //error

    std::cout << std::endl;

    Derived* dd = new Derived;
    Base* bbb = static_cast<Base*>(dd);
    std::cout << "bbb is " << typeid(bbb).name() << std::endl;
    bbb->f();

    std::cout << std::endl;
}

int main() {
    dyn_cast();
    //stat_cast();
}
