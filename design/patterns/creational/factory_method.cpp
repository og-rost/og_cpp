/*

The Factory Method is a creational pattern that defines an interface for creating objects,
but allows subclasses to decide which class to instantiate.
This allows for greater flexibility and extensibility in object creation.

Defines an interface for creating objects, but let subclasses to decide which class to instantiate.

Client <--> Shape Factory --> Square Factory, Rectangle Factory --> Square, Rectangle

Factory Method is a creational design pattern that provides an interface for creating objects in a superclass,
but allows subclasses to alter the type of objects that will be created.

Problem
Imagine that you’re creating a logistics management application. The first version of your app can only handle transportation by trucks,
so the bulk of your code lives inside the Truck class.

After a while, your app becomes pretty popular. Each day you receive dozens of requests from
sea transportation companies to incorporate sea logistics into the app.

At present, most of your code is coupled to the Truck class. Adding Ships into the app would require making changes to the entire codebase.
Moreover, if later you decide to add another type of transportation to the app, you will probably need to make all of these changes again.

As a result, you will end up with pretty nasty code, riddled with conditionals that switch the app’s behavior depending
on the class of transportation objects.

Solution
The Factory Method pattern suggests that you replace direct object construction calls (using the new operator)
with calls to a special factory method. The objects are still created via the new operator, but it’s being called from within the factory method.
Objects returned by a factory method are often referred to as products.

At first glance, this change may look pointless: we just moved the constructor call from one part of the program to another.
However, consider this: now you can override the factory method in a subclass and change the class of products being created by the method.

There’s a slight limitation though: subclasses may return different types of products only if these products have a common base class or interface.
Also, the factory method in the base class should have its return type declared as this interface.

The code that uses the factory method (often called the client code) doesn’t see a difference between the actual products returned by various subclasses.
The client treats all the products as abstract Transport. The client knows that all transport objects are supposed to have the deliver method, but exactly
how it works isn’t important to the client.


*/

#include <iostream>

// Abstract shape
class Shape {
public:
    virtual void draw() = 0;
};

// Concrete shape 1
class Rectangle : public Shape {
public:
    void draw() override {
        std::cout << "Inside Rectangle::draw() method" << std::endl;
    }
};

// Concrete shape 2
class Square : public Shape {
public:
    void draw() override {
        std::cout << "Inside Square::draw() method" << std::endl;
    }
};

// Abstract Factory
class ShapeFactory {
public:
    virtual Shape* createShape() const = 0;
};

// Concrete Factory 1
class SquareFactory : public ShapeFactory {
public:
    Shape* createShape() const override {
        return new Square();
    }
};

// Concrete Factory 2
class RectangleFactory : public ShapeFactory {
public:
    Shape* createShape() const override {
        return new Rectangle();
    }
};

int main() {
    ShapeFactory* squareFactory = new SquareFactory(); 
    Shape* square = squareFactory->createShape(); // Create square
    square->draw();

    ShapeFactory* rectangleFactory = new RectangleFactory(); 
    Shape* rectangle = rectangleFactory->createShape(); // Create rectangle
    rectangle->draw();

    return 0;
}