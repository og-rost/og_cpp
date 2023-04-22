#include <iostream>

void f1(int x) {
    x = 30;
}

void f2(int* ptr) {
    *ptr = 30;
}

void f3(int* p, int* q) { 
    p = q; 
    *p = 2; 
} 

int f4(int x, int* py, int** ppz) { 
    int y, z; 
    **ppz += 1; 
    z  = **ppz; 
    *py += 2; 
    y = *py; 
    x += 3; 
    return x + y + z; 
} 

int main() {
    int y = 20;
    f1(y);
    std::cout<<y<<std::endl;
    
    int yy = 20; 
    f2(&yy);
    std::cout<<yy<<std::endl;
    
    const char* ptr = "Rost";
    std::cout<<*&*&*ptr<<std::endl;
    std::cout<<ptr<<std::endl;

	int i = 0, j = 1;
	f3(&i, &j); 
	std::cout<<i<<"  "<<j<<std::endl;
	 
    int c, *b, **a; 
    c = 4; 
    b = &c; 
    a = &b; 
    std::cout<<f4(c, b, a)<<std::endl;
    
    //int aa = 12;
    //void* ptr1 = &aa;    
    //std::cout<<*ptr1<<std::endl;
    
    int arr[] = {1, 2, 3, 4, 5};
    int* p = arr;
    ++*p;
    std::cout<<arr[0]<<std::endl;
    p += 2;
    std::cout<<*p<<std::endl;
    return 0;
}