void fun(int a) {}
void add(int a, int b) {}
void sub(int a, int b) {}
void mul(int a, int b) {}

int main() {
    void (*fun_ptr)(int) = &fun; // or void (*fun_ptr)(int) = fun;
    (*fun_ptr)(10);

    void (*fun_ptr_arr[])(int, int) = {add, sub, mul};
    (*fun_ptr_arr[2])(1, 2);
  
    return 0;
}