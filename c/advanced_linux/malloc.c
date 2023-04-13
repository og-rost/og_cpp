#include <stdio.h>
#include <stdlib.h>

int main() {

    for(int i = 1;i<256;++i)
    {
        int* p = (int*) malloc(i*sizeof(int)); 
        p = (char*)p - sizeof(size_t);
        printf("%zu - %zu \t Difference: %zu\n",sizeof(int)*i ,*((size_t*)p),*((size_t*)p)-sizeof(int)*i);
    }
    return 0;
}
