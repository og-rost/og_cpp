#include <pthread.h>
#include <stdio.h>

struct params {
    char character;
    int count;
};

void* char_print(void* parameters) {
    struct params* p = (struct params*) parameters;
    int i;
    for (i = 0; i < p->count; ++i)
        fputc (p->character, stderr);
    return NULL;
}

int main () {
    pthread_t thread1_id;
    pthread_t thread2_id;
    struct params arg1 = {'x', 30000};
    struct params arg2 = {'o', 20000};

    pthread_create (&thread1_id, NULL, &char_print, &arg1);   
    pthread_create (&thread2_id, NULL, &char_print, &arg2);
    
    pthread_join(thread1_id, NULL);
    pthread_join(thread2_id, NULL);
    
    printf("%s", "\n");
    return 0;
}
