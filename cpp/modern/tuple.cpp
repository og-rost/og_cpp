#include <iostream>
#include <map>
#include <unordered_map>
#include <string>
#include <tuple>
#include <functional> //std::ref

struct Node {
    char id; 
    int value;
    Node(char i, int v) : id(i), value(v) {}
    Node() : id(0), value('z') {}
};

void test_tuple1() {
    std::tuple<int, std::string, char> t(32, "Penny wise", 'a');
    //std::tuple<int, std::string, char> t = {32, "Penny wise", 'a'};  // Wont compile, constructor is explicit

    std::cout << std::get<0>(t) << std::endl;
    std::cout << std::get<1>(t) << std::endl;
    std::cout << std::get<2>(t) << std::endl;

    std::get<1>(t) = "Pound foolish";
    std::cout << std::get<1>(t) << std::endl;

    std::string& s = std::get<1>(t);
    s = "Patience is virtue"; 
    std::cout << std::get<1>(t) << std::endl;   
    //std::get<3>(t);  // Won't compile, t only has 3 fields
    //std::get<1>(t) is similar to t[1] for vector

    int i = 1;
    //std::get<i>(t); // Won't compile, i must be a compile time constant


    std::tuple<int, std::string, char> t2;  // default construction 
    t2 = std::tuple<int, std::string, char>(12, "Curiosity kills the cat", 'd'); 
    t2 = std::make_tuple(12, "Curiosity kills the cat", 'd'); 

    if (t > t2) {  // Lexicographical comparison
        std::cout << "t is larger than t2" << std::endl;
    }

    t = t2;  // member by member copying


    // Tuple can store references !!  STL containers such as vectors cannot.  Pair can.
    std::string st = "In for a penny";
    std::tuple<std::string&> t3(st);  
    //auto t3 = make_tuple(ref(st));  // Do the same thing
    std::get<0>(t3) = "In for a pound";  // st has "In for a pound"
    std::cout << st << std::endl;
    t2 = std::make_tuple(12, "Curiosity kills the cat", 'd'); 
    int x;
    std::string y;
    char z;
    std::make_tuple(std::ref(x), std::ref(y), std::ref(z)) = t2;  // assign t2 to x, y, z
    std::tie(x,y,z) = t2;  // same thing
    std::tie(x, std::ignore, z) = t2;  // std::get<1>(t2) is ignored

    // Other features
    auto t4 = std::tuple_cat( t2, t3 );  // t4 is tuple<int, string, char, string>
    std::cout << std::get<3>(t4) << std::endl;  // "In for a pound" 

    // type traits
    std::cout << std::tuple_size<decltype(t4)>::value << std::endl;  // Output: 4
    std::tuple_element<1, decltype(t4)>::type dd; // dd is a string

}

// tuple vs struct

std::tuple<std::string, int> getNameAge() { 
    return std::make_tuple("Bob", 34);
}

void test_tuple2() {
    struct Person { std::string name; int age; } p;
    std::tuple<std::string, int> t;

    std::cout << p.name << " " << p.age << std::endl;
    std::cout << std::get<0>(t) << " " << std::get<1>(t) << std::endl;

    // As a one-time only structure to transfer a group of data
    std::string name;
    int age;
    std::tie(name, age) = getNameAge();

    // Comparison of tuples
    std::tuple<int, int, int> time1, time2; // hours, minutes, seconds
    if (time1 > time2) 
        std::cout << " time1 is a later time" << std::endl;

    // Multi index map
    std::map<std::tuple<int, int, int>, std::string> timemap1;
    timemap1.insert(std::make_pair(std::make_tuple(12, 2, 3), "Game start"));
    std::cout << timemap1[std::make_tuple(2, 3, 4)]; 

    // Little trick
    int a, b, c;
    std::tie(b, c, a) = std::make_tuple(a, b, c);
}

int main() {
    test_tuple1();
    test_tuple2();
    return 0;
}
