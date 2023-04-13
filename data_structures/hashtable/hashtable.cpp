#include <vector>
#include <list>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <unordered_set>

static int prime_list[] = {
			11, 53, 97, 193, 227, 307, 389, 431, 769, 983, 
			1231, 1543, 2393, 3079, 4091, 5009, 6151, 8287, 10753, 12289, 
			14879, 17419, 21089, 24593, 27059, 32297, 36551, 39371, 44917,
			49157, 53861, 60257, 65927, 70949
		};

class hashtable {
public:
	hashtable();
	~hashtable() {}
	void add_elem(int);
	bool search(int);
	bool erase(int);
	void test_hash();
private:
	std::vector<std::list<int>> table;
	void reallocate();
	int hash_func(int);	
	int table_size;
	int current_prime_index;	
};

hashtable::hashtable() : current_prime_index(0) {
	table_size = prime_list[current_prime_index];
	table.resize(table_size);
	std::cout << "table_size is "  << table.size() << std::endl;
}

void hashtable::reallocate() {
	std::cout << "reallocate  is  called "  << std::endl;
	std::vector<std::list<int>> temp_table;	
	table_size = prime_list[++current_prime_index];
	temp_table.resize(table_size);

	for(auto i : table)
		for(auto elem : i)
			temp_table[hash_func(elem)].push_front(elem);
	
	table = temp_table;
	std::cout << "table_size is "  << table.size() << std::endl;
}

void hashtable::test_hash() {
	std::cout << std::endl;
	std::vector<int> sizes;
	for(int i = 0; i < table.size(); ++i)
		sizes.push_back(table[i].size());
	
	std::sort(sizes.begin(), sizes.end());
	
	std::cout << std::endl << std::endl;
	
	std::cout << "my hashtable size is  " << table.size() << std::endl;
	std::cout << "max bucket size in my hashtable is " << sizes.back() << std::endl;
}

int hashtable::hash_func(int k) {
	return k % table_size;	
}

void hashtable::add_elem(int elem) {
	if(search(elem)) return;
	static int counter = 0;
	if (counter++ == table_size / 3) {
		reallocate();
		counter = 0;
	}
	table[hash_func(elem)].push_front(elem);
}

bool hashtable::search(int elem) {
	int hash_value = hash_func(elem);
	std::list<int>::iterator it = table[hash_value].begin();
	for(; it != table[hash_value].end(); ++it)
		if(*it == elem)
			return true;
	return false;
}

bool hashtable::erase(int elem) {
	int hash_value = hash_func(elem);
	std::list<int>::iterator it = table[hash_value].begin();
	for(; it != table[hash_value].end(); ++it) {
		if(*it == elem) {
			table[hash_value].erase(it);
			return true;
		}
	}
	return false;
}

void test_unodered_set(std::unordered_set<int>& myset) {
	int buckets = myset.bucket_count();

	std::cout << std::endl;
  	std::cout << "unodered set size is " << buckets << std::endl;

  	std::vector<int> mysetTest;
  	for (int i = 0; i < buckets; ++i) {
    	mysetTest.push_back(myset.bucket_size(i));
  	}

  	std::sort(mysetTest.begin(), mysetTest.end());
  	std::cout << "max bucket size in unodered set is " << mysetTest.back() << std::endl;
}

int main(int argc, char* argv[]) { 
	// takes command line argument as the number of elements to be inserted into hash table
	

	srand(time(NULL));

	hashtable hash;
	std::unordered_set<int> myset;
	
	int count = atoi(argv[1]);
	for(int i = 0; i < count; ++i) {
		int r = rand();
		hash.add_elem(r);
		myset.emplace(r);
	}

	hash.test_hash();
	test_unodered_set(myset);

	//testing search and erase

	hash.add_elem(40);

	bool b = hash.search(40);
	if(b) std::cout << "40 exists" << std::endl;
	
	hash.erase(40);
	b = hash.search(40);
	if(!b) std::cout << "40 does not exist" << std::endl;
}