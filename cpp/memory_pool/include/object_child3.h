#pragma once

#include "object_base.h"

class ObjectChild3 : public ObjectBase {
public:
    ObjectChild3(std::string name) : ObjectBase(name) {}

    ~ObjectChild3() {
        std::cout << "child destructor 3 " << std::endl;
    }
};
