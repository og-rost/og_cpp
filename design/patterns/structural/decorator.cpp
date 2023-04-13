/*

The Decorator pattern is a structural pattern that allows objects to dynamically add or modify
behavior at runtime without affecting other objects of the same class.
This is achieved by wrapping an object inside a decorator object that provides additional functionality,
while still maintaining the same interface as the original object.

Decorator is a structural design pattern that lets you attach new behaviors to objects
by placing these objects inside special wrapper objects that contain the behaviors.

*/


#include <iostream>
#include <string>

// Abstract Component
class Component {
public:
    virtual std::string operation() const = 0;
    virtual ~Component() {}
};

// Concrete Component
class ConcreteComponent : public Component {
public:
    std::string operation() const override {
        return "ConcreteComponent";
    }
};

// Abstract Decorator
class Decorator : public Component {
protected:
    Component* component;

public:
    Decorator(Component* component) : component(component) {}
    virtual ~Decorator() {}

    std::string operation() const override {
        return component->operation();
    }
};

// Concrete Decorator A
class ConcreteDecoratorA : public Decorator {
public:
    ConcreteDecoratorA(Component* component) : Decorator(component) {}

    std::string operation() const override {
        return "ConcreteDecoratorA(" + Decorator::operation() + ")";
    }
};

// Concrete Decorator B
class ConcreteDecoratorB : public Decorator {
public:
    ConcreteDecoratorB(Component* component) : Decorator(component) {}

    std::string operation() const override {
        return "ConcreteDecoratorB(" + Decorator::operation() + ")";
    }
};

int main() {
    // create a ConcreteComponent object
    Component* component = new ConcreteComponent();

    // wrap the object with a ConcreteDecoratorA object
    component = new ConcreteDecoratorA(component);

    // wrap the object with a ConcreteDecoratorB object
    component = new ConcreteDecoratorB(component);

    // call the operation() method on the decorated object
    std::cout << component->operation() << std::endl;

    // clean up
    delete component;

    return 0;
}


/*

In this example, we have two concrete decorator classes, ConcreteDecoratorA and ConcreteDecoratorB,
that add different types of behavior to the decorated object.

In the main() function, we create a ConcreteComponent object and wrap it with two decorator objects
(ConcreteDecoratorA and ConcreteDecoratorB) to add behavior to it.
We then call the operation() method on the decorated object, which returns a string that includes
the names of all the decorators applied to it.

This example demonstrates how the Decorator pattern can be used to add behavior to an object at runtime,
without affecting other objects of the same class. It also shows how decorators can be stacked on top of each other
to create complex combinations of behavior.

*/