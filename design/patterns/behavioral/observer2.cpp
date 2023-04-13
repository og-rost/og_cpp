#include <iostream>
#include <list>
#include <string>

class ObserverItf {
public:
    virtual ~ObserverItf(){};
    virtual void update(const std::string& msg) = 0;
};

class SubjectItf {
public:
    virtual ~SubjectItf(){};
    virtual void attach(ObserverItf* observer) = 0;
    virtual void detach(ObserverItf* observer) = 0;
    virtual void notify() = 0;
};


class Subject : public SubjectItf {
public:
    virtual ~Subject() {
        std::cout << "Goodbye, I was the Subject." << std::endl;
    }

    void attach(ObserverItf* observer) override {
        list_observer.push_back(observer);
    }
    void detach(ObserverItf* observer) override {
        list_observer.remove(observer);
    }
    void notify() override {
        std::list<ObserverItf*>::iterator iterator = list_observer.begin();
        observersCount();
        while (iterator != list_observer.end()) {
            (*iterator)->update(message);
            ++iterator;
        }
    }

    void createMessage(std::string msg = "Empty") {
        message = msg;
        notify();
    }
    void observersCount() {
        std::cout << "There are " << list_observer.size() << " observers in the list." << std::endl;
    }

    void someBusinessLogic() {
        message = "change message message";
        notify();
        std::cout << "I'm about to do some thing important" << std::endl;
    }

private:
  std::list<ObserverItf*> list_observer;
  std::string message;
};

class Observer : public ObserverItf {
public:
    Observer(Subject& sub) : subject(sub) {
        subject.attach(this);
        std::cout << "Hi, I'm the Observer \"" << ++Observer::static_number << std::endl;
        number = Observer::static_number;
    }
    virtual ~Observer() {
        std::cout << "Goodbye, I was the Observer \"" << number << std::endl;
    }

    void update(const std::string& msg) override {
        message_from_subject = msg;
        printInfo();
    }
    void removeMeFromTheList() {
        subject.detach(this);
        std::cout << "Observer \"" << number << "\" removed from the list." << std::endl;
    }
    void printInfo() {
        std::cout << "Observer \"" << number << "\": a new message is available --> " << message_from_subject << std::endl;
    }

private:
    std::string message_from_subject;
    Subject& subject;
    static int static_number;
    int number;
};

int Observer::static_number = 0;

void ClientCode() {
    Subject* subject = new Subject;
    Observer* observer1 = new Observer(*subject);
    Observer* observer2 = new Observer(*subject);
    Observer* observer3 = new Observer(*subject);
    Observer* observer4;
    Observer* observer5;

    subject->createMessage("Hello World! :D");
    observer3->removeMeFromTheList();

    subject->createMessage("The weather is hot today! :p");
    observer4 = new Observer(*subject);

    observer2->removeMeFromTheList();
    observer5 = new Observer(*subject);

    subject->createMessage("My new car is great! ;)");
    observer5->removeMeFromTheList();

    observer4->removeMeFromTheList();
    observer1->removeMeFromTheList();

    delete observer5;
    delete observer4;
    delete observer3;
    delete observer2;
    delete observer1;
    delete subject;
}

int main() {
    ClientCode();
    return 0;
}