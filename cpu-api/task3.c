#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) { // Child process
        printf("hello\n");
    } else { // Parent process
        sleep(1); // Sleep to ensure child prints first
        printf("goodbye\n");
    }

    return 0;
}

