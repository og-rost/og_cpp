#include <iostream>
#include <vector>

template <typename T>
class shared_ptr {
public:
    shared_ptr(T*);
    shared_ptr(const shared_ptr&);
    shared_ptr& operator= (const shared_ptr&);
    shared_ptr& operator= (T*);
    ~shared_ptr();
    size_t get_count() const;
    T& operator*();
    T* operator->();
private:
    T* data;
    size_t* ref;
    void clear();
};

template <typename T>
void shared_ptr<T>::clear() {
    --*ref;
    if (*ref == 0) {
        delete data;
        delete ref;
    }
}

template <typename T>
shared_ptr<T>::shared_ptr(T* ptr = nullptr) : data(ptr) {
    if (data)
        ref = new size_t(1);
    else ref = new size_t(0);
}

    template <typename T>
shared_ptr<T>::shared_ptr(const shared_ptr<T>& rhs) 
    : data(rhs.data), ref(rhs.ref) {
        ++*ref;
    }

template <typename T>
shared_ptr<T>::~shared_ptr() {
    clear();
}

template <typename T>
shared_ptr<T>& shared_ptr<T>::operator= (const shared_ptr<T>& rhs) {
    clear();
    data = rhs.data;
    ref = rhs.ref;
    ++*ref;
    return *this;
}

template <typename T>
shared_ptr<T>& shared_ptr<T>::operator= (T* ptr) {
    clear();
    data = ptr;
    if(data) ref = new size_t(1);
    else ref = new size_t(0);
    return *this;
}

template <typename T>
size_t shared_ptr<T>::get_count() const {
    return *ref;
}

template <typename T>
T& shared_ptr<T>::operator*() {
    if (data)
        return *data;
}

template <typename T>
T* shared_ptr<T>::operator->() {
    if (data)
        return data;
}

struct a {
    void f() {
        std::cout<<"yeah"<<std::endl;
    }
};

int main() {
    shared_ptr<int> p = new int(42);
    std::cout << p.get_count() << std::endl;
    std::cout << *p << std::endl;

    shared_ptr<std::vector<int>> pp = new std::vector <int>;
    pp->push_back(42);


    p = new int(52);
    std::cout << p.get_count() << std::endl;
    std::cout << *p << std::endl;

    shared_ptr<int> p2 = p;
    std::cout << p.get_count() << std::endl;
    std::cout << p2.get_count() << std::endl;

    p2 = nullptr;
    std::cout << p.get_count() << std::endl;
    std::cout << p2.get_count() << std::endl;
    shared_ptr<a> pa = new a();
    pa->f();

    return 0;
}

