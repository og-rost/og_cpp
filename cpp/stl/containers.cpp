#include <vector>
#include <deque>
#include <list>
#include <set>   			// std::set and multistd::set
#include <map>   			// std::map and multistd::map
#include <unordered_set>  	// unordered std::set/multistd::set
#include <unordered_map>  	// unordered std::map/multistd::map
#include <iterator>
#include <algorithm>
#include <numeric>    		// some numeric algorithm
#include <functional>

// STL: Standard Template Library -- Data Structures and Algorithms

// Properties of std::vector:
// 1. fast insert/remove at the end: O(1)
// 2. slow insert/remove at the begining or in the middle: O(n)
// 3. slow search: O(n)


int main() {
	std::vector<int> vec;
	vec.push_back(4);
	vec.push_back(1);
	vec.push_back(8);  // vec: {4, 1, 8}

	std::vector<int>::iterator itr1 = vec.begin();  // half-open:  [begin, end)
	std::vector<int>::iterator itr2 = vec.end();

	for (std::vector<int>::iterator itr = itr1; itr != itr2; ++itr)
		std::cout << *itr << " ";  // Print out:  4 1 8

	std::sort(itr1, itr2);  // vec: {1, 4, 8}

	std::vector<int> vec;   // vec.size() == 0
	vec.push_back(4);
	vec.push_back(1);
	vec.push_back(8);  // vec: {4, 1, 8};    vec.size() == 3

	// std::vector specific operations:
	std::cout << vec[2];     // 8  (no range check)
	std::cout << vec.at(2);  // 8  (throw range_error exception of out of range)

	for (int i; i < vec.size(); ++i)
	    std::cout << vec[i] << " ";

	for (std::list<int>::iterator itr = vec.begin(); itr!= vec.end(); ++itr)
	    std::cout << *itr << " ";  

	for (it: vec)    // C++ 11
	    std::cout << it << " ";

	// std::vector is a dynamically allocated contiguous array in memory
	int* p = &vec[0];
	p[2] = 6;


	// Common member functions of all containers.
	// vec: {4, 1, 8}
	if (vec.empty()) { std::cout << "Not possible.\n"; }

	std::cout << vec.size();   // 3

	std::vector<int> vec2(vec);  // Copy constructor, vec2: {4, 1, 8}

	vec.clear();    // Remove all items in vec;   vec.size() == 0

	vec2.swap(vec);   // vec2 becomes empty, and vec has 3 items.


	// Properties of std::deque
	// 1. fast insert/remove at the begining and the end;
	// 2. slow insert/remove in the middle: O(n)
	// 3. slow search: O(n)

	std::deque<int> deq = { 4, 6, 7 };
	deq.push_front(2);  // deq: {2, 4, 6, 7}
	deq.push_back(3);   // deq: {2, 4, 6, 7, 3}

	// std::deque has similar interface with std::vector
	std::cout << deq[1];  // 4

	// Properties:
	// 1. fast insert/remove at any place: O(1)
	// 2. slow search: O(n)
	// 3. no random access, no [] operator.

	std::list<int> mystd::list = {5, 2, 9 }; 
	mystd::list.push_back(6);  // mystd::list: { 5, 2, 9, 6}
	mystd::list.push_front(4); // mystd::list: { 4, 5, 2, 9, 6}


	std::list<int>::iterator itr = find(mystd::list.begin(), mystd::list.end(), 2); // itr -> 2
	mystd::list.insert(itr, 8);   // mystd::list: {4, 5, 8, 2, 9, 6}  
	// O(1), faster than std::vector/std::deque
	itr++;                   // itr -> 9
	mystd::list.erase(itr);       // mystd::list: {4, 8, 5, 2, 6}   O(1)


	mystd::list1.splice(itr, mystd::list2, itr_a, itr_b );   // O(1)

	//Associative Container
	// Always sorted, default criteria is <
	// No push_back(), push_front()


	// Properties:
	// 1. Fast search: O(log(n))
	// 2. Traversing is slow (compared to std::vector & std::deque)
	// 3. No random access, no [] operator.
	// 4. No duplicates
	 
	std::set<int> mystd::set;
	mystd::set.insert(3);    // mystd::set: {3}
	mystd::set.insert(1);    // mystd::set: {1, 3}
	mystd::set.insert(7);    // mystd::set: {1, 3, 7},  O(log(n))

	std::set<int>::iterator it;
	it = mystd::set.find(7);  // O(log(n)), it points to 7
	// Sequence containers don't even have find() member function
	pair<std::set<int>::iterator, bool> ret;
	ret = mystd::set.insert(3);  // no new element inserted
	if (ret.second==false) 
	    it=ret.first;       // "it" now points to element 3

	mystd::set.insert(it, 9);  // mystd::set:  {1, 3, 7, 9}   O(log(n)) => O(1)
	// it points to 3
	mystd::set.erase(it);         // mystd::set:  {1, 7, 9}

	mystd::set.erase(7);   // mystd::set:  {1, 9}
	// Note: none of the sequence containers provide this kind of erase.


	// multistd::set is a std::set that allows duplicated items
	multistd::set<int> mystd::set;

	// std::set/multistd::set: value of the elements cannot be modified
	*it = 10;  // *it is read-only

	// std::map

	std::map<char,int> mystd::map;
	mystd::map.insert ( pair<char,int>('a',100) );
	mystd::map.insert ( make_pair('z',200) );

	std::map<char,int>::iterator it = mystd::map.begin();
	mystd::map.insert(it, pair<char,int>('b',300));  // "it" is a hint

	it = mystd::map.find('z');  // O(log(n))

	// showing contents:
	for ( it=mystd::map.begin() ; it != mystd::map.end(); it++ )
	    std::cout << (*it).first << " => " << (*it).second << endl;

	// multimap is a std::map that allows duplicated keys
	multistd::map<char,int> mystd::map;

	// std::map/std::multimap:
	// keys cannot be modified
	// type of *it:   pair<const char, int>
	(*it).first = 'd';  // Error


	// Associative Containers: std::set, multistd::set, std::map, multistd::map
	
	/*
	 *  Unordered Container (C++ 11)
	 *   - Unordered std::set and multistd::set
	 *   - Unordered std::map and multistd::map

	 *  Order not defined, and may change overtime
	 *
	 *  Default hash function defined for fundamental types and string.
	 *
	 *  No subscript operator[] or at()
	 *  No push_back(), push_front()
	 */

	// unordered std::set
	unordered_std::set<string> mystd::set = { "red","green","blue" };
	unordered_std::set<string>::const_iterator itr = mystd::set.find ("green"); // O(1)
	if (itr != mystd::set.end())   // Important check 
	    std::cout << *itr << endl;
	mystd::set.insert("yellow");  // O(1)

	std::vector<string> vec = {"purple", "pink"};
	mystd::set.insert(vec.begin(), vec.end());

	// Hash table specific APIs:
	std::cout << "load_factor = " << mystd::set.load_factor() << endl;
	string x = "red";
	std::cout << x << " is in bucket #" << mystd::set.bucket(x) << endl;
	std::cout << "Total bucket #" << mystd::set.bucket_count() << endl;

	// unordered multistd::set: unordered std::set that allows duplicated elements
	// unordered std::map: unordered std::set of pairs
	// unordered multistd::map: unordered std::map that allows duplicated keys


	// hash collision => performance degrade

	/* Properties of Unordered Containers:
	 * 1. Fastest search/insert at any place: O(1)
	 *     Associative Container takes O(log(n))
	 *     std::vector, std::deque takes O(n)
	 *     std::list takes O(1) to insert, O(n) to search
	 * 2. Unorderd std::set/multistd::set: element value cannot be changed.
	 *    Unorderd std::map/multistd::map: element key cannot be changed.
	 */

	/*
	 * Associative Array
	 * - std::map and unordered std::map
	 */
	unordered_std::map<char, string> day = {{'S',"Sunday"}, {'M',"Monday"}};

	std::cout << day['S'] << endl;    // No range check
	std::cout << day.at('S') << endl; // Has range check

	std::vector<int> vec = {1, 2, 3};
	vec[5] = 5;   // Compile Error

	day['W'] = "Wednesday";  // Inserting {'W', "Wednesday}
	day.insert(make_pair('F', "Friday"));  // Inserting {'F', "Friday"}

	day.insert(make_pair('M', "MONDAY"));  // Fail to modify, it's an unordered_std::map
	day['M'] = "MONDAY";                   // Succeed to modify


	void foo(const unordered_std::map<char, string>& m) {
	    //m['S'] = "SUNDAY";
	    //std::cout << m['S'] << endl;
	    auto itr = m.find('S');
	    if (itr != m.end())
	        std::cout << *itr << endl;
	}
	foo(day);

	//   std::cout << m['S'] << endl;
	//   auto itr = m.find('S');
	//   if (itr != m.end() )
	//      std::cout << itr->second << endl;

	//Notes about Associative Array: 
	//1. Search time: unordered_std::map, O(1); std::map, O(log(n));
	//2. Unordered_std::map may degrade to O(n);
	//3. Can't use multistd::map and unordered_multistd::map, they don't have [] operator.

	/*
	 * Array
	 */
	int a[3] = {3, 4, 5};
	array<int, 3> a = {3, 4, 5};
	a.begin();
	a.end();
	a.size();
	a.swap();
	array<int, 4> b = {3, 4, 5};

	/*
	 * Container Adaptor
	 *  - Provide a restricted interface to meet special needs
	 *  - Implemented with fundamental container classes
	 *
	 *  1. stack:  LIFO, push(), pop(), top()
	 *
	 *  2. queue:  FIFO, push(), pop(), front(), back() 
	 *
	 *  3. priority queue: first item always has the greatest priority
	 *                   push(), pop(), top()
	 */


	/*
	 * Another way of categorizing containers:
	 *
	 * 1. Array based containers: std::vector, std::deque
	 *
	 * 2. Node base containers: std::list + associative containers + unordered containers
	 *
	 * Array based containers invalidates pointers:
	 *    - Native pointers, iterators, references
	 */

	std::vector<int> vec = {1,2,3,4};
	int* p = &vec[2];   // p points to 3
	vec.insert(vec.begin(), 0);
	std::cout << *p << endl;   // 2, or ?
}