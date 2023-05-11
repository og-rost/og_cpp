/*

Simplified Definition:

lvalue - An object that occupies some identifiable location in memory
rvalue - Any object that is not a lvalue

*/



// Lvalue Examples:
int i;        // i is a lvalue
int* p = &i;  // i's address is identifiable
i = 2;        // Memory content is modified

class dog;
dog d1;   // lvalue of user defined type (class)
          // Most variables in C++ code are lvalues



// Rvalue Examples:
int x = 2;        // 2 is an rvalue
int x = i + 2;      // (i + 2) is an rvalue
int* p = &(i + 2);  // Error
i + 2 = 4;     // Error
2 = i;         // Error

dog d1;
d1 = dog();  // dog() is rvalue of user defined type (class)

int sum(int x, int y) { return x + y; }
int i = sum(3, 4);  // sum(3, 4) is rvalue





// Reference (or lvalue reference):
int i;
int& r = i;

int& r = 5;      // Error

// Exception: Constant lvalue reference can be assign a rvalue;
const int& r = 5;



int square(int& x) { return x * x; }
square(i);   //  OK
square(40);  //  Error


//Workaround:
int square(const int& x) { return x * x; }  // square(40) and square(i) work



// lvalue can be used to create an rvalue

int i = 1;
int x = i + 2; 

int x = i;



// rvalue can be used to create an lvalue

int v[3];
*(v + 2) = 4;



// Misconception 1: function or operator always yields rvalues.

int x = i + 3;  
int y = sum(3, 4);

int myglobal ;
int& foo() {
   return myglobal;
}
foo() = 50;

// A more common example:
array[3] = 50;  // Operator [] almost always generates lvalue



// Misconception 2: lvalues are modifiable.
// C language: lvalue means "value suitable for left-hand-side of assignment"

const int c = 1;  // c is a lvalue
c = 2;   // Error, c is not modifiable.



// Misconception 3: rvalues are not modifiable.
i + 3 = 6;    // Error
sum(3, 4) = 7; // Error

// It is not true for user defined type (class)
class dog;
dog().bark();  // bark() may change the state of the dog object.


/*

Summary:

1. Every C++ expression yield either an rvalue or a lvalue.
2. If the expression has an identifiable memory address, it's lvalue; otherwise, rvalue.

*/




/*

Rvalue Reference Explained (C++ 11)
Prerequisite: Understanding rvalue and lvalue 

*/

// What is rvalue reference?

int a = 5;
int& b = a;   // b is a lvalue reference, originally called reference in C++ 03

int&& c;       // c is an rvalue reference


void printInt(int& i) { std::cout << "lvalue reference: " << i << std::endl; }
void printInt(int&& i) { std::cout << "rvalue reference: " << i << std::endl; } 

void f() {
   int i = 1;
   printInt(i);   // Call the first printInt
   printInt(6);   // Call the second printInt


   printInt(std::move(i));   // Call the second printInt
}

/* 

Function Signature: 

int and int& are indistinguishable.
int and int&& are indistinguishable.
int& and int&& are distinguishable.

*/




/* 

Note 1: the most useful place for rvalue reference is overloading copy 
constructor and assignment operator, to achieve move semantics.

*/

X& X::operator=(X const& rhs); 
X& X::operator=(X&& rhs);


/*

Note 2: Move semantics is implemented for all STL containers, which means:
   a. Move to C++ 11, You code will be faster without changing a thing.
   b. You should use passing by value more often.

*/

std::vector<int> foo() { return myvector; }

void goo(vector<int>& arg);   // Pass by reference if you use arg to carry data back from goo()




/*

Move constructor:

Purpose: avoid costly and unnecessary deep copying.
1. Move constructor is particularly powerful where passing by reference and passing by value are both needed.
2. Move constructor give you finer control of which part of your object to be moved.

*/



// Usage 2: Perfect Forwarding


// TODO



/* 

Reference Collapsing Rules (C++ 11):
1. T& &   ==>  T&
2. T& &&  ==>  T&
3. T&& &  ==>  T&
4. T&& && ==>  T&&

*/


// std::move() vs std::forward()
std::move<T>(arg);    // Turn arg into an rvalue type
std::forward<T>(arg); // Turn arg to type of T&&
