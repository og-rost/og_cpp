
//############################################################################

// Introduction to Template

template<typename T>
T square(T x) {
	return x * x;
}

template<typename T>
class Vector {
	T arr[1000];
	int size;
public:
	Vector() : size(0) {}
	void push(T x) { 
		arr[size] = x; 
		size++; 
	}
	T get(int i) const { 
		return arr[i]; 
	}
	int getSize() const { 
		return size; 
	}
	void print() const { 
		const int* p = arr; 
		for(int i = 0;  i < size; i++) {
			cout << *(p++) << endl;
		}
	}
};

template<typename T>
Vector<T> operator*(const Vector<T>& rhs1, Vector<T>& rhs2) {
	Vector<T> ret;
	for (int i = 0; i < rhs1.getSize(); ++i) {
		ret.push(rhs1.get(i) * rhs2.get(i));
	}
	return ret;
}

void f1() {
	std::cout << square(5) << std::endl;

	Vector<int> bv;
	bv.push(2);
	bv.push(5);
	bv.push(8);
	bv.push(9);
	bv.print();

	std::cout << "Print squared bv: " << std::endl;
	bv = square(bv);
	bv.print();
}

//////////////////////////////////////////////////////

// Template Specializaton and Partial Specialization

// Function Template Type Deduction

template<class T>
void f() {}

void f2() {
	f<int>();  // T is explicitly specified
}

// The type T can also be deduced 

template<class T>
void f(T t) {}

void f3() {
	f(67);  // T is deduced by compiler to be integer

	f<long>(67);  // explicitly tell compiler T's type

	f(67L);
}

///////////////////////////////////////////////

// Keyword typename and Its Usage

template<class T>
void printAge(T& item) {}

template<typename T>
void printAge(T& item) {}

//Question: What's the difference?
//          Which one should I use?


// Dependent Type

template<typename T> A {
	std::vector<T> vec;
}

// Nested Dependent Type

template<typename T> A {
	T::age myAge = 9;
	std::vector<T>::iterator itr;
}

// Second Usage of 'typename'

class Dog {
public:
	typedef int age;
};

template<class T>
void printMyAge(T& item) {
	int n = 9;
	T::age* a = &n;
	std::cout << (*a) << std::endl;
}

void f4() {
	Dog d;
	printMyAge<Dog>(d);    
}

// The code won't compile, why?

// RULE: always preceed a nested dependant type name with 'typename'

// EXCEPTION: in base class list or in initialization list

template<typename T>
class D : public T::NestedBaseClass {
public:
	D(int x) : T::NestedBaseClass(x) { 
		typename T::NestedBaseClass y;
	}
}
