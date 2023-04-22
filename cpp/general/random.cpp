/* Random Engine:
 *    stateful generator that generates random value within predefined min and max.
 *    Not truely random -- pseudorandom
 */

#include <iostream>
#include <random>
#include <vector>
#include <sstream>

void printRandom(std::default_random_engine e) {
	for (int i = 0; i < 10; ++i) { 
		std::cout << e() << " ";
    }
	std::cout << std::endl;
}

template <typename T>
void printArray(T arr) {
	for (auto v : arr) {
		std::cout << v << " ";
	}
	std::cout << std::endl;
}

void test1() {
    std::default_random_engine eng;
    std::cout << "Min: " << eng.min() << std::endl; 
	std::cout << "Max: " << eng.max() << std::endl;

	std::cout << eng() << std::endl;  // Generate one random value
	std::cout << eng() << std::endl;  // Generate second random value

	std::stringstream state;
	state << eng;  // Save the state

	std::cout << eng() << std::endl;  // Generate one random value
	std::cout << eng() << std::endl;  // Generate second random value

	state >> eng;  // Restore the state
	std::cout << eng() << std::endl;  // Generate one random value
	std::cout << eng() << std::endl;  // Generate second random value
}

void test2() {    
    std::default_random_engine eng;
	printRandom(eng);

	std::default_random_engine eng2;
	printRandom(eng2);

	unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
	std::default_random_engine e3(seed);
	printRandom(e3);

	eng.seed();  // reset engine to initial state
	eng.seed(109); // set engine to a state according to seed 109

	eng2.seed(109);
	if (eng == eng2) {   // will return true
		std::cout << "eng and eng2 have the same state" << std::endl;
    }

	std::cout << "\n\n Shuffling:" << std::endl;
	int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	std::vector<int> d1(arr, arr + 9);
	printArray(d1);

	std::vector<int> d2 = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	std::shuffle(d2.begin(), d2.end(), std::default_random_engine());
	printArray(d2);
	std::shuffle(d2.begin(), d2.end(), std::default_random_engine());  // same order
	printArray(d2);
	
	std::shuffle(d2.begin(), d2.end(), eng);
	printArray(d2);
	std::shuffle(d2.begin(), d2.end(), eng);  // different order
	printArray(d2);
}

/* Other random engines */

/* Distribution */

void test3()  {
	// engine only provides a source of randomness
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine e(seed);
   // How to get a random number between 0 and 5?
   //  e()%6  
	//    -- Bad quality of randomness
	//    -- Can only provide uniform distribution

	std::uniform_int_distribution<int> distr(0,5);  // range: [0,5]  -- both 1 and 5 are included
													// default param: [0, INT_MAX]
	std::cout << " int_distribution: " << std::endl; 
    for (int i = 0; i < 30; ++i) {
        std::cout << distr(e) << " ";
    }


	std::cout << "\n\n real_distribution: " << std::endl;

	std::uniform_real_distribution<double> distrReal(0,5);  // half open: [1, 5)  -- 1 is included, 5 is not.
														// default param: [0, 1)
    for (int i = 0; i < 30; ++i) {
        std::cout << distrReal(e) << " ";
    }

	std::cout << " poisson_distribution: " << std::endl; 
	std::poisson_distribution<int> distrP(1.0);  //  mean (double) 
    for (int i = 0; i < 30; ++i) {
        std::cout << distrP(e) << " ";
    }
	std::cout << std::endl;	

	std::cout << " normal_distribution: " << std::endl; 
	std::normal_distribution<double> distrN(10.0, 3.0);  // mean and standard deviation
	std::vector<int> v(20);
    for (int i = 0; i < 800; ++i) {
        int num = distrN(e); // convert double to int
		if (num >= 0 && num < 20) {
			v[num]++;   // E.g., v[10] records number of times 10 appeared
		}
    }
	for (int i = 0; i < 20; ++i) {
		std::cout << i << ": " << std::string(v[i], '*') << std::endl;
	}
	std::cout << std::endl;

	// Stop using rand()%n; 
}

int main() {
	test1();
	test2();
	test3();

	return 0;
}
