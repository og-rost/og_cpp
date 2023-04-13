/*

The Command pattern is a behavioral pattern that allows you to encapsulate a request as an object
and pass it to other objects. The request is encapsulated in a Command object,
which contains all the information needed to execute the request.
This pattern decouples the object that invokes the operation from the one that knows how to perform it.

Command is a behavioral design pattern that turns a request into a stand-alone object that contains all information about the request.
This transformation lets you pass requests as a method arguments, delay or queue a request’s execution, and support undoable operations.


Good software design is often based on the principle of separation of concerns, which usually results in breaking an app into layers.
The most common example: a layer for the graphical user interface and another layer for the business logic.
The GUI layer is responsible for rendering a on the screen, capturing any input and showing results of what the user and the app are doing.
However, when it comes to doing something important the GUI layer delegates the work to the underlying layer of business logic.

In the code it might look like this: a GUI object calls a method of a business logic object, passing it some arguments.
This process is usually described as one object sending another a request.

The Command pattern suggests that GUI objects shouldn’t send these requests directly.
Instead, you should extract all of the request details, such as the object being called,
the name of the method and the list of arguments into a separate command class with a single method that triggers this request.

Command objects serve as links between various GUI and business logic objects.
From now on, the GUI object doesn’t need to know what business logic object will receive the request and how it’ll be processed.
The GUI object just triggers the command, which handles all the details.


*/


#include <iostream>
#include <functional>

// Invoker class
class Invoker {
public:
    void setCommand(std::function<void()> cmd) {
        command = cmd;
    }

    void executeCommand() {
        if (command) {
            command();
        } else {
            std::cout << "No command set" << std::endl;
        }
    }

private:
    std::function<void()> command;
};

int main() {
    // Create some commands as lambdas
    auto command1 = []() { std::cout << "Command 1 executed" << std::endl; };
    auto command2 = []() { std::cout << "Command 2 executed" << std::endl; };

    // Create an invoker and execute the commands
    Invoker invoker;
    invoker.setCommand(command1);
    invoker.executeCommand();

    invoker.setCommand(command2);
    invoker.executeCommand();

    return 0;
}

/*

The main usage of the Command pattern is to decouple the requester of an action (client)
from the object that performs the action (receiver). This allows for greater flexibility
in how commands are executed and makes it easier to implement features like undo/redo
functionality or macro commands.

In general, the Command pattern is useful in situations where you need to:

    Parameterize objects with actions to be performed (e.g. different actions for a button in a GUI)
    Queue actions for later execution (e.g. in a macro command)
    Support undo/redo functionality
    Implement logging or auditing of actions
    Implement transactional behavior (i.e. a group of actions that should be treated as a single unit of work)

By encapsulating actions as objects, the Command pattern provides a way to separate the implementation details
of how an action is performed from the higher-level logic of when and why it should be performed.
This can lead to more modular and maintainable code.

*/
