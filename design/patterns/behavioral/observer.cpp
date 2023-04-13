/*

The Observer pattern is a behavioral pattern that allows one-to-many communication between objects,
so that when one object changes state, all its dependents are notified and updated automatically.

Observer is a behavioral design pattern that lets you define a subscription mechanism to notify
multiple objects about any events that happen to the object they’re observing.

Problem
Imagine that you have two types of objects: a Customer and a Store. The customer is very interested in a particular brand of product
(say, it’s a new model of the iPhone) which should become available in the store very soon.

The customer could visit the store every day and check product availability.
But while the product is still en route, most of these trips would be pointless.

On the other hand, the store could send tons of emails (which might be considered spam) to all customers
each time a new product becomes available. This would save some customers from endless trips to the store.
At the same time, it’d upset other customers who aren’t interested in new products.

It looks like we’ve got a conflict. Either the customer wastes time checking product availability
or the store wastes resources notifying the wrong customers.

Solution
The object that has some interesting state is often called subject, but since it’s also going to notify other objects about
the changes to its state, we’ll call it publisher.
All other objects that want to track changes to the publisher’s state are called subscribers.

The Observer pattern suggests that you add a subscription mechanism to the publisher class so individual objects can subscribe
to or unsubscribe from a stream of events coming from that publisher.

In reality, this mechanism consists of
1) an array field for storing a list of references to subscriber objects and
2) several public methods which allow adding subscribers to and removing them from that list.

Now, whenever an important event happens to the publisher, it goes over its subscribers and
calls the specific notification method on their objects.


*/

#include <iostream>
#include <vector>

// Abstract Observer
class Observer {
public:
    virtual void update() = 0;
    virtual ~Observer() {}
};

// Concrete Observer A
class ObserverA : public Observer {
public:
    void update() {
        std::cout << "Observer A notified" << std::endl;
    }
};

// Concrete Observer B
class ObserverB : public Observer {
public:
    void update() {
        std::cout << "Observer B notified" << std::endl;
    }
};

// Abstract Subject
class Subject {
protected:
    std::vector<Observer*> observers;

public:
    virtual void attach(Observer* observer) = 0;
    virtual void detach(Observer* observer) = 0;
    virtual void notify() = 0;
    virtual ~Subject() {}
};

// Concrete Subject
class ConcreteSubject : public Subject {
public:
    void attach(Observer* observer) {
        observers.push_back(observer);
    }

    void detach(Observer* observer) {
        for (auto it = observers.begin(); it != observers.end(); ++it) {
            if (*it == observer) {
                observers.erase(it);
                break;
            }
        }
    }

    void notify() {
        for (auto observer : observers) {
            observer->update();
        }
    }
};

int main() {
    ConcreteSubject subject;

    // create two observers
    Observer* observerA = new ObserverA();
    Observer* observerB = new ObserverB();

    // attach the observers to the subject
    subject.attach(observerA);
    subject.attach(observerB);

    // notify the observers
    subject.notify();

    // detach one observer and notify again
    subject.detach(observerB);
    subject.notify();

    delete observerA;
    delete observerB;

    return 0;
}
