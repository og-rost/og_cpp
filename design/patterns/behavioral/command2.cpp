#include <iostream>
#include <string>

class Command {
public:
    virtual ~Command() {}
    virtual void execute() const = 0;
};


class SimpleCommand : public Command {
private:
    std::string pay_load;
public:
    explicit SimpleCommand(std::string pl) : pay_load(pl) {}
    void execute() const override {
        std::cout << "SimpleCommand: See, I can do simple things like printing (" << pay_load << ")" << std::endl;
    }
};

class Receiver {
public:
    void doSomething(const std::string& a) {
        std::cout << "Receiver: Working on (" << a << ".)" << std::endl;
    }
    void doSomethingElse(const std::string& b) {
        std::cout << "Receiver: Also working on (" << b << ".)" << std::endl;
    }
};

class ComplexCommand : public Command {
private:
    Receiver* receiver;
    std::string a;
    std::string b;
public:
    ComplexCommand(Receiver* r, std::string a, std::string b) : receiver(r), a(a), b(b) {}

    void execute() const override {
        std::cout << "ComplexCommand: Complex stuff should be done by a receiver object." << std::endl;
        receiver->doSomething(a);
        receiver->doSomethingElse(b);
    }
};

class Invoker {
private:
    Command* on_start;
    Command* on_finish;
public:
    ~Invoker() {
        delete on_start;
        delete on_finish;
    }

    void setOnStart(Command* command) {
        on_start = command;
    }
    void setOnFinish(Command* command) {
        on_finish = command;
    }

    void doSomethingImportant() {
        std::cout << "Invoker: Does anybody want something done before I begin?" << std::endl;
        if (on_start) {
            on_start->execute();
        }
        std::cout << "Invoker: ...doing something really important..." << std::endl;
        std::cout << "Invoker: Does anybody want something done after I finish?" << std::endl;
        if (on_finish) {
            on_finish->execute();
        }
    }
};


int main() {
    Invoker* invoker = new Invoker;
    invoker->setOnStart(new SimpleCommand("Say Hi!"));
    Receiver* receiver = new Receiver;
    invoker->setOnFinish(new ComplexCommand(receiver, "Send email", "Save report"));
    invoker->doSomethingImportant();

    delete invoker;
    delete receiver;

    return 0;
}