/*

State is a behavioral design pattern that lets an object alter its behavior when its internal state changes.
It appears as if the object changed its class.

Problem
The State pattern is closely related to the concept of a Finite-State Machine .

The main idea is that, at any given moment, there’s a finite number of states which a program can be in.
Within any unique state, the program behaves differently, and the program can be switched from one state to another instantaneously.
However, depending on a current state, the program may or may not switch to certain other states.
These switching rules, called transitions, are also finite and predetermined.

Solution
The State pattern suggests that you create new classes for all possible states of an object and
extract all state-specific behaviors into these classes.

Instead of implementing all behaviors on its own, the original object, called context, stores a reference to one of the state objects
that represents its current state, and delegates all the state-related work to that object.

*/

#include <iostream>

class Context;

class State {
public:
    virtual void handle(Context& context) = 0;
};

class ConcreteStateA : public State {
public:
    void handle(Context& context) override;
};

class ConcreteStateB : public State {
public:
    void handle(Context& context) override;
};

class Context {
public:
    Context(State* s) : state(s) {}
    void setState(State* s) { state = s; }
    void request() { state->handle(*this); }
private:
    State* state;
};

void ConcreteStateA::handle(Context& context) {
    std::cout << "ConcreteStateA handles request." << std::endl;
    context.setState(new ConcreteStateB());
}

void ConcreteStateB::handle(Context& context) {
    std::cout << "ConcreteStateB handles request." << std::endl;
    context.setState(new ConcreteStateA());
}

int main() {
    Context context(new ConcreteStateA());
    context.request();
    context.request();
    context.request();
    context.request();
    return 0;
}

/*

In this example, the State design pattern is used to create a state machine with two concrete states,
ConcreteStateA and ConcreteStateB, and a context object that can transition between these states.

*/
