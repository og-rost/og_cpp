/*

Simple Factory

Factory pattern (simple factory) is a creational pattern as this pattern provides one of the best ways to create an object.
Creates objects without exposing the instantiation logic to the client.

Client <--> Factory --> Square, Rectangle

*/

#include <iostream>

class Shape {
public:
    virtual void draw() = 0;
};

class Rectangle : public Shape {
public:
    void draw() override {
        std::cout << "Inside Rectangle::draw() method" << std::endl;
    }
};

class Square : public Shape {
public:
    void draw() override {
        std::cout << "Inside Square::draw() method" << std::endl;
    }
};

class SimpleFactory {
public:
    Shape* CreateSquare() {
        return new Square();
    }

    Shape* CreateRectangle() {
        return new Rectangle();
    }
};


int main() {
    SimpleFactory* simpleFactory = new SimpleFactory();
    Shape* square = simpleFactory->CreateSquare(); // Create square
    square->draw();
    Shape* rectangle = simpleFactory->CreateRectangle(); // Create rectangle
    rectangle->draw();

    return 0;
}