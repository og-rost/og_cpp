/*

Strategy is a behavioral design pattern which is used when we have multiple algorithm for a specific task
and client decides the actual implementation to be used at runtime

Strategy is a behavioral design pattern that lets you define a family of algorithms,
put each of them into a separate class, and make their objects interchangeable.


The Strategy pattern suggests that you take a class that does something specific in a lot of different ways and extract
all of these algorithms into separate classes called strategies.

The original class, called context, must have a field for storing a reference to one of the strategies.
The context delegates the work to a linked strategy object instead of executing it on its own.

The context isn’t responsible for selecting an appropriate algorithm for the job. Instead, the client passes
the desired strategy to the context. In fact, the context doesn’t know much about strategies.
It works with all strategies through the same generic interface, which only exposes a single method
for triggering the algorithm encapsulated within the selected strategy.

This way the context becomes independent of concrete strategies, so you can add new algorithms
or modify existing ones without changing the code of the context or other strategies.


*/

#include <iostream>

class PaymentStrategy {
public:
    virtual void pay(double amount) = 0;
    virtual ~PaymentStrategy() = default;
};

class CreditCardPayment : public PaymentStrategy {
public:
    void pay(double amount) override {
        std::cout << "Paying $" << amount << " using credit card." << std::endl;
        // implementation of credit card payment
    }
};

class PayPalPayment : public PaymentStrategy {
public:
    void pay(double amount) override {
        std::cout << "Paying $" << amount << " using PayPal." << std::endl;
        // implementation of PayPal payment
    }
};

class PaymentProcessor {
private:
    PaymentStrategy* strategy;
public:
    PaymentProcessor(PaymentStrategy* s) : strategy(s) {}
    void setStrategy(PaymentStrategy* s) {
        strategy = s;
    }
    void processPayment(double amount) {
        strategy->pay(amount);
    }
};

int main() {
    PaymentProcessor processor(new CreditCardPayment());
    processor.processPayment(50.0); // pays using credit card

    processor.setStrategy(new PayPalPayment());
    processor.processPayment(100.0); // pays using PayPal

    return 0;
}
