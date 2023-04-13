#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int spawn(char* program) {
    pid_t child_pid;
    child_pid = fork();
    if (child_pid != 0)
        /* This is the parent process. */
        return child_pid;
    else {
        execlp(program, "/home/gorr/Desktop/fork", (char*)NULL);
        fprintf(stderr, "an error occurred in execvp\n");
        abort();
    }
}

int main() {
    spawn("/home/gorr/Desktop/fork");
    printf("done with main program\n");
    return 0;
}
