/*

The Liskov Substitution Principle states that objects of a superclass should be able to be replaced with objects of a subclass
without affecting the correctness of the program. In other words, a subclass should be substitutable for its superclass without
breaking the program's behavior.

To adhere to the Liskov Substitution Principle, subclasses must adhere to the same contracts and invariants as their parent class.
This means that a subclass should implement all the methods of the parent class and that these methods should behave in the same way
as the parent class's methods. Additionally, any preconditions of the parent class's methods should be preserved by the subclass's methods.


The Liskov substitution principle (LSP) is a particular definition of a subtyping relation, called strong behavioral subtyping.
It is based on the concept of "substitutability" – a principle in object-oriented programming stating that an object may be replaced
by a sub-object without breaking the program.


behavioral subtyping (is-a relationship)

1) contravariance of method arguments in subtype
2) covariance of return types in subtype
3) preconditions cannot be strengthened in subtype
4) postconditions cannot be weakened in subtype
5) invariants of the super type must be preserved in a subtype

*/

// example that violates the Liskov Substitution Principle

#include <cassert>
#include <iostream>
#include <exception>

class Rectangle {
public:
    Rectangle(double width, double height) : width(width), height(height) {}

    virtual void setWidth(double width) {
        this->width = width;
    }

    virtual void setHeight(double height) {
        this->height = height;
    }

    virtual double area() const {
        return width * height;
    }

protected:
    double width;
    double height;
};

class Square : public Rectangle {
public:
    Square(double side) : Rectangle(side, side) {}

    void setWidth(double width) override {
        this->width = width;
        this->height = width;
    }

    void setHeight(double height) override {
        this->width = height;
        this->height = height;
    }
};

void clientCode(Rectangle& rec) {
    rec.setHeight(5);
    rec.setWidth(4);
    assert(rec.area() == 20); // 16
}

// solution

class Shape {
public:
    virtual double area() const = 0;
};

class Rectangle1 : public Shape {
public:
    Rectangle1(double w, double h) : width(w), height(h) {}

    double area() const override {
        return width * height;
    }

private:
    double width;
    double height;
};

class Square1 : public Shape {
public:
    Square1(double s) : side(s) {}

    double area() const override {
        return side * side;
    }

private:
    double side;
};

// example 2

class Bird {
public:
    virtual void fly() {
        std::cout << "Flying in the air" << std::endl;
    }
};

class Ostrich : public Bird {
public:
    void fly() override {
        throw std::runtime_error("Ostrich cannot fly");
    }
};

// solution

class FlightlessBird {
public:
    virtual void walk() = 0;
};

class FlyingBird {
public:
    virtual void fly() = 0;
};

class Bird1 : public FlyingBird {
public:
    void fly() override {
        std::cout << "Flying in the air" << std::endl;
    }
};

class Ostrich1 : public FlightlessBird {
public:
    void walk() override {
        std::cout << "Walking on the ground" << std::endl;
    }
};

int main() {
    return 0;
}