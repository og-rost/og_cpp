#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <functional>
#include <deque>

/*******************************************************************************************/

//Function Objects (functors)

class X {
public:
    void operator()(std::string str) { 
        std::cout << "Calling functor X with parameter " << str << std::endl;
    }  
};

int main() {
    X foo;
    foo("Hi");    // Calling functor X with parameter Hi
}

/*****************************************************************************************/


// Benefits of functor:
// 1. It can remember state.
// 2. It can have its own type.


// operator string () const { return "X"; }  type conversion function not a functor

// Parameterized Function

class X {
public:
    X(int i) {}
    void operator()(std::string str) { 
        std::cout << "Calling functor X with parameter " << str<< std::endl;
    }
};

int main() {
    X(8)("Hi");
}

/*****************************************************************************************/

void add2(int i) {
    std::cout << i + 2 << std::endl;
}

template<int val>
void addVal(int i) {
    std::cout << val + i << std::endl;
}

class AddValue {
    int val;
public:
    AddValue(int j) : val(j) {}
    void operator()(int i) {
        std::cout << i + val << std::endl;
    }
};

int main() {
    std::vector<int> vec = {2, 3, 4, 5};   
    //std::for_each(vec.begin(), vec.end(), add2); // {4, 5, 6, 7}
    int x = 2;
    //std::for_each(vec.begin(), vec.end(), addVal<x>); // {4, 5, 6, 7}
    std:for_each(vec.begin(), vec.end(), AddValue(x)); // {4, 5, 6, 7}
}


/*************************************************************************************/


// Build-in Functors

// less greater  greater_equal  less_equal  not_equal_to
// logical_and  logical_not  logical_or
// multiplies minus  plus  divide  modulus  negate

void addVal(int i, int val) {
    std::cout << i + val << std::endl;
}

int main() {
	int x = std::multiplies<int>()(3, 4);  //  x = 3 * 4 

	if (std::not_equal_to<int>()(x, 10))   // if (x != 10)
	    std::cout << x << std::endl;

	 
	// Parameter Binding
	    
	std::set<int> myset = {2, 3, 4, 5};   
	std::vector<int> vec;


	int xx = std::multiplies<int>()(3, 4);  //  x = 3 * 4 

	// Multiply myset's elements by 10 and save in vec:
	std::transform(myset.begin(), myset.end(),    // source
	        std::back_inserter(vec),              // destination
	        std::bind(std::multiplies<int>(), std::placeholders::_1, 10));  // functor
	// First parameter of multiplies<int>() is substituted with myset's element
	// vec: {20, 30, 40, 50}

	std::for_each(vec.begin(), vec.end(), std::bind(addVal, std::placeholders::_1, 2));

	// C++ 03: bind1st, bind2nd	
}

// C++ 03: bind1st, bind2nd


/*****************************************************************************************/

// Convert a regular function to a functor
double Pow(double x, double y) {
    return pow(x, y);
}

int main() {
    std::set<int> myset = {3, 1, 25, 7, 12};
    std::deque<int> d;
    auto f = std::function<double (double, double)>(Pow);   //C++ 11
    std::transform(myset.begin(), myset.end(),     // source
            std::back_inserter(d),              // destination
            std::bind(f, std::placeholders::_1, 2));  // functor
    //  d: {1, 9, 49, 144, 625}
}
// C++ 03 uses ptr_fun 

/*****************************************************************************************/
bool needCopy(int x) {
    return (x > 20) || (x < 5);
}

int main() {
	std::set<int> myset = {3, 1, 25, 7, 12};
	// when (x > 20) || (x < 5),  copy from myset to d
	std::deque<int> d;

	std::transform(myset.begin(), myset.end(),     // source
	        std::back_inserter(d),               // destination
	        needCopy
	        );

	// C++ 11 lambda function:
	std::transform(myset.begin(), myset.end(),     // source
	        std::back_inserter(d),              // destination
	        [](int x){return (x > 20) || (x < 5);}
	        );
}

// Why do we need functor in STL?

/*****************************************************************************************/

std::set<int> myset1 = {3, 1, 25, 7, 12}; // myset: {1, 3, 7, 12, 25}
// same as:
std::set<int, std::less<int>> myset2 = {3, 1, 25, 7, 12};

bool lsb_less(int x, int y) {
    return (x % 10) < (y % 10);
}

class Lsb_less {
public:
    bool operator()(int x, int y) {
        return (x % 10) < (y % 10);
    }
};

int main() {
    std::set<int, Lsb_less> myset3 = {3, 1, 25, 7, 12};  // myset: {1,12,3,25,7}
}

/*****************************************************************************************/

// Predicate

// A functor or function that:
// 1. Returns a boolean
// 2. Does not modify data


class NeedCopy {
public:
    bool operator()(int x){   
        return (x > 20) || (x < 5);  
    }
};

int main() {
	std::set<int, std::less<int>> myset = {3, 1, 25, 7, 12};
	std::deque<int> d;

	std::transform(myset.begin(), myset.end(),     // source
	        std::back_inserter(d),               // destination
	        NeedCopy()
	        );
}

// Predicate is used for comparison or condition check

/*****************************************************************************************/