/*

Composite is a structural design pattern that lets you compose objects into tree structures
and then work with these structures as if they were individual objects.

Problem
Using the Composite pattern makes sense only when the core model of your app can be represented as a tree.

For example, imagine that you have two types of objects: Products and Boxes.
A Box can contain several Products as well as a number of smaller Boxes.
These little Boxes can also hold some Products or even smaller Boxes, and so on.

Say you decide to create an ordering system that uses these classes.
Orders could contain simple products without any wrapping, as well as boxes stuffed with products...and other boxes.
How would you determine the total price of such an order?


You could try the direct approach: unwrap all the boxes, go over all the products and then calculate the total.
That would be doable in the real world; but in a program, it’s not as simple as running a loop.
You have to know the classes of Products and Boxes you’re going through, the nesting level of the boxes and other
nasty details beforehand. All of this makes the direct approach either too awkward or even impossible.

Solution
The Composite pattern suggests that you work with Products and Boxes through a common interface
which declares a method for calculating the total price.

How would this method work? For a product, it’d simply return the product’s price. For a box, it’d go over each item the box contains,
ask its price and then return a total for this box. If one of these items were a smaller box,
that box would also start going over its contents and so on, until the prices of all inner components were calculated.
A box could even add some extra cost to the final price, such as packaging cost.

The greatest benefit of this approach is that you don’t need to care about the concrete classes of objects that compose the tree.
You don’t need to know whether an object is a simple product or a sophisticated box.
You can treat them all the same via the common interface.
When you call a method, the objects themselves pass the request down the tree.

*/

#include <algorithm>
#include <iostream>
#include <list>
#include <string>


// The base Component class declares common operations for both simple and complex objects of a composition.

class Component {
protected:
    Component* parent;
  /**
   * Optionally, the base Component can declare an interface for setting and
   * accessing a parent of the component in a tree structure. It can also
   * provide some default implementation for these methods.
   */
public:
    virtual ~Component() {}
    void setParent(Component* p) {
        parent = p;
    }
    Component* getParent() const {
        return parent;
    }
    // it would be beneficial to define the child-management operations right in the base Component class.
    // This way, you won't need to expose any concrete component classes to the client code, even during the
    // object tree assembly. The downside is that these methods will be empty for
    // the leaf-level components.

    virtual void add(Component* component) {}
    virtual void remove(Component* component) {}

    // You can provide a method that lets the client code figure out whether a component can bear children.
    virtual bool isComposite() const {
        return false;
    }

    virtual std::string operation() const = 0;
};


// The Leaf class represents the end objects of a composition. A leaf can't have any children.
// Usually, it's the Leaf objects that do the actual work, whereas Composite objects only delegate to their sub-components.

class Leaf : public Component {
public:
    std::string operation() const override {
        return "Leaf";
    }
};

// The Composite class represents the complex components that may have children.
// Usually, the Composite objects delegate the actual work to their children and then "sum-up" the result.

class Composite : public Component {
protected:
    std::list<Component*> children;
public:
    // A composite object can add or remove other components (both simple or complex) to or from its child list.
    void add(Component *component) override {
        children.push_back(component);
        component->setParent(this);
    }

    // Have in mind that this method removes the pointer to the list but doesn't frees the
    // memory, you should do it manually or better use smart pointers.
    void remove(Component *component) override {
        children.remove(component);
        component->setParent(nullptr);
    }
    bool isComposite() const override {
        return true;
    }

    // The Composite executes its primary logic in a particular way. It traverses
    // recursively through all its children, collecting and summing their results.
    // Since the composite's children pass these calls to their children, the whole object tree is traversed as a result.

    std::string operation() const override {
        std::string result;
        for (const Component* c : children) {
            if (c == children.back()) {
                result += c->operation();
            } else {
                result += c->operation() + "+";
            }
        }
        return "Branch(" + result + ")";
    }
};

void ClientCode(Component* component) {
    std::cout << "RESULT: " << component->operation() << std::endl;
}

void ClientCode2(Component* component1, Component* component2) {
    if (component1->isComposite()) {
        component1->add(component2);
    }
    std::cout << "RESULT: " << component1->operation() << std::endl;
}

int main() {
    Component* simple = new Leaf;
    std::cout << "Client: I've got a simple component:" << std::endl;
    ClientCode(simple);


    Component* tree = new Composite;
    Component* branch1 = new Composite;

    Component* leaf_1 = new Leaf;
    Component* leaf_2 = new Leaf;
    Component* leaf_3 = new Leaf;
    branch1->add(leaf_1);
    branch1->add(leaf_2);
    Component* branch2 = new Composite;
    branch2->add(leaf_3);
    tree->add(branch1);
    tree->add(branch2);
    std::cout << "Client: Now I've got a composite tree:" << std::endl;
    ClientCode(tree);

    std::cout << "Client: I don't need to check the components classes even when managing the tree:" << std::endl;
    ClientCode2(tree, simple);

    delete simple;
    delete tree;
    delete branch1;
    delete branch2;
    delete leaf_1;
    delete leaf_2;
    delete leaf_3;

    return 0;
}