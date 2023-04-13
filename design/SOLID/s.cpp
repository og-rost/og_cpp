/*

The Single Responsibility Principle states that a class or module should have only one responsibility,
which means it should have only one job to do.

This principle encourages developers to create smaller, more focused classes that are easier to understand,
maintain, and test. By separating responsibilities, changes to one part of the system are less likely
to have unintended consequences on other parts of the system.
This also makes it easier to reuse code and modify it for different purposes without affecting other
parts of the codebase.

Overall, the Single Responsibility Principle helps to create code that is more maintainable, flexible,
and scalable.


"every class should have only one reason to change"

*/

// example violating SOLID principles

#include <string>

class Product {};

class Customer1 {
public:
    void buyProduct(Product p) {
        // code to buy product goes here
    }

    void returnProduct(Product p) {
        // code to return product goes here
    }

    void contactCustomerService(std::string message) {
        // code to contact customer service goes here
    }

private:
    std::string name;
    std::string email;
    // other customer-related data members
};

/*******************************************************/

// example following SOLID principles


class ProductPurchase {
public:
    void buyProduct(Product p) {
        // code to buy product goes here
    }

    void returnProduct(Product p) {
        // code to return product goes here
    }

private:
    // other data members related to buying and returning products
};

class CustomerService {
public:
    void contactCustomerService(std::string message) {
        // code to contact customer service goes here
    }

private:
    // other data members related to customer service
};

class Customer {
public:
    Customer(std::string name, std::string email) : name(name), email(email) {}

    void buyProduct(Product p) {
        productPurchase.buyProduct(p);
    }

    void returnProduct(Product p) {
        productPurchase.returnProduct(p);
    }

    void contactCustomerService(std::string message) {
        customerService.contactCustomerService(message);
    }

private:
    std::string name;
    std::string email;
    ProductPurchase productPurchase;
    CustomerService customerService;
};

int main() {
    return 0;
}

