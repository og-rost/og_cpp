/*

The Abstract Factory pattern is a creational design pattern that provides an interface for creating
families of related objects without specifying their concrete classes.
The key idea of this pattern is to encapsulate a group of factories that have a common theme
and create objects that fit into a specific theme.

Abstract Factory (factory of factories)

Abstract Factory offers the interface for creating a family of related objects, without explicitly specifying their classes.

Client <--> GUIFactory --> WinFactory --> WinButton, WinScrollBar
                           MacFactory --> MacButton, MacScrollBar


                        
Abstract Factory is a creational design pattern that lets you produce families of related objects without specifying their concrete classes.

Problem
Imagine that you’re creating a furniture shop simulator. Your code consists of classes that represent:

A family of related products, say: Chair + Sofa + CoffeeTable.
Several variants of this family. For example, products Chair + Sofa + CoffeeTable are available in these variants: Modern, Victorian, ArtDeco.

You need a way to create individual furniture objects so that they match other objects of the same family.

A Modern-style sofa doesn’t match Victorian-style chairs.

Also, you don’t want to change existing code when adding new products or families of products to the program.
Furniture vendors update their catalogs very often, and you wouldn’t want to change the core code each time it happens.

*/

#include <iostream>

// Abstract button
class Button {
public:
    virtual void paint() = 0;
};

// Concrete button 1
class WinButton : public Button {
public:
    void paint() { std::cout << " Window Button" << std::endl; }
};

// Concrete button 2
class MacButton : public Button {
public:
    void paint() { std::cout << " Mac Button" << std::endl; }
};

// Abstract scrollbar
class ScrollBar {
public:
    virtual void paint() = 0;
};

// Concrete scrollbar 1
class WinScrollBar : public ScrollBar {
public:
    void paint() { std::cout << " Window ScrollBar" << std::endl; }
};

// Concrete scrollbar 2
class MacScrollBar : public ScrollBar {
public:
    void paint() { std::cout << " Mac ScrollBar" << std::endl; }
};

// Abstract factory
class GUIFactory {
public:
    virtual Button* createButton() = 0;
    virtual ScrollBar* createScrollBar() = 0;
};

// Concrete factory 1
class WinFactory : public GUIFactory {
public:
    Button* createButton() { return new WinButton; }
    ScrollBar* createScrollBar() { return new WinScrollBar; }
};

// Concrete factory 2
class MacFactory : public GUIFactory {
public:
    Button* createButton() { return new MacButton; }
    ScrollBar* createScrollBar() { return new MacScrollBar; }
};

int main() {
    GUIFactory* winFactory = new WinFactory();
    Button* winButton = winFactory->createButton(); // Create win button
    winButton->paint();
    ScrollBar* winScrollBar = winFactory->createScrollBar(); // Create win scroll bar
    winScrollBar->paint();

    GUIFactory* macFactory = new MacFactory();
    Button* macButton = macFactory->createButton(); // Create mac button
    macButton->paint();
    ScrollBar* macScrollBar = macFactory->createScrollBar(); // Create mac scroll bar
    macScrollBar->paint();

    return 0;
}

/*

Both Abstract Factory and Factory Method are creational design patterns that aim to encapsulate the creation of objects.
However, they differ in their focus and how they achieve that encapsulation.

The Factory Method pattern provides an interface for creating objects, but delegates the actual creation of the objects
to concrete subclasses. This allows clients to create objects without knowing their concrete types.
In other words, the Factory Method pattern focuses on creating a single product at a time,
and the choice of the product is delegated to the subclasses.

On the other hand, the Abstract Factory pattern provides an interface for creating families of related objects,
without specifying their concrete classes. The key idea is to encapsulate a group of factories that have a common theme,
and create objects that fit into a specific theme. In other words, the Abstract Factory pattern focuses on creating
multiple related products at a time, and the choice of the product families is delegated to the clients.

So, while the Factory Method pattern creates objects of a single type, the Abstract Factory pattern creates
families of related objects, providing a way to create complex objects with multiple parts that work together.

*/
