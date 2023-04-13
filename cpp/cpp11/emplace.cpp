class MyKlass {
public:
    MyKlass(int ii_, float ff_) {}
};

int main() {
    std::vector<MyKlass> v;
    v.push_back(MyKlass(2, 3.14f));
    v.emplace_back(2, 3.14f);

    return 0;
}

/*
push_back calls:

Constructor for a temporary MyKlass object
Move constructor (if one was defined for MyKlass, otherwise a copy constructor) for the object actually allocated inside the vector
Destructor for the temporary

there's no reason to create and destroy a temporary - why not just construct the object inside the vector directly

For the v.emplace_back(2, 3.14f) call above, we have a single constructor invocation. This is the object constructed
inside the vector. No temporaries are needed. emplace_back accomplishes this by invoking the constructor of MyKlass on
its own and forwarding its arguments to the constructor.
This is made possible by two new features in C++11: variadic templates and perfect forwarding.
*/

/*==========================================
Perfect forwarding problem

Let func(E1, E2, ..., En) be an arbitrary function call with generic parameters E1, E2, ..., En.
We'd like to write a function wrapper such that wrapper(E1, E2, ..., En) is equivalent to func(E1, E2, ..., En).

pre-11 C++

the first logical approach is
*/

template <typename T1, typename T2>
void wrapper(T1 e1, T2 e2) {
    func(e1, e2);
}

/*
This will obviously not work if func accepts its parameters by reference, since wrapper introduces
a by-value passing step. If func modifies its by-reference parameter, it won't be visible in the caller of wrapper.

we change to
*/

template <typename T1, typename T2>
void wrapper(T1& e1, T2& e2) {
    func(e1, e2);
}

/*
This should not interfere with func's taking parameters by value,
because the call to func within wrapper will create the required copy.

This has another problem, though. Rvalues cannot be bound to function parameters that are references.

wrapper(42, 3.14f); // error

Making those reference parameters const won't cut it either, because func may want to accept non-const reference parameters.

What remains is the brute-force approach taken by some libraries: define overloads for both const and non-const references:
*/

template <typename T1, typename T2>
void wrapper(T1& e1, T2& e2) { func(e1, e2); }

template <typename T1, typename T2>
void wrapper(const T1& e1, T2& e2) { func(e1, e2); }

template <typename T1, typename T2>
void wrapper(T1& e1, const T2& e2) { func(e1, e2); }

template <typename T1, typename T2>
void wrapper(const T1& e1, const T2& e2) { func(e1, e2); }

// To make things worse, C++11 adds rvalue references to the mix and this clearly isn't a scalable solution.

/*==========================================

Taking a reference to a reference is illegal in C++.
However, it can sometimes arise in the context of templates and type deduction.
*/

template <typename T>
void baz(T t) {
    T &k = t;
}

int ii = 4;
baz<int&>(ii);

/*
What the compiler "sees" as the type of k is int& & - while this isn't something the user
is allowed to write, the compiler simply infers a single reference from this.

Prior to C++11 this wasn't standardized, but many compilers accepted such code anyway because
these cases occasionally arise in template metaprogramming.
With the addition of rvalue references in C++11, it became important to define what happens
when various reference types collapse.

The result is the reference collapsing rule. The rule is very simple. & always wins.
So & & is &, and so are && & and & &&. The only case where && emerges from collapsing is && &&.
You can think of it as a logical-OR, with & being 1 and && being 0.
*/

//==========================================

// special type deduction rules for rvalue references

template <class T>
void func(T&& t) {}

func(4); // 4 is an rvalue: T deduced to int

double d = 3.14;
func(d); // d is an lvalue; T deduced to double&

float f() {}
func(f()); // f() is an rvalue; T deduced to float

int bar(int i) {
    func(i); // i is an lvalue; T deduced to int&
}

/*==========================================

Solving perfect forwarding with std::forward

The original wrapper template should be written in C++11 the following way:
*/

template <typename T1, typename T2>
void wrapper(T1&& e1, T2&& e2) {
    func(forward<T1>(e1), forward<T2>(e2));
}

// And this is forward:

template <class T>
T&& forward(typename std::remove_reference<T>::type& t) noexcept {
    return static_cast<T&&>(t);
}

template <class T>
T&& forward(typename std::remove_reference<T>::type&& t) noexcept {
    return static_cast<T&&>(t);
}

/*Let's say we call:

int ii ...;
float ff ...;
wrapper(ii, ff);

Examining the first argument: ii is an lvalue, so T1 is deduced to int& following the special deduction rules.
We get the call func(forward<int&>(e1), ...).
Therefore, forward is instantiated with int& and we get this version of it:
*/

int& && forward(int& t) noexcept {
    return static_cast<int& &&>(t);
}

// Now it's time to apply the reference collapsing rule:

int& forward(int& t) noexcept {
    return static_cast<int&>(t);
}

/*In other words, the argument is passed on by reference to func, as needed for lvalues.

The other case to handle is:

wrapper(42, 3.14f);
Here the arguments are rvalues, so T1 is deduced to int.
We get the call func(forward<int>(e1), ...). Therefore, forward is instantiated with int and we get this version of it [3]:
*/

int&& forward(int&& t) noexcept {
    return static_cast<int&&>(t);
}

/*
One can see forward as a pretty wrapper around static_cast<T&&>(t) when T can be deduced to either U& or U&&,
depending on the kind of argument to the wrapper (lvalue or rvalue).
Now we get wrapper as a single template that handles all kinds of forwarding cleanly.

The forward template exists in C++11, in the <utility> header, as std::forward.

The use of std::remove_reference<T>.
In fact, forward could do without it. Reference collapsing does the job already, so std::remove_reference<T> is superfluous.
It's there to turn the T& t into a non-deducing context, thus forcing us to explicitly specify the template
parameter when calling std::forward.
*/

//==========================================

// Examples of using perfect forwarding

template <typename T, typename... Args>
unique_ptr<T> make_unique(Args&&...args) {
    return unique_ptr<T>(new T(std::forward<Args>(args)...));
}
