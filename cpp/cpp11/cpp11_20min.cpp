#include <vector>
#include <iostream>
#include <string>
#include <initializer_list>
#include <assert.h>
#include <memory>

// 1. Initializer List


//C++ 03 initializer list:

void old_init() {
    int arr[4] = {3, 2, 4, 5};

    std::vector<int> v;
    v.push_back(3);
    v.push_back(2);
    v.push_back(4);
    v.push_back(5);
}

// C++ 11 extended the support 
std::vector<int> v1 = {3, 4, 1, 9};   // Calling initializer_list constructor

// All the relevant STL containers have been updated to accept initializer_list.

// Define your own initializer_list constructor:
class myvector {
    std::vector<int> m_vec;
public:
    myvector(const std::initializer_list<int>& v) {
        for (std::initializer_list<int>::iterator itr = v.begin(); itr != v.end(); ++itr)
            m_vec.push_back(*itr);
    }
};

myvector v2 = {0, 2, 3, 4};
myvector v3{0, 2, 3, 4};   // effectively the same


// Automatic normal Initialization
class Rectangle {
public:
    Rectangle(int height, int width, int length){ }
};

void draw_rect(Rectangle r) {}

void rect() {
    draw_rect({5, 6, 9});  // Rectangle{5,6,9} is automatically called
}

// Note: use it with caution.
// 1. Not very readable, even with the help of IDE. Funcion name rarely indicates
//    the type of parameter the function takes.
// 2. Function could be overloaded with differenct parameter types like void draw_rect(Triangle t);


// 2. Uniform Initialization


// C++ 03
class Dog1 {     // Aggregate class or struct
public:
    int age;
    std::string name;
};

Dog1 d1 = {5, "Henry"};   // Aggregate Initialization

// C++ 11 extended the scope of curly brace initialization
class Dog2 {
public:
    Dog2(int age, std::string name) {}
};

Dog2 d2 = {5, "Henry"}; 


/* Uniform Initialization Search Order:
 * 1. Initializer_list constructor
 * 2. Regular constructor that takes the appropriate parameters.
 * 3. Aggregate initializer.
 */

// Dog2 d3{3}; //works under C++03

class Dog3 {
public:
    int age;                                // 3rd choice
    Dog3(int a) {                            // 2nd choice
        age = a;
    }

    Dog3(const std::initializer_list<int>& vec) { // 1st choice
        age = *(vec.begin());      
    }
};

// 3. auto type

void auto_type() {
    std::vector<int> vec = {2, 3, 4, 5};
    std::vector<int> m_vec;
    // C++ 03
    for (std::vector<int>::iterator it = vec.begin(); it != vec.end(); ++it)
        m_vec.push_back(*it);
}

void auto_type_2() {
    std::vector<int> vec = {2, 3, 4, 5};
    std::vector<int> m_vec;
    // C++ 11: use auto type
    for (auto it = vec.begin(); it != vec.end(); ++it)
        m_vec.push_back(*it);

    auto a = 6;    // a is integer
    auto b = 9.6;  // b is double
    auto c = a;    // c is integer
    auto const x = a;   // int const x = a
    auto& y = a;        // int& y = a
}

// It's static type, no run-time cost, fat-free.
// It also makes code easier to maintain.

// 1. Don't use auto when type conversion is needed
// 2. IDE becomes more important


// 4. foreach

// C++ 03:

std::vector<int> vvv = {2, 3, 4, 5};

void for_each_old() {
    for (std::vector<int>::iterator itr = vvv.begin(); itr != vvv.end(); ++itr)
        std::cout << (*itr);
}

void for_each_new() {

    // C++ 11:
    for (auto i : vvv) { // works on any class that has begin() and end()
        std::cout << i ;    // readonly access
    }

    for (auto& i : vvv) {
        ++i;                 // changes the values in v
    }                       // and also avoids copy construction

    auto x = std::begin(vvv);  // Same as: int x = v.begin();

    int arr[4] = {3, 2, 4, 5};
    auto y = std::begin(arr); // y == 3
    auto z = std::end(arr);   // z == 5
}
// How this worked? Because begin() and end() are defined for array.
// Adapt your code to third party library by defining begin() and end()
// for their containers.


// 5. nullptr

void foo(int i) { std::cout << "foo_int" << std::endl; }
void foo(char* pc) { std::cout << "foo_char*" << std::endl; }

void null_test() {
    // foo(NULL);    // Ambiguity compiler error

    // C++ 11
    foo(nullptr); // call foo(char*)
}

// 6. enum class

// C++ 03
enum apple {green_a, red_a};
enum orange {big_o, small_o};
apple a = green_a;
orange o = big_o;

void enum_old() {
    if (a == o) { // warning 
        std::cout << "green apple and big orange are the same" << std::endl;
    }
    else {
        std::cout << "green apple and big orange are not the same" << std::endl;
    }
}

void enum_new() {

    // C++ 11
    enum class apple {green, red};
    enum class orange {big, small};
    apple a = apple::green;
    orange o = orange::big;

    // if (a == o) // compiler error no operator== for these types
}

// Compile fails because we haven't define ==(apple, orange)

// 7. static_assert

void assert_t() { 
    // run-time assert
    void* myPointer = NULL;
    assert( myPointer != NULL );

    // Compile time assert (C++ 11)
    static_assert( sizeof(int) == 4, "int is not 4 bytes" );
}


// 8. Delegating Constructor 

void doOtherThings(int a = 0) {}

class Dog4 {
public:
    Dog4() {}
    Dog4(int a) { Dog4(); doOtherThings(a); }
};


// C++ 03:
class Dog5 {
    int a;
    void init() {
        this->a = 10;
    };
    public:
    Dog5() { init(); }
    Dog5(int a) { init(); doOtherThings(); }
};

/* Cons:
 * 1. Cumbersome code.
 * 2. init() could be invoked by other functions.
 */

// C++ 11:
class Dog6 {
    int age = 9;
    public:
    Dog6() {}
    Dog6(int a) : Dog6() { doOtherThings(); }
};
// Limitation: Dog() has to be called first.


// 9. override (for virtual function)

// To avoid inadvertently creating new function in derived classes.

// C++ 03
class Dog7 {
public:
    virtual void A(int);
    virtual void B() const;
};

class Yellowdog1 : public Dog7 {
public:
    virtual void A(float);  // Created a new function
    virtual void B(); // Created a new function 
};


// C++ 11
class Dog8 {
public:
    virtual void A(int);
    virtual void B() const;
    void C();
};

class Yellowdog2 : public Dog8 {
public:
    //virtual void A(float) override;  // Error: no function to override
    //virtual void B() override;       // Error: no function to override
    //void C() override;               // Error: not a virtual function
};


// 10. final (for virtual function and for class)

class Dog9 final {};    // no class can be derived from Dog


class Dog9_1 {
    virtual void bark() final;  // No class can override bark() 
};


// 11. Compiler Generated Default Constructor

class Dog10 {
    Dog10(int age) {}
};

// Dog10 d10;  // Error: compiler will not generate the default constructor


// C++ 11:
class Dog11 {
public:
    Dog11(int age);
    Dog11() = default;    // Force compiler to generate the default constructor
};


// 12. delete

class Dog12 {
public:
    Dog12(int age) {}
};

// Dog12 a(2);
// Dog12 b(3.0); // 3.0 is converted from double to int
// a = b;     // Compiler generated assignment operator


// C++ 11:
class Dog13 {
public:
    Dog13(int age) {}
    Dog13(double ) = delete;
    Dog13& operator=(const Dog13&) = delete;
};

// 13. constexpr

int arr1[6];    //OK
int A1() { return 3; }
// int arr[A1() + 3];   // Compile Error 

// C++ 11
constexpr int A2() { return 3; }  // Forces the computation to happen 
// at compile time.
int arr2[A2() + 3];   // Create an array of size 6

// Write faster program with constexpr
constexpr int cubed(int x) { return x * x * x; }

int y = cubed(1789);  // computed at compile time

//Function cubed() is:
//1. Super fast. It will not consume run-time cycles
//2. Super small. It will not occupy space in binary.

// 14. New String Literals

// C++ 03:
const char*     c1 = "string";  

// C++ 11:
const char*     c2 = u8"string";      // to define an UTF-8 string. 
const char16_t* c3 = u"string";       // to define an UTF-16 string. 
const char32_t* c4 = U"string";       // to define an UTF-32 string. 
//const char*     c4 = R"string";        // to define raw string. 


// 15. lambda function

void lambda() {

    std::cout << [](int x, int y) {return x + y; }(3, 4) << std::endl;  // Output: 7
    auto f = [](int x, int y) { return x + y; };
    std::cout << f(3, 4) << std::endl;   // Output: 7
}

template<typename func>
void filter(func f, std::vector<int> arr) {
    for (auto i: arr) {
        if (f(i))
            std::cout << i << " ";
    }
}

void test() {
    std::vector<int> v = {1, 2, 3, 4, 5, 6 };

    filter([](int x) {return (x > 3);},  v);    // Output: 4 5 6

    filter([](int x) {return (x > 2 && x < 5);},  v); // Output: 3 4


    int y = 4;  
    filter([&](int x) {return (x > y);},  v);    // Output: 5 6
    //Note: [&] tells compiler that we want variable capture
}

// Lambda function works almost like a language extention

// 16. User defined Literals


// C++ went a long way to make user defined types (classes) to behave same as buildin types.
// User defined literals pushes this effort even further

//Old C++:
long double height1 = 3.4;

// C++ 11:
long double operator"" _cm(long double x) { return x * 10; }
long double operator"" _m(long double x) { return x * 1000; }
long double operator"" _mm(long double x) { return x; }

// Remember in high school physics class?
long double height2 = 3.4_cm;
long double ratio = 3.4_cm / 2.1_mm; 

//Why we don't do that anymore?
// 1. No language support
// 2. Run time cost associated with the unit translation

void literal() {
    long double height = 3.4_cm;
    std::cout << height  << std::endl;              // 34
    std::cout << (height + 13.0_m)  << std::endl;   // 13034
    std::cout << (130.0_mm / 13.0_m)  << std::endl; // 0.01
}

//Note: add constexpr to make the translation happen in compile time.


// Restriction: it can only work with following paramters:
// char const*
// unsigned long long
// long double
// char const*, std::size_t
// wchar_t const*, std::size_t
// char16_t const*, std::size_t
// char32_t const*, std::size_t
// Note: return value can be of any types.


// Example:
int operator"" _hex(char const* str, size_t l) { 
    int ret = 0;
    // Convert hexdecimal formated str to integer ret
    return ret;
}

int operator"" _oct(char const* str, size_t l) { 
    int ret = 0;
    // Convert octal formated str to integer ret
    return ret;
}

void lit() {
    std::cout << "FF"_hex << std::endl;  // 255
    std::cout << "40"_oct << std::endl;  // 32
}


// 17. decltype

// It is equivalent of GNU typeof

const int& foo();      // Declare a function foo()
int aaaa = 10;
decltype(foo()) x1 = aaaa;  //  type is const int&

struct S { 
    double x;
    S(double d) : x(d) {}
};
decltype(S::x) x2;  //  x2 is double

auto s = std::make_shared<S>(12.789);
decltype(s->x) x3;  //  x3 is double

int i;
decltype(i) x4;  //  x4 is int  

float f;              
decltype(i + f) x5;   // x5 is float

// decltype turns out to be very useful for template generic programming
template<typename X, typename Y>
void foo(X x, Y y) {
    decltype(x + y) z;
}

// How about return type needs to use decltype?
//template<typename X, typename Y>
//decltype(x + y) goo(X x, Y y) {      // Error: x & y are undefined 
//    return  x + y;
//}

// Combining auto and decltype to implement templates with trailing return type
template<typename X, typename Y>
auto goo(X x, Y y)->decltype(x + y) {
    return  x + y;
}

int main() {
    return 0;
}
