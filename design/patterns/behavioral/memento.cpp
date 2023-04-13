/*

The Memento design pattern is a behavioral design pattern that allows an object to capture and save
its internal state so that it can be restored later without violating encapsulation.
The pattern consists of three main components:
    the Originator, which is the object that has an internal state that needs to be saved;
    the Memento, which is a snapshot of the Originator's state at a particular point in time;
    the Caretaker, which is responsible for storing and managing the Mementos.


Memento is a behavioral design pattern that lets you save and restore the previous state of
an object without revealing the details of its implementation.

Problem
Imagine that you’re creating a text editor app. In addition to simple text editing, your editor can format text, insert inline images, etc.
At some point, you decided to let users undo any operations carried out on the text.
This feature has become so common over the years that nowadays people expect every app to have it.
For the implementation, you chose to take the direct approach. Before performing any operation,
the app records the state of all objects and saves it in some storage. Later, when a user decides to revert an action,
the app fetches the latest snapshot from the history and uses it to restore the state of all objects.

Solution
All the problems that can happen here are caused by broken encapsulation. Some objects try to do more than they are supposed to.
To collect the data required to perform some action, they invade the private space of other objects instead of letting
these objects perform the actual action.

The Memento pattern delegates creating the state snapshots to the actual owner of that state, the originator object.
Hence, instead of other objects trying to copy the editor’s state from the “outside,” the editor class itself can make
the snapshot since it has full access to its own state.

The pattern suggests storing the copy of the object’s state in a special object called memento.
The contents of the memento aren’t accessible to any other object except the one that produced it.
Other objects must communicate with mementos using a limited interface which may allow fetching
the snapshot’s metadata (creation time, the name of the performed operation, etc.),
but not the original object’s state contained in the snapshot.



*/


// The Memento interface provides a way to retrieve the memento's metadata, such
// as creation date or name. However, it doesn't expose the Originator's state.
 
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <chrono>
#include <thread>
#include <algorithm>
#include <random>



class Memento {
public:
    virtual ~Memento() {}
    virtual std::string getName() const = 0;
    virtual std::string getDate() const = 0;
    virtual std::string getState() const = 0;
};

// The Concrete Memento contains the infrastructure for storing the Originator's state.

class ConcreteMemento : public Memento {
private:
    std::string state;
    std::string date;
public:
    ConcreteMemento(std::string s) : state(s) {
        std::cout << "Created a ConcreteMemento" << std::endl;
        std::time_t result = std::time(nullptr);
        date = std::ctime(&result);
    }
    // The Originator uses this method when restoring its state.
    std::string getState() const override { 
        return state;
    }
    // The rest of the methods are used by the Caretaker to display metadata.
    std::string getName() const override {
        return date + " / (" + state.substr(0, 9) + "...)";
    }
    std::string getDate() const override {
        return date;
    }
};

// The Originator holds some important state that may change over time. It also
// defines a method for saving the state inside a memento and another method for
// restoring the state from it.

class Originator {
private:
    std::string state;

    std::string generateRandomString(int length = 10) {
        auto& chrs = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
        std::mt19937 rg{std::random_device{}()};
        std::uniform_int_distribution<std::string::size_type> pick(0, sizeof(chrs) - 2);

        std::string s(length, 0);

        while(length--) {
            s += chrs[pick(rg)];
        }

        return s;
    }

public:
    Originator(std::string s) : state(s) {
        std::cout << "Originator: My initial state is: " << state << std::endl;
    }

    // The Originator's business logic may affect its internal state. Therefore,
    // the client should backup the state before launching methods of the business
    // logic via the save() method.
    void doSomething() {
        std::this_thread::sleep_for(std::chrono::seconds(5));
        std::cout << "Originator: I'm doing something important." << std::endl;
        state = generateRandomString(30);
        std::cout << "Originator: and my state has changed to: " << state << std::endl;
    }

    // Saves the current state inside a memento.
    Memento* save() {
        return new ConcreteMemento(state);
    }

    // Restores the Originator's state from a memento object.
    void restore(Memento *memento) {
        state = memento->getState();
        std::cout << "Originator: My state has changed to: " << state << std::endl;
    }
};

// The Caretaker doesn't depend on the Concrete Memento class. Therefore, it
// doesn't have access to the originator's state, stored inside the memento. It
// works with all mementos via the base Memento interface.

class Caretaker {
private:
    std::vector<Memento*> mementos;
    Originator* originator;

public:
    Caretaker(Originator* o) : originator(o) {}

    ~Caretaker() {
        for (auto m : mementos) {
            delete m;
        }
    }

    void backup() {
        std::cout << "Caretaker: Saving Originator's state..." << std::endl;
        mementos.push_back(originator->save());
    }
    void undo() {
        if (!mementos.size()) {
            return;
        }
        Memento* memento = mementos.back();
        mementos.pop_back();
        std::cout << "Caretaker: Restoring state to: " << memento->getName() << std::endl;
        try {
            originator->restore(memento);
        } catch (...) {
            undo();
        }
    }
    void showHistory() const {
        std::cout << "Caretaker: Here's the list of mementos:" << std::endl;
        for (Memento* memento : mementos) {
            std::cout << memento->getName() << std::endl;
        }
    }
};

void ClientCode() {
    Originator *originator = new Originator("Super-duper-super-puper-super.");
    Caretaker *caretaker = new Caretaker(originator);
    caretaker->backup();
    originator->doSomething();
    caretaker->backup();
    originator->doSomething();
    caretaker->backup();
    originator->doSomething();
    caretaker->showHistory();
    std::cout << "Client: Now, let's rollback!" << std::endl;
    caretaker->undo();
    std::cout << "Client: Once more!" << std::endl;
    caretaker->undo();
    std::cout << "Client: Once for the last time!" << std::endl;
    caretaker->undo();

    delete originator;
    delete caretaker;
}

int main() {
    ClientCode();
    return 0;
}