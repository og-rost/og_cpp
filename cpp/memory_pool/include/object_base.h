#pragma once

#include <string>
#include <iostream>

class ObjectBase {
public:
    ObjectBase(std::string name) : m_name(name) {}

    ~ObjectBase() {
	    std::cout << "Base Destructor" << std::endl;	
    }

    std::string get_name() {
	    return m_name;
    }
private:
    std::string m_name;
};
