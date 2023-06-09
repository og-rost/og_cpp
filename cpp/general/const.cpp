const int* p1 = &i;        // data is const, pointer is not

int* const p2 = &i;        // pointer is const, data is not

const int* const p3 = &i;  // data and pointer are both const

// If const is on the left  of *, data is const
// If const is on the right of *, pointer is const


/*
  Why use const
		a.) Guard against inadvertent write to the variable.
		b.) Self documenting
		c.) Enable compiler to do more optimiztion, making code tighter.
		d.) const usually means the variable is put in ROM.
*/

// const used with functions
class Dog {
   int age;
   string name;
public:
   Dog() { age = 3; name = "dummy"; }

   // const parameters
   void setAge(const int& a) { age = a; }
   void setAge(int& a) { age = a; }

   // Const return value
   const string& getName() { return name; }

   // const function
   void printDogName() const { cout << name << "const" << endl; }
   void printDogName() { cout << getName() << " non-const" << endl; }
};

// Function overloading: which const can overload function?

// Q. When const is useless?
void setAge(const int a) {}
const int getAge() {}

// A. In both cases, the int is a temparary. It doesn't make sense for them to be const


// Casting
const Dog d2(8);
d2.f();  // const f()
const_cast<Dog&>(&d2)->f() // non-const f()


Dog d(9);
d.f(); // invoke non-const f()
static_cast<const Dog&>(&d)->f(); // invoke const f()

class BigArray {
	std::vector<int> v; // huge vector
  	mutable int accessCounter;

	int* v2; // another int array

public:
	int getItem(int index) const {
		++accessCounter;
		return v[index];
	}

	void setV2Item(int index, int x)  {
		*(v2 + index) = x;
	}
};
