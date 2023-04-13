#include <iostream>
#include <string>

// Example 1

template <typename T> T adder(T v) {
  //std::cout << __PRETTY_FUNCTION__ << "\n";

  return v;
}

template <typename T, typename... Args> T adder(T first, Args... args) {
  //std::cout << __PRETTY_FUNCTION__ << "\n";

  return first + adder(args...);
}

// typename... Args is called a template parameter pack
// Args... args is called a function parameter pack

// Variadic templates are written just the way you'd write
// recursive code - you need a base case and a general case which "recurses"



// Example 2

template<typename T>
bool pair_comparer(T a, T b) {
  return a == b;
}

template<typename T, typename... Args>
bool pair_comparer(T a, T b, Args... args) {
  return a == b && pair_comparer(args...);
}

// Example 3

// Varidic data structures
// Variadic templates make it possible to define data structures that could
// have an arbitrary number of fields, and have this number configured per use.
// The prime example of this is a tuple class.

template <class... Ts> struct tuple {}; // empty base case

template <class T, class... Ts>
struct tuple<T, Ts...> : tuple<Ts...> {
  tuple(T t, Ts... ts) : tuple<Ts...>(ts...), tail(t) {}

  T tail;
};

// This is a recursive definition that stops when there are no more types to peel off
// and the base of the hierarchy is an empty tuple.

// For tuple<double, uint64_t, const char*> t1(12.2, 42, "big");

/*
struct tuple<double, uint64_t, const char*> : tuple<uint64_t, const char*> {
  double tail;
}

struct tuple<uint64_t, const char*> : tuple<const char*> {
  uint64_t tail;
}

struct tuple<const char*> : tuple {
  const char* tail;
}

struct tuple {
}
*/

// define a helper type that lets us access the type of the k-th element in a tuple:

template <size_t, class> struct elem_type_holder;

template <class T, class... Ts>
struct elem_type_holder<0, tuple<T, Ts...>> {
  typedef T type;
};

template <size_t k, class T, class... Ts>
struct elem_type_holder<k, tuple<T, Ts...>> {
  typedef typename elem_type_holder<k - 1, tuple<Ts...>>::type type;
};

/****************************************/

int main() {
  long sum = adder(1, 2, 3, 8, 7);

  /*
    T adder(T, Args ...) [with T = int; Args = {int, int, int, int}]
    T adder(T, Args ...) [with T = int; Args = {int, int, int}]
    T adder(T, Args ...) [with T = int; Args = {int, int}]
    T adder(T, Args ...) [with T = int; Args = {int}]
    T adder(T) [with T = int]
  */

  std::string s1 = "x", s2 = "aa", s3 = "bb", s4 = "yy";
  std::string ssum = adder(s1, s2, s3, s4);

  std::cout << sum << std::endl;
  std::cout << ssum << std::endl;


  pair_comparer(1.5, 1.5, 2, 2); // true
  // pair_comparer(1.5, 1, 2, 2); // won't compile, double and int are different types
  // pair_comparer(1.5, 1.5, 2, 2, 7); won't compile, odd number of arguments
  // to fix it we can add
  /*
  template<typename T>
  bool pair_comparer(T a) {
    return false;
  }
  */
}