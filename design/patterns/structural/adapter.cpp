/*

The Adapter pattern is a structural pattern that allows two incompatible interfaces to work together
by wrapping an object with a new interface that is compatible with one or both of the existing interfaces.
This pattern is useful when you want to reuse existing code with a system that expects a different interface.

Adapter is a structural design pattern that allows objects with incompatible interfaces to collaborate.


Problem
Imagine that you’re creating a stock market monitoring app. The app downloads the stock data from multiple sources
in XML format and then displays nice-looking charts and diagrams for the user.

At some point, you decide to improve the app by integrating a smart 3rd-party analytics library.
But there’s a catch: the analytics library only works with data in JSON format.

You could change the library to work with XML. However, this might break some existing code that relies on the library.
And worse, you might not have access to the library’s source code in the first place, making this approach impossible.

Solution
You can create an adapter. This is a special object that converts the interface of one object so that another object can understand it.

An adapter wraps one of the objects to hide the complexity of conversion happening behind the scenes.
The wrapped object isn’t even aware of the adapter. For example, you can wrap an object that operates
in meters and kilometers with an adapter that converts all of the data to imperial units such as feet and miles.

Adapters can not only convert data into various formats but can also help objects with different interfaces collaborate.
Here’s how it works:

1) The adapter gets an interface, compatible with one of the existing objects.
2) Using this interface, the existing object can safely call the adapter’s methods.
3) Upon receiving a call, the adapter passes the request to the second object, but in a format and order that the second object expects.

*/


#include <iostream>
#include <string>

// Adaptee interface
class Adaptee {
public:
    virtual std::string specificRequest() const {
        return "Adaptee request";
    }
    virtual ~Adaptee() {}
};

// Target interface
class Target {
public:
    virtual std::string request() const = 0;
    virtual ~Target() {}
};

// Adapter
class Adapter : public Target {
private:
    Adaptee* adaptee;

public:
    Adapter(Adaptee* adaptee) : adaptee(adaptee) {}

    std::string request() const override {
        return "Adapter: " + adaptee->specificRequest();
    }
};

int main() {
    Adaptee* adaptee = new Adaptee();
    Target* target = new Adapter(adaptee);

    std::cout << target->request() << std::endl;

    delete adaptee;
    delete target;

    return 0;
}

/*

In this example, we have an Adaptee class that defines an interface that is incompatible with the Target interface.
We also have a Target interface that our client code expects to use.

We then create an Adapter class that implements the Target interface and wraps an Adaptee object.
The Adapter class provides a bridge between the Target and Adaptee interfaces by translating the calls from the Target
interface to the Adaptee interface.

In the main() function, we create an Adaptee object and wrap it with an Adapter object.
We then call the request() method on the Target interface, which is implemented by the Adapter class,
and it returns a string that includes the specificRequest() method of the Adaptee object.

This example demonstrates how the Adapter pattern can be used to adapt an incompatible
interface to a compatible one by wrapping the incompatible object with an adapter object.
The client code can then use the adapter object as if it were a compatible object.

*/
