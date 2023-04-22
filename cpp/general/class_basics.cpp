//############################################################################
/*
Compiler silently writes 4 functions if they are not explicitly declared:
1. Copy constructor.
2. Copy Assignment Operator.
3. Destructor.
4. Default constructor (only if there is no constructor declared).
*/

class dog {};

/* equivalent to */

class dog {
public:
    dog(const dog& rhs) {...};   // Member by member initialization
    dog& operator=(const dog& rhs) {...}; // Member by member copying
    dog() {...};  // 1. Call base class's default constructor;
                  // 2. Call data member's default constructor.
    ~dog() {...}; // 1. Call base class's destructor;
                  // 2. Call data member's destructors.
};

/*
Note:
1. They are public and inline.
2. They are generated only if they are needed.
*/


/*  Example:
  1. Copy constructor.   - no
  2. Copy Assignment Operator. - yes
  3. Destructor.  - no
  4. Default constructor - no
*/
class dog {
public:
	string m_name;

	dog(string name = "Bob") {m_name = name; cout << name << " is born." << endl;}
	~dog() { cout<< m_name << " is destroyed.\n" << endl; }
};

void f1() {
	dog dog1("Henry");
	dog dog2;
	dog2 = dog1;
}

/*
OUTPUT:
Henry is born.
Bob is born.
Henry is distroyed.
Henry is distroyed.
*/

/*
Notes:
 Compiler will refuse to generate default copy assignment operator when it is illegal.
 1. Reference member data
 2. Const member data
 Such classes cannot be used in STL containers because a container's elements has to
 be copy constructable and assignable.
*/


/*
 * Disallow the use of compiler generated functions
 *
 *
 *
 * Not all classes need the compiler generated functions.
 *
 * E.g.  a class "OpenFile" represents a file being opened. Its constructor at
 * least needs a file name as parameter. So default constructor is not needed.
 */

class dog {
public:
	dog(const dog& ) = delete; // Prevent copy constructor from being used.
                              // Useful when dog holds unsharable resource.
};

/* For C++ 03:
 *
1. Default constructor.      - easy
2. Copy constructor.         - see following solutions
3. Copy Assignment Operator. - see following solutions


Solution:
 Declare them as private functions, but not define them.
 -- Members and friends get link-time error, others get compile-time error.
*/
class dog {
private:
	dog& operator=(const dog& rhs);
};

/*
Solution 2:
 In its base class, declare them as private function, but not define them.
 -- Compile time error.
*/

class yellowdog : public dog {};

void f2() {
   yellowdog y1("henry");
   yellowdog  y2;
   y2 = y1;
}

// Note: the same techniques can be used to disallow any function from being used.


// Question: Can we disallow destructor from being used?

/* Solution */
class dog {
public:
	void destroy() { delete this; }
private:
     ~dog() { std::cout << m_name.m_str << " is destroyed." << std::endl; }
};

int main () {
	dog* dog1 = new dog();
	dog1->destroy();
}


// Usage: 1. Reference counting smart pointer.
//	      2. Small stack embedded programming.


/*
Declare a destructor virtual in polymorphic base classes
*/

/* Problem */
class yellowdog : public dog {};

dog* dogFactory::createDog() {
	dog* pd = new yellowdog();
	return pd;
}

void f3() {
	dog* pd = dogFactory::createDog();
	delete pd;  // Only dog's destructor is invoked, not yellowdog's.
}

// Solution

class dog {
public:
	virtual ~dog() {}
}

//Note: All classes in STL have no virtual destructor, so be careful inheriting from them.


/*
When we should use virtual destructor:
Any class with virtual functions should have a virtual destructor.

When not to use virtual destructor:
1. Size of the class needs to be small;
2. Size of the class needs to be precise, e.g. passing an object from C++ to C.
*/

// Solution 2:   using shared_prt

class Dog {
public:
	~Dog() { std::cout << "Dog is destroyed" << std::endl; }
};

class Yellowdog : public Dog {
public:
	~Yellowdog() { std::cout << "Yellow dog destroyed." << std::endl; }
};

class DogFactory {
public:
	static shared_ptr<Dog> createYellowDog() {
		return shared_ptr<Yellowdog>(new Yellowdog());
	}
};

void f4() {
	shared_ptr<Dog> pd = DogFactory::createYellowDog();
	// no need to delete pd, destructors will be invoked in correct order
	return 0;
}
// you cannot use unique_ptr for this purpose


// Prevent Exceptions from Leaving Destructors.

class dog {
public:
	std::string m_name;
	dog(std::string name) {m_name = name; std::cout << name << " is born." << std::endl; }
	~dog() { std::cout << m_name << " is distroied." << std::endl; }
	void prepareToDestr() { throw 20; }
	void bark() {}
};

void f5() {
	try {
		dog dog1("Henry");
		dog dog2("Bob");
		dog1.bark();
		dog2.bark();
		dog1.prepareToDestr();
		dog2.prepareToDestr();
	}
	catch (int e) {
		std::cout << e << " is caught" << std::endl;
	}
}

/*
OUTPUT:
Henry is born.
Bob is born.
Bob is distroyed.
Henry is distroyed.
20 is caught
*/


// Solution 1: Destructor swallow the exception.


class Dog {
public:
	~dog() {
		try {
			// Enclose all the exception prone code here
		} catch (MYEXCEPTION e) {
			// Catch exception
		} catch (...) {}
	}
};


// Solution 2: Move the exception-prone code to a different function.


// Which one to use?

// It depends on who is the better person to handle the exception, dog or dog's client.


// Never call virtual functions in constructor or destructor.

class dog {
public:
	string m_name;
	dog(std::string name) {m_name = name;  bark();}
	virtual void bark() { std::cout << "Woof, I am just a dog " << m_name << std::endl;}
};

class yellowdog : public dog {
public:
	yellowdog(std::string name) : dog(string name) {...}
	virtual void bark() { std::cout << "Woof, I am a yellow dog " << m_name << std::endl; }
};

void f6() {
	yellowdog mydog("Bob");
}

/*
OUTPUT:
Woof, I am just a dog Bob.
*/

/*

During the construction, all virtual function works like non-virtual function.

Why?
Base class's constructor run before derived class's constructor. So at the
time of bark(), the yellowlog is not constructed yet.


Why Java behaves differently?

There is a fundamental difference in how Java and C++ defines an object's Life time.
Java: All members are null initialized before constructor runs. Life starts before constructor.
C++: Constructor is supposed to initialize members. Life starts after constructor is finished.

Calling down to parts of an object that haven not yet initialized is inherently dangerous.

*/


// Solution 1:

class dog {
public:
	dog(std::string name, std::string color) {
		m_name = name;
		bark(color);
	}
	void bark(std::string str) {
		std::cout << "Woof, I am " << str << " dog " << m_name << std::endl;
	}
};

class yellowdog : public dog {
public:
	yellowdog(string name) : dog(name, "yellow") {}
};

void f7() {
 	yellowdog mydog("Bob");
}

/*
OUTPUT:
Woof, I am yellow dog Bob
*/
// Solution 2:

class dog {
public:
	dog(std::string name, std::string woof) {
		m_name = name;
		bark(woof);
	}
	dog(std::string name) {
		m_name = name;
		bark(getMyColor());
	}
	void bark(std::string str) { std::cout << "Woof, I am " << str << "	private " << std::endl;
private:
	static std::string getMyColor() {return "just a";}
};

class yellowdog : public dog {
public:
	yellowdog(std::string name) : dog(name, getMyColor()) {}
private:
	static std::string getMyColor() {return "yellow";}  //Why static?
};

void f8() {
	yellowdog mydog("Bob");
}

/*
OUTPUT:
Woof, I am yellow dog Bob
*/

/*
 * Handle self-assignment in operator=
 *
 *
 * Operator overload: exploite people's intuition and reduce their learning curve
 */

void f9() {
    dog dd;
    dd = dd;  // Looks silly

    dogs[i] = dogs[j]; // looks less silly
}

/* Implementing Assignment Operator */
class collar;

class dog {
	collar* pCollar;
	dog& operator=(const dog& rhs) {
		if (this == &rhs) {
			return *this;
		}

		collar* pOrigCollar = pCollar;
		pCollar = new collar(*rhs.pCollar);
		delete pOrigCollar;
		return *this;
	}
}

/*
Copy functions copy all parts of an object.
	- Copy constructor
	- Copy assignment operator


Make sure to do three things in copy constructor and copy assignment operator:
1. Copy all local data members.
   - Inside a class definition, separate data members from function members.

2. Invoke copying function in all base classes.
   - Multiple inheritance.

3. Every time a new data member is added, update the copying functions.
   - Difficult to remember until it becomes a habit.
   - Copy assignment operator calling copy constructor?
      (what happens? Java?)
*/

// Named Parameter Idiom

// Problem
// C++ only supports positional parameters, it doesn't support named parameters as what Python does.

class OpenFile {
public:
	OpenFile(std::string filename,
			bool readonly = true,
			bool appendWhenWriting = false,
			int blockSize = 256,
			bool unbuffered = true,
			bool exclusiveAccess = false);
}

OpenFile pf = OpenFile("foo.txt", true, false, 1024, true, true);
// Inconvenient to use
// Unreadable
// Inflexible

// What's ideal is:
OpenFile pf = OpenFile(.filename("foo.txt"), .blockSize(1024) );


// Solution
class OpenFile {
public:
	OpenFile(std::string const& filename);
	OpenFile& readonly()  { readonly_ = true; return *this; }
	OpenFile& createIfNotExist() { createIfNotExist_ = true; return *this; }
	OpenFile& blockSize(unsigned nbytes) { blockSize_ = nbytes; return *this; }
};

OpenFile f = OpenFile("foo.txt")
           .readonly()
           .createIfNotExist()
           .appendWhenWriting()
           .blockSize(1024)
           .unbuffered()
           .exclusiveAccess();

OpenFile f = OpenFile("foo.txt").blockSize(1024);



// Named Constructor Idiom
// C++ constructors always have the same name as the class


// Point epresents a point on a 2-dimension plane

class Point {
public:
	Point(float x, float y);          // Rectangular coordinates
	Point(float radius, float angle); // Polar coordinates (radius and angle)
};

void f10() {
	Point p = Point(5.7, 1.2);   // Ambiguous: Which coordinate system?
}


// Solution
class Point {
public:
	Point(float x, float y);     // Rectangular coordinates

	// These static methods are the so-called "named constructors"
	static Point rectangular(float x, float y) { return Point(x,y);}  
	static Point rectangular_heap(float x, float y) { return new Point(x,y);}  
	static Point rectangular_heap_p(float x, float y) { return new(buffer) Point(x,y);}  
	static Point polar(float radius, float angle) { 
		return Point(radius*cos(angle), radius*sin(angle)); 
  	}
};

Point p = Point::rectangular(5.7, 1.2);   // No longer ambiguous
Point* p = new Point::rectangular(5.7, 1.2);   // Wrong

/* Benefits:
 1. Less error-prone
 2. No longer depends on parameter list to differentiate constructors.
*/


// How to create a Point on heap

// Solution 1: Create a separate heap version of named constructor.

//* Solution 2:

Point* pp = new Point(Point::rectangular(5.7, 1.2));
Point* pp = new(buffer) Point(Point::rectangular(5.7, 1.2));


// Solution 3: A variation of named constructor

enum Rectangular {rectangular};
enum Polar       {polar};

class Point {
public:
	Point(Rectangular, float x, float y) {
		std::cout << "creating Point with rectangular coordinates" << std::endl;
	}
	Point(Polar, float radius, float angle) {
		std::cout << "creating Point with polar coordinates" << std::endl;
	}
};

Point* pp = new Point(polar, 5.7, 1.2);


// RAII

// Use objects to manage resources: memory, hardware device, network handle, etc.

/*
 * The only code that can be guaranteed to be executed after exception is
 * thrown are the destructor of objects residing on the stack.
 *
 * Resource management therefore needs to be tied to the lifespan of
 * suitable objects in order to gain automatic deallocation and reclamation.
 */

// Don't combine storing objects in shared pointer with other statement.


/* Solution 1:
 * Prohibit copying. To see how to disallow copy constructor and copy
 * assignment operator from being used.
 * Disallow Compiler Generated Functions.
 */

/* Solution 2:
 * Reference-count the underlying resource by using shared_ptr
 */

// User Defined Implicit Type Conversion

// Implicit Standard Type Conversion

char c = 'A';
int i = c;  // Integral promotion
char*  pc = 0;  // int -> Null pointer
void f(int i);
f(c);
dog* pd = new yellowdog();  // pointer type conversion


// Implicit User Defined Type Conversion

// There are 2 methods to define implicit user defined type conversion:
// Method 1: Use constructor that can accept a single parameter - convert other types of object into your class
// Method 2: Use the type conversion function - convert an object of your class into other types

class dog {
public:
	dog(std::string name) { m_name = name; }  // NO explicit
	// If you only want to define a constructor, and no implicit type
	// conversion, always put "explicit" before the constructor to
	// avoid inadvertent type conversion.
	std::string getName() { return m_name; }
private:
	std::string m_name;
};

void f12(){
	std::string dogname = "Bob";
	dog dog1 = dogname;
}

// Implicit type conversion is useful when creating numerical types of class,
// such as a rational class.

class Rational {
public:
	Rational(int numerator = 0, int dennominator = 1) : num(numerator), den(denominator) {}
	int num;  // Demo only, public data members are not recommended
	int den;
	const Rational operator*(const Rational& rhs) {
		return Rational(num*rhs.num, den*rhs.den);
	}
};

void f13() {
	Rational r1 = 23;
	Rational r2 = r1 * 2;
}

//   Rational r3 = 3 * r1;
const Rational operator*(const Rational& lhs, const Rational& rhs) {
	return Rational(lhs.num * rhs.num, lhs.den * rhs.den);
}

// How about this one:
operator int() const { return num / den; }
// one-way conversion is better


// Question:
// Can I use named parameter for non-member functions?


// Solution 2: Use Type

void setBirthDate(int month, int day, int year);

setBirthDate(3, 1, 2012);  // March 1st, or  Jan 3rd ?

struct Day {
	explicit Day(int d):val(d){}  // Important to use explicit
	int val;
}
struct Month {
	explicit Month(int d):val(d){}  // Important to use explicit
	int val;
}
struct Year {
	explicit Year(int d):val(d){}  // Important to use explicit
	int val;
}

void setBirthDate(Month m, Day d, Year y);

setBirthDate(Month(3), Day(1), Year(2010));

setBirthDate(3, 1, 2010);  // Not compilable -- Hard to use incorrectly
