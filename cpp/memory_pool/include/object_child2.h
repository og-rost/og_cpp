#pragma once

#include "object_base.h"

class ObjectChild2 : public ObjectBase {
public:
    ObjectChild2(std::string name) : ObjectBase(name) {}

    ~ObjectChild2() {
        std::cout << "child destructor 2 " << std::endl;
    }
};
