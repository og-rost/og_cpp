/*

In C++, a template is a generic blueprint for creating types or functions that can be instantiated with different arguments.
There are three types of templates in C++: primary templates, template specializations, and partial specializations.

A primary template is the basic template definition that provides the generic blueprint for creating types or functions.
It's the template that is defined first and doesn't have any template arguments specialized.
Primary templates are used as a fallback when there is no specialized version available for a particular set of arguments.

*/

/*

In C++, there are two types of template specializations: explicit specializations and partial specializations.

An explicit specialization provides a specialized version of a template for a specific set of template arguments.
It's used to completely override the behavior of the primary template for a specific case.
An explicit specialization is defined using the template<> syntax followed by the specialization of the template parameters.

A partial specialization provides a specialized version of a template for a subset of template arguments that match a specific pattern.
It's used to specialize a template for a more specific case than the primary template, but not as specific as an explicit specialization.
A partial specialization is defined using the template<typename T1, typename T2> syntax followed
by a specialization that matches a pattern of the template parameters.

*/

#include <iostream>

// Primary template
template <typename T>
class MyTemplate {
public:
    void foo() {
        std::cout << "MyTemplate<T>::foo()" << std::endl;
    }
};

// Explicit specialization for int type
template <>
class MyTemplate<int> {
public:
    void foo() {
        std::cout << "MyTemplate<int>::foo()" << std::endl;
    }
};

// Partial specialization for pointer type
template <typename T>
class MyTemplate<T*> {
public:
    void foo() {
        std::cout << "MyTemplate<T*>::foo()" << std::endl;
    }
};

int main() {
    MyTemplate<float> obj1;
    obj1.foo(); // Output: MyTemplate<T>::foo()

    MyTemplate<int> obj2;
    obj2.foo(); // Output: MyTemplate<int>::foo()

    MyTemplate<int*> obj3;
    obj3.foo(); // Output: MyTemplate<T*>::foo()

    return 0;
}
