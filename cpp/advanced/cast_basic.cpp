/*
 * =========================================  C++ Style Casting ================================
 *                             Generate_Code   Generate_data      risky   data_type
 * Object Casting:
 *    static_cast                 yes              yes             2     any types
 *                                                                       (as long as type
 *                                                                       conversion is defined)
 * Pointer/Reference Casting:
 *    static_cast                 no               no              4     related types
 *    dynamic_cast                yes              no              3     related types(down-cast)
 *    const_cast                  no               no              1     same type
 *    reinterpret_cast            no               no              5     any types
 *
 *
 *
 *
 *
 * =========================================  C Style Casting ================================
 *                             Generate_Code  Generate_data      risky   data_type
 * Object Casting:               yes              yes             5      any types
 *                                                                       (as long as type
 *                                                                       conversion is defined)
 * Pointer/Reference Casting:    no               no              5      any types
 *
 * Note:
 * 1. const_cast, dynamic_cast and reinterpret_cast can only work on pointers/references.
 * 2. static_cast of objects is very different from static_cast of pointers.
 * 3. reinterpret_cast is basically reassigning the type information of the bit pattern.
 *    It should only be used in low-level coding.
 * 4. dynamic_cast does static_cast plus run-time type check.
 * 5. dynamic_cast and static_cast for pointers can only work on related type (e.g.,
 *    base <-> derived).
 *
 */

/*
Converting a pointer-to-derived-type into a pointer-to-base-type can be done without
knowing anything about the exact type of the object that's being pointed to, because 
the derived type is always an instance of the base type. 
That is, the conversion depends only on static information. 
So  dynamic_cast in that direction is always okay.

Using dynamic_cast to convert the other way requires knowing the actual type of the 
object being pointed to, because without that information there's no way to know 
whether the conversion is valid.

*/

#include <iostream>
#include <string>

class dog {
public:
    virtual ~dog() {}
};

class yellowdog : public dog {
    int age;
public:
    void bark() {
        std::cout << "woof. I am " << age << std::endl;
    }
};

void stat_cast() {
    int i = 9;
    float f = static_cast<float>(i);  // convert object from one type to another
    //dog d1 = static_cast<dog>(std::string("Bob"));  // Type conversion needs to be defined.
    dog* pd = static_cast<dog*>(new yellowdog()); // convert pointer/reference from one type
    // to a related type (down/up cast)
}

void dyn_cast() {
    dog* pd = new yellowdog();
    yellowdog* py = dynamic_cast<yellowdog*>(pd);
    // a. It converts pointer/reference from one type to a related type (down cast)
    // b. run-time type check.  If succeed, py==pd; if fail, py==0;
    // c. It requires the 2 types to be polymorphic (have virtual function).
}

void cnst_cast() {
    const char* str = "Hello, world.";         // Only works on same type
    char* modifiable = const_cast<char*>(str); // cast away constness of the object
}

void reint_cast() {
    long p = 51110980;
    dog* dd = reinterpret_cast<dog*>(p);  // re-interpret the bits of the object pointed to
    // The ultimate cast that can cast one pointer to any other type of pointer.
}

void c_casts() {
    short a = 2000;
    int i = (int)a;  // c-like cast notation
    int j = int(a);   // functional notation
    // A mixture of static_cast, const_cast and reinterpret_cast
}

// Generally C++ style of casts are preferred over the C-style, because:
// 1. Easier to identify in the code.
// 2. Less usage error. C++ style provides:
//   a. Narrowly specified purpose of each cast, and
//   b. Run-time type check capability.

void risky() {
    dog* pd = new dog();
    yellowdog* py = dynamic_cast<yellowdog*>(pd);
    // py->bark(); // crashes on mac
    std::cout << "py = " << py << std::endl;
    std::cout << "pd = " << pd << std::endl;

    //	OUTPUT:
    //	woof.
    //	py = NULL
    //	pd = not NULL
}

void minimize() {
    dog* pd = new dog;
    if (yellowdog* py = dynamic_cast<yellowdog*>(pd)) {
        py->bark();
    }
    delete pd;
}

int main() {
    stat_cast();
    dyn_cast();
    cnst_cast();
    reint_cast();
    c_casts();
    risky();
    minimize();
    return 0;
}
