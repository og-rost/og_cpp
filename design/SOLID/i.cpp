/*

The Interface Segregation Principle (ISP) is a principle of object-oriented design that states that clients should not be forced
to depend on interfaces they do not use. In other words, classes should be designed with narrowly focused interfaces
that are specific to the needs of the client code.

*/

#include <iostream>

class IShape {
public:
    virtual void draw() = 0;
    virtual void rotate() = 0;
};

class Circle : public IShape {
public:
    void draw() override {
        std::cout << "Drawing circle" << std::endl;
    }

    void rotate() override {
        std::cout << "Rotating circle" << std::endl;
    }
};

class Square : public IShape {
public:
    void draw() override {
        std::cout << "Drawing square" << std::endl;
    }

    void rotate() override {
        std::cout << "Rotating square" << std::endl;
    }
};

class ShapeManager {
public:
    void drawShapes(IShape** shapes, int count) {
        for (int i = 0; i < count; i++) {
            shapes[i]->draw();
        }
    }

    void rotateShapes(IShape** shapes, int count) {
        for (int i = 0; i < count; i++) {
            shapes[i]->rotate();
        }
    }
};


/*

ShapeManager class violates the Interface Segregation Principle because it depends on both the draw() and rotate() methods of the IShape interface,
even though the drawShapes() and rotateShapes() methods have different responsibilities. This means that any class that depends on ShapeManager
must also depend on both the draw() and rotate() methods, even if it only needs one of them.

To adhere to the Interface Segregation Principle, we could create separate interfaces for the draw() and rotate() methods,
and have the Circle and Square classes implement only the methods they need. Then, the ShapeManager class could depend
on the appropriate interface(s) for the methods it needs, without forcing client code to depend on unnecessary methods.

*/


// example 2


class Vehicle1 {
    virtual void setPrice(double price) = 0;
    virtual void setColor(double color) = 0;
    virtual void start() = 0;
    virtual void stop() = 0;
    virtual void fly() = 0;
};

// instead we can have

class Vehicle {
    virtual void setPrice(double price) = 0;
    virtual void setColor(double color) = 0;
};


class Movable {
    virtual void start() = 0;
    virtual void stop() = 0;
};

class Flyable {
    virtual void fly() = 0;
};

// Car will implement Vehicle and Moveable
// Plane will implement all 3 interfaces

int main() {
    return 0;
}