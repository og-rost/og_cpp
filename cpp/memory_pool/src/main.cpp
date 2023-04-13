#include <iostream>

#include "factory.h"
#include "controller.h"

int main() {

    Controller* controller = new Controller;
	{
		auto c1 = create_child1(*controller, "Klir");
		std::cout << "Child 1 " << c1->get_name() << std::endl;
		auto c2 = create_child2(*controller, "Mlir");
		std::cout << "Child 2 " << c2->get_name() << std::endl;
		auto c3 = create_child3(*controller, "Flir");
		std::cout << "Child 3 " << c3->get_name() << std::endl;


		auto dummy1 = create_child1(*controller, "Klir");
		auto dummy2 = create_child1(*controller, "Klir");
		auto dummy3 = create_child1(*controller, "Klir");
		auto dummy4 = create_child2(*controller, "Mlir");
		auto dummy5 = create_child2(*controller, "Mlir");

		std::cout << "Done ========================" << std::endl;
	}

    delete controller;
    return 0;
}

