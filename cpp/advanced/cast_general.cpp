#include <iostream>
#include <exception>
#include <typeinfo> 

/************************************************************/

struct type_A {
    int x;
    double y;
    char c;
};

struct type_B {
    int x;
    double y;
};

// Warning avoid doing this!!!!!!
// Actually standard doesn't give any guaranties that this will work!!
// AVOID THIS!!!!!!!!

void rnpt_cast() {
    type_A a = { 2, 5.7 };

    type_B* b = reinterpret_cast<type_B*>(&a);
    std::cout << b->y << std::endl;
}

/************************************************************/

class A {
public:
    virtual ~A() {}
    void print_something() { 
        std::cout << "Something!" << std::endl; 
    }
};

class B : public A {};

class C : public A {};

void cnst_cast() {
    const A a;
    // a.print_something(); <--compilation error!!!
    // can't execute non-const function

    //for educational purposes only
    //avoid doing this!!!!!!!!!!
    A& aa = const_cast<A&> (a);
    aa.print_something();
}

void all() {
    int x = 7;
    double d = static_cast<double>(x);
    std::cout << d << std::endl;
    int y = static_cast<int>(d);
    std::cout << y << std::endl;

    B b;
    C c;

    A* a_ptr = &b;

    B* new_b_ptr = static_cast<B*> (a_ptr); //no check
    std::cout << new_b_ptr << std::endl;
    C* new_c_ptr = static_cast<C*> (a_ptr); //converts to wrong type. NO CHECK!!!
    std::cout << new_c_ptr << std::endl;
    B* new_b_ptr_dyn = dynamic_cast<B*> (a_ptr); //checks!
    std::cout << new_b_ptr_dyn << std::endl;

    C* new_c_ptr_dyn = dynamic_cast<C*> (a_ptr); //checks. Returns nullptr
    std::cout << new_c_ptr_dyn << std::endl;

    try {
        B& new_b_ref = dynamic_cast<B&> (*a_ptr);
    }
    catch (std::bad_cast ex){
        std::cerr << "error during conversation to B " << ex.what() << std::endl;
    }
    try {
        C& new_c_ref = dynamic_cast<C&> (*a_ptr);
    }
    catch (std::bad_cast ex){
        std::cerr << "error during conversation to C " << ex.what() << std::endl;
    }
}

int main() {
    rnpt_cast();
    cnst_cast();
    all();
}
