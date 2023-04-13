/*

The Proxy pattern is a structural design pattern that provides a surrogate or placeholder
for another object to control access to it. In this pattern, a proxy object is created that behaves
like the original object and can be used as a substitute for it.

The main purpose of the proxy is to control access to the original object,
either by providing additional functionality, or by restricting access to it.

Proxy is a structural design pattern that lets you provide a substitute or placeholder for another object.
A proxy controls access to the original object, allowing you to perform something either
before or after the request gets through to the original object.

Problem
Why would you want to control access to an object?
Here is an example: you have a massive object that consumes a vast amount of system resources.
You need it from time to time, but not always.

You could implement lazy initialization: create this object only when it’s actually needed.
All of the object’s clients would need to execute some deferred initialization code.
Unfortunately, this would probably cause a lot of code duplication.

In an ideal world, we’d want to put this code directly into our object’s class,
but that isn’t always possible. For instance, the class may be part of a closed 3rd-party library.

Solution
The Proxy pattern suggests that you create a new proxy class with the same interface as an original service object.
Then you update your app so that it passes the proxy object to all of the original object’s clients.
Upon receiving a request from a client, the proxy creates a real service object and delegates all the work to it.

But what’s the benefit? If you need to execute something either before or after the primary logic of the class,
the proxy lets you do this without changing that class. Since the proxy implements the same interface as the original class,
it can be passed to any client that expects a real service object.

*/

#include <iostream>
#include <string>

// The Subject interface declares common operations for both RealSubject and the Proxy.
// As long as the client works with RealSubject using this interface,
// you'll be able to pass it a proxy instead of a real subject.

class Subject {
public:
    virtual void request() const = 0;
};


// The RealSubject contains some core business logic. Usually, RealSubjects are capable of doing
// some useful work which may also be very slow or sensitive -

class RealSubject : public Subject {
public:
    void request() const override {
        std::cout << "RealSubject: Handling request." << std::endl;
    }
};


// The Proxy has an interface identical to the RealSubject.

class Proxy : public Subject {
private:
    RealSubject* real_subject;

    bool checkAccess() const {
        // Some real checks should go here.
        std::cout << "Proxy: Checking access prior to firing a real request." << std::endl;
        return true;
    }
    void logAccess() const {
        std::cout << "Proxy: Logging the time of request." << std::endl;
    }

    // The Proxy maintains a reference to an object of the RealSubject class.
    //It can be either lazy-loaded or passed to the Proxy by the client.

public:
    Proxy(RealSubject* rs) : real_subject(new RealSubject(*rs)) {}

    ~Proxy() {
        delete real_subject;
    }

    //The most common applications of the Proxy pattern are lazy loading, 
    // caching, controlling the access, logging, etc. A Proxy can perform one of
    // these things and then, depending on the result, pass the execution to the
    // same method in a linked RealSubject object.

    void request() const override {
        if (checkAccess()) {
            real_subject->request();
            logAccess();
        }
    }
};

// The client code is supposed to work with all objects (both subjects and proxies)
//via the Subject interface in order to support both real subjects and proxies.
// In real life, however, clients mostly work with their real subjects directly.
// In this case, to implement the pattern more easily, you can extend your proxy from the real subject's class.

void ClientCode(const Subject& subject) {
    subject.request();
}

int main() {
    std::cout << "Client: Executing the client code with a real subject:" << std::endl;
    RealSubject* real_subject = new RealSubject;
    ClientCode(*real_subject);
    std::cout << "Client: Executing the same client code with a proxy:" << std::endl;
    Proxy* proxy = new Proxy(real_subject);
    ClientCode(*proxy);

    delete real_subject;
    delete proxy;
    return 0;
}


/*

In this example, the RealSubject class is the class that we want to control access to,
and the Proxy class is the surrogate that we will use to access it.
The Proxy class has a request() method that behaves like the request() method of the RealSubject class,
but also has additional functionality to control access.


The proxy can provide additional functionality (e.g. logging, caching, security checks) or restrict access
to the original object (e.g. by only allowing access to certain methods or properties).

*/
