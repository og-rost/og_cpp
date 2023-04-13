#include <iostream>
#include <typeinfo>

class Context;

class State {
protected:
    Context* context;
public:
    virtual ~State() {}

    void set_context(Context* ctx) {
        context = ctx;
    }

    virtual void handle1() = 0;
    virtual void handle2() = 0;
};


class Context {
private:
    State* state;
public:
    Context(State* s) : state(nullptr) {
        transitionTo(s);
    }
    ~Context() {
        delete state;
    }

    void transitionTo(State* s) {
        std::cout << "Context: Transition to " << typeid(*s).name() << std::endl;
        if (state != nullptr) {
            delete state;
        }
        state = s;
        state->set_context(this);
    }

    void request1() {
        state->handle1();
    }
    void request2() {
        state->handle2();
    }
};

class ConcreteStateA : public State {
public:
    void handle1() override;

    void handle2() override {
        std::cout << "ConcreteStateA handles request2." << std::endl;
    }
};

class ConcreteStateB : public State {
public:
    void handle1() override {
        std::cout << "ConcreteStateB handles request1." << std::endl;
    }
    void handle2() override {
        std::cout << "ConcreteStateB handles request2." << std::endl;
        std::cout << "ConcreteStateB wants to change the state of the context." << std::endl;
        context->transitionTo(new ConcreteStateA);
    }
};

void ConcreteStateA::handle1() {
    std::cout << "ConcreteStateA handles request1." << std::endl;
    std::cout << "ConcreteStateA wants to change the state of the context." << std::endl;
    context->transitionTo(new ConcreteStateB);
}

void ClientCode() {
    Context* context = new Context(new ConcreteStateA);
    context->request1();
    context->request2();
    delete context;
}

int main() {
    ClientCode();
    return 0;
}