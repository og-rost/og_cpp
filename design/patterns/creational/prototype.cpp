/*

Prototype is a creational design pattern that lets you copy existing objects without making your code dependent on their classes.


Problem
Say you have an object, and you want to create an exact copy of it. 
First, you have to create a new object of the same class.
Then you have to go through all the fields of the original object and copy their values over to the new object.

But there’s a catch. Not all objects can be copied.
Copying an object “from the outside” isn’t always possible.

There’s one more problem with the direct approach. Since you have to know the object’s class to create a duplicate,
your code becomes dependent on that class. If the extra dependency doesn’t scare you, there’s another catch.
Sometimes you only know the interface that the object follows, but not its concrete class, when.

Solution
The Prototype pattern delegates the cloning process to the actual objects that are being cloned.
The pattern declares a common interface for all objects that support cloning.
This interface lets you clone an object without coupling your code to the class of that object.
Usually, such an interface contains just a single clone method.

The implementation of the clone method is very similar in all classes. The method creates an object of the current class and
carries over all of the field values of the old object into the new one.

An object that supports cloning is called a prototype. When your objects have dozens of fields and hundreds of possible configurations,
cloning them might serve as an alternative to subclassing.



Here’s how it works:
you create a set of objects, configured in various ways. When you need an object like the one you’ve configured,
you just clone a prototype instead of constructing a new object from scratch.


*/


#include <string>
#include <iostream>

// Prototype Design Pattern: Lets you copy existing objects without making your code dependent on their classes.


class Prototype {
protected:
    std::string name;
    float field;

public:
    Prototype() {}
    Prototype(std::string n) : name(n) {}
    virtual ~Prototype() {}
    virtual Prototype* Clone() const = 0;
    virtual void Method(float f) {
        field = f;
        std::cout << "Call Method from " << name << " with field : " << field << std::endl;
    }
};


// ConcretePrototype1 is a Sub-Class of Prototype and implement the Clone Method


class ConcretePrototype1 : public Prototype {
private:
    float field1;

public:
    ConcretePrototype1(std::string name, float f1) : Prototype(name), field1(f1) {}

    Prototype* Clone() const override {
        return new ConcretePrototype1(*this);
    }
};

class ConcretePrototype2 : public Prototype {
private:
    float field2;

public:
    ConcretePrototype2(std::string prototype_name, float f2) : Prototype(prototype_name), field2(f2) {}
    Prototype* Clone() const override {
        return new ConcretePrototype2(*this);
    }
};

// In PrototypeFactory you have two concrete prototypes, one for each concrete prototype class
// so each time you want to create a bullet, you can use the existing ones and clone those.


class PrototypeFactory {
private:
    ConcretePrototype1* type1 = nullptr;
    ConcretePrototype2* type2 = nullptr;

public:
    PrototypeFactory() {
        type1 = new ConcretePrototype1("PROTOTYPE_1 ", 50.f);
        type2 = new ConcretePrototype2("PROTOTYPE_2 ", 60.f);
    }

    ~PrototypeFactory() {
        delete type1;
        delete type2;
        // or better: use smart pointers
    }

    Prototype* CreatePrototype(bool b) {
        if (b) {
            return type1->Clone();
        } else {
            return type2->Clone();
        }
    }
};

void Client(PrototypeFactory &prototype_factory) {
    std::cout << "Let's create a Prototype 1" << std::endl;

    Prototype* prototype = prototype_factory.CreatePrototype(true);
    prototype->Method(90);
    delete prototype;

    std::cout << "Let's create a Prototype 2" << std::endl;

    prototype = prototype_factory.CreatePrototype(false);
    prototype->Method(10);

    delete prototype;
}

int main() {
    PrototypeFactory* prototype_factory = new PrototypeFactory();
    Client(*prototype_factory);
    delete prototype_factory;

    return 0;
}