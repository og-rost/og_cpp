#include <vector>
#include <string>
#include <iostream>
#include <stack>
#include <algorithm>
#include <climits>
#include <string_view>
#include <mdspan>
#include <print>
#include <span>

using iter = std::vector<int>::iterator;
using citer = std::vector<int>::const_iterator;

/***************************************************/

// string haash

template<class _Key>
struct hash {};

size_t hash_function (const char* s) {
    unsigned long h = 0;
    for ( ; *s; ++s)
        h = 5 * h + *s;
    return size_t(h);
}

template<>
struct hash<char*> {
    size_t operator() (const char* s) const { 
        return hash_function(s); 
    }
};

template<>
struct hash<const char*> {
    size_t operator() (const char* s) const {
        return hash_function(s); 
    }
};

/***************************************************/

int max(int a, int b, int c) { 
	return std::max(std::max(a, b), c); 
}

int maxCrossingSum(const std::vector<int>& vec, int l, int m, int r) {
    int sum = 0;
    int left_sum = INT_MIN;
    for (int i = m; i >= l; --i) {
        sum = sum + vec[i];
        if (sum > left_sum)
            left_sum = sum;
    }

    sum = 0;
    int right_sum = INT_MIN;
    for (int i = m + 1; i <= r; ++i) {
        sum = sum + vec[i];
        if (sum > right_sum)
            right_sum = sum;
    }
    return left_sum + right_sum;
}

int maxSubArraySum(const std::vector<int>& vec, int l, int r) {
    if (l == r)
        return vec[l];
    int m = (l + r) / 2;
    return max(maxSubArraySum(vec, l, m),
            maxSubArraySum(vec, m + 1, r),
            maxCrossingSum(vec, l, m, r));
}

/***************************************************/

citer lower(const std::vector<int>& vec, iter low, iter high, int x) {    
    if(low < high)  {
        iter mid = low + (high - low) / 2;  
        if (mid == low || (*mid == x && *(mid - 1) < x))
            return mid;
        else if (x > *mid)
            return lower(vec, mid + 1, high, x);
        else
            return lower(vec, low, mid, x);
    }
    return vec.end();    
}

bool isMajority(std::vector<int>& vec, int x) {
    citer it = lower(vec, vec.begin(), vec.end(), x);
    if (it == vec.end())
        return false;
    else if (*it == x && *(it + vec.size() / 2) == x)
        return true;
    else
        return false;
}

/***************************************************/

// max number from array elements

int reverse(int num) {
    int rev_num = 0;
    while (num > 0)	{
        rev_num = rev_num * 10 + num % 10;
        num = num / 10;
    }
    return rev_num;
}

bool functor(int i, int j) {
    int a = reverse(i);
    int b = reverse(j);
    a %= 10;
    b %= 10;
    return a > b;
}

void make(std::vector<int>& vec) {
    std::sort(vec.begin(), vec.end(), functor);
}

/***************************************************/

int lcsRec (const std::string& str1, const std::string& str2, int m, int n) {
    if (m == 0 || n == 0)
        return 0;
    if (str1[m - 1] == str2[n - 1])
        return 1 + lcsRec(str1, str2, m - 1, n - 1);
    else
        return std::max(lcsRec(str1, str2, m, n - 1), lcsRec(str1, str2, m - 1, n));
}

int lcsDyn (const std::string& str1, const std::string& str2) {
    int m = str1.size();
    int n = str2.size();

    int L[m + 1][n + 1];

    for (int i = 0; i <= m; ++i) {
        for (int j = 0; j <= n; ++j) {
            if (i == 0 || j == 0)
                L[i][j] = 0;

            else if (str1[i - 1] == str2[j - 1])
                L[i][j] = L[i - 1][j - 1] + 1;

            else
                L[i][j] = std::max(L[i - 1][j], L[i][j - 1]);
        }
    }

    return L[m][n];
}

/***************************************************/

int maxDiff(const std::vector<int>& vec) {
    int max_diff = vec[1] - vec[0];
    int min = vec[0];

    for(int i = 1; i < vec.size(); ++i) {  
        if(vec[i] - min > max_diff)                               
            max_diff = vec[i] - min;
        if(vec[i] < min)
            min = vec[i];                     
    }
    return max_diff;
}

/***************************************************/

void myMemCpy(void* dest, void* src, size_t n) {
    char* csrc = (char*)src;
    char* cdest = (char*)dest;
    char* temp = new char[n];
    for (int i = 0; i < n; ++i)
        temp[i] = csrc[i]; 

    for (int i = 0; i < n; ++i)
        cdest[i] = temp[i];
}

/***************************************************/

long fact(int num) {
    int f = 1;
    int i = 1;
    while (i <= num) {
        f *= i;
        ++i;
    }
    return f;
}

void pascal(int line) {
    for (int i = 0; i < line; ++i) {
        for (int j = 0; j < line - i - 1; ++j) {
            std::cout << " ";
        }
        for (int j = 0; j <= i; ++j) {
            std::cout << fact(i) / (fact(j) * fact(i - j)) << "  ";
        }
        std::cout << std::endl;
    }
}

/***************************************************/

int help(int a, int b) {
    if(b==0)
        return a;
    else
        return help(b, a%b);
}

void leftRotate(std::vector<int>& vec, int d) {
    for (int i = 0; i < help(d, vec.size()); ++i) {
        int temp = vec[i];
        int j = i;
        while(1) {
            int k = j + d;
            if (k >= vec.size())
                k = k - vec.size();
            if (k == i)
                break;
            vec[j] = vec[k];
            j = k;
        }
        vec[j] = temp;
    }
}

/***************************************************/

void randomize (std::vector<int>& vec) {   
    srand (time(0));   
    for (int i = 0; i < vec.size(); ++i) {
        int j = rand() % (i + 1);
        std::swap(vec[i], vec[j]);
    }
}

/***************************************************/

bool isSubset(iter b1, iter e1, iter b2, iter e2) {
    //if(std::distance(b1, e1) < std::distance(b2, e2))
    if ((e1 - b1) < (e2 - b2))  
        return false;

    while (b1 < e1 && b2 < e2) {
        if (*b2 < *b1) {
            return false;
        }
        else if (*b2 == *b1) {
            ++b1;  
            ++b2;
        }
        else if (*b2 > *b1) {
            ++b1;            
        }
    }
    if (b2 < e2)
        return false;
    else
        return true;
}

/***************************************************/

int sumOfDigits(int n) {
    static int s = 0;
    if (n < 1)
        return s;
    else {
        s += n % 10;
        return sumOfDigits(n / 10);		
    }
}

/***************************************************/

void splitString(std::string str) {
    std::vector<std::string> v;
    std::string buffer;
    for (auto n : str) {
        if(n != ' ')
            buffer += n;
        else if (n == ' ' && buffer != "") {
            v.push_back(buffer);
            buffer = "";
        }
    }
    if (buffer != "")
        v.push_back(buffer);

    for (auto i : v)
        std::cout << i << std::endl; 
}

/***************************************************/

void digits(int n) {
    if (n < 10)
        std::cout << n << "   ";
    else  {	
        digits(n / 10);
        std::cout << (n % 10) << "   ";
    }
}

/***************************************************/

bool isPalindrom(int num) {
    int check = num;
    int reverse = 0;
    int temp = 0;

    while (num != 0) {
        temp = num % 10;
        num = num / 10;
        reverse = temp + (reverse * 10);
    } 

    if (reverse == check)
        return true;
    return false;
}

/***************************************************/

int maxSubArray(int* arr, int size) {
    int max_so_far = 0;
    int max_ending_here = 0;
    for(int i = 0; i < size; ++i)   {
        max_ending_here += arr[i];
        if(max_ending_here < 0)
            max_ending_here = 0;
        else if(max_so_far < max_ending_here)
            max_so_far = max_ending_here;
    }
    return max_so_far;
}

/***************************************************/

void binaryCode1(int n) {	
    int bits = 1 << 16;	
    for (int i = 0; i < 16; ++i) {
        std::cout << (n & bits ? '1' : '0');
        n <<= 1;		
    }
    std::cout << std::endl;
}

/***************************************************/

void binaryCode2(int n) {
    if (n == 1)
        std::cout << n;
    else {
        binaryCode2(n / 2);
        std::cout << n % 2;
    }
}

/***************************************************/

bool arePair(char opening, char closing) {
    if (opening == '(' && closing == ')') 
        return true;
    else if (opening == '{' && closing == '}')
        return true;
    else if (opening == '[' && closing == ']')
        return true;
    return false;
}

bool isBalanced(std::string exp) {
    std::stack<char> stk;
    for(int i = 0; i < exp.length(); ++i) {
        if(exp[i] == '(' || exp[i] == '{' || exp[i] == '[')
            stk.push(exp[i]);
        else if(exp[i] == ')' || exp[i] == '}' || exp[i] == ']') {
            if(stk.empty() || !arePair(stk.top(),exp[i]))
                return false;
            else
                stk.pop();
        }
    }
    return stk.empty() ? true : false;
}

/***************************************************/

void binaryToDecimal() {
    long dec = 0, rem, num, base = 1;

    std::cout << "Enter the binary number(1s and 0s) : ";
    std::cin >> num;
    long bin = num;
    while (num > 0) {
        rem = num % 10;
        dec = dec + rem * base;
        base = base * 2;
        num = num / 10;
    }
    std::cout << "The decimal equivalent of " << bin << " : " << dec << std::endl;
}

/***************************************************/

void drawCircle(int r) {
    int N = 2 * r + 1; // Consider a rectangle of size N*N 
    int x, y;  // Coordinates inside the rectangle

    // Draw a square of size N*N.
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            // Start from the left most corner point
            x = i - r;
            y = j - r; 
            // If this point is inside the circle, print it
            if (x * x + y * y <= r * r + 1)
                std::cout << '.';
            else // If outside the circle, print space
                std::cout << ' ';
            std::cout << ' ';
        }
        std::cout << std::endl;
    }
}

/***************************************************/

void deleteRepeats(char* arr, int& size) {
    int num = size;
    int start = 0;
    while(start != num)	{
        char test = arr[start];
        for(int i = start + 1; i <= num; ++i) {
            if(test == arr[i]) {
                for(int j = i; j < num; ++j)
                    arr[j] = arr[j + 1];
                --num;
                --start; 
            }
        }
        ++start;
    }
    for(int i = num + 1; i < size; ++i)
        arr[i] = ' ';
    size = num;
}

/***************************************************/

void dynamicMultiArray() {
    int** p = new int*[10];
    for (int i = 0; i < 10; ++i)
        p[i] = new int[20];
    for (int i = 0; i < 10; ++i)
        delete[] p[i];
    delete[] p;
}

/***************************************************/

/*

std::span

span is an object that can refer to a contiguous sequence of objects with the first element of the sequence at position zero.
A span can either have a static extent, in which case the number of elements in the sequence is known at compile-time and
encoded in the type, or a dynamic extent. If a span has dynamic extent a typical implementation holds two members:
a pointer to T and a size. A span with static extent may have only one member: a pointer to T.

span<T> is:

A very lightweight abstraction of a contiguous sequence of values of type T somewhere in memory.
A non-owning type (i.e. a "reference-type" rather than a "value type"): It never allocates nor deallocates anything and does not
keep smart pointers alive.
*/
 
void print(std::span<const int> sp) {
  for(auto it = sp.begin(); it != sp.end(); ++it) {
    std::cout << *it << ' ';
  }
  std::cout << '\n';
}
 
void transmogrify(std::span<int> sp) {
  if (!sp.empty()) {
    std::cout << *sp.begin() << '\n';
    *sp.begin() = 2;
  }
}
 
void testSpan() {
  int array[] { 1, 3, 4, 5 };
  print(array);
  transmogrify(array);
  print(array);
}

/*
Now for when to actually use a span:

Use span<T> instead of a free-standing T* when the allocated length or size also matter. So, replace functions like:

void read_into(int* buffer, size_t buffer_size);

with:

void read_into(span<int> buffer);

Why should I use it? Why is it a good thing?

Using a span means that you can work with that pointer+length / start+end pointer combination like you would with
a standard library container:

for (auto& x : my_span) {}
std::find_if(my_span.cbegin(), my_span.cend(), some_predicate);
std::ranges::find_if(my_span, some_predicate);

Spans let the compiler do more work for you sometimes. For example, this:

int buffer[BUFFER_SIZE];
read_into(buffer, BUFFER_SIZE);

becomes this:

int buffer[BUFFER_SIZE];
read_into(buffer);

It's the reasonable alternative to passing const vector<T>& to functions when you expect your data to be contiguous in memory.
It facilitates static analysis, so the compiler might be able to help you catch silly bugs.
Indicates that your code (that's using the span) doesn't own the pointed-to memory.
*/

/***************************************************************************************************************/

// std::mdspan is a non-owning view into a contiguous sequence of objects that reinterprets it as a multidimensional array.


void test_mdspan() {
  std::vector v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};

  // View data as contiguous memory representing 2 rows of 6 ints each
  auto ms2 = std::mdspan(v.data(), 2, 6);
  // View the same data as a 3D array 2 x 3 x 2
  auto ms3 = std::mdspan(v.data(), 2, 3, 2);

  // write data using 2D view
  for (size_t i = 0; i != ms2.extent(0); i++) {
    for (size_t j = 0; j != ms2.extent(1); j++) {
      ms2[i, j] = i * 1000 + j;
    }
  }

  // read back using 3D view
  for (size_t i = 0; i != ms3.extent(0); i++) {
    std::println("slice @ i = {}", i);
    for (size_t j = 0; j != ms3.extent(1); j++) {
      for (size_t k = 0; k != ms3.extent(2); k++) {
        std::print("{} ", ms3[i, j, k]);
      }
      std::println("");
    }
  }
}

/***************************************************************************************************************/

// std::string_view


static int alloc_times = 0;
void* operator new(size_t n) {
  ++alloc_times;
  std::cout << "Allocating of a size " << n << std::endl;
  return malloc(n);
}

void test_string_view() {
  std::string s {"qunem lavt ay chatlax bozi txa"}; // allocation

  std::string s1 = s.substr(0, 20); // allocation
  std::string s2 = s;               // allocation

  std::string_view sv1 = s.substr(0, 20); // no allocation
  std::string_view sv2 = s;               // no allocation
}

/***************************************************************************************************************/

// std::clamp

template<class T>
constexpr const T& clamp( const T& v, const T& lo, const T& hi );

template<class T, class Compare>
constexpr const T& clamp( const T& v, const T& lo, const T& hi, Compare comp );

/*
1) If v compares less than lo, returns lo; otherwise if hi compares less than v, returns hi; otherwise returns v.
 Uses operator< to compare the values.
2) Same as (1), but uses comp to compare the values.
The behavior is undefined if the value of lo is greater than hi.
*/

template<class T>
constexpr const T& clamp( const T& v, const T& lo, const T& hi )
{
    return clamp(v, lo, hi, less{});
}

template<class T, class Compare>
constexpr const T& clamp( const T& v, const T& lo, const T& hi, Compare comp )
{
    return comp(v, lo) ? lo : comp(hi, v) ? hi : v;
}

/*
Clamps a variable to a given range[high – low].
If num > high, num is assigned high.
If num < low, num is assigned low.
If num is already clamped, no modifications.
*/

/***************************************************************************************************************/

// Inline Variable In C++17
/*

1) makes a global variable unique to all compilation units if included in different cpp files

2) in a class it's not allowed to initialize static variable

class A {
  static int i = 0; // error
};

needs to be defined outside

int A::i = 0;

inline fixes the problem

class A {
  static inline int i = 0; // no error
};

*/

/***************************************************************************************************************/


int main() {

}
