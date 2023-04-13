/*

The Dependency Inversion Principle (DIP) is one of the SOLID principles that deals with how software components should depend on each other.

The principle states that:

High-level modules should not depend on low-level modules. Both should depend on abstractions.
Abstractions should not depend on details. Details should depend on abstractions.

In other words, DIP encourages programmers to depend on abstractions rather than concrete implementations.
This helps to reduce the coupling between components and make them more flexible and easy to modify.

*/

#include <string>
#include <iostream>
#include <fstream>

class ConsoleLogger1 {
public:
    void log(std::string username) {}
};

class UserManager1 {
private:
    ConsoleLogger1 logger;

public:
    void addUser(std::string username, std::string password) {
        // code to add user to the system
        logger.log("User added: " + username);
    }
};

/*

UserManager class depends on the ConsoleLogger class directly, instead of depending on an abstraction
(such as the Logger interface we defined in the previous example).

This violates the Dependency Inversion Principle because it creates a tight coupling between the UserManager class and the ConsoleLogger class.
If we want to switch to a different logging strategy (such as logging to a file), we would need to modify the UserManager class
to remove the dependency on the ConsoleLogger class and replace it with a dependency on a different logging class.

By depending on an abstraction (such as the Logger interface), we can avoid this problem and make the UserManager class
more flexible and easier to modify in the future.

*/


// fixed version


class Logger {
public:
    virtual void log(std::string message) = 0;
};

class ConsoleLogger : public Logger {
public:
    void log(std::string message) override {
        std::cout << message << std::endl;
    }
};

class FileLogger : public Logger {
public:
    void log(std::string message) override {
        std::ofstream file("log.txt", std::ios::app);
        file << message << std::endl;
    }
};

class UserManager {
private:
    Logger* logger;

public:
    UserManager(Logger* l) : logger(l) {}

    void addUser(std::string username, std::string password) {
        // code to add user to the system
        logger->log("User added: " + username);
    }
};


int main() {
    return 0;
}