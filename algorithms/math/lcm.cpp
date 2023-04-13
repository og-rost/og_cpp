// LCM (Least Common Multiple) of two numbers is the smallest number which can be divided by both numbers. 

#include <iostream>

// Time Complexity: O(log(min(a,b))
// Auxiliary Space: O(log(min(a,b))
long long gcd(long long int a, long long int b) {
  if (b == 0) {
    return a;
  }
  return gcd(b, a % b);
}
 
long long lcm(int a, int b) {
    return (a / gcd(a, b)) * b;
}
  
int main() {
    int a = 15, b = 20;
    std::cout << "LCM of " << a << " and " << b << " is " << lcm(a, b) << std::endl;
    return 0;
}