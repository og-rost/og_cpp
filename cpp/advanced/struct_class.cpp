#include <iostream>
#include <string>
#include <vector>

// Small passive objects that carry public data and have no or few basic member functions. --  data container
struct Person_t {  
	std::string name;
	unsigned age;
};

// Bigger active objects that carry private data, interfaced through public member functions
class Person1 {  
	std::string name_;
	unsigned age_;
public:
	unsigned age() { return age_; }  // getter / accessor
	void set_age(unsigned a) { age_ =  a; }  // setter / mutator
};

void f1() {
	Person_t Pt;
	Pt.age = 69;
	std::cout << Pt.age << std::endl;
	Person1 P;
	P.set_age(4);
	std::cout << P.age() << std::endl;
}


// Summary:
// 1. Use struct for passive objects with public data, use class for active objects with private data.
// 2. Use setter/getter to access class's data
// 3. Avoid making setter/getter if possible


// Person owns the string through its pointer
class Person2 {
public:
	Person2(std::string name) { pName_ = new std::string(name); }
	~Person2() { delete pName_; }

	void printName() { std::cout << *pName_ << std::endl; }
private:
	std::string* pName_;
};

void f2() {

	std::vector<Person2> persons;
	persons.push_back(Person2("George"));

	persons.front().printName();

	std::cout << "Goodbye" << std::endl;
}


// 1. "George" is constructed
// 2. A copy of "George" is saved in the vector (shallow copy)
// 3. "George" is destroyed.

// Solution 1: Define copy constructor and copy assignment operator for deep copying
/*
Person2(const Person2& rhs) {   // deep copying
	pName_ = new string(*(rhs.pName()));
}

Person2& operator=(const Person2& rhs);  // deep copying
string* pName() const { return pName_; }
*/

// Solution 2: delete copy constructor and copy assignment operator
/*
Person2(const Person2& rhs);  // Delare them but not define them
Person2& operator=(const Person2& rhs);  
// for C++ 03, declare them and not define them

// If copying is still needed, use clone()
// Make the copying explicit
Person2* clone() {  
	return (new Person2(*(pName_)));
}
*/

// Prefer solution2:
// 1. Copy constructor and assignment operator are often not needed.
// 2. Make copying explicit, implicit copying is bug prone

// C++ 11 solution:
//    shared_ptr<string> pName_;
//    most of the time uniqu_ptr will also work, but in order to work with STL container, you have to use shared_ptr, 
//    because STL container requires containee copiable


class Dog { 
public:
	virtual Dog* clone() { return (new Dog(*this)); }  // co-variant return type
};

class Yellowdog : public Dog { 
	virtual Yellowdog* clone() { return (new Yellowdog(*this)); }
};

void foo(Dog* d) {      // d is a Yellowdog
	//Dog* c = new Dog(*d); // c is a Dog
	Dog* c = d->clone();    // c is a Yellowdog
}

void f3() {
	Yellowdog d;
	foo(&d);
}

int main() {
	f1();
	f2();
	f3();
}
