/*

The Open/Closed Principle states that software entities (such as classes, modules, or functions)
should be open for extension but closed for modification. In other words, you should be able
to add new functionality (types) to a system without changing its existing code.

One way to achieve this is to use abstractions, such as interfaces or abstract classes,
to define the behavior that can be extended. This allows new functionality to be added
through the implementation of new classes that conform to these abstractions,
rather than modifying existing classes.


Open/Closed principle uses interfaces instead of superclasses to allow different implementations
which you can easily substitute without changing the code that uses them.
The interfaces are closed for modifications, and you can provide new implementations
to extend the functionality of your software.

*/

// code violating open/close


class Circle {
private:
    int radius;
public:
    Circle(int r) {
        radius = r;
    }

    int getRadius() {
        return radius;
    }
};

class Square {
private:
    int side;
public:
    Square(int s) {
        side = s;
    }

    int getSide() {
        return side;
    }
};

class DrawShapes {
public:
    void draw(/*list of shapes */) {
        // if shape is circle get radius
        // if shape is square get side
    }
};


// any introduction of a new type of shape will need change in the draw() method
// adding additional if/else statement to handle the new shape.


// using SOLID

class Shape {
public:
    virtual void draw() = 0;
};

class Circle1 : public Shape {
private:
    int radius;
public:
    Circle1(int r) {
        radius = r;
    }

    int getRadius() {
        return radius;
    }

    void draw() override {}
};

class Square1 : public Shape {
private:
    int side;
public:
    Square1(int s) {
        side = s;
    }

    int getSide() {
        return side;
    }

    void draw() override {}
};

class DrawShapes1 {
public:
    void draw(/*list of shapes */) {

        //for each shape
            // shape.draw();
    }
};

int main() {
    return 0;
}
