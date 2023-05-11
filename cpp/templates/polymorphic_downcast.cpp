/*

boost::polymorphic_downcast is a utility function that performs a downcast from a base
class pointer or reference to a derived class pointer or reference.

It is used when you have a pointer or reference to a base class object, and you know
for sure that it actually refers to an object of a derived class.

boost::polymorphic_downcast performs a static_cast in release builds (for performance reasons)
and a dynamic_cast followed by an assertion in debug builds (to catch any incorrect casts during development).

*/

#include <iostream>
#include <boost/cast.hpp>

class Base {
public:
    virtual ~Base() {}
};

class Derived : public Base {
public:
    void print() {
        std::cout << "Derived class" << std::endl;
    }
};

int main() {
    Base* base_ptr = new Derived();

    // Downcast the base class pointer to a derived class pointer
    Derived* derived_ptr = boost::polymorphic_downcast<Derived*>(base_ptr);

    // Now, we can call the print function of the Derived class
    derived_ptr->print();

    delete base_ptr;
    return 0;
}

// Implementation
namespace boost_og {

template <typename Derived, typename Base>
inline Derived polymorphic_downcast(Base base_value) {
#if !defined(NDEBUG) && !defined(BOOST_DISABLE_ASSERTS)
    assert(dynamic_cast<Derived>(base_value) == base_value);
#endif
    return static_cast<Derived>(base_value);
}

} // namespace boost

