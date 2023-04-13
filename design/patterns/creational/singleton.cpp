/*

The Singleton design pattern is a creational pattern that ensures that only one instance of a class
is created and provides a global point of access to it. This can be useful in situations where there
should only be one instance of a class, such as a configuration manager or a logging system.

Singleton is a creational design pattern that lets you ensure that a class has only one instance,
while providing a global access point to this instance.

The Singleton pattern solves two problems at the same time, violating the Single Responsibility Principle:

1) Ensure that a class has just a single instance.
The most common reason for this is to control access to some shared resource—for example, a database or a file.

2) Provide a global access point to that instance.
The global variables are very handy, but also very unsafe since any code can potentially overwrite the contents of those variables.

Just like a global variable, the Singleton pattern lets you access some object from anywhere in the program.
However, it also protects that instance from being overwritten by other code.

There’s another side to this problem: you don’t want the code that solves problem #1 to be scattered all over your program.
It’s much better to have it within one class, especially if the rest of your code already depends on it.

*/

#include <iostream>
#include <mutex>
#include <string>
#include <thread>

class Singleton {
private:
    static Singleton* instance; // the one and only instance of the class
    static std::mutex mtx;
protected:
    Singleton(const std::string v): value(v) {}
    ~Singleton() {}
    std::string value;
public:
    Singleton(const Singleton&) = delete;
    void operator=(const Singleton&) = delete;

    std::string getValue() const{
        return value;
    } 

    static Singleton* getInstance(const std::string& value) {
        std::lock_guard<std::mutex> lock(mtx);
        if (instance == nullptr) { // if there is no instance yet
            instance = new Singleton(value); // create a new instance
        }
        return instance; // return the one and only instance
    }
};

Singleton* Singleton::instance = nullptr; // initialize instance to nullptr
std::mutex Singleton::mtx;


void ThreadFoo(){
    // Following code emulates slow initialization.
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    Singleton* singleton = Singleton::getInstance("FOO");
    std::cout << singleton->getValue() << "\n";
}

void ThreadBar(){
    // Following code emulates slow initialization.
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    Singleton* singleton = Singleton::getInstance("BAR");
    std::cout << singleton->getValue() << "\n";
}

int main() {
    std::cout << "If you see the same value, then singleton was reused!" << std::endl; 
    std::thread t1(ThreadFoo);
    std::thread t2(ThreadBar);
    t1.join();
    t2.join();
    return 0;
}
