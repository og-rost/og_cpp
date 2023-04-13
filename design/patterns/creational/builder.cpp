/*

The Builder design pattern is a creational design pattern that separates the construction of a complex object
from its representation, allowing the same construction process to create different representations.
The main idea behind this pattern is to encapsulate the construction process of an object and allow its
different parts to be created independently.

In this pattern, there are usually two main actors: the Director and the Builder. The Director is responsible
for managing the construction process and coordinating with the Builder to create the final object.
The Builder is responsible for creating the different parts of the object and providing an interface
for the Director to access them.

The process of building the object is divided into multiple steps, with each step handled
by a method in the Builder interface. This allows different implementations of the Builder interface
to be used to create different representations of the same object.


Builder is a creational design pattern that lets you construct complex objects step by step.
The pattern allows you to produce different types and representations of an object using the same construction code.

Problem:
Imagine a complex object that requires laborious, step-by-step initialization of many fields and nested objects.
Such initialization code is usually buried inside a monstrous constructor with lots of parameters.
In most cases most of the parameters will be unused, making the constructor calls pretty ugly.

Solution:
The Builder pattern suggests that you extract the object construction code out of its own class and move it to separate objects called builders.

The pattern organizes object construction into a set of steps. To create an object, you execute a series of these steps on a builder object.
The important part is that you don’t need to call all of the steps.
You can call only those steps that are necessary for producing a particular configuration of an object.

You can go further and extract a series of calls to the builder steps you use to construct a product into a separate class called director.
The director class defines the order in which to execute the building steps, while the builder provides the implementation for those steps.

Having a director class in your program isn’t strictly necessary.
You can always call the building steps in a specific order directly from the client code.
However, the director class might be a good place to put various construction routines so you can reuse them across your program.

*/


#include <iostream>
#include <string>

class Car {
private:
    std::string engine;
    int wheels;
    std::string body;
public:
    void setEngine(const std::string& engine) {
        this->engine = engine;
    }
    void setWheels(int wheels) {
        this->wheels = wheels;
    }
    void setBody(const std::string& body) {
        this->body = body;
    }
    void display() const {
        std::cout << "Engine: " << engine << std::endl;
        std::cout << "Wheels: " << wheels << std::endl;
        std::cout << "Body: " << body << std::endl;
    }
};

class CarBuilder {
public:
    virtual void buildEngine() = 0;
    virtual void buildWheels() = 0;
    virtual void buildBody() = 0;
    virtual Car getResult() = 0;
    virtual ~CarBuilder() = default;
};

class SportCarBuilder : public CarBuilder {
private:
    Car car;
public:
    void buildEngine() override {
        car.setEngine("V8");
    }
    void buildWheels() override {
        car.setWheels(4);
    }
    void buildBody() override {
        car.setBody("Sleek");
    }
    Car getResult() override {
        return car;
    }
};

class SUVBuilder : public CarBuilder {
private:
    Car car;
public:
    void buildEngine() override {
        car.setEngine("V6");
    }
    void buildWheels() override {
        car.setWheels(4);
    }
    void buildBody() override {
        car.setBody("Rugged");
    }
    Car getResult() override {
        return car;
    }
};

class CarDirector {
private:
    CarBuilder* builder;
public:
    CarDirector(CarBuilder* builder) : builder(builder) {}
    void construct() {
        builder->buildEngine();
        builder->buildWheels();
        builder->buildBody();
    }
};

int main() {
    CarBuilder* builder = new SportCarBuilder();
    CarDirector director(builder);
    director.construct();
    Car car = builder->getResult();
    car.display();
    delete builder;
    builder = new SUVBuilder();
    director = CarDirector(builder);
    director.construct();
    car = builder->getResult();
    car.display();
    delete builder;
    return 0;
}
