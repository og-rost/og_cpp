#include <stdio.h>
#include <stdlib.h>

int main () {
    char* path = getenv ("PATH");
    if (path == NULL)
        path = "/bin;/usr/bin";
    printf ("accessing path %s\n", path);
    return 0;
}
