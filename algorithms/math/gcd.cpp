// GCD (Greatest Common Divisor) or HCF (Highest Common Factor) of two numbers is the largest number that divides both of them. 

#include <iostream>

// Time Complexity: O(min(a,b)) 
// Auxiliary Space: O(1)
int gcd(int a, int b) {
    int result = std::min(a, b);
    while (result > 0) {
        if (a % result == 0 && b % result == 0) {
            break;
        }
        --result;
    }

    return result;
}

// Time Complexity: O(min(a,b))
// Auxiliary Space: O(min(a,b))
int gcd_recursive(int a, int b) {
    if (a == 0) {
       return b;
    }
    if (b == 0) {
       return a;
    }   
    // base case
    if (a == b) {
        return a;
    }   
    // a is greater
    if (a > b) {
        return gcd_recursive(a - b, b);
    }
    return gcd_recursive(a, b - a);
}

// Time Complexity: O(log(min(a,b))
// Auxiliary Space: O(log(min(a,b))
int gcd_modulo(int a, int b) {
    if (b == 0) {
        return a;
    }
    return gcd_modulo(b, a % b); 
}
  
int main() {
    int a = 98, b = 56;
    std::cout << "GCD of " << a << " and " << b << " is " << gcd(a, b) << std::endl;
    std::cout << "GCD (recursive) of " << a << " and " << b << " is " << gcd_recursive(a, b) << std::endl;
    std::cout << "GCD (modulo) of " << a << " and " << b << " is " << gcd_modulo(a, b) << std::endl;
    return 0;
}