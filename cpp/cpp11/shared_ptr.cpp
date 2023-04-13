/*********** Shared_ptr ***********/

// 1. When a pointer outlives pointee: danling pointer
// 2. When a pointee outlives all its pointers: resource leak
//
// Smart Pointers: Make sure the lifetime of a pointer and pointee match.

#include <memory>
#include <iostream>

class Dog1 {
    std::string m_name;
public:
    void bark() { 
        std::cout << "Dog " << m_name << " rules!" << std::endl; 
    }
    Dog1(std::string name) { 
        std::cout << "Dog is created: " << name << std::endl; 
        m_name = name; 
    }
    Dog1() { 
        std::cout << "Nameless dog created." << std::endl; 
        m_name = "nameless"; 
    }
    ~Dog1() { 
        std::cout << "dog is destroyed: " << m_name << std::endl; 
    }
    //void enter(DogHouse* h) { h->setDog(shared_from_this()); }  // Dont's call shared_from_this() in constructor
};

class DogHouse {
    std::shared_ptr<Dog1> m_pD;
public:
    void setDog(std::shared_ptr<Dog1> p) { m_pD = p; std::cout << "Dog entered house." << std::endl;}
};

void f1() {
    std::shared_ptr<Dog1> pD1(new Dog1(std::string("Gunner")));
    std::shared_ptr<Dog1> pD2 = std::make_shared<Dog1>(Dog1(std::string("Gunner"))); // faster and safer

    pD1->bark();

    (*pD1).bark();

    //DogHouse h;
    //    DogHouse* ph = new DogHouse();
    //    ph->setDog(pD);
    //    delete ph;


    //auto pD2 = make_shared<Dog>( Dog("Smokey") ); // Don't use shared pointer for object on stack.
    //    auto pD2 = make_shared<Dog>( *(new Dog("Smokey")) ); 
    //    pD2->bark();
    //
    //    Dog* p = new Dog();
    //    shared_ptr<int> p1(p);
    //    shared_ptr<int> p2(p);  // Erroneous

    std::shared_ptr<Dog1> pD3;
    pD3.reset(new Dog1("Tank"));
    pD3.reset();  // Dog destroyed. Same effect as: pD3 = nullptr;
    //    
    //pD3.reset(pD.get());  // crashes

    /********** Custom Deleter ************/
    std::shared_ptr<Dog1> pD4( new Dog1("Victor"), 
            [](Dog1* p) {std::cout << "deleting a dog.\n"; delete p;}
            );
    // default deleter is operator delete.

    //shared_ptr<Dog> pD5(new Dog[3]);
    std::shared_ptr<Dog1> pD5(new Dog1[3], [](Dog1* p) {delete[] p;} );
}
/*********** weak_ptr *********************/
class Dog2 {
    //shared_ptr<Dog> m_pFriend;
    std::weak_ptr<Dog2> m_pFriend;
public:
    std::string m_name;
    void bark() { 
        std::cout << "Dog " << m_name << " rules!" << std::endl; 
    }
    Dog2(std::string name) { 
        std::cout << "Dog is created: " << name << std::endl; 
        m_name = name; 
    }
    ~Dog2() { std::cout << "dog is destroyed: " << m_name << std::endl; 
    }
    void makeFriend(std::shared_ptr<Dog2> f) { 
        m_pFriend = f; 
    }
    void showFriend() { //cout << "My friend is: " << m_pFriend.lock()->m_name << endl;
        if (!m_pFriend.expired()) {
            std::cout << "My friend is: " << m_pFriend.lock()->m_name << std::endl;
        }
        std::cout << " He is owned by " << m_pFriend.use_count() << " pointers." << std::endl; 
    }
};

void f2() {
    std::shared_ptr<Dog2> pD(new Dog2("Gunner"));
    std::shared_ptr<Dog2> pD2(new Dog2("Smokey"));
    pD->makeFriend(pD2);
    pD2->makeFriend(pD);

    pD->showFriend();
}

/*********** unique_ptr *********************/

// Unique Pointers: exclusive owenership

class Bone {};

class Dog3 {
    //Bone* pB;
    std::unique_ptr<Bone> pB;  // This prevents memory leak even constructor fails.
public:
    std::string m_name;
    void bark() { 
        std::cout << "Dog " << m_name << " rules!" << std::endl; 
    }
    Dog3() { 
        pB = std::make_unique<Bone>(); 
        std::cout << "Nameless dog created." << std::endl; 
        m_name = "nameless"; 
    }
    Dog3(std::string name) { 
        std::cout << "Dog is created: " << name << std::endl; 
        m_name = name; 
    }
    ~Dog3() { 
        // delete pB; // compile time error 
        std::cout << "dog is destroyed: " << m_name << std::endl; 
    }
};

void f3() {

    //Dog* pD = new Dog("Gunner");
    std::unique_ptr<Dog3> pD(new Dog3("Gunner"));

    pD->bark();
    /* pD does a bunch of different things*/

    //Dog* p = pD.release();
    pD = nullptr;
    //pD.reset(new Dog("Smokey"));

    if (!pD) {
        std::cout << "pD is empty." << std::endl;
    }

    //delete pD;   
}

std::unique_ptr<Dog3> getDog() {
    std::unique_ptr<Dog3> p(new Dog3("Smokey"));
    return p;
}

void f4() {
    std::unique_ptr<Dog3> pD(new Dog3("Gunner"));
    std::unique_ptr<Dog3> pD2(new Dog3("Smokey"));
    pD2 = move(pD);
    // 1. Smokey is destroyed
    // 2. pD becomes empty.
    // 3. pD2 owns Gunner.

    pD2->bark();
    //    f(move(pD));
    //    if (!pD) {
    //        cout << "pD is empty.\n";
    //    }
    //    
    //    unique_ptr<Dog> pD2 = getDog();
    //    pD2->bark();

    std::unique_ptr<Dog3[]> dogs(new Dog3[3]);
    dogs[1].bark();
    //(*dogs).bark(); // * is not defined
}

int main () {
    f1();
    f2();
    f3();
    f4();

    return 0;
}
