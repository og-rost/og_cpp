#include <vector>

class A {
public:
    /*virtual std::vector<A*> test() {
        return std::vector<A*>();
    }*/
    virtual A* test() {
        return nullptr;
    }
};

class B : public A {
public:
    // compile error: error: invalid covariant return type for 'virtual std::vector<B*> B::test()
    /*virtual std::vector<B*> test() override {
        return std::vector<B*>();
    }*/

    // ok covariant
    virtual B* test() override {
        return nullptr;
    }
};

int main() {
    return 0;
}

/*

The return type of an overriding function shall be either identical to the return type
of the overridden function or covariant with the classes of the functions.
If a function D::f overrides a function B::f, the return types of the functions are covariant
if they satisfy the following criteria:

1) both are pointers to classes, both are lvalue references to classes,
or both are rvalue references to classes
(Multi-level pointers to classes or references to multi-level pointers to classes are not allowed)

2) the class in the return type of B::f is the same class as the class in the return type of D::f,
or is an unambiguous and accessible direct or indirect base class of the class in the return type of D::f

3) both pointers or references have the same cv-qualification and the class type in the return type
of D::f has the same cv-qualification as or less cv-qualification than the class type in the return
type of B::f.

*/