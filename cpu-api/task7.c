#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) { // Child process
        close(STDOUT_FILENO); // Close standard output
        printf("This will not be printed.\n"); // This won't appear
    }

    return 0;
}

