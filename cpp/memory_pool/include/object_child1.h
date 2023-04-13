#pragma once

#include "object_base.h"

class ObjectChild1 : public ObjectBase {
public:
    ObjectChild1(std::string name) : ObjectBase(name) {}

    ~ObjectChild1() {
	    std::cout << "child destructor 1 " << std::endl;
    }
};
