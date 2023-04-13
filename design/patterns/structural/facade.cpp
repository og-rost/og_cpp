/*

The Facade pattern is a structural pattern that provides a simplified interface to a complex system,
making it easier to use and understand. It defines a higher-level interface that makes the subsystem
easier to use by hiding its complexity.

Facade is a structural design pattern that provides a simplified interface to a library,
a framework, or any other complex set of classes.

Problem
Imagine that you must make your code work with a broad set of objects that belong to a sophisticated library or framework.
Ordinarily, you’d need to initialize all of those objects, keep track of dependencies, execute methods in the correct order, and so on.

As a result, the business logic of your classes would become tightly coupled to the implementation details of 3rd-party classes,
making it hard to comprehend and maintain.

Solution
A facade is a class that provides a simple interface to a complex subsystem which contains lots of moving parts.
A facade might provide limited functionality in comparison to working with the subsystem directly.
However, it includes only those features that clients really care about.

Having a facade is handy when you need to integrate your app with a sophisticated library that has dozens of features,
but you just need a tiny bit of its functionality.

For instance, an app that uploads short funny videos with cats to social media could potentially use a professional video conversion library.
However, all that it really needs is a class with the single method encode(filename, format).
After creating such a class and connecting it with the video conversion library, you’ll have your first facade.

*/

#include <string>
#include <iostream>

class Subsystem1 {
public:
    std::string operation1() const {
        return "Subsystem1: Ready!\n";
    }

    std::string operationN() const {
        return "Subsystem1: Go!\n";
    }
};

class Subsystem2 {
public:
    std::string operation1() const {
        return "Subsystem2: Get ready!\n";
    }
    std::string operationZ() const {
        return "Subsystem2: Fire!\n";
    }
};

class Facade {
protected:
    Subsystem1* subsystem1;
    Subsystem2* subsystem2;
public:
    Facade(Subsystem1* s1 = nullptr, Subsystem2* s2 = nullptr) {
        subsystem1 = s1 ? : new Subsystem1;
        subsystem2 = s2 ? : new Subsystem2;
    }
    ~Facade() {
        delete subsystem1;
        delete subsystem2;
    }

    std::string operation() {
        std::string result = "Facade initializes subsystems:\n";
        result += subsystem1->operation1();
        result += subsystem2->operation1();
        result += "Facade orders subsystems to perform the action:\n";
        result += subsystem1->operationN();
        result += subsystem2->operationZ();
        return result;
    }
};


void ClientCode(Facade* facade) {
    std::cout << facade->operation() << std::endl;
}


int main() {
    Subsystem1* subsystem1 = new Subsystem1;
    Subsystem2* subsystem2 = new Subsystem2;
    Facade* facade = new Facade(subsystem1, subsystem2);
    ClientCode(facade);

    delete facade;

    return 0;
}

/*

We create a Facade class that acts as a simplified interface to the complex subsystem.
The Facade class knows which subsystem classes are responsible for which operations,
and it delegates the work to them.

In the main() function, we create a Facade object and call its operation() method.
The Facade object then calls the appropriate methods on the subsystem classes to perform the desired operations.

This example demonstrates how the Facade pattern can be used to provide a simplified interface
to a complex subsystem. The client code does not need to know the details of the subsystem
classes or their operations. Instead, it can use the Facade class to perform the desired operations.

*/
